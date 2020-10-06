
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <string>


using namespace std;

typedef struct {
	string key;
	int value;
} kvPair;

class hashTable {
private:
	int numEntries;
	list<kvPair> *table;
	hashTable();
public:
	hashTable(int entries);
	~hashTable();
	void insert(string key, int value);
	int  get(string key);
	void remove(string key);
	int hashFunction(string key);
	void dumpHash();
};

