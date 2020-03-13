## A C++ High Performance Http Server
### Introduction
本项目为C++11编写的Http服务器，使用epoll+非阻塞异步IO+多线程多协程实现并发模型，支持Http长连接和连接池，支持二进制数据的序列化和反序列化，并实现了自定义格式的日志模块，支持yaml文件及变更通知的配置模块，记录服务器的运行状态和基本配置。

|Part1 | Part2 | Part3 | Part4 |
|:-----------: | :-----------: | :-----------: | :------------: |
|[项目介绍]() |[模块介绍]() | [项目难点]() |[性能测试]() |

### Environment
```
- Ubuntu 18.03
- g++ 4.7
- yaml-cpp
- boost
- ragel
```
### Build
```c++
cd build
cmake ..
make -j8
```
### Usage
```c++
cd bin
./test_http_server 
```

### Technical points
- 使用非阻塞IO，Epoll边沿触发的IO多路复用技术；
- 使用基于ucontext的协程调度器，处理IO事件和定时器事件，方便切换控制流，轻量化；
- 采用非对称式协程方式实现协程调度，每个线程的主协程负责协程调度，子协程执行结束将控制权交还主协程；
- 配置Hook模块将阻塞的系统I/O调用改为异步的调用，将socke io相关的同步接口异步化；
- 使用多线程充分利用多核CPU, 使协程调度器具备并行性，并使用线程池避免线程频繁创建销毁的开销; 
- accept_worker协程调度器负责服务器socket接收连接，io_worker协程调度器负责处理新连接的socket工作；
- 支持二进制数据的序列化和反序列化；
- 实现支持自定义日志格式的日志系统，支持yaml文件及变更通知的配置模块；
- 为减少内存泄漏的可能，使用智能指针等RAII机制；
- 采用ragel有限状态机实现HTTP/1.1的简单协议实现和uri的解析；
- 支持静态资源访问和uri注册，支持Http长连接和连接池，减少频繁创建和销毁连接的开销。

### Code Amount

![代码统计](https://github.com/YuyiLin-Oliva/tinyServer/test_results/代码行数统计.png)



