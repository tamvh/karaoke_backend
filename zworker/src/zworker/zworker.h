#ifndef ZWORKER_H
#define ZWORKER_H

#include <string>
#include <Poco/Dynamic/Var.h>
#include <Poco/BasicEvent.h>
#include <include/zcommon/zserviceinterface.h>
#include <include/zcommon/errorcode.h>

class ZWorkerResult {
public:

    ZWorkerResult(ZErrorCode error) : error_(error) {
    }

    ZWorkerResult(Poco::Dynamic::Var obj) : obj_(obj), error_(ZErrorCode::OK) {
    }
public:

    ZErrorCode errorCode() const {
        return error_;
    }

    bool succeeded() const {
        return errorCode() == ZErrorCode::OK;
    }

    bool failed() const {
        return errorCode() != ZErrorCode::OK;
    }

    template <typename T>
    const T& extract() const {
        return obj_.extract<T>();
    }
private:
    Poco::Dynamic::Var obj_;
    ZErrorCode error_;
};

class ZWorker : public ZServiceInterface
{
public:
    ZWorker();
    virtual ~ZWorker();
public:
    virtual bool initialize();
    virtual bool start();
    virtual bool stop();
    virtual bool cleanup();
public:
    ZWorkerResult createUser(const std::string& userId,
                                const std::string& userName,
                                const std::string& email,
                                const std::string& avatar,
                                const std::string& gender,
                                const std::string& apikey,
                                const std::string& birthday);
    ZWorkerResult removeUser(const std::string& userId);
    ZWorkerResult getUser(const std::string& userId);
private:
    ZWorkerResult validateUserAuthentication(const std::string& token);
};

#endif // ZWORKER_H
