#include<stdio.h>
#include<stdlib.h>
#include"fullass.h"
#include"sim.h"
#include"datastructs.h"




main(){
	int Lsize = 3;
	Block* queue = (Block*)malloc(sizeof(Block));
	
	Block **L;
		L = malloc(3* sizeof(Block*));
	Block *L0 = (Block*)malloc(sizeof(Block));
		L0->tag = 0x01;
		L0->index = 0;
		L0->valid = 1;
	Block *L1 = (Block*)malloc(sizeof(Block));
		L1->tag = 0x02;
		L1->index = 1;
		L1->valid = 1;
	Block *L2 = (Block*)malloc(sizeof(Block));
		L2->tag = 0x03;
		L2->index = 0;
		L2->valid = 1;
	
	
	L[0] = L0;
	addToQueue(L0);
	L[1] = L1;
	addToQueue(L1);
	L[2] = L2;
	addToQueue(L2);
	
	printList();
	
	//tag = 0x00
	//index = 2
	//int hit = assocHit(L, 0x00, 2);
	
	//printf("%d\n", hit);




}
