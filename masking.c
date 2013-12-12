#include<stdio.h>
#include<stdlib.h>
//#include"fullass.h"
//#include"sim.h"
//#include"datastructs.h"

int logTwo(unsigned long number) {
	if (number == 0) {
		return -1;
	}
	int counter = 0;
	while (number != 1) {
		counter++;
		number = number / 2;
	}
	return counter;
}

main(){
	
	size_t number = 0x7fff00689190;
	//printf("%zx\n", number);
	int tagbits =(9+4)*4;
	int setbits = 2*4;
	int offsetbits = 1*4;
	
	size_t maskset;
	maskset = 0xFFFFFFFFFFFF;
	
	maskset <<= tagbits;
	maskset >>= tagbits;
	maskset >>= offsetbits;
	maskset <<= offsetbits;
	
	size_t masktag;
	masktag = 0xFFFFFFFFFFFF;
	masktag >>= setbits + offsetbits;
	masktag <<= setbits + offsetbits;
	//printf("%zx\n", masktag);
	
	size_t tag = number & masktag;
	size_t set = number & maskset;
	
	printf("%zx\n", tag);
	printf("%zx\n", set);
	
	
	

}
