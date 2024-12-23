add_library(hellolib STATIC hello.cpp)

#定义hellolib的头文件搜索路径
#引用他的可执行文件CMake会自动添加该路劲
#PUBLIC/PRIVATE与属性传播有关
target_include_directories(hellolib PUBLIC .)