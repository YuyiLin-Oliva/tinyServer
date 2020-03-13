#include "olivia/http/http_server.h"
#include "olivia/log.h"

static olivia::Logger::ptr g_logger = LOG_ROOT();

#define XX(...) #__VA_ARGS__


olivia::IOManager::ptr worker;
void run() {
    g_logger->setLevel(olivia::LogLevel::INFO);
    olivia::http::HttpServer::ptr server(new olivia::http::HttpServer(false, worker.get(), worker.get(), olivia::IOManager::GetThis()));
    //olivia::http::HttpServer::ptr server(new olivia::http::HttpServer(true));
    olivia::Address::ptr addr = olivia::Address::LookupAnyIPAddress("0.0.0.0:8020");
    while(!server->bind(addr)) {
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/olivia/xx", [](olivia::http::HttpRequest::ptr req
                ,olivia::http::HttpResponse::ptr rsp
                ,olivia::http::HttpSession::ptr session) {
            rsp->setBody(req->toString());
            return 0;
    });

    sd->addGlobServlet("/olivia/*", [](olivia::http::HttpRequest::ptr req
                ,olivia::http::HttpResponse::ptr rsp
                ,olivia::http::HttpSession::ptr session) {
            rsp->setBody("Glob:\r\n" + req->toString());
            return 0;
    });

    sd->addGlobServlet("/oliviax/*", [](olivia::http::HttpRequest::ptr req
                ,olivia::http::HttpResponse::ptr rsp
                ,olivia::http::HttpSession::ptr session) {
            rsp->setBody(XX(<html>
<head><title>404 Not Found</title></head>
<body>
<center><h1>404 Not Found</h1></center>
<hr><center>nginx/1.16.0</center>
</body>
</html>
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
<!-- a padding to disable MSIE and Chrome friendly error page -->
));
            return 0;
    });

    server->start();
}

int main(int argc, char** argv) {
    olivia::IOManager iom(1, true, "main");
    worker.reset(new olivia::IOManager(3, false, "worker"));
    iom.schedule(run);
    return 0;
}
