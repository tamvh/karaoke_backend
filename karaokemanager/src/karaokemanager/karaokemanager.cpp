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
#include "karaokemanager.h"

class ZDBKey;
using Poco::Util::Application;
class KaraokeManager::Impl {
public:

};

KaraokeManager::KaraokeManager() : d_ptr(new Impl)
{
}

KaraokeManager::~KaraokeManager()
{
}

bool KaraokeManager::initialize() {
    return true;
}

bool KaraokeManager::start() {
    return true;
}

bool KaraokeManager::stop() {
    return true;
}

bool KaraokeManager::cleanup() {
    return true;
}

int32_t KaraokeManager::setVideo(VideoInfo::Ptr videoInfo) {
    ZIdGenerator* generator = ZServiceLocator::instance()->get<ZIdGenerator>(ZServiceLocator::ServiceId::IDGenerator);
    int32_t videoId = generator->getNext(ZDBKey::generatorVideos());
    videoInfo->setId(videoId);
    std::string key = ZDBKey::VideoEntry(videoId);
    saveToDB(*videoInfo);
    return videoId;
}

VideoInfo::Ptr KaraokeManager::getVideo(int32_t videoId) {
    std::string videokey = ZDBKey::VideoEntry(videoId);
    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    if (dbProxy->HLEN(videokey) == 0) {
        VideoInfo::Ptr empty;
        return empty;
    }
    VideoInfo::Ptr video(new VideoInfo);
    ZDBProxy::StringList vals = dbProxy->HMGET(videokey, {
        "videoId", "videoUrl", "createdAt", "updatedAt"
    });
    Poco::Int64 i64Value;
    Poco::Int32 i32Value;
    if (Poco::NumberParser::tryParse(vals[0], i32Value)) {
        video->setId(i32Value);
    }
    video->setVideoUrl(vals[0]);
    if (Poco::NumberParser::tryParse64(vals[2], i64Value)) {
        video->setCreateAt(i64Value);
    }
    if (Poco::NumberParser::tryParse64(vals[3], i64Value)) {
        video->setUpdateAt(i64Value);
    }
    return video;
}

KaraokeManager::ErrorCode KaraokeManager::deleteVideo(int32_t videoId) {
    VideoInfo::Ptr videoInfo = getVideo(videoId);
    if (!videoInfo) {
        return ErrorCode::NotFound;
    }
    std::string key = ZDBKey::VideoEntry(videoId);
    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    dbProxy->DEL(key);
    return ErrorCode::OK;
}

void KaraokeManager::saveToDB(VideoInfo& videoInfo) {
    std::string key = ZDBKey::VideoEntry(videoInfo.getId());
    ZDBProxy* dbProxy = ZServiceLocator::instance()->get<ZDBProxy>(ZServiceLocator::ServiceId::DBProxy);
    dbProxy->HMSET(key,{
        { "videoId", std::to_string(videoInfo.getId())},
        { "videoUrl", videoInfo.getVideoUrl()},
        { "createdAt", std::to_string(videoInfo.getCreateAt())},
        { "updatedAt", std::to_string(videoInfo.getUpdateAt())},
    });
}
