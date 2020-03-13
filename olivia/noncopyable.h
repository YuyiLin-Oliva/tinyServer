#ifndef __NONCOPYABLE_H
#define __NONCOPYABLE_H

namespace olivia{

// 对象无法拷贝,赋值
class Noncopyable{
public:
    Noncopyable() = default;
    ~Noncopyable() = default;
    Noncopyable& operator=(const Noncopyable&) = delete;
    Noncopyable(const Noncopyable&) = delete;
};

}


#endif