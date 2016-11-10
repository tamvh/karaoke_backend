#include "videoinfo.h"

class VideoInfo::Impl {
public:
    int32_t id;
    std::string videoUrl;
    int64_t createAt;
    int64_t updateAt;
};

VideoInfo::VideoInfo() : d_ptr(new Impl)
{
}

VideoInfo::~VideoInfo()
{
}

void VideoInfo::setId(int32_t value) {
    d_ptr->id = value;
}

int32_t VideoInfo::getId(){
    return d_ptr->id;
}

void VideoInfo::setVideoUrl(const std::string& value) {
    d_ptr->videoUrl = value;
}

std::string VideoInfo::getVideoUrl() {
    return d_ptr->videoUrl;
}

void VideoInfo::setCreateAt(int64_t value) {
    d_ptr->createAt = value;
}

int64_t VideoInfo::getCreateAt() {
    return d_ptr->createAt;
}

void VideoInfo::setUpdateAt(int64_t value) {
    d_ptr->updateAt = value;
}

int64_t VideoInfo::getUpdateAt() {
    return d_ptr->updateAt;
}
