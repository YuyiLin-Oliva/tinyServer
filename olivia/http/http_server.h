#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__

#include "olivia/tcp_server.h"
#include "http_session.h"
#include "servlet.h"

namespace olivia {
namespace http {

/**
 * @brief HTTP服务器类
 */
class HttpServer : public TcpServer {
public:
    typedef std::shared_ptr<HttpServer> ptr;

    /**
     * @brief 构造函数
     * @param[in] keepalive 是否长连接
     * @param[in] worker 工作调度器
     * @param[in] accept_worker 接收连接调度器
     */
    HttpServer(bool keepalive = false
               ,olivia::IOManager* worker = olivia::IOManager::GetThis()
               ,olivia::IOManager* io_worker = olivia::IOManager::GetThis()
               ,olivia::IOManager* accept_worker = olivia::IOManager::GetThis());

    /**
     * @brief 获取ServletDispatch
     */
    ServletDispatch::ptr getServletDispatch() const { return m_dispatch;}

    /**
     * @brief 设置ServletDispatch
     */
    void setServletDispatch(ServletDispatch::ptr v) { m_dispatch = v;}

    virtual void setName(const std::string& v) override;
protected:
    virtual void handleClient(Socket::ptr client) override;
private:
    // 是否支持长连接
    bool m_isKeepalive;
    // Servlet分发器
    ServletDispatch::ptr m_dispatch;
};

}
}

#endif
