#include<stdio.h>
#include<stdlib.h>
#include"sim.h"

test(Block** L, Block* toAdd){

Block *temp = (Block*)malloc(sizeof(Block));

	temp = L[0];
	L[0] = L[1];
	L[1] = temp;

}

main(){
	Block** L = malloc(5* sizeof(Block*));
	Block *toAdd = (Block*)malloc(sizeof(Block));
	
	if(L[0] == NULL){
	printf("valid\n");
	}
	
	
	toAdd->tag = 1;
	toAdd->index = 2;
	toAdd->valid= 1;
	
	Block *to = (Block*)malloc(sizeof(Block));
	to->tag =2;
	L[0] = toAdd;
	L[1] = to;
	
	if(L[0] != NULL){
	printf("valid2\n");
	}
	
	test(L, toAdd);
	printf("after test: %d\n", L[0]->tag);
	printf("%d\n", L[1]->tag);
	
}
