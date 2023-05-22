#pragma once

template <typename T>
class SharedPtr
{
private:
    T* data;
    unsigned int* refCount;

public:
    SharedPtr();
    explicit SharedPtr(T* ptr);
    SharedPtr(const SharedPtr<T>& other);
    ~SharedPtr();

    SharedPtr<T>& operator=(const SharedPtr<T>& other);

    T& operator*() const;
    T* operator->() const;

    bool operator==(const SharedPtr<T>& other) const;
    bool operator!=(const SharedPtr<T>& other) const;

    operator bool() const;

    unsigned int useCount() const;
    void reset();
};

#include <iostream>
template <typename T>
SharedPtr<T>::SharedPtr() : data(nullptr), refCount(nullptr)
{
}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) : data(ptr), refCount(new unsigned int(1))
{
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) : data(other.data), refCount(other.refCount)
{
    if (refCount)
        ++(*refCount);
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
    if (refCount)
    {
        --(*refCount);
        if (*refCount == 0)
        {
            delete data;
            delete refCount;
        }
    }
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
    if (this != &other)
    {
        if (refCount)
        {
            --(*refCount);
            if (*refCount == 0)
            {
                delete data;
                delete refCount;
            }
        }

        data = other.data;
        refCount = other.refCount;
        if (refCount)
            ++(*refCount);
    }
    return *this;
}

template <typename T>
T& SharedPtr<T>::operator*() const
{
    return *data;
}

template <typename T>
T* SharedPtr<T>::operator->() const
{
    return data;
}

template <typename T>
bool SharedPtr<T>::operator==(const SharedPtr<T>& other) const
{
    return data == other.data;
}

template <typename T>
bool SharedPtr<T>::operator!=(const SharedPtr<T>& other) const
{
    return data != other.data;
}

template <typename T>
SharedPtr<T>::operator bool() const
{
    return data != nullptr;
}

template <typename T>
unsigned int SharedPtr<T>::useCount() const
{
    return refCount ? *refCount : 0;
}

template <typename T>
void SharedPtr<T>::reset()
{
    if (refCount)
    {
        --(*refCount);
        if (*refCount == 0)
        {
            delete data;
            delete refCount;
        }
    }
    data = nullptr;
    refCount = nullptr;
}
