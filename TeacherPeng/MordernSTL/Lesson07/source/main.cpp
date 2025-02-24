#include <string>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <mutex>
#include <deque>
#include <vector>
#include <condition_variable>

#define QUIT_SIGN "EXIT"

class ThreadPool
{
public:
    ThreadPool() = default;
    ~ThreadPool()
    {
        for (auto& it : threads)
        {
            it.join();
        }
    }
    void push_back(std::thread thread)
    {
        threads.push_back(std::move(thread));
    }

private:
    std::vector<std::thread>threads;
};

int main()
{
    ThreadPool thread_pool;
    std::mutex mutex_data;
    std::condition_variable con_var;
    std::deque<std::string>msg_queue;

    std::string data = "data1";
    auto func_send = [&](std::string msg)
        {
            std::unique_lock lock(mutex_data);
            msg_queue.push_front(msg);
            con_var.notify_one();
        };
    auto func_exit = [&]
        {
            std::unique_lock lock(mutex_data);
            msg_queue.push_front(QUIT_SIGN);
            //通知所有进程退出
            con_var.notify_all();
        };

    auto func1 = [&]
        {
            func_send("First message!");
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            func_send("Second message!");
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            func_send("Third message!");
            func_exit();
        };
    auto func_recv = [&]()->bool
        {
            std::unique_lock<std::mutex> lock(mutex_data);
            while (msg_queue.empty())
            {
                con_var.wait(lock);
            }
            std::cout << "Message recieved: " << msg_queue.back() << std::endl;
            bool ret_val = true;
            if (msg_queue.back() == QUIT_SIGN)
            {
                ret_val = false;
            }
            msg_queue.pop_back();
            return ret_val;
        };
    auto func2 = [&]
        {
            while (func_recv()) {}
        };
    std::thread t1(func1);
    thread_pool.push_back(std::move(t1));
    std::thread t2(func2);
    thread_pool.push_back(std::move(t2));

    return 0;
}
