cmake_minimum_required(VERSION 3.27)
project(playing_with_winsock2)

set(CMAKE_CXX_STANDARD 17)

add_executable(playing_with_winsock2 main.cpp
        functions/basic_accept_wo_return.h
        functions/basic_accept_w_return.h)

target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)
