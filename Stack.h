#pragma once

template <class T, int size>
class Stack
{
	T data[size];
	int head;
public:
	Stack();
	T Pop();
	void Push(T item);
};

template<class T, int size>
Stack<T, size>::Stack() : data()
{
	head = -1;
}

template<class T, int size>
inline T Stack<T, size>::Pop()
{
	if (head < 0) {
		return 0;
	}

	T item = data[head];
	head--;
	return item;
}

template<class T, int size>
inline void Stack<T, size>::Push(T item)
{
	if ((head + 1) > size) {
		return;
	}

	head++;
	data[head] = item;
}
