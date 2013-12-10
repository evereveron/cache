#include<stdio.h>
#include<stdlib.h>
#include"fullass.h"
#include"sim.h"
#include"datastructs.h"




main(){
	
	//Block* queue = (Block*)malloc(sizeof(Block));
	
	Block **L;
		L = malloc(6* sizeof(Block*));
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
		L2->index = 2;
		L2->valid = 1;
	Block *L3 = (Block*)malloc(sizeof(Block));
		L3->tag = 0x04;
		L3->index = 2;
		L3->valid = 1;
	Block *L4 = (Block*)malloc(sizeof(Block));
		L4->tag = 0x05;
		L4->index = 3;
		L4->valid = 1;
	Block *L5 = (Block*)malloc(sizeof(Block));
		L5->tag = 0x06;
		L5->index = 4;
		L5->valid = 1;
	
	Block* queue = L0;
	
	L[0] = L0;
	L[1] = L1;
	L[2] = L2;
	L[3] = L3;
	L[4] = L4;
	L[5] = L5;
	int i;
	for(i=1; i<6; i++){
		Block* temp = queue;
		while(temp != NULL){
			temp = temp->next;
		}
		temp->next = L[i];
	}
	
	updateQueue(queue, L0);

	/*
	Block* temp = removeFromQueue(queue);
	printf("%d\n", temp->tag);
	temp = removeFromQueue(queue);
	printf("%d\n", temp->tag);
	
	int test = queue->tag;
	printf("%d\n", test);
	
	*/
	printList(L0);
	
	//tag = 0x00
	//index = 2
	//int hit = assocHit(L, 0x00, 2);
	
	//printf("%d\n", hit);




}
