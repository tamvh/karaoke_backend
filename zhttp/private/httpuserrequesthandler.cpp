#include <stdint.h>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <Poco/RegularExpression.h>
#include <Poco/Util/Application.h>
#include <Poco/Dynamic/Struct.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>
#include <Poco/NumberParser.h>
#include <Poco/DateTimeParser.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/LocalDateTime.h>
#include <Poco/Timestamp.h>
#include <src/zcommon/zservicelocator.h>
#include <src/zsession/zsessionservice.h>
#include <src/zworker/zworker.h>
#include <src/usermanager/userinfo.h>
#include <private/httpclient.h>
#include <private/httpsclient.h>
#include "httpuserrequesthandler.h"

using namespace Poco::JSON;
using namespace Poco::Dynamic;
using Poco::DynamicStruct;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Util::Application;
using Poco::DateTimeParser;
using Poco::DateTimeFormat;
using Poco::DateTimeFormatter;
using Poco::LocalDateTime;
using Poco::DateTime;

//void ReportError::reportTo(HttpApiError error, Poco::JSON::Object::Ptr& responseData) {
//    responseData->set("error", static_cast<int> (error));
//}

HTTPUserRequestHandler::HTTPUserRequestHandler(const std::string& path, const std::map<std::string, std::string>& params) :
    HTTPRequestBaseHandler(path),
    _params(params)
{
}

HTTPUserRequestHandler::~HTTPUserRequestHandler()
{
}

bool HTTPUserRequestHandler::CanHandleRequest(const std::string& path, const std::string& method) {
    if (path.compare("/login") == 0) {
        return true;
    }

    return false;
}

void HTTPUserRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    Application& app = Application::instance();
    app.logger().information("Request from " + request.clientAddress().toString());
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    Poco::JSON::Object::Ptr responseData = new Poco::JSON::Object;

    if (requestPath().compare("/login") == 0) {
        handleLogin(request, responseData);
    }

    std::ostream& ostr = response.send();
    Poco::JSON::Stringifier::stringify(responseData, ostr);
}

Poco::Dynamic::Var HTTPUserRequestHandler::handleLogin(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {
    using namespace Poco::JSON;
    using namespace Poco::Dynamic;
    Application& app = Application::instance();
    Parser parser;
    try {
        if(_params.size() <= 0)
        {
            ReportError::reportTo(HttpApiError::ParameterMissing, responseData);
            return responseData;
        }

        std::string access_token = _params["access_token"];
        std::string uri = "https://graph.facebook.com/v2.8/me?access_token=" + access_token+"&fields=birthday,email,gender,name";
        app.logger().information("uri: " + uri);
        httpsClient = new HttpsClient(uri);
        std::string data = httpsClient->responseData();
        Var result = parser.parse(data);
        if (result.type() != typeid (Object::Ptr)) {
            ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
            return responseData;
        }
        UserInfo::Ptr user(new UserInfo);
        Object::Ptr object = result.extract<Object::Ptr>();
        std::string id = object->optValue("id", std::string());
        std::string name = object->optValue("name", std::string());
        std::string gender = object->optValue("gender", std::string());
        std::string email = object->optValue("email", std::string());
        std::string birthday = object->optValue("birthday", std::string());
        std::string avatar = "https://graph.facebook.com/" + id + "/picture?type=large";
        std::string apikey = "";
        if(Poco::trim(id).empty() ||
                Poco::trim(name).empty() ||
                Poco::trim(gender).empty() ||
                Poco::trim(email).empty()){
            ReportError::reportTo(HttpApiError::ParameterMissing, responseData);
            return responseData;
        }

        user->setId(id);
        user->setName(name);
        user->setEmail(email);
        user->setAvatar(avatar);
        user->setGender(gender);
        user->setBirthday(birthday);
        user->setApiKey(apikey);
        user->setCreatedAt(time(NULL));
        user->setUpdatedAt(time(NULL));
        apikey = generateAccountClaims(user, responseData);

        ZWorker* worker = ZServiceLocator::instance()->get<ZWorker>(ZServiceLocator::ServiceId::Worker);
        ZWorkerResult workerResult = worker->getUser(id);
        if (workerResult.failed()) {
            ReportError::reportTo(static_cast<HttpApiError> (workerResult.errorCode()), responseData);
            return responseData;
        }
        user = workerResult.extract<UserInfo::Ptr>();
        if(Poco::trim(user->getId()).empty()) {
            workerResult = worker->createUser(id,
                                                 name,
                                                 email,
                                                 avatar,
                                                 gender,
                                                 apikey,
                                                 birthday);
            if (workerResult.failed()) {
                ReportError::reportTo(static_cast<HttpApiError> (workerResult.errorCode()), responseData);
                return responseData;
            }
            std::string result = Poco::trim(workerResult.extract<std::string>());
            if(!result.empty()) {
                fillJsonUserResponseData(id,
                                         name,
                                         email,
                                         gender,
                                         birthday,
                                         apikey,
                                         responseData);
                return responseData;
            }
            else {
                ReportError::reportTo(HttpApiError::Unknown, responseData);
                return responseData;
            }
        }
        fillJsonUserResponseData(id,
                                 name,
                                 email,
                                 gender,
                                 birthday,
                                 apikey,
                                 responseData);
    } catch (Poco::Exception &ex) {
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return responseData;
    }
    return responseData;
}

void HTTPUserRequestHandler::fillJsonUserResponseData(const std::string& id,
                                                      const std::string& name,
                                                      const std::string& email,
                                                      const std::string& gender,
                                                      const std::string& birthday,
                                                      const std::string& apikey,
                                                      Poco::JSON::Object::Ptr& responseData) {
    Poco::JSON::Object::Ptr user = new Poco::JSON::Object();
    user->set("id", id);
    user->set("name", name);
    user->set("email", email);
    user->set("gender", gender);
    user->set("birthday", birthday);
    user->set("apikey", apikey);
    responseData->set("error", 0);
    responseData->set("msg", user);
}

std::string HTTPUserRequestHandler::generateAccountClaims(const std::shared_ptr<UserInfo> &user, Poco::JSON::Object::Ptr& responseData) const {
    std::string claims = "{\"isActivated\":1}";
    // create user session
    ZSessionService* sessionService = ZServiceLocator::instance()->
            get<ZSessionService>(ZServiceLocator::ServiceId::SessionService);
    std::string jwt;
    ZErrorCode errorCode = sessionService->create_jwt(user->getId(), claims, jwt);
    if (errorCode != ZErrorCode::OK) {
        ReportError::reportTo(static_cast<HttpApiError> (errorCode), responseData);
        return std::string();
    }
    return jwt;
}



