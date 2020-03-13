cmake_minimum_required(VERSION 2.8)
project(olivia)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Werror -Wno-deprecated -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
#set(CMAKE_C_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -fPIC -g -std=c++11 -pthread -Wall -Werror -Wno-deprecated -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
set(CMAKE_C_FLAGS "$ENV{CXXFLAGS} -rdynamic -fPIC -g -std=c11 -pthread -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

include_directories(.)
include_directories(/opt/boost_1_71_0/include)
link_directories(/opt/boost_1_71_0/stage/lib)

set(LIB_SRC
        olivia/log.cpp
        olivia/mutex.cpp
        olivia/config.cpp
        olivia/util.cpp
        olivia/thread.cpp
        olivia/fiber.cpp
        olivia/scheduler.cpp
        olivia/fd_manager.cpp
        olivia/timer.cpp
        olivia/hook.cpp
        olivia/io_manager.cpp
        olivia/address.cpp
        olivia/socket.cpp
        olivia/bytearray.cpp
        olivia/stream.cpp
        olivia/streams/socket_stream.cpp
        olivia/tcp_server.cpp
        olivia/uri.rl.cpp
        olivia/http/http11_parser.rl.cpp
        olivia/http/httpclient_parser.rl.cpp
        olivia/http/http.cpp
        olivia/http/http_connection.cpp
        olivia/http/http_parser.cpp
        olivia/http/http_server.cpp
        olivia/http/http_session.cpp
        olivia/http/servlet.cpp
	)

add_library(olivia SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(olivia)
find_library(PTHREAD pthread)

set(LIBS
        olivia
        dl
        pthread
        yaml-cpp
        event
        )

#olivia_add_executable(test_log "tests/test_log.cpp" olivia "${LIBS}")
#olivia_add_executable(test_config "tests/test_config.cpp" olivia "${LIBS}")
#olivia_add_executable(test_scheduler "tests/test_scheduler.cpp" olivia "${LIBS}")
#olivia_add_executable(echo_server "tests/echo_server.cpp" olivia "${LIBS}")
#olivia_add_executable(test_io_manager "tests/test_io_manager.cpp" olivia "${LIBS}")
olivia_add_executable(test_http_server "tests/test_http_server.cpp" olivia "${LIBS}")
olivia_add_executable(test_http_server_close "tests/test_http_server_close.cpp" olivia "${LIBS}")
olivia_add_executable(test_http_server_threadpool_close "tests/test_http_server_threadpool.cpp" olivia "${LIBS}")
olivia_add_executable(test_http_server_threadpool_2_close "tests/test_http_server_threadpool_2.cpp" olivia "${LIBS}")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
