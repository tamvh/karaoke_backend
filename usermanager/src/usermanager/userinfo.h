#ifndef USERINFO_H
#define USERINFO_H

#include <map>
#include <list>
#include <string>
#include <vector>
#include <memory>

class UserInfo
{
public:
    typedef std::shared_ptr<UserInfo> Ptr;
    typedef std::vector<Ptr> List;
    typedef std::map<std::string, Ptr> Map;
    typedef std::vector<std::string> KeyList;
public:
    UserInfo();
public:
    void setId(const std::string& value);
    std::string getId() const;

    void setName(const std::string& value);
    std::string getName() const;    

    void setEmail(const std::string& value);
    std::string getEmail() const;

    void setAvatar(const std::string& value);
    std::string getAvatar() const;

    void setGender(const std::string& value);
    std::string getGender() const;

    void setBirthday(const std::string& value);
    std::string getBirthday() const;

    void setApiKey(const std::string& value);
    std::string getApiKey() const;

    void setCreatedAt(const int64_t value);
    int64_t getCreatedAt() const;

    void setUpdatedAt(const int64_t value);
    int64_t getUpdatedAt() const;
private:
    std::string _id;
    std::string _name;
    std::string _email;
    std::string _avatar;
    std::string _gender;
    std::string _birthday;
    std::string _apiKey;
    int64_t _createdAt;
    int64_t _updatedAt;
};

#endif // USERINFO_H
