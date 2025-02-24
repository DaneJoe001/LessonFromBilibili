cmake_minimum_required(VERSION 3.18)

project(Lesson03 LANGUAGES CXX)

if(MSVC)
    add_compile_options(/Zc:__cplusplus /permissive-)
    #需要找到windows上的qt路径
    set(CMAKE_PREFIX_PATH "D:/Application/Qt6.5/6.5.3/msvc2019_64")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
file(GLOB_RECURSE SOURCES "source/*.cpp" "include/*.h")

add_executable(lesson03 ${SOURCES})

target_link_libraries(lesson03 PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(lesson03 PUBLIC include)