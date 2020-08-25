cmake_minimum_required(VERSION 3.16)
project(Study)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK")

add_executable(Study chapter1.cpp chapter2.cpp main.cpp)
#add_executable(Study temp.cpp)