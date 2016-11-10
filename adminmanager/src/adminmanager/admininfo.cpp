#include "admininfo.h"

class AdminInfo::Impl {
public:
    int32_t id;
    std::string name;
    std::string password;
    std::string email;
    std::string avatar;
    int8_t gender;
    int64_t birthday;
    std::string apiKey;
    int64_t createdAt;
    int64_t updatedAt;
};

AdminInfo::AdminInfo() : d_ptr(new Impl)
{
}

AdminInfo::~AdminInfo()
{
}

void AdminInfo::setId(const int32_t value) {
    d_ptr->id = value;
}

int32_t AdminInfo::getId() const {
    return d_ptr->id;
}

void AdminInfo::setName(const std::string& value){
    d_ptr->name = value;
}

std::string AdminInfo::getName() const{
    return d_ptr->name;
}

void AdminInfo::setPassword(const std::string& value) {
    d_ptr->password = value;
}

std::string AdminInfo::getPassword() const {
    return d_ptr->password;
}

void AdminInfo::setEmail(const std::string& value) {
    d_ptr->email = value;
}

std::string AdminInfo::getEmail() const {
    return d_ptr->email;
}

void AdminInfo::setAvatar(const std::string& value){
    d_ptr->avatar = value;
}

std::string AdminInfo::getAvatar() const{
    return d_ptr->avatar;
}

void AdminInfo::setGender(const int32_t value){
    d_ptr->gender = value;
}

int32_t AdminInfo::getGender() const{
    return d_ptr->gender;
}
void AdminInfo::setBirthday(const int64_t value){
    d_ptr->birthday = value;
}

int64_t AdminInfo::getBirthday() const{
    return d_ptr->birthday;
}
void AdminInfo::setApiKey(const std::string& value){
    d_ptr->apiKey = value;
}

std::string AdminInfo::getApiKey() const{
    return d_ptr->apiKey;
}
void AdminInfo::setCreatedAt(const int64_t value) {
    d_ptr->createdAt = value;
}

int64_t AdminInfo::getCreatedAt() const {
    return d_ptr->createdAt;
}

void AdminInfo::setUpdatedAt(const int64_t value) {
    d_ptr->updatedAt = value;
}

int64_t AdminInfo::getUpdatedAt() const {
    return d_ptr->updatedAt;
}
