#ifndef __THREAD_H
#define __THREAD_H

//#include <pthread.h>
#include "log.h"
#include "util.h"
#include "mutex.h"
#include "noncopyable.h"

namespace olivia{

class Thread : Noncopyable{
public:
    typedef std::shared_ptr<Thread> ptr;
    Thread(std::function<void()> cb, const std::string& name);
    ~Thread();
    pid_t getId() const { return m_id;}
    const std::string& getName() const { return m_name;}
    void join();
    static Thread* GetThis();
    static const std::string& GetName();
    static void SetName(const std::string& name);
private:
    // 线程执行函数
    static void* run(void* arg);
private:
    // 线程ID, 在系统中唯一
    pid_t m_id = -1;
    // 线程标识符，在当前进程中唯一
    pthread_t m_thread = 0;
    //线程执行函数
    std::function<void()> m_cb;
    //线程名称
    std::string m_name;
    Semaphore m_semaphore;
};


}


#endif
