#include "thread.h"
#include "util.h"

namespace olivia{
static thread_local Thread* t_thread = nullptr;
static thread_local std::string t_thread_name = "UNKNOW";
static Logger::ptr g_logger = LOG_NAME("system");

Thread::Thread(std::function<void()> cb, const std::string& name)
    :m_cb(cb)
    ,m_name(name){
    if(name.empty()){
        m_name = "UNKNOW";
    }
    // int pthread_create(pthread_t *tidp,const pthread_attr_t *attr,
	// (void*)(*start_rtn)(void*), void *arg);
	//第一个参数为指向线程标识符的指针。
	//第二个参数用来设置线程属性。
	//第三个参数是线程运行函数的起始地址。
	//最后一个参数是运行函数的参数。
    int rt = pthread_create(&m_thread, nullptr, &Thread::run, this);
    if(rt) {
        LOG_ERROR(g_logger) << "pthread_create thread fail, rt=" << rt
            << " name=" << name;
        throw std::logic_error("pthread_create error");
    }

	// 等待线程运行起来再返回,即等待run函数发出通知
    m_semaphore.wait();
}

Thread::~Thread(){
    if(m_thread){
        pthread_detach(m_thread);
    }
}

void Thread::join(){
    if(m_thread) {
        int rt = pthread_join(m_thread, nullptr);
        if(rt) {
            LOG_ERROR(g_logger) << "pthread_join thread fail, rt=" << rt
                << " name=" << m_name;
            throw std::logic_error("pthread_join error");
        }
        m_thread = 0;
    }
}

Thread* Thread::GetThis(){
    return t_thread;
}

const std::string& Thread::GetName(){
    return t_thread_name;
}

void Thread::SetName(const std::string& name){
    if(name.empty()){
        return;
    }
    if(t_thread){
        t_thread->m_name = name;
    }
    t_thread_name = name;
}

void* Thread::run(void* arg){
    Thread* thread = (Thread*)arg;
    t_thread = thread;
    t_thread_name = thread->m_name;
    thread->m_id = GetThreadId();
    pthread_setname_np(pthread_self(), thread->m_name.substr(0, 15).c_str());
    
    std::function<void()> cb;
    cb.swap(thread->m_cb);
    // 线程初始化结束后就发出通知
    thread->m_semaphore.notify();
    cb();
    return 0;
}

}
