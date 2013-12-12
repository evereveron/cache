#include<stdio.h>
#include<stdlib.h>

#include"fullass.h"
#include"sim.h"
#include"datastructs.h"

main(){
	
	unsigned long num;
	 FILE *fp;
	 Block* queue = (Block*)malloc(sizeof(Block));
	 Block **L;
		L = malloc(100* sizeof(Block*));
	 Block* temp = (Block*)malloc(sizeof(Block));
	 
	 fp = fopen("trace.txt", "r");
	 
	 fscanf(fp, "%lx", &num);
	//printf("%lx\n", num);
		Block *newBlock = (Block*)malloc(sizeof(Block));
		newBlock->tag = num;
		newBlock->index = 1;
		queue = newBlock;
		
	 while(fscanf(fp, "%lx", &num) != EOF){
		
		//printf("%lx\n", num);
		Block *newBlock = (Block*)malloc(sizeof(Block));
		newBlock->tag = num;
		newBlock->index =1;
		temp = queue;
	
		while(temp -> next != NULL){
			temp = temp -> next;
		}
		temp -> next = newBlock;
		temp = temp -> next;
		temp -> next = NULL;
	 }
	 printList(queue);
		
		Block *temp2;
		temp2->tag = 0x3;
		temp2->index = 0x1;
		queue = updateQueue(queue, temp2);
		
		
		printList(queue);


}
