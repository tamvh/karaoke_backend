#include "userinfo.h"

UserInfo::UserInfo()
{
}

void UserInfo::setId(const std::string& value) {
    _id = value;
}

std::string UserInfo::getId() const {
    return _id;
}

void UserInfo::setName(const std::string& value){
    _name = value;
}

std::string UserInfo::getName() const{
    return _name;
}

void UserInfo::setEmail(const std::string& value) {
    _email = value;
}

std::string UserInfo::getEmail() const {
    return _email;
}

void UserInfo::setAvatar(const std::string& value){
    _avatar = value;
}

std::string UserInfo::getAvatar() const{
    return _avatar;
}

void UserInfo::setGender(const std::string& value){
    _gender = value;
}

std::string UserInfo::getGender() const{
    return _gender;
}
void UserInfo::setBirthday(const std::string& value){
    _birthday = value;
}

std::string UserInfo::getBirthday() const{
    return _birthday;
}
void UserInfo::setApiKey(const std::string& value){
    _apiKey = value;
}

std::string UserInfo::getApiKey() const{
    return _apiKey;
}
void UserInfo::setCreatedAt(const int64_t value) {
    _createdAt = value;
}

int64_t UserInfo::getCreatedAt() const {
    return _createdAt;
}

void UserInfo::setUpdatedAt(const int64_t value) {
    _updatedAt = value;
}

int64_t UserInfo::getUpdatedAt() const {
    return _updatedAt;
}
