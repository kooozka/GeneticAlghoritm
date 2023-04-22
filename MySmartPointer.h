#include <iostream>

#pragma once
class RefCounter
{
public:
	RefCounter() { count = 0; }
	int add() { return(++count); }
	int dec() { return(--count); };
	int get() { return(count); }
private:
	int count;
};

template <typename T>
class MySmartPointer
{
public:
	MySmartPointer(T* newPointer);
	MySmartPointer(const MySmartPointer& other);
	~MySmartPointer();
	T& operator*() { return(*pointer); }
	T* operator->() { return(pointer); }
	void operator=(const MySmartPointer& other);
	T* getPointer();
	//MySmartPointer operator=(MySmartPointer&& other);
private:
	RefCounter* counter;
	T* pointer;
	void copyPointer(const MySmartPointer& other);
};

template <typename T>
MySmartPointer<T>::MySmartPointer(T* newPointer) {
	pointer = newPointer;
	counter = new RefCounter();
	counter->add();
}

template <typename T>
MySmartPointer<T>::MySmartPointer(const MySmartPointer& other) {
	pointer = other.pointer;
	counter = other.counter;
	counter->add();
}

template <typename T>
MySmartPointer<T>::~MySmartPointer() {
	if (counter->dec() == 0)
	{
		delete[] pointer;
		delete counter;
		std::cout << "usuwam gowno";
	}
}

template <typename T>
void MySmartPointer<T>::operator=(const MySmartPointer& other) {
	if (pointer != NULL) {
		delete this;
	}
	pointer = other.pointer;
	counter = other.counter;
	counter->add();
}

template<typename T>
T* MySmartPointer<T>::getPointer()
{
	return pointer;
}

