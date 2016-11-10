#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <memory>
#include <include/zcommon/zserviceinterface.h>
#include <src/usermanager/userinfo.h>

class UserManager : public ZServiceInterface
{
public:
    UserManager();
    virtual ~UserManager();
public:
    virtual bool initialize();
    virtual bool start();
    virtual bool stop();
    virtual bool cleanup();
public:
    enum class ErrorCode : int32_t {
        OK = 0,
        NotFound,
        InvalidInput
    };
public:
    virtual std::string setUser(UserInfo userInfo);
    virtual UserInfo::Ptr getUser(std::string userId);
    virtual UserManager::ErrorCode deleteUser(std::string userId);
    virtual UserManager::ErrorCode updateUser(UserInfo userInfo);
private:
    void saveToDB(UserInfo& userInfo);
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

#endif // USERMANAGER_H
