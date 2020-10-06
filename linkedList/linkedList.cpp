#include <stdio.h>
#include <stdlib.h>
#include <map>

class Node {
public:
	int   value;
	Node *next;

	Node(int value) {
		this->value = value;
		this->next = nullptr;
	}


	~Node() {
		delete this->next;
	}
};

class linkedList {
	Node* head;
public:
	linkedList() {
		this->head = nullptr;
	}
	~linkedList() {
	}
	void addNode(Node newNode) {
		if(this->head==nullptr) this->head = &newNode;
		else {
			//traverse through linkedList
			Node *nodePtr = head;
			while(nodePtr->next != nullptr) {
				nodePtr = nodePtr->next;
			}
			nodePtr->next = &newNode;
		}
	}

	void printLL() {
		printf("printing linkedList\n");
		Node *nodePtr = this->head;
		while(nodePtr->next != nullptr) {
			printf("0x%p : %d\n",(void *)nodePtr,nodePtr->value);
			nodePtr = nodePtr->next;
		}
		printf("0x%p : %d\n",(void *)nodePtr,nodePtr->value);
	}

	int returnKthFromLast(int k) {
		Node *headPtr = this->head;
		Node *kPtr = headPtr;
		for(int i=0;i<k;i++) kPtr = kPtr->next;
		while(kPtr->next != nullptr) {
			headPtr = headPtr->next;
			kPtr    = kPtr->next;
		}
		return headPtr->value;
	}

	void deleteNodeAtPos(int pos) {
		if(pos==0) {
			this->head = this->head->next;
			return;
		}
		Node *headPtr;
		headPtr = this->head;
		for(int i=0;i<(pos-1);i++) {
			headPtr = headPtr->next;
		}
		headPtr->next = headPtr->next->next;
	}

	void deleteNodeVal(int nodeVal) {
		Node *headPtr = this->head;
		if(headPtr->value == nodeVal) {
			this->head = headPtr->next;
			return;
		}
		while(headPtr != nullptr) {
			if(headPtr->next->value == nodeVal) {
				headPtr->next = headPtr->next->next;
				return;
			}
			headPtr = headPtr->next;
		}
	}

	void createCycle(int pos) {
		Node *headPtr = this->head;
		//while(headPtr->next != nullptr) headPtr = headPtr->next;
		for(int i=0;i<pos;i++) headPtr = headPtr->next;
		headPtr->next = this->head;
	}

	void detectCycle() {
		std::map<void*,int> nodeMap;
		auto headPtr = this->head;
		int pos = 0;
		while(headPtr->next != nullptr) {
 			else {
				printf("Cycle Detected! Element %d points back to elment %d\n",pos,nodeMap[headPtr]);
				for(auto element : nodeMap) {
					printf("nodeMap[0x%p] = %d\n",element.first,element.second);
				}

				return;
			}
		}
		printf("No Cycle Detected!\n");
		//nodeMap[(void*)this->head] = 0;
		// for(auto element : nodeMap) {
		// 	printf("nodeMap[0x%p] = %d\n",element.first,element.second);
		// }
	}

};

int main() {
	printf("hello, linkedList!\n");
	Node n1 = Node(1);
	Node n2 = Node(2);
	Node n3 = Node(3);
	Node n10 = Node(10);
	linkedList ll = linkedList();
	ll.addNode(n1);
	ll.addNode(n2);
	ll.addNode(n3);
	ll.addNode(n10);
	ll.printLL();
	printf("0th from last value = %d\n",ll.returnKthFromLast(0));
	printf("1st from last value = %d\n",ll.returnKthFromLast(1));
	printf("2nd from last value = %d\n",ll.returnKthFromLast(2));
	//ll.deleteNodeAtPos(1);
	//ll.deleteNodeVal(10);
	ll.printLL();
	//insert new node which causes a cycle
	//Node nCyc = Node(25,);
	//ll.addNode(Node(25,n2));
	//ll.printLL();
	ll.detectCycle();
	ll.createCycle(3);
	//ll.printLL();
	ll.detectCycle();

}