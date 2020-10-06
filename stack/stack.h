#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <string>

template <class T> 
class stack {
private:
	std::vector<T> theStack;
public:
	stack();
	~stack();
	void push(T val);
	T pop();
	T peek();
	bool isEmpty();
	int getSize();

};


class minStack : public stack<int> {
private:
	stack<int> theMinStack;
public:
	void push(int val);
	int pop();
	int getMin();
};

template <class T>
stack<T>::stack() {
}

template <class T>
stack<T>::~stack() {
	theStack.clear();
}

template <class T>
void stack<T>::push(T val) {
	theStack.push_back(val);
}

template <class T>
T stack<T>::pop() {
	if(isEmpty()) {
		printf("ERROR! Cannot pop from empty stack!\n");
		exit(1);
	}
	T retVal = theStack.back();
	theStack.pop_back();
	return retVal;
}

template <class T>
T stack<T>::peek() {
	if(isEmpty()) {
		printf("ERROR! Cannot peek from empty stack!\n");
		exit(1);
	}
	return theStack.back();
}

template <class T>
bool stack<T>::isEmpty() {
	return (theStack.size()==0);
}

template <class T>
int stack<T>::getSize() {
	return theStack.size();
}

//minStack
void minStack::push(int val) {
	stack<int>::push(val);
	if(theMinStack.isEmpty()) {
		theMinStack.push(val);
	}
	else {
		if(theMinStack.peek() > val) theMinStack.push(val);
	}
}

int minStack::pop() {
	int retVal = stack<int>::pop();
	if(retVal==getMin()) theMinStack.pop();
	return retVal;
}

int minStack::getMin() {
	return theMinStack.peek();
}