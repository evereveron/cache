#include<stdio.h>
#include<stdlib.h>

#include"fullass.h"
#include"sim.h"
#include"datastructs.h"
#include"globals.h"



int logTwo(int num){
	int ans = 0;
	while(num != 1){
		ans++;
		num = num/2;	
	}
	return ans;
}

// Block* queue;
Block* initBlock(Block* block, int numSet, int blockSize, size_t address){
	
	int i;
	i = address % numSet;
	printf("index: %d\n", i);
	
	int setbits = logTwo(numSet) * 4;
	int offbits = logTwo(blockSize) * 4;
	int tagbits = (address/numSet);
	
	size_t masktag;
	masktag = 0xFFFFFFFFFFFF;
	size_t maskset;
	maskset = 0xFFFFFFFFFFFF;
	
	maskset = maskset >> tagbits;
	printf("maskset1: %zx\n", maskset);
	maskset >>= offbits;
	printf("maskset2: %zx\n", maskset);
	maskset <<= offbits;
	printf("maskset: %zx\n", maskset);

	masktag >>= setbits + offbits;
	masktag <<= setbits + offbits;
	printf("masktag: %zx\n", masktag);

	size_t tag = address & masktag;
	size_t index = address & maskset;
	//index <<= tagbits;
	index >>= offbits;
	tag >>= setbits + offbits;
	
	block->tag = tag;
	block->index = index;
	block-> valid = 1;
	return block;
}

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

	Block* block = (Block*)malloc(sizeof(Block));
	block = initBlock(block, 16, 8, 0x89);
	printf("tag: %zx\n", block->tag);
	printf("index: %zx\n", block->index);


}
