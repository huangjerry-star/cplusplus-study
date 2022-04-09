#pragma once

#include <iostream>
#include <memory>

template <typename T>
class myshared_ptr
{
public:
    //构造函数
    myshared_ptr(T *_ptr) : ptr(_ptr)
    {
        if (ptr!=nullptr)
        {
            count = new int(1);
        }
        else
        {
            count = new int(0);
        }
    }

    //拷贝构造函数
    myshared_ptr(const myshared_ptr &s)
    {
        if (this == &s)
        {
            return;
        }
        else
        {
            this->ptr = s.ptr;
            this->count = s.count;
            (*count)++;
        }
    }

    //赋值函数
    myshared_ptr &operator=(const myshared_ptr &s)
    {
        if (*this == s)
        {
            return *this;
        }
        if (this->ptr)
        {
            (*this->count)--;
            if (*(this->count) == 0)
            {
                delete this->ptr;
                delete this->count;
            }
        }
        this->ptr = s.ptr;
        this->count = s.count;
        (*count)++;
        return *this;
    }

    T &operator*()
    {
        return *(this->ptr);
    }

    T *operator->()
    {
        return this->ptr;
    }

    int use_count()
    {
        return *(this->count);
    }

    //析构函数
    ~myshared_ptr()
    {
        (*count)--;
        if (*count <= 0)
        {
            delete ptr;
            delete count;
            ptr = nullptr;
            count = nullptr;
        }
    }

private:
    T *ptr;
    int *count;
};