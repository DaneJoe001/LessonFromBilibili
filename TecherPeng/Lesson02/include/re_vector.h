#pragma once
#include <cstdlib>

class ReVector
{
public:
    ReVector(size_t size);
    ~ReVector();
    //手动实现拷贝构造函数，避免浅拷贝导致double free;
    ReVector(const ReVector&);
    ReVector& operator=(ReVector const& other);
    size_t size();
    void resize(size_t size);
    int& operator[](size_t index);

private:
    size_t m_size;
    int* m_data;
};