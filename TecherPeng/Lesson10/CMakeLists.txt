cmake_minimum_required(VERSION 3.18)

project(Lesson10 LANGUAGES CXX)

set(CXX_STANDARD 20)

set(CXX_STANDARD_REQUIRED on)

file(GLOB srcs include/*.h source/*.cpp)

add_executable(lesson10.out ${srcs})

target_include_directories(lesson10.out PUBLIC include)