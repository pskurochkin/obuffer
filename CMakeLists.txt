cmake_minimum_required(VERSION 3.15)
project(obuffer)

set(CMAKE_CXX_STANDARD 11)

find_package(Threads)

add_executable(obuffer main.cpp circular_buffer.cpp circular_buffer.h)

target_link_libraries(obuffer Threads::Threads)