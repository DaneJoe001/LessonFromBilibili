cmake_minimum_required(VERSION 3.12)

#指定项目名称及语言
project(hellocmake LANGUAGES CXX)

if(MSVC)
    add_compile_options(/Zc:__cplusplus /permissive-)
    #set(CMAKE_PREFIX_PATH "D:/Application/Qt6.5/6.5.3/msvc2019_64")
endif()

#生成静态库
#add_library(hellolib STATIC hello.cpp)

# 添加 hellolib 子目录
add_subdirectory(hellolib)

add_executable(a.out main.cpp)

#链接静态库
target_link_libraries(a.out PUBLIC hellolib)

#通过target_include_directories指定的路径会被视为与系统路径等价
target_include_directories(a.out PUBLIC hellolib)