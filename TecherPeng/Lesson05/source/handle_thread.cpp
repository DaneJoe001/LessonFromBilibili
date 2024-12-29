#include <iostream>
#include <future>
#include <chrono>
#include <mutex>
#include <atomic>
#include <handle_thread.h>
#include <multi_thread_vector.h>
#include <multi_thread_queue.h>

void ThreadPool::push_back(std::thread thread)
{
    m_pool.push_back(std::move(thread));
}

ThreadPool::~ThreadPool()
{
    for (auto& it : m_pool)
    {
        it.join();
    }
}

void handle_thread()
{
    //std::thread构造函数的参数可以是任意lambda表达式
    std::thread t1([&]
        {
            //调用处理函数
            std::cout << "Thread T1!" << std::endl;
        });
    //std::thread遵循RAII思想和三五法则
    //std::thread自定义了析构函数，删除了拷贝构造和赋值函数，提供了移动构造和赋值函数
#ifdef THREAD_JOIN
    t1.join();
#endif

#ifdef THREAD_DETACH
    //detach用于分离线程，但进程退出时候不会等待所有子线程执行完毕
    t1.detach();
#endif
    //可以移交控制权至一个具有更长生命周期的变量，如线程池
    ThreadPool thread_pool;
    thread_pool.push_back(std::move(t1));
    if (!t1.joinable())
    {
        std::cout << "NULL thread!" << std::endl;
    }

#if __cplusplus == 202002L
    std::vector<std::jthread>pool;
    //C++20引入的jthread会在析构时自动调用Join()函数
#endif

    //使用std::async执行异步操作
    //async会创建一个线程在后台执行
    std::future<int> future = std::async([&]
        {
            std::cout << "In async!" << std::endl;
            return 0;
        });

    //使用参数std::launch::deferred后
    //async不会再创建线程来执行函数
    //lambda函数的执行会延迟到get()被调用时
    //可以实现惰性求值
    std::future<int> future02 = std::async(std::launch::deferred, [&]
        {
            std::cout << "In async with std::launch::deferred!" << std::endl;
            return 1;
        });

#ifdef WAIT_THREAD
    //wait()无限等待直至线程完成
    future.wait();
#endif

#ifdef WAIT_FOR_THREAD
    //wait_for()等待指定时间
    //超过时间则放弃等待，返回future_status::timeout
    //等待时间内完成则返回future_status::ready
    future.wait_for(std::chrono::milliseconds(1000));
#endif

#ifdef WAIT_UNTIL_THREAD
    //wait_until()等待至某一时刻
    auto time = std::chrono::steady_clock::now() + std::chrono::milliseconds(400);;
    future.wait_until(time);
#endif

    //等待异步函数的完成并获取返回值
    int check_return = future.get();
    std::cout << "Executable result: " << check_return << std::endl;

    int check_return_02 = future02.get();
    std::cout << "Executable result02: " << check_return_02 << std::endl;

    //使用promise手动创建线程
    std::promise<int> promise;
    std::thread t2([&]
        {
            //使用set_value设置返回值
            promise.set_value(200);
        });
    std::future<int> future03 = promise.get_future();

    int check_return_03 = future03.get();
    std::cout << "Excutable result03: " << check_return_03 << std::endl;
    thread_pool.push_back(std::move(t2));

    //future移除了拷贝构造和赋值函数
    //shared_future可以实现共享一个future对象
    //async的匿名函数返回值可以是void,future对应位std::future<void>
    //std::promise<void>时，set_value不接受参数，仅作为同步使用

}

void thread_protect()
{
    ThreadPool thread_pool;
#ifdef MULTI_THREAD_VECTOR
    MultiThreadVector array;
#else
    std::vector<int> array;
#endif
    //mutex会使线程被挂起
    //需要通过系统调用，进入内核层
    //调度到其他线程执行，有很大的开销
    //mutex对于效率影响较严重
    std::mutex mutex;
#define ONLY_MUTEX
#ifdef ONLY_MUTEX
    std::thread t1([&]
        {
            //调用lock()时会检测是否已经上锁
            //如果没有锁定则对mutex进行上锁
            //如果锁定则等待至另一线程解锁
            mutex.lock();

            //try_lock()无阻塞上锁，失败返回false成功返回true;
            //std::timed_mutex的try_lock_for()等待一段时间上锁
            //try_lock_until等待某个时间点的上锁
            array.push_back(1);
            //unlock进行解锁操作
            mutex.unlock();
        });
    thread_pool.push_back(std::move(t1));
    std::thread t2([&]
        {
            mutex.lock();
            array.push_back(2);
            mutex.unlock();
        });
    thread_pool.push_back(std::move(t2));
#endif

    std::thread t3([&]
        {
            //std::lock_guard符合RAII思想
            //在构造时上锁，在退出析构时解锁
            //std::lock_guard不能手动释放锁
            //通过花括号调整作用域，可以控制锁的生命周期
            std::lock_guard grd(mutex);
            array.push_back(3);
        });
    thread_pool.push_back(std::move(t3));
    std::thread t4([&]
        {
            std::lock_guard grd(mutex);
            array.push_back(4);
        });
    thread_pool.push_back(std::move(t4));

    std::thread t5([&]
        {
            //使用std::defer_lock可以提前释放锁
            //其构造函数可以添加一个额外参数std::defer_lock
            //当添加std::defer_lock后，grd不会构造时调用lock
            //需要时手动调用grd.lock()才能上锁
            //优点是会自动unlock();
            //std::defer_lock是一个用于区分构造函数的空tag类
            //当参数为std::try_to_lock时，会调用try_lock()
            //可以用grd.owns_lock()判断是否上锁成功
            //使用参数std::adopt_lock会默认mutex已上锁
            std::unique_lock grd(mutex, std::defer_lock);
            grd.lock();
            array.push_back(5);
        });
    thread_pool.push_back(std::move(t5));
    std::thread t6([&]
        {
            std::unique_lock grd(mutex);
            array.push_back(6);
        });
    thread_pool.push_back(std::move(t6));

    std::thread thread_output([&]
        {
            mutex.lock();
            std::cout << "Size of Array: " << array.size() << std::endl;
            for (auto& it : array)
            {
                std::cout << it << ' ';
            }
            mutex.unlock();
        });
    thread_pool.push_back(std::move(thread_output));


}

#ifdef DEADLOCK
void deadlock_example()
{
    std::mutex mutex01;
    std::mutex mutex02;
    std::thread t1 = ([&]
        {
            for (int i = 0;i < 1000;i++)
            {
                mutex01.lock();
                mutex02.lock();
                mutex01.unlock();
                mutex02.unlock();
            }
        });
    std::thread t1 = ([&]
        {
            for (int i = 0;i < 1000;i++)
            {
                mutex01.lock();
                mutex02.lock();
                mutex01.unlock();
                mutex02.unlock();
            }
        });
    t1.join();
    t2.join();
    //解决方案，保持双方上锁顺序一致，或不同时持有两个锁
    //或使用std::lock(mutex01,mutex02...);可以同时对多个mutex上锁
    //解锁使用unlock()即可
    //C++17标准std::lock的RAII版本：std::scoped_lock
    //std::scoped_lock grd(mutex01,mutex02);

    //避免在函数内部上锁后在继续调用的函数中重复上锁导致死锁
    //使用std::recursive_mutex可以判断是不是同一个线程多次同一个锁
    //如果是，则计数器加一，unlock计数器减一，0时真正解锁
    //std::recursive_mutex与普通的mutex相比会有性能损失

    //响应的时间控制版本std::recursive_timed_mutex
}
#endif

void try_multi_safety_vector()
{
    ThreadPool thread_pool;
    MultiThreadVector array;
    std::thread t1([&]
        {
            auto axr = array.accessor();
            for (int i = 0;i < 1000;i++)
            {
                axr.push_back(i);
            }
        });
    thread_pool.push_back(std::move(t1));
    std::thread t2([&]
        {
            auto axr = array.accessor();
            for (int i = 0;i < 1000;i++)
            {
                axr.push_back(1000 + i);
            }
        });
    thread_pool.push_back(std::move(t2));
    std::cout << "Size of array: " << array.accessor().size() << std::endl;
}

void thread_with_conditional_variable()
{
    std::condition_variable cv;
    std::mutex mutex;
    ThreadPool thread_pool;
    std::thread t1([&]
        {
            //std::condition_variable必须和std::unque_lock<std::mutex>一起用
            //确保多个线程被唤醒时，只有一个能够被启动
            //std::condition_variable只接受std::unque_lock<std::mutex>
            //std::condition_variable_any可以接受其他类型的mutex
            std::unique_lock lck(mutex);
            //cv.wait(lck)将会让当前线程陷入等待
            cv.wait(lck);
            //不需要限制一个启动可以调用lck.unlock();
            //wait()的过程中会暂时unlock()这个锁
            //wait()也具有wait_for()和wait_until()函数
#ifdef WAIT_CONDITION
            //wait函数可以多添加一个lambda表达式参数，当表达式返回true时才会真正唤醒，否则继续等待
            cv.wait(lck, [&]->bool
                {
                    return true;
                });
#endif
            std::cout << "t1 is awake!" << std::endl;
        });

    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::cout << "notifying……" << std::endl;
    //cv.notify_one()会唤醒那个陷入等待的线程
    //cv.notify_all()会等待全部的线程
    cv.notify_one();
    t1.join();
}

void try_multi_thread_queue()
{
    MultiThreadQueue<int> foods;
    std::thread t1([&]
        {
            for (int i = 0;i < 2;i++)
            {
                auto food = foods.pop();
                std::cout << "t1 got food: " << food << std::endl;
            }
        });
    std::thread t2([&]
        {
            for (int i = 0;i < 2;i++)
            {
                auto food = foods.pop();
                std::cout << "t1 got food: " << food << std::endl;
            }
        });
    foods.push(42);
    foods.push(42);
    foods.push_many({ 666,4399 });
    t1.join();
    t2.join();

}

void thread_with_atomic()
{
    //现代CPU在汇编指令执行过程中会将其拆分为多个微指令
    //现代CPU有很多优化策略，一定程度上导致指令执行顺序未知
    //不加保护的情况，无法保证原子操作
    //mutex能保证，但性能消耗大
    //atomic更轻量，对于+= -= &= |= ^= ++ --等操作
    //会被编译器转换成专门的指令
    //cpu识别到该指令时，会锁住内存总线
    //放弃乱序执行等优化策略
    //从而保证该操作是原子的
    //对于int只用将其替换为atomic<int>即可
    //不需要像mutex一样手动上锁解锁
    std::atomic<int> counter = 0;

    std::thread t1([&]
        {
            for (int i = 0;i < 10000;i++)
            {
                counter += 1;
            }
        });
    std::thread t2([&]
        {
            for (int i = 0;i < 10000;i++)
            {
                counter += 1;
            }
        });
    t1.join();
    t2.join();
    counter.store(0);
    //counter先取出旧值，再写入新值
    int old = counter.exchange(3);
    //compare_exchange_strong先比较是否和old相等，相等则将val写入
    //返回bool表示是否成功
    bool equal = counter.compare_exchange_strong(old, 3);

    std::cout << counter << std::endl;
    return 0;
}