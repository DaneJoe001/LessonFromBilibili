cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 23)

project(Lesson02 LANGUAGES CXX)

file(GLOB SOURCE_FILES source/*.cpp)

add_executable(lesson02.out ${SOURCE_FILES})

target_include_directories(lesson02.out PUBLIC include)