#include <deque>
#include <chrono>
#include <optional>
#include <condition_variable>

template<class T>
class MTQueue
{
public:
    //推入数据并通知，队列满则阻塞
    void push(T value)
    {
        std::unique_lock lock(m_mutex);
        while (m_queue.size() > m_size)
        {
            m_cv_is_full.wait(lock);
        }
        m_queue.push_front(std::move(value));
        m_cv.notify_one();
    }

    //陷入阻塞直到有数据
    T pop()
    {
        std::unique_lock lock(m_mutex);
        while (m_queue.empty())
        {
            m_cv.wait(lock);
        }
        T value = std::move(m_queue.back());
        m_queue.pop_back();
        m_cv_is_full.notify_one();
        return value;
    }

    //尝试读取数据，不阻塞，没有返回空值
    std::optional<T> try_pop()
    {
        std::unique_lock lock(m_mutex);
        if (m_queue.empty())
        {
            return std::nullopt;
        }
        T value = std::move(m_queue.back());
        m_queue.pop_back();
        m_cv_is_full.notify_one();
        return value;
    }

    //尝试等待读取，超时返回空值
    std::optional<T> try_pop_for(std::chrono::steady_clock::duration time_out)
    {
        std::unique_lock lock(m_mutex);
        if (!m_cv.wait_for(lock, time_out, [&]
            {
                return !m_queue.empty();
            }))
        {
            return std::nullopt;
        }
        T value = std::move(m_queue.back());
        m_queue.pop_back();
        m_cv_is_full.notify_one();
        return value;
    }
private:
    std::size_t m_size = 10;
    std::deque<T>m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::condition_variable m_cv_is_full;
};