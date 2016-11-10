#include <stdint.h>
#include <sstream>
#include <Poco/RegularExpression.h>
#include <Poco/Util/Application.h>
#include <Poco/Dynamic/Struct.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Parser.h>
#include <Poco/NumberParser.h>
#include <src/zcommon/zservicelocator.h>
#include <src/zsession/zsessionservice.h>
#include <private/httpclient.h>
#include "httpkaraokerequesthandler.h"

using namespace Poco::JSON;
using namespace Poco::Dynamic;
using Poco::DynamicStruct;
using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Util::Application;

void ReportError::reportTo(HttpApiError error, Poco::JSON::Object::Ptr& responseData) {
    responseData->set("error", static_cast<int> (error));
}

HTTPKaraokeRequestHandler::HTTPKaraokeRequestHandler(const std::string& path, const std::map<std::string, std::string>& params) :
    HTTPRequestBaseHandler(path),
    _params(params) {    
}

HTTPKaraokeRequestHandler::~HTTPKaraokeRequestHandler() {

}

bool HTTPKaraokeRequestHandler::CanHandleRequest(const std::string& path, const std::string& method) {
    if (path.compare("/search") == 0) {
        return true;
    }

    if (path.compare("/lyric") == 0) {
        return true;
    }

    if (path.compare("/lyric_by_id") == 0) {
        return true;
    }

    if (path.compare("/list_song") == 0) {
        return true;
    }

    if (path.compare("/mp3_by_id") == 0) {
        return true;
    }

    if (path.compare("/mp3_karaoke") == 0) {
        return true;
    }

    if (path.compare("/list_host_karaoke") == 0) {
        return true;
    }

    if (path.compare("/mykaraoke") == 0) {
        return true;
    }

    if (path.compare("/listkaraoke") == 0) {
        return true;
    }

    if (path.compare("/detailskaraoke") == 0) {
        return true;
    }
    return false;
}

void HTTPKaraokeRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    Application& app = Application::instance();
    app.logger().information("Request from " + request.clientAddress().toString());
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    Poco::JSON::Object::Ptr responseData = new Poco::JSON::Object;

    if (requestPath().compare("/search") == 0) {
        handleSearchSong(request, responseData);
    }

    if (requestPath().compare("/lyric") == 0) {
        handleGetLysic(request, responseData);
    }

    if (requestPath().compare("/lyric_by_id") == 0) {
        handleGetLysicById(request, responseData);
    }

    if (requestPath().compare("/list_song") == 0) {
        handleGetListSong(request, responseData);
    }

    if (requestPath().compare("/mp3_by_id") == 0) {
        handleGetMp3ById(request, responseData);
    }

    if (requestPath().compare("/mp3_karaoke") == 0) {
        handleGetMp3Karaoke(request, responseData);
    }

    if (requestPath().compare("/list_host_karaoke") == 0) {
        handleGetListHotKaraoke(request, responseData);
    }

    if (requestPath().compare("/mykaraoke") == 0) {
        handleGetListKaraokeFollowUser(request, responseData);
    }

    if (requestPath().compare("/listkaraoke") == 0) {
        handleGetListKaraoke(request, responseData);
    }

    if (requestPath().compare("/detailskaraoke") == 0) {
        handleDetailsKaraoke(request, responseData);
    }

    std::ostream& ostr = response.send();
    Poco::JSON::Stringifier::stringify(responseData, ostr);
}

Poco::Dynamic::Var HTTPKaraokeRequestHandler::handleSearchSong(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {
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
        std::string song = _params["song"];
        _httpClient = new HttpClient("http://ac.mp3.zing.vn/complete?type=artist,album,video,song&num=4&callback=jQuery210007569393399171531_1452762760980&query=" + song);
        std::string data = _httpClient->responseData();
        Var result = parser.parse(data);
        if (result.type() != typeid (Object::Ptr)) {
            ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
            return responseData;
        }
        Object::Ptr object = result.extract<Object::Ptr>();
        std::string msg = object->optValue("data", std::string());
        fillJsonResponseData(msg, responseData);
    } catch (Poco::Exception &ex) {
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return responseData;
    }
    return responseData;
}

Poco::Dynamic::Var HTTPKaraokeRequestHandler::handleGetLysic(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {

    return responseData;
}

Poco::Dynamic::Var HTTPKaraokeRequestHandler::handleGetLysicById(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {
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
        std::string songid = _params["id"];
        _httpClient = new HttpClient("http://mp3.zing.vn/xhr/song/get-lyrics?songid=" + songid);
        std::string data = _httpClient->responseData();
        Var result = parser.parse(data);
        if (result.type() != typeid (Object::Ptr)) {
            ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
            return responseData;
        }
        Object::Ptr object = result.extract<Object::Ptr>();
        std::string msg = object->optValue("data", std::string());


        fillJsonResponseData(data, responseData);
    } catch (Poco::Exception &ex) {
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return responseData;
    }
    return responseData;
}

Poco::Dynamic::Var HTTPKaraokeRequestHandler::handleGetListSong(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {
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
        std::string songid = _params["id"];
        _httpClient = new HttpClient("http://mp3.zing.vn/xhr/song/get-lyrics?songid=" + songid);
        std::string data = _httpClient->responseData();
        Var result = parser.parse(data);
        if (result.type() != typeid (Object::Ptr)) {
            ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
            return responseData;
        }
        Object::Ptr object = result.extract<Object::Ptr>();
        std::string msg = object->optValue("data", std::string());


        fillJsonResponseData(data, responseData);
    } catch (Poco::Exception &ex) {
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return responseData;
    }
    return responseData;
}

Poco::Dynamic::Var HTTPKaraokeRequestHandler::handleGetMp3ById(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {
    return responseData;
}

Poco::Dynamic::Var HTTPKaraokeRequestHandler::handleGetMp3Karaoke(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {
    return responseData;
}


Poco::Dynamic::Var HTTPKaraokeRequestHandler::handleGetListHotKaraoke(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {
    using namespace Poco::JSON;
    using namespace Poco::Dynamic;
    Application& app = Application::instance();
    Parser parser;
    try {
        std::string data = "";
//        Var result = parser.parse(data);
//        if (result.type() != typeid (Object::Ptr)) {
//            ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
//            return responseData;
//        }
//        Object::Ptr object = result.extract<Object::Ptr>();
//        std::string msg = object->optValue("data", std::string());
        fillJsonResponseData(data, responseData);
    } catch (Poco::Exception &ex) {
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return responseData;
    }
    return responseData;
}

Poco::Dynamic::Var HTTPKaraokeRequestHandler::handleGetListKaraokeFollowUser(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {
    using namespace Poco::JSON;
    using namespace Poco::Dynamic;
    Application& app = Application::instance();
    Parser parser;
    try {

//        if(_params.size() <= 0)
//        {
//            ReportError::reportTo(HttpApiError::ParameterMissing, responseData);
//            return responseData;
//        }
//        std::string userid = _params["userid"];
//        _httpClient = new HttpClient("http://mp3.zing.vn/xhr/song/get-lyrics?songid=" + songid);
//        std::string data = _httpClient->responseData();
//        Var result = parser.parse(data);
//        if (result.type() != typeid (Object::Ptr)) {
//            ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
//            return responseData;
//        }
//        Object::Ptr object = result.extract<Object::Ptr>();
//        std::string msg = object->optValue("data", std::string());

//        fillJsonResponseData(data, responseData);
    } catch (Poco::Exception &ex) {
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return responseData;
    }
    return responseData;
}

Poco::Dynamic::Var HTTPKaraokeRequestHandler::handleGetListKaraoke(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {
    using namespace Poco::JSON;
    using namespace Poco::Dynamic;
    Application& app = Application::instance();
    Parser parser;
    try {
        std::string data = "";
//        Var result = parser.parse(data);
//        if (result.type() != typeid (Object::Ptr)) {
//            ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
//            return responseData;
//        }
//        Object::Ptr object = result.extract<Object::Ptr>();
//        std::string msg = object->optValue("data", std::string());
        fillJsonResponseData(data, responseData);
    } catch (Poco::Exception &ex) {
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return responseData;
    }
    return responseData;
}

Poco::Dynamic::Var HTTPKaraokeRequestHandler::handleDetailsKaraoke(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData) {
    using namespace Poco::JSON;
    using namespace Poco::Dynamic;
    Application& app = Application::instance();
    Parser parser;
    try {
        std::string data = "";
//        Var result = parser.parse(data);
//        if (result.type() != typeid (Object::Ptr)) {
//            ReportError::reportTo(HttpApiError::InvalidRequest, responseData);
//            return responseData;
//        }
//        Object::Ptr object = result.extract<Object::Ptr>();
//        std::string msg = object->optValue("data", std::string());
        fillJsonResponseData(data, responseData);
    } catch (Poco::Exception &ex) {
        app.logger().error("Exception while processing message: %s", ex.displayText());
        ReportError::reportTo(HttpApiError::Unknown, responseData);
        return responseData;
    }
    return responseData;
}

void HTTPKaraokeRequestHandler::fillJsonResponseData(const std::string& msg, Poco::JSON::Object::Ptr& responseData) {
    responseData->set("error", 0);
    responseData->set("msg", msg);
}

void HTTPKaraokeRequestHandler::fillJsonResponseMyKaraoke(const std::string& msg, Poco::JSON::Object::Ptr& responseData) {
    responseData->set("error", 0);
    responseData->set("msg", msg);
}







