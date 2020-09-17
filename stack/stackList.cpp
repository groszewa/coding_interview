#include "stack.h"

template <class T>
class stackList {
private:
	std::vector< stack<T> > stacks;
	int maxStackSize;
	int curTopPtr;
public:
	stackList(int maxStackSize) : maxStackSize(maxStackSize), curTopPtr(0){
		stacks.push_back(stack<T>());
	}

	~stackList() {
		stacks.clear();
	}

	void push(T val) {
		if(stacks[curTopPtr].getSize()==maxStackSize) {
			curTopPtr++;
			stacks.push_back(stack<T>());
			printf("PUSH : incrementing curTopPtr to %d\n",curTopPtr);
		}
		printf("PUSH : pushing %d onto stacks[%d]\n",val,curTopPtr);
		stacks[curTopPtr].push(val);
	}

	T pop() {
		if(stacks[curTopPtr].getSize()==0) {
			curTopPtr--;
			printf("POP  : decrementing curTopPtr to %d\n",curTopPtr);
		}
		T retVal = stacks[curTopPtr].pop();
		printf("POP  : stacks[%d] popped %d\n",curTopPtr,retVal);
		return retVal;
	}

	T peek() {
		auto retVal = stacks[curTopPtr].peek();
		printf("PEEK : stacks[%d] peeked %d\n",curTopPtr,retVal);
		return retVal;
	}
	bool isEmpty() {
		for(auto subStack : stacks) {
			if(!subStack.isEmpty()) return false;
		}
		return true;
	}
	int getSize() {
		int sizeTotal = 0;
		for(auto subStack : stacks) {
			sizeTotal += subStack.getSize();
		}
		printf("Total size = %d\n",sizeTotal);
		return sizeTotal;
	}
};




int main() {
	printf("hello, stackList!\n");
	stackList<int> sl(3);
	printf("isEmpty : %d\n",sl.isEmpty());
	sl.push(1);
	printf("isEmpty : %d\n",sl.isEmpty());	
	sl.getSize();
	sl.push(2);
	sl.getSize();
	sl.push(3);
	printf("isEmpty : %d\n",sl.isEmpty());	
	sl.getSize();	
	sl.push(4);
	sl.getSize();
	sl.push(5);
	sl.getSize();
	sl.pop();
	sl.getSize();
	sl.pop();
	sl.getSize();
	sl.pop();
	sl.getSize();
	sl.peek();
	sl.getSize();
	sl.peek();
	sl.getSize();
	sl.pop();
	sl.getSize();
	sl.pop();
	sl.getSize();
	printf("isEmpty : %d\n",sl.isEmpty());


	return 0;
}