cmake_minimum_required(VERSION 3.22.1)

project("native_lib")


add_library(${CMAKE_PROJECT_NAME} SHARED
        findsym.cpp  java_hook.cpp native_lib.cpp)


target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log)