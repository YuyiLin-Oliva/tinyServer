#include "mutex.h"

namespace olivia{

Semaphore::Semaphore(uint32_t count){
    // int sem_init(sem_t *sem, int pshared, unsigned int value);
	// sem ：指向信号量对象
	// pshared: 指明信号量的类型。不为0时此信号量在进程间共享，否则只能为当前进程的所有线程共享。
	// value : 指定信号量值的大小
	// sem_init() 成功时返回 0；错误时，返回 -1，并把 errno 设置为合适的值。
    if(sem_init(&m_semaphore, 0, count)) {
        throw std::logic_error("sem_init error");
    }
}
Semaphore::~Semaphore(){
    sem_destroy(&m_semaphore);
}
// 获取信号量
void Semaphore::wait(){
    if(sem_wait(&m_semaphore)) {
        throw std::logic_error("sem_wait error");
    }
}
// 释放信号量
void Semaphore::notify(){
    if(sem_post(&m_semaphore)){
        throw std::logic_error("sem_wait error");
    }
}

}