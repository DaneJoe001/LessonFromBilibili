#include <multi_thread_vector.h>

#ifndef ACCESS_MODE
void MultiThreadVector::push_back(int value)
{
    //写入数据使用lock和unlock的写锁
    //写锁会限制共享锁和写锁
    m_mutex.lock();
    m_array.push_back(value);
    m_mutex.unlock();
}

std::size_t MultiThreadVector::size() const
{
#ifndef SHARED_MUTEX
    m_mutex.lock();
    std::size_t size = m_array.size();
    m_mutex.unlock();
#else
    //读取数据使用lock_shared和unlock_shared的共享锁
    //共享锁不会限制共享锁，但会限制写锁
    m_mutex.lock_shared();
    std::size_t size = m_array.size();
    m_mutex.unlock_shared();
#endif
    return size;
}

#else

MultiThreadVector::Accessor::Accessor(MultiThreadVector& that) :m_that(that), m_guard(that.m_mutex) {}

void MultiThreadVector::Accessor::push_back(int value)
{
    return m_that.m_array.push_back(value);
}

std::size_t MultiThreadVector::Accessor::size() const
{
    return m_that.m_array.size();
}

MultiThreadVector::Accessor MultiThreadVector::accessor()
{
    return { *this };
}
#endif