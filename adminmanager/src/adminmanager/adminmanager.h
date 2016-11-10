#ifndef ADMINMANAGER_H
#define ADMINMANAGER_H

#include <memory>
#include <include/zcommon/zserviceinterface.h>
#include <src/adminmanager/admininfo.h>
class AdminManager : public ZServiceInterface
{
public:
    AdminManager();
    virtual ~AdminManager();
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
    virtual int32_t setAdmin(AdminInfo::Ptr adminInfo);
    virtual AdminInfo::Ptr getAdmin(int32_t adminId);
    virtual AdminManager::ErrorCode deleteAdmin(int32_t adminId);
private:
    void saveToDB(AdminInfo& adminInfo);
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

#endif // ADMINMANAGER_H
