#include<stdio.h>
#include<stdlib.h>

int hammingDistance(unsigned int a, unsigned int b) {
	int count = 0;
	unsigned int y = a^b;
	//printf("size of unsigned int = %lu\n",sizeof(y));
	unsigned int mask = 0x1;
	for(int i=0;i<8*((int)sizeof(unsigned int));i++) {
		count += ((mask&y)!=0);
		//printf("mask = 0x%x\n",mask);
		//printf("y    = 0x%x\n",y);
		mask <<= 1;

	}
	return count;
}

int main() {
	int hd = hammingDistance(4,5);
	printf("hammingDistance : (4,5) : %d\n",hd);
	hd = hammingDistance(0x0,0xffffffff);
	printf("hammingDistance : (0,ffffffff) : %d\n",hd);

	return 0;
}