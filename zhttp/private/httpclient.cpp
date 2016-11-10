#include "httpclient.h"

using namespace Poco::Net;
using namespace Poco;
HttpClient::HttpClient(const std::string& _uri)
{
    // prepare session
    URI uri(_uri);
    HTTPClientSession session(uri.getHost(), uri.getPort());
    // prepare path
    std::string path(uri.getPathAndQuery());
    if (path.empty())
        path = "/";
    // send request
    HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
    session.sendRequest(req);

    // get response
    HTTPResponse res;
    // print response
    std::istream &is = session.receiveResponse(res);
    std::string out_str = std::string(std::istreambuf_iterator<char>(is), {});
    _data = out_str;
}

std::string HttpClient::responseData() {
    return _data;
}
