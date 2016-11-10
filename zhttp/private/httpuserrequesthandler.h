#ifndef HTTPUSERREQUESTHANDLER_H
#define HTTPUSERREQUESTHANDLER_H

#include <memory>
#include <map>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/JSON/Object.h>
#include <Poco/Dynamic/Var.h>
#include <include/zcommon/errorcode.h>
#include <src/zhttp/httprequestbasehandler.h>

class HttpClient;
class HttpsClient;
class UserInfo;
class HTTPUserRequestHandler : public HTTPRequestBaseHandler
{
public:
    HTTPUserRequestHandler(const std::string& path, const std::map<std::string, std::string>& params);
    virtual ~HTTPUserRequestHandler();
public:
    static bool CanHandleRequest(const std::string& path, const std::string& method);
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
public:
    Poco::Dynamic::Var handleLogin(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
public:
    void fillJsonUserResponseData(const std::string& id,
                                  const std::string& name,
                                  const std::string& email,
                                  const std::string& gender,
                                  const std::string& birthday,
                                  const std::string& apikey,
                                  Poco::JSON::Object::Ptr& responseData);
private:
    std::string generateAccountClaims(const std::shared_ptr<UserInfo> &user, Poco::JSON::Object::Ptr& responseData) const;
private:
    std::map<std::string, std::string> _params;
    std::string app_id = "";
    std::string secret_key = "";
    HttpClient *httpClient;
    HttpsClient *httpsClient;
};

#endif // HTTPUSERREQUESTHANDLER_H
