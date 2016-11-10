#ifndef KARAOKEMANAGER_H
#define KARAOKEMANAGER_H

#include <memory>
#include <include/zcommon/zserviceinterface.h>
#include <src/karaokemanager/videoinfo.h>
class KaraokeManager : public ZServiceInterface
{
public:
    KaraokeManager();
    virtual ~KaraokeManager();
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
    virtual int32_t setVideo(VideoInfo::Ptr videoInfo);
    virtual VideoInfo::Ptr getVideo(int32_t videoId);
    virtual KaraokeManager::ErrorCode deleteVideo(int32_t videoId);
private:
    void saveToDB(VideoInfo& videoInfo);
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

#endif // KARAOKEMANAGER_H
