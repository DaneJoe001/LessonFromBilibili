#include <stdexcept>
#include <cstring>
#include <re_vector.h>

ReVector::ReVector(size_t size) :m_size(size)
{
    m_data = (int*)malloc(size * sizeof(int));
    if (m_data == NULL)
    {
        throw std::bad_alloc();
    }
}

ReVector::~ReVector()
{
    free(m_data);
}

ReVector::ReVector(const ReVector& other)
{
    m_size = other.m_size;
    m_data = (int*)malloc(m_size * sizeof(int));
    if (m_data == NULL)
    {
        throw std::bad_alloc();
    }
    memcpy(m_data, other.m_data, m_size * sizeof(int));
}

ReVector& ReVector::operator=(ReVector const& other)
{
    // 自我赋值检查
    if (this == &other)
    {
        return *this;
    }
    // 先释放当前对象的资源
    free(m_data);
    // 复制其他对象的资源
    m_size = other.m_size;
    m_data = (int*)malloc(m_size * sizeof(int));
    if (m_data == NULL)
    {
        throw std::bad_alloc(); // 处理内存分配失败
    }

    // 复制数据
    std::copy(other.m_data, other.m_data + m_size, m_data);

    return *this;
}


size_t ReVector::size()
{
    return m_size;
}

void ReVector::resize(size_t size)
{
    m_size = size;
    int* new_data = (int*)realloc(m_data, m_size);
    if (new_data == NULL)
    {
        throw std::bad_alloc();
    }
    m_data = new_data;
}

int& ReVector::operator[](size_t index)
{
    return m_data[index];
}