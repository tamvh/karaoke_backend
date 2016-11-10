#include <sstream>
#include <algorithm>
#include <string>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/NumberParser.h>
#include <Poco/Util/Application.h>
#include <src/zcommon/zservicelocator.h>
#include <src/zcommon/zdbkey.h>
#include <src/zdb/zdbproxy.h>
#include <src/zdb/zidgenerator.h>
#include "adminmanager.h"

class ZDBKey;
using Poco::Util::Application;
class AdminManager::Impl {
public:

};

AdminManager::AdminManager(): d_ptr(new Impl)
{
}

AdminManager::~AdminManager()
{
}

bool AdminManager::initialize() {
    return true;
}

bool AdminManager::start() {
    return true;
}

bool AdminManager::stop() {
    return true;
}

bool AdminManager::cleanup() {
    return true;
}

int32_t AdminManager::setAdmin(AdminInfo::Ptr adminInfo) {
    ZIdGenerator* generator = ZServiceLocator::instance()->get<ZIdGenerator>(ZServiceLocator::ServiceId::IDGenerator);
    int32_t adminId = generator->getNext(ZDBKey::generatorAdmins());
    adminInfo->setId(adminId);
    std::string key = ZDBKey::AdminEntry(adminId);
    saveToDB(*adminInfo);
    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    std::string uuid_str = generator->createUuid();
    dbProxy->HSET(key, ZDBKey::AdminApiKey(), uuid_str);
    return adminId;
}

AdminInfo::Ptr AdminManager::getAdmin(int32_t adminId) {
    std::string adminkey = ZDBKey::AdminEntry(adminId);
    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    if (dbProxy->HLEN(adminkey) == 0) {
        AdminInfo::Ptr empty;
        return empty;
    }

    AdminInfo::Ptr admin(new AdminInfo);

    ZDBProxy::StringList vals = dbProxy->HMGET(adminkey, {
        "userId", "userName", "password", "email", "avatar", "gender", "birthday", "createdAt", "updatedAt"
    });

    Poco::Int64 i64Value;
    Poco::Int32 i32Value;

    if (Poco::NumberParser::tryParse64(vals[0], i64Value)) {
        admin->setId(i64Value);
    }
    admin->setName(vals[1]);
    admin->setPassword(vals[2]);
    admin->setEmail(vals[3]);
    admin->setAvatar(vals[4]);

    if (Poco::NumberParser::tryParse(vals[5], i32Value)) {
        admin->setGender(i32Value);
    }

    if (Poco::NumberParser::tryParse64(vals[6], i64Value)) {
        admin->setBirthday(i64Value);
    }

    if (Poco::NumberParser::tryParse64(vals[7], i64Value)) {
        admin->setCreatedAt(i64Value);
    }

    if (Poco::NumberParser::tryParse64(vals[8], i64Value)) {
        admin->setUpdatedAt(i64Value);
    }

    admin->setApiKey(dbProxy->HGET(adminkey, ZDBKey::AdminApiKey()));
    return admin;
}

AdminManager::ErrorCode AdminManager::deleteAdmin(int32_t adminId) {
    AdminInfo::Ptr aminInfo = getAdmin(adminId);
    if (!aminInfo) {
        return ErrorCode::NotFound;
    }

    std::string key = ZDBKey::AdminEntry(adminId);

    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    std::string uuid = dbProxy->HGET(key, ZDBKey::AdminApiKey());
    dbProxy->DEL(key);
    dbProxy->HDEL(ZDBKey::AdminApiKey(), uuid);
    return ErrorCode::OK;
}

void AdminManager::saveToDB(AdminInfo& adminInfo) {
    std::string key = ZDBKey::AdminEntry(adminInfo.getId());
    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    dbProxy->HMSET(key,{
        { "userId", std::to_string(adminInfo.getId())},
        { "userName", adminInfo.getName()},
        { "password", adminInfo.getPassword()},
        { "email", adminInfo.getEmail()},
        { "avatar", adminInfo.getAvatar()},
        { "gender", std::to_string(adminInfo.getGender())},
        { "apikey", adminInfo.getApiKey()},
        { "birthday", std::to_string(adminInfo.getBirthday())},
        { "createdAt", std::to_string(adminInfo.getCreatedAt())},
        { "updatedAt", std::to_string(adminInfo.getUpdatedAt())},
    });
}
