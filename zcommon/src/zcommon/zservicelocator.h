#ifndef ZSERVICELOCATOR_H
#define ZSERVICELOCATOR_H


#include <map>

class ZServiceLocator {
public:
    static ZServiceLocator* instance();
public:

    enum class ServiceId : int32_t {
        UserManager,
        KaraokeManager,
        DBProxy,
        MemCacheProxy,
        IDGenerator,
        SessionService,
        Worker,
        AdminManager
    };
public:
    template <typename T>
    T* get(ServiceId serviceId) const;

    void registerService(ServiceId serviceId, void* service);
private:
    ZServiceLocator();
    static ZServiceLocator* _instance;
    std::map<ServiceId, void*> _services;
};

template <typename T>
T* ZServiceLocator::get(ServiceId serviceId) const {
    auto iter = _services.find(serviceId);
    if (iter == _services.end()) {
        return 0;
    }

    return static_cast<T*> (iter->second);
}

#endif // ZSERVICELOCATOR_H
