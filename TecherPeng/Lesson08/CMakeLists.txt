cmake_minimum_required(VERSION 3.12)

project(Lesson05 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES source/*.cpp include/*.h)

add_executable(lesson08.out ${SOURCE_FILES})

find_package(Threads REQUIRED)

target_link_libraries(lesson08.out PUBLIC Threads::Threads)

target_include_directories(lesson08.out PUBLIC include)