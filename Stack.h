#pragma once

#define MAX 100
/* template cho phép một hàm hoặc lớp hoạt động trên nhiều kiểu dữ liệu khác nhau
mà không phải viết lại cho mỗi kiểu*/
template <class T>
class Stack {

private:
	int last;

public:
	T buffer[MAX];

	Stack() { last = -1; }
	~Stack() {}

	bool push(T opt);
	T pop();
	T get();
	bool isEmpty();

};



template <class T>
bool Stack<T>::push(T opt) {
	if (this->last + 1 > MAX) return false;

	this->buffer[++this->last] = opt;
	return true;
}

template <class T>
T Stack<T>::pop() {
	this->last--;
	return this->buffer[last + 1];
}

template <class T>
T Stack<T>::get() {
	return this->buffer[last];
}

template <class T>
bool Stack<T>::isEmpty() {
	return (this->last == -1);
}




