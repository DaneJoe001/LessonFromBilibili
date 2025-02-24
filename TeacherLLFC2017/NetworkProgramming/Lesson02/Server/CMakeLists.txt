file(GLOB srcs include/*.h source/*.cpp)

find_package(Boost REQUIRED COMPONENTS system filesystem thread)

add_executable(server.out ${srcs})

target_include_directories(server.out PUBLIC include)

target_link_libraries(server.out Boost::thread Boost::system Boost::filesystem)