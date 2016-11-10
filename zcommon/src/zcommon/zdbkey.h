#ifndef ZDBKEY_H
#define ZDBKEY_H

#include <string>
#include <sstream>

class ZDBKey {
public:
    //KEY generator
    static std::string generatorUsers() {
        return "users";
    }

    static std::string generatorGroups() {
        return "groups";
    }

    static std::string generatorAdmins() {
        return "admins";
    }

    static std::string apiKey() {
        return "users:lookup:apikey";
    }

    static std::string AdminApiKey() {
        return "admins:lookup:apikey";
    }

    static std::string generatorVideos() {
        return "videos";
    }

    static std::string VideoSet() {
        return "videos:set";
    }

    static std::string Videos2Apikey() {
        return "videos:lookup:apikey";
    }

    static std::string GroupSet() {
        return "groups:set";
    }

    static std::string UserSet() {
        return "users:set";
    }

    static std::string GroupApiKey() {
        return "groups:lookup:apikey";
    }

    static std::string UserApiKey() {
        return "users:lookup:apikey";
    }

    static std::string UserEmail() {
        return "users:lookup:email";
    }

    static std::string GroupEntry(int32_t adminId) {
        std::stringstream stream;
        stream << "groups:" << adminId;
        return stream.str();
    }

    static std::string AdminEntry(int32_t adminId) {
        std::stringstream stream;
        stream << "admins:" << adminId;
        return stream.str();
    }

    static std::string UserEntry(std::string userId) {
        std::stringstream stream;
        stream << "users:" << userId;
        return stream.str();
    }

    static std::string VideoEntry(int32_t videoId) {
        std::stringstream stream;
        stream << "videos:" << videoId;
        return stream.str();
    }

    static std::string UserSession(std::string userId) {
        std::stringstream stream;
        stream << "users:" << userId << ":sessions";
        return stream.str();
    }
};

#endif // ZDBKEY_H
