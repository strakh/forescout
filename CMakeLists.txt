cmake_minimum_required(VERSION 3.5)
project(forescout)

set(CMAKE_CXX_STANDARD 14)

add_executable(forescout main.cpp TaskManager.cpp TaskManager.h PeriodicTask.h)
add_executable(test PeriodicTask.h TaskManager.cpp TaskManager.h PeriodicTaskTst.cpp TaskManagerTst.cpp)
target_link_libraries(forescout pthread)
target_link_libraries(test pthread)