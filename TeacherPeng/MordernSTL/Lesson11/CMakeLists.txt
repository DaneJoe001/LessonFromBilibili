cmake_minimum_required(VERSION 3.18)

project(Lesson11 LANGUAGES CXX)

if(MSVC)
    add_compile_options(/Zc:__cplusplus /permissive-)
    #set(CMAKE_PREFIX_PATH "D:/Application/Qt6.5/6.5.3/msvc2019_64")
endif()

set(CXX_STANDARD 20)

set(CXX_STANDARD_REQUIRED on)

file(GLOB srcs include/*.h source/*.cpp)

add_executable(lesson11.out ${srcs})

target_include_directories(lesson11.out PUBLIC include)