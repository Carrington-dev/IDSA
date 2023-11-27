cmake_minimum_required(VERSION 3.5)

project(prt_3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prt_3 main.cpp)

install(TARGETS prt_3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
