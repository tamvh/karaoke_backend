#include <memory>
#include <sstream>
#include <Poco/Util/Application.h>
#include <Poco/RegularExpression.h>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/Parser.h>

#include <src/zcommon/zservicelocator.h>
#include <src/zcommon/stringutil.h>
#include <src/zcommon/zdbkey.h>

#include <src/zsession/zsessionservice.h>
#include <src/zdb/zdbproxy.h>
#include <src/zdb/zidgenerator.h>

#include <src/usermanager/userinfo.h>
#include <src/usermanager/usermanager.h>
#include "zworker.h"


using namespace Poco::JSON;
using namespace Poco::Dynamic;
using Poco::Util::Application;
using Poco::JSON::Object;
using Poco::JSON::Array;
using Poco::Dynamic::Var;

class ZDBKey;
ZWorker::ZWorker()
{
}

ZWorker::~ZWorker()
{
}

bool ZWorker::initialize() {
    return true;
}

bool ZWorker::start() {
    return true;
}

bool ZWorker::stop() {
    return true;
}

bool ZWorker::cleanup() {
    return true;
}

ZWorkerResult ZWorker::validateUserAuthentication(const std::string& token) {
    ZSessionService* sessionService = ZServiceLocator::instance()->
            get<ZSessionService>(ZServiceLocator::ServiceId::SessionService);
    int64_t userId;
    ZErrorCode errorCode = sessionService->validate_jwt(token, userId);
    if (errorCode != ZErrorCode::OK) {
        return errorCode;
    }

    return ZWorkerResult(Poco::Dynamic::Var(userId));
}

ZWorkerResult ZWorker::createUser(const std::string& userId,
                            const std::string& userName,
                            const std::string& email,
                            const std::string& avatar,
                            const std::string& gender,
                            const std::string& apikey,
                            const std::string& birthday) {
    UserInfo userInfo;
    userInfo.setId(userId);
    userInfo.setName(userName);
    userInfo.setEmail(email);
    userInfo.setAvatar(avatar);
    userInfo.setGender(gender);
    userInfo.setApiKey(apikey);
    userInfo.setBirthday(birthday);
    userInfo.setCreatedAt(time(NULL));
    userInfo.setUpdatedAt(time(NULL));
    UserManager* userManager = ZServiceLocator::instance()->get<UserManager>(ZServiceLocator::ServiceId::UserManager);
    return ZWorkerResult(userManager->setUser(userInfo));
}

ZWorkerResult ZWorker::removeUser(const std::string& userId) {
    UserManager* userManager = ZServiceLocator::instance()->get<UserManager>(ZServiceLocator::ServiceId::UserManager);
    UserInfo::Ptr user = userManager->getUser(userId);
    if (!user) {
        return ZWorkerResult(ZErrorCode::User_NotFound);
    }
    userManager->deleteUser(userId);
    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    dbProxy->DEL(ZDBKey::UserSession(userId));
    return ZWorkerResult(ZErrorCode::OK);
}


ZWorkerResult ZWorker::getUser(const std::string& userId) {
    UserManager* userManager = ZServiceLocator::instance()->get<UserManager>(ZServiceLocator::ServiceId::UserManager);
    UserInfo::Ptr user = userManager->getUser(userId);
    if (!user) {
        return ZWorkerResult(ZErrorCode::User_NotFound);
    }
    return ZWorkerResult(user);
}
