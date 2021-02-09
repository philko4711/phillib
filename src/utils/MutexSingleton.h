#ifndef MUTEX_SINGLETON_H_
#define MUTEX_SINGLETON_H_

#include <mutex>
#include <memory>

class MutexSingleton
{
  
  public:
    static MutexSingleton& getInstance(void);//{return **_instance;}
    void lock(void){_mutex.lock();}
    void unlock(void){_mutex.unlock();}
    bool tryLock(void){return _mutex.try_lock();}
    virtual ~MutexSingleton(void){}
    private:
    MutexSingleton(void){}
    static std::unique_ptr<MutexSingleton> _instance;
    std::mutex _mutex;
};

#endif