cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

project(Lesson05 LANGUAGES CXX)

file(GLOB SOURCE_FILES source/*.cpp include/*.h)

add_executable(lesson05.out ${SOURCE_FILES})

find_package(Threads REQUIRED)

target_link_libraries(lesson05.out PUBLIC Threads::Threads)

target_include_directories(lesson05.out PUBLIC include)