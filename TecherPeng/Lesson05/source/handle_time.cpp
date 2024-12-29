#include <iostream>
#include <thread>
#include <handle_time.h>

#ifdef C_TIME
void check_handle_time_in_C()
{
    //C语言原始API，没有类型区分
    //获取从1970年1月1日到当前时经过的秒数
    long t0 = time(NULL);
    //sleep(3);
    long t1 = t0 + 3;
    //usleep(3000000);
}
#endif

void check_handle_time_in_Cpp()
{
    //时间点类型：chrono::steady_clock::time_point(高精度)
    //时间段类型：chrono::milliseconds(毫秒),chrono::seconds,chrono::miniutes
    //方便的运算符重载：时间点+时间段=时间点，时间点-时间点=时间段

    //获取当前时间点
    auto t0 = std::chrono::steady_clock::now();

    //当前时间点的30秒后
    auto t1 = t0 + std::chrono::seconds(30);
    //获取两个时间点的差（时间段） 
    auto dt = t1 - t0;
    //时间差的秒数
    int64_t sec = std::chrono::duration_cast<std::chrono::seconds>(dt).count();
    std::cout << "Interval: " << sec << std::endl;

    for (volatile int i = 0;i < 10000000;i++);

    //获取时间点
    auto t3 = std::chrono::steady_clock::now();
    dt = t3 - t0;
    sec = std::chrono::duration_cast<std::chrono::milliseconds>(dt).count();
    std::cout << "From begin to end: " << sec << std::endl;

    //duration_cast可以在任意的duration类型之间进行转换
    //duration<T,R>表示用T类型，时间单位为R
    //R省略为秒，std::milli为毫秒，std::micro为微秒
    //seconds是duration<int64_t>类型的别名
    //milliseconds是duration<int64_t,std::milli>类型的别名
    using double_ms = std::chrono::duration<double, std::milli>;
    double ms = std::chrono::duration_cast<double_ms>(dt).count();

    //跨平台的休眠函数(使当前线程休眠一段时间，时间单位可指定)
    //此处的时间单位是milliseconds可以替换为seconds
    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    //使用sleep_until可以让程序休眠到某个时间点
    auto time = std::chrono::steady_clock::now() + std::chrono::milliseconds(400);
    std::this_thread::sleep_until(time);
}