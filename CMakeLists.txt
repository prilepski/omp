cmake_minimum_required(VERSION 2.6)
project(hello_world)

add_executable(hello_world main.cpp)

install(TARGETS hello_world RUNTIME DESTINATION bin)
