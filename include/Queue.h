#pragma once
#include <exception>

const int MAX_QUEUE_SIZE = 100;

template <class T = int>
class Queue
{
private:
	T* pMem;
	int capacity;
	int last;
public:
	Queue(int capacity = 20);
	Queue(const Queue& q);
	~Queue();
	inline int size() { return last; }
	inline bool empty() { return last == 0; }
	inline bool full() { return last == MAX_QUEUE_SIZE; }
	void push(const T& value);
	T getd(int index);
	T& geti(int index);
	T pop();
	T& peek();
	inline void clear() { last = 0; }
	int search(const T& value);
	Queue& operator=(const Queue& q);
	bool operator==(const Queue& q);
	bool operator!=(const Queue& q);
};

template <class T>
Queue<T>::Queue(int capacity) : capacity(capacity), last(0)
{
	if (capacity < 1 || MAX_QUEUE_SIZE < capacity)
		throw std::exception("Invalid queue capacity");
	pMem = new T[capacity];
}

template <class T>
Queue<T>::Queue(const Queue<T>& q) : capacity(q.capacity), last(q.last)
{
	pMem = new T[capacity];
	for (int i = 0; i < last; ++i)
		pMem[i] = q.pMem[i];
}

template <class T>
Queue<T>::~Queue()
{
	delete[] pMem;
	pMem = nullptr;
}

template <class T>
void Queue<T>::push(const T& value)
{
	if (full())
		throw std::exception("Queue overflow");
	if (capacity == last)
	{
		capacity = capacity * 2 > MAX_QUEUE_SIZE ? MAX_QUEUE_SIZE : capacity * 2;
		T* tmp = new T[capacity];
		for (int i = 0; i < last; ++i)
			tmp[i] = pMem[i];
		delete[] pMem;
		pMem = tmp;
	}
	pMem[last++] = value;
}

template <class T>
T Queue<T>::pop()
{
	return getd(0);
}

template <class T>
T& Queue<T>::peek()
{
	return geti(0);
}

template <class T>
T Queue<T>::getd(int index)
{
	if (empty())
		throw std::exception("Queue underflow");
	if (index < 0 || last <= index)
		throw std::exception("Illegal argument");
	T tmp = pMem[index];
	for (int i = index + 1; i < last; ++i)
		pMem[i - 1] = pMem[i];
	--last;
	return tmp;
}

template <class T>
T& Queue<T>::geti(int index)
{
	if (empty())
		throw std::exception("Queue underflow");
	if (index < 0 || last <= index)
		throw std::exception("Illegal argument");
	return pMem[index];
}

template <class T>
int Queue<T>::search(const T& value)
{
	int i, count;
	for (i = 0, count = 0; i < last; ++i)
		if (pMem[i] == value)
			break;
		else
			++count;
	return i == last ? -1 : count;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& q)
{
	if (this != &q)
	{
		delete[] pMem;
		capacity = q.capacity;
		last = q.last;
		pMem = new T[capacity];
		for (int i = 0; i < last; ++i)
			pMem[i] = q.pMem[i];
	}
	return *this;
}

template <class T>
bool Queue<T>::operator==(const Queue<T>& q)
{
	if (this != &q)
	{
		if (last != q.last)
			return false;
		for (int i = 0; i < last; ++i)
			if (pMem[i] != q.pMem[i])
				return false;
	}
	return true;
}

template <class T>
bool Queue<T>::operator!=(const Queue<T>& q)
{
	return !(*this == q);
}