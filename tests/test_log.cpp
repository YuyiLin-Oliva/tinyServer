#include <iostream>
#include "olivia/log.h"
// #include "olivia/util.h"

int main(int argc, char** argv) {
    olivia::Logger::ptr logger(new  olivia::Logger);
    logger->addAppender(olivia::LogAppender::ptr(new olivia::StdoutLogAppender));

    // 将error日志单独写入log.txt文件中
    // olivia::FileLogAppender::ptr file_appender(new olivia::FileLogAppender("/home/olivia/sylar/myserver/serverTest/bin/conf/log.txt"));
    // olivia::LogFormatter::ptr fmt(new olivia::LogFormatter("%d%T%p%T%m%n"));
    // file_appender->setFormatter(fmt);
    // file_appender->setLevel(olivia::LogLevel::ERROR);

    // logger->addAppender(file_appender);

    //sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__, __LINE__, 0, sylar::GetThreadId(), sylar::GetFiberId(), time(0)));
    //event->getSS() << "hello sylar log";
    //logger->log(sylar::LogLevel::DEBUG, event);
    std::cout << "hello sylar log" << std::endl;

    LOG_INFO(logger) << "test macro";
    LOG_ERROR(logger) << "test macro error";

    LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

    auto l = olivia::LoggerMgr::GetInstance()->getLogger("xx");
    LOG_INFO(l) << "xxx";
    return 0;
}