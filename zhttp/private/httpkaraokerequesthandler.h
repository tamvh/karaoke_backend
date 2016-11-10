#ifndef HTTPKARAOKEREQUESTHANDLER_H
#define HTTPKARAOKEREQUESTHANDLER_H

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
class HTTPKaraokeRequestHandler : public HTTPRequestBaseHandler
{
public:
    HTTPKaraokeRequestHandler(const std::string& path, const std::map<std::string, std::string>& params);
    virtual ~HTTPKaraokeRequestHandler();
public:
    static bool CanHandleRequest(const std::string& path, const std::string& method);
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);
private:
    Poco::Dynamic::Var handleSearchSong(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    Poco::Dynamic::Var handleGetLysic(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    Poco::Dynamic::Var handleGetLysicById(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    Poco::Dynamic::Var handleGetListSong(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    Poco::Dynamic::Var handleGetMp3ById(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    Poco::Dynamic::Var handleGetMp3Karaoke(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    Poco::Dynamic::Var handleGetListHotKaraoke(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    Poco::Dynamic::Var handleGetListKaraokeFollowUser(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    Poco::Dynamic::Var handleGetListKaraoke(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
    Poco::Dynamic::Var handleDetailsKaraoke(Poco::Net::HTTPServerRequest& request, Poco::JSON::Object::Ptr& responseData);
public:
    void fillJsonResponseData(const std::string& msg, Poco::JSON::Object::Ptr& responseData);
    void fillJsonResponseMyKaraoke(const std::string& msg, Poco::JSON::Object::Ptr& responseData);
private:
    std::map<std::string, std::string> _params;
    HttpClient* _httpClient;
};

#endif // HTTPKARAOKEREQUESTHANDLER_H
