#pragma once
#include <mutex>
#include <thread>
#include <future>
#include <shared_mutex>

template<class T>
class MultiThreadQueue
{
public:
    T pop()
    {
        std::unique_lock lck(m_mutex);
        m_cv.wait(lck, [this]
            {
                return !m_array.empty();
            });
        T ret = std::move(m_array.back());
        m_array.pop_back();
        return ret;
    }
    auto pop_hold()
    {
        std::unique_lock lck(m_mutex);
        m_cv.wait(lck, [this]
            {
                return !m_array.empty();
            });
        T ret = std::move(m_array.back());
        m_array.pop_back();
        return std::pair(std::move(ret), std::move(lck));
    }
    void push(T value)
    {
        std::unique_lock lck(m_mutex);
        m_array.push_back(std::move(value));
        m_cv.notify_one();
    }

    void push_many(std::initializer_list<T> values)
    {
        std::unique_lock lck(m_mutex);
        std::copy(
            std::move_iterator(values.begin()),
            std::move_iterator(values.end()),
            std::back_insert_iterator(m_array)
        );
        m_cv.notify_all();
    }
private:
    std::condition_variable m_cv;
    std::mutex m_mutex;
    std::vector<T> m_array;
};