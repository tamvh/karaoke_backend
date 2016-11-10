#include <sstream>
#include <algorithm>
#include <string>
#include <Poco/UUID.h>
#include <Poco/UUIDGenerator.h>
#include <Poco/NumberParser.h>
#include <src/zcommon/zservicelocator.h>
#include <src/zcommon/zdbkey.h>
#include <src/zdb/zdbproxy.h>
#include <src/zdb/zidgenerator.h>
#include "usermanager.h"

class ZDBKey;
class UserManager::Impl {
public:

};

UserManager::UserManager(): d_ptr(new Impl)
{
}

UserManager::~UserManager()
{
}

bool UserManager::initialize() {
    return true;
}

bool UserManager::start() {
    return true;
}

bool UserManager::stop() {
    return true;
}

bool UserManager::cleanup() {
    return true;
}

std::string UserManager::setUser(UserInfo userInfo) {
    ZIdGenerator* generator = ZServiceLocator::instance()->get<ZIdGenerator>(ZServiceLocator::ServiceId::IDGenerator);
    std::string userId = userInfo.getId();
    std::string key = ZDBKey::UserEntry(userId);

    saveToDB(userInfo);
    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);

    // create apikey for new user
    std::string uuid_str = generator->createUuid();
    dbProxy->HSET(key, ZDBKey::apiKey(), uuid_str);
    dbProxy->HSET(ZDBKey::UserApiKey(), uuid_str, key);
    dbProxy->HSET(ZDBKey::UserEmail(), userInfo.getEmail(), userId);
    dbProxy->SADD(ZDBKey::UserSet(),{key});
    return userId;
}

UserInfo::Ptr UserManager::getUser(std::string userId) {
    std::string userkey = ZDBKey::UserEntry(userId);
    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    if (dbProxy->HLEN(userkey) == 0) {
        UserInfo::Ptr empty;
        return empty;
    }

    UserInfo::Ptr user(new UserInfo);

    ZDBProxy::StringList vals = dbProxy->HMGET(userkey, {
        "userId", "userName", "email", "avatar", "gender", "birthday", "createdAt", "updatedAt"
    });

    Poco::Int64 i64Value;
    Poco::Int32 i32Value;

    user->setId(vals[0]);
    user->setName(vals[1]);
    user->setEmail(vals[2]);
    user->setAvatar(vals[3]);
    user->setGender(vals[4]);
    user->setBirthday(vals[5]);

    if (Poco::NumberParser::tryParse64(vals[6], i64Value)) {
        user->setCreatedAt(i64Value);
    }

    if (Poco::NumberParser::tryParse64(vals[7], i64Value)) {
        user->setUpdatedAt(i64Value);
    }

    user->setApiKey(dbProxy->HGET(userkey, ZDBKey::apiKey()));
    return user;
}

UserManager::ErrorCode UserManager::deleteUser(std::string userId) {
    UserInfo::Ptr userInfo = getUser(userId);
    if (!userInfo) {
        return ErrorCode::NotFound;
    }

    std::string key = ZDBKey::UserEntry(userId);

    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    std::string uuid = dbProxy->HGET(key, ZDBKey::apiKey());
    dbProxy->DEL(key);
    dbProxy->SREM(ZDBKey::UserSet(),{key});
    dbProxy->HDEL(ZDBKey::UserApiKey(), uuid);
    dbProxy->HDEL(ZDBKey::UserEmail(), userId);

    return ErrorCode::OK;
}

UserManager::ErrorCode UserManager::updateUser(UserInfo userInfo) {
    userInfo.setUpdatedAt(time(NULL));
    saveToDB(userInfo);
    return ErrorCode::OK;
}

void UserManager::saveToDB(UserInfo& userInfo) {
    std::string key = ZDBKey::UserEntry(userInfo.getId());
    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    dbProxy->HMSET(key,{
        { "userId", userInfo.getId()},
        { "userName", userInfo.getName()},
        { "email", userInfo.getEmail()},
        { "avatar", userInfo.getAvatar()},
        { "gender", userInfo.getGender()},
        { "apikey", userInfo.getApiKey()},
        { "birthday", userInfo.getBirthday()},
        { "createdAt", std::to_string(userInfo.getCreatedAt())},
        { "updatedAt", std::to_string(userInfo.getUpdatedAt())},
    });
}

