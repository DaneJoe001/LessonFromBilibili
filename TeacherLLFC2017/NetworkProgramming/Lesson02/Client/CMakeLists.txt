file(GLOB srcs include/*.h source/*.cpp)

find_package(Boost REQUIRED COMPONENTS system filesystem thread)

add_executable(client.out ${srcs})

target_include_directories(client.out PUBLIC include)

target_link_libraries(client.out Boost::system Boost::filesystem Boost::thread)