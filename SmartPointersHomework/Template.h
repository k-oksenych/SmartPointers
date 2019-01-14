#pragma once

template <typename T>
class SharedPointer
{
private:
	T* m_ptr;
	T* counter;

	void IncrementUses();
	void DecrementUses();

public:
	SharedPointer(const SharedPointer& source);
	SharedPointer(T* const m_ptr);
	~SharedPointer();
	SharedPointer& operator=(const SharedPointer& right);
	T& operator*();
	T* operator->();
};

template <typename T>
void SharedPointer<T>::IncrementUses()
{
	++(*counter);
}

template <typename T>
void SharedPointer<T>::DecrementUses()
{
	--(*counter);
	if (*counter == 0)
	{
		delete m_ptr;
	}
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer& source) :
	counter(source.counter),
	m_ptr(source.m_ptr)
{
	IncrementUses();
}

template <typename T>
SharedPointer<T>::SharedPointer(T* const m_ptr) :
	counter(new T(1)),
	m_ptr(m_ptr)
{
}

template <typename T>
SharedPointer<T>::~SharedPointer()
{
	DecrementUses();
}

template <typename T>
SharedPointer<T>& SharedPointer<T> :: operator=(const SharedPointer& right)
{
	if (this != &right)
	{
		DecrementUses();

		counter = right.counter;
		m_ptr = right.m_ptr;

		IncrementUses();
	}

	return *this;
}

template <typename T>
T& SharedPointer<T> :: operator*()
{
	return *m_ptr;
}

template <typename T>
T* SharedPointer<T> :: operator->()
{
	return m_ptr;
}