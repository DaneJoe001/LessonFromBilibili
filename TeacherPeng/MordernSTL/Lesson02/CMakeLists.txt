cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 23)

project(Lesson02 LANGUAGES CXX)

if(MSVC)
    add_compile_options(/Zc:__cplusplus /permissive-)
    #set(CMAKE_PREFIX_PATH "D:/Application/Qt6.5/6.5.3/msvc2019_64")
endif()

file(GLOB SOURCE_FILES source/*.cpp)

add_executable(lesson02.out ${SOURCE_FILES})

target_include_directories(lesson02.out PUBLIC include)