cmake_minimum_required(VERSION 3.18)

project(Lesson02 LANGUAGES CXX)

if(MSVC)
    add_compile_options(/Zc:__cplusplus /permissive-)
    set(CMAKE_PREFIX_PATH "D:/Application/Qt6.5/6.5.3/msvc2019_64")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SOURCES "source/*.cpp" "include/*.h")

add_executable(lesson02 ${SOURCES})

target_link_libraries(lesson02
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)