#ifndef VIDEOINFO_H
#define VIDEOINFO_H

#include <map>
#include <list>
#include <string>
#include <vector>
#include <memory>
class VideoInfo
{
public:
    typedef std::shared_ptr<VideoInfo> Ptr;
    typedef std::vector<Ptr> List;
    typedef std::map<int32_t, Ptr> Map;
    typedef std::vector<int32_t> KeyList;
public:
    VideoInfo();
    virtual ~VideoInfo();
public:
    void setId(int32_t value);
    int32_t getId();

    void setVideoUrl(const std::string& value);
    std::string getVideoUrl();

    void setCreateAt(int64_t value);
    int64_t getCreateAt();

    void setUpdateAt(int64_t value);
    int64_t getUpdateAt();
public:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

#endif // VIDEOINFO_H
