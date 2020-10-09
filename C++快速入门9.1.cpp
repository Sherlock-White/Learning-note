#include<iostream>
#include<string>
template<class T>
class Stack {
public:
	Stack(unsigned int size = 100); //默认size = 100
	~Stack();
	void push(T value);
	T pop();
private:
	unsigned int size;
	unsigned int sp;     //索引
	T* data;             //动态分配
};
template<class T>
Stack<T>::Stack(unsigned int size) {
	this->size = size;
	data = new T[size];
	sp = 0;
}
template<class T>
Stack<T>::~Stack() {
	delete[]data;
}
template<class T>
void Stack<T>::push(T value) {
	data[sp++] = value;//先使用索引，再自加
}
template<class T>
T Stack<T>::pop() {
	return data[--sp]; //因为上面多自加了一次，所以要先自减再使用
}

int main() {
	Stack<int> intStack(100);
	intStack.push(1);
	intStack.push(2);
	intStack.push(3);
	std::cout << intStack.pop() << '\n';
	std::cout << intStack.pop() << '\n';
	std::cout << intStack.pop() << '\n';
	return 0;
}
