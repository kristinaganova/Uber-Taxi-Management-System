#pragma once
#include <iostream>
#include <memory>

template <typename T>
class SharedPtr
{
	T* data;
	unsigned* pointersCount;

	void free();
	void copyFrom(const SharedPtr<T>& other);

public:
	SharedPtr();
	SharedPtr(T* data);

	SharedPtr(const SharedPtr<T>& other);
	SharedPtr& operator=(const SharedPtr<T>& other);

	const T& operator*() const;
	T& operator*();
	const T* operator->() const;
	T* operator->();
	explicit operator bool() const;

	~SharedPtr();

	friend std::istream& operator>>(std::istream& is, SharedPtr<T>& sp);

	friend std::ostream& operator<<(std::ostream& os, const SharedPtr<T>& sp);
};

template <typename T>
std::istream& operator>>(std::istream& is, SharedPtr<T>& sp);

template <typename T>
std::ostream& operator<<(std::ostream& os, const SharedPtr<T>& sp);

template<typename T>
std::istream& operator>>(std::istream& is, SharedPtr<T>& sp)
{
	T* ptr = new T();
	if (!(is >> *ptr))
	{
		delete ptr;
		throw std::runtime_error("Failed to read input for T");
	}
	sp = SharedPtr<T>(ptr);
	return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const SharedPtr<T>& sp)
{
	if (sp.data)
		os << *sp.data;
	return os;
}

template <typename T>
void SharedPtr<T>::free()
{
	if (data == nullptr || pointersCount == nullptr)
		return;

	if (*pointersCount == 1)
	{
		delete data;
		delete pointersCount;
	}
	else
		(*pointersCount)--;

	data = nullptr;
	pointersCount = nullptr;
}

template <typename T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other)
{
	data = other.data;
	pointersCount = other.pointersCount;
	if (pointersCount)
	{
		(*pointersCount)++;
	}
	else
	{
		data = nullptr;
	}
}


template <typename T>
SharedPtr<T>::SharedPtr()
{
	data = nullptr;
	pointersCount = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(T* data)
{
	if (data == nullptr) {
		this->data = nullptr;
		this->pointersCount = nullptr;
	}
	else {
		this->data = data;
		this->pointersCount = new unsigned(1);
	}
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	if (this != &other)
	{
		free();

		if (other.data == nullptr) {
			data = nullptr;
			pointersCount = nullptr;
		}
		else {
			copyFrom(other);
		}
	}
	return *this;
}


template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{
	copyFrom(other);
}

template <typename T>
const T& SharedPtr<T>::operator*() const
{
	if (data == nullptr)
	{
		throw std::runtime_error("Pointer not set");
	}
	return *data;
}

template <typename T>
T& SharedPtr<T>::operator*()
{
	if (data == nullptr)
	{
		throw std::runtime_error("Pointer not set");
	}
	return *data;
}

template <typename T>
SharedPtr<T>::~SharedPtr()
{
	free();
}

template<typename T>
T* SharedPtr<T>::operator->()
{
	return data;
}

template<typename T>
const T* SharedPtr<T>::operator->() const
{
	return data;
}

template<typename T>
SharedPtr<T>::operator bool() const {
	return data;
}