#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>

using namespace std;

string frequency(string str) {
	string cpy = str;
	sort(cpy.begin(),cpy.end());
	map<char,int> charFreq;
	string ret;
	for(auto c : cpy) {
		charFreq[c] += 1;
	}
	for(auto c : charFreq) {
		printf("%c : %d\n",c.first,c.second);
		ret.push_back(c.first);
		ret.push_back('0' + c.second);
	}
	if(ret.length() > str.length()) return str;
	else return ret;

}

int main() {
	printf("hello, stringCompress!\n");
	string test = "abracadabra";
	printf("frequency = %s\n",frequency(test).c_str());
	test = "abcd";
	printf("frequency = %s\n",frequency(test).c_str());
	test = "alexander";
	printf("frequency = %s\n",frequency(test).c_str());

	return 0;
}