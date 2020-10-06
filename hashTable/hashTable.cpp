#include "hashTable.h"

hashTable::hashTable(int entries) : numEntries(entries) {
	table = new list<kvPair>[numEntries];
}

hashTable::~hashTable() {
	//delete table
	// for(int i=0;i<numEntries;i++) {
	// 	delete table[i];
	// }
}

int hashTable::hashFunction(string key) {
	int sum = 0;
	for(int k=0;k<key.length();k++) sum += int(key[k]);
	return sum % numEntries;
}

void hashTable::dumpHash() {
	for(int i=0;i<numEntries;i++) {
		printf("[%d]",i);
		for(auto x : table[i]) {
			printf(" --> {%s,%d}",x.key.c_str(),x.value);
		}
		printf("\n");
	}
}

void hashTable::insert(string key, int value) {
	int keyHash = hashFunction(key);
	kvPair kv;
	kv.key = key;
	kv.value = value;
	table[keyHash].push_back(kv);
}

int hashTable::get(string key) {
	int keyHash = hashFunction(key);
	for(auto x : table[keyHash]) {
		if(x.key == key) {
			printf("get :: hashTable[%s] = %d\n",key.c_str(),x.value);
			return x.value;
		}
	}
	printf("get :: key %s does not exist in hashTable!\n",key.c_str());
	return -1;
}

void hashTable::remove(string key) {
	int keyHash = hashFunction(key);
	for(auto iptr = table[keyHash].begin(); iptr != table[keyHash].end(); iptr++) {
		if((*iptr).key == key) table[keyHash].erase(iptr);
	}
}

int main() {
	printf("hello, hashTable!\n");
	hashTable h(5);
	h.insert("hello",3);
	h.insert("alex",12);
	h.insert("emily",15);
	h.insert("nicky",33);
	h.insert("barbara",99);
	h.insert("livia",82);
	h.insert("gastone",123);
	h.insert("martin",44);
	h.insert("debby",43);
	h.dumpHash();
	h.get("alex");
	h.get("hello");
	h.get("walter");
	h.get("nicky");
	h.remove("gastone");
	h.dumpHash();
	return 0;
}