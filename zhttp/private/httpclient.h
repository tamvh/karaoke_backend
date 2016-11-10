#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>
#include <memory>
#include <iostream>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>

class HttpClient
{
public:
    HttpClient(const std::string& _uri);
public:
    std::string responseData();
private:
    std::string _data;
};

#endif // HTTPCLIENT_H
