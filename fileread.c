#include<stdio.h>
#include<stdlib.h>

#include"fullass.h"
#include"sim.h"
#include"datastructs.h"
#include"globals.h"

// Block* queue;

main(){
	
	unsigned long num;
	 FILE *fp;
	queue = (Block*)malloc(sizeof(Block));
	 Block **L;
		L = malloc(100* sizeof(Block*));
	 Block* temp = (Block*)malloc(sizeof(Block));
	 
	 fp = fopen("trace.txt", "r");
	 
	 fscanf(fp, "%zx", &num);
	//printf("%lx\n", num);
		Block *newBlock = (Block*)malloc(sizeof(Block));
		newBlock->tag = num;
		newBlock->index = 1;
		queue = newBlock;
		
	 while(fscanf(fp, "%zx", &num) != EOF){
		
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
		
		Block *temp2 = (Block*)malloc(sizeof(Block));
		temp2->tag = 0x3;
		temp2->index = 0x1;
		printf("1st\n");
		Block* temp3 = (Block*)malloc(sizeof(Block));;
		printf("2nd\n");
		temp3->tag = 0x89;
		printf("3rd\n");
		temp3->index = 0x1;
		queue = updateQueue(temp2);
		queue = updateQueue(temp3);
		Block *removed = removeFromQueue();
		
		printf("removed tag: %zx\n", removed->tag);
		printList(queue);


}
