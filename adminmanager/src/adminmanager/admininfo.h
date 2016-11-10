#ifndef ADMININFO_H
#define ADMININFO_H

#include <map>
#include <list>
#include <string>
#include <vector>
#include <memory>
class AdminInfo
{
public:
    typedef std::shared_ptr<AdminInfo> Ptr;
    typedef std::vector<Ptr> List;
    typedef std::map<int32_t, Ptr> Map;
    typedef std::vector<int32_t> KeyList;
public:
    AdminInfo();
    virtual ~AdminInfo();

    void setId(const int32_t value);
    int32_t getId() const;

    void setName(const std::string& value);
    std::string getName() const;

    void setPassword(const std::string& value);
    std::string getPassword() const;

    void setEmail(const std::string& value);
    std::string getEmail() const;

    void setAvatar(const std::string& value);
    std::string getAvatar() const;

    void setGender(const int32_t value);
    int32_t getGender() const;

    void setBirthday(const int64_t value);
    int64_t getBirthday() const;

    void setApiKey(const std::string& value);
    std::string getApiKey() const;

    void setCreatedAt(const int64_t value);
    int64_t getCreatedAt() const;

    void setUpdatedAt(const int64_t value);
    int64_t getUpdatedAt() const;
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

#endif // ADMININFO_H
