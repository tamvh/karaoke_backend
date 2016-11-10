#ifndef HTTPSCLIENT_H
#define HTTPSCLIENT_H
#include <string>
#include <memory>
#include <iostream>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>

class HttpsClient
{
public:
    HttpsClient(const std::string& _uri);
public:
    std::string responseData();
private:
    std::string _data;
};

#endif // HTTPSCLIENT_H
