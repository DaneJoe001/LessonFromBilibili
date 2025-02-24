cmake_minimum_required(VERSION 3.18)

project(Lesson01 LANGUAGES CXX)

set(CXX_STANDARD 17)

set(CXX_STANDARD_REQUIRED on)

file(GLOB srcs source/*.cpp include/*.h)

find_package(Boost REQUIRED COMPONENTS system filesystem thread)

#find_package(jsoncpp REQUIRED)

add_executable(lesson01.out ${srcs})

target_include_directories(lesson01.out PUBLIC include)

target_link_libraries(lesson01.out Boost::system Boost::filesystem Boost::thread)

#target_link_libraries(gate_server.out jsoncpp_lib)