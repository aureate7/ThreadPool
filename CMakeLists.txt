cmake_minimum_required(VERSION 3.10)
project(ThreadPool)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(ThreadPoolTest test/main.cpp src/ThreadPool.cpp)