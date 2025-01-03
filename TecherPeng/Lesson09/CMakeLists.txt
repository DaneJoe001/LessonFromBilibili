cmake_minimum_required(VERSION 3.18)

project(Lesson09 LANGUAGES CXX)

set(CXX_STANDARD 17)

set(CXX_STANDARD_REQUIRED on)

file(GLOB srcs include/*.h source/*.cpp)

add_executable(lesson09.out ${srcs})

target_include_directories(lesson09.out PUBLIC include)