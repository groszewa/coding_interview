 #include "stack.h"


int main() {
	printf("Hello INT stack!\n");
	stack<int> intStack;
	printf("Pushing 1 onto the stack\n");
	intStack.push(1);
	printf("Pushing 2 onto the stack\n");
	intStack.push(2);
	printf("Pushing 3 onto the stack\n");	
	intStack.push(3);
	printf("Popping from stack : %d\n",intStack.pop());
	printf("Popping from stack : %d\n",intStack.pop());
	printf("Pushing 12 onto the stack\n");	
	intStack.push(12);
	printf("Popping from stack : %d\n",intStack.pop());
	printf("Popping from stack : %d\n",intStack.pop());
	//printf("Popping from stack : %d\n",myStack.pop());

	printf("Hello STRING stack!\n");
	stack<std::string> stringStack;
	printf("Pushing \"hello\" onto the stack\n");
	stringStack.push("hello");
	printf("Pushing \"world\" onto the stack\n");
	stringStack.push("world");
	printf("Pushing \"alex\" onto the stack\n");	
	stringStack.push("alex");
	printf("Popping from stack : %s\n",stringStack.pop().c_str());
	printf("Popping from stack : %s\n",stringStack.pop().c_str());
	printf("Pushing \"emily\" onto the stack\n");	
	stringStack.push("emily");
	printf("Peeking from stack : %s\n",stringStack.peek().c_str());	
	printf("Popping from stack : %s\n",stringStack.pop().c_str());
	printf("Popping from stack : %s\n",stringStack.pop().c_str());

	minStack myMinStack;
	printf("Pushing 12 onto the minStack\n");	
	myMinStack.push(12);
	printf("min = %d\n",myMinStack.getMin());
	printf("Pushing 9 onto the minStack\n");	
	myMinStack.push(9);
	printf("min = %d\n",myMinStack.getMin());
	printf("Pushing 15 onto the minStack\n");	
	myMinStack.push(15);
	printf("min = %d\n",myMinStack.getMin());	
	printf("Popping from stack : %d\n",myMinStack.pop());
	printf("min = %d\n",myMinStack.getMin());	
	printf("Popping from stack : %d\n",myMinStack.pop());
	printf("min = %d\n",myMinStack.getMin());	
	printf("Popping from stack : %d\n",myMinStack.pop());


	return 0;
}