cmake_minimum_required(VERSION 3.5)

project(p3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(p3 main.cpp)

install(TARGETS p3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
