#include<stdio.h>
#include<stdlib.h>
#include"sim.h"

Block* initBlock(Block* block, int numSet, int blockSize, size_t address){
	
	int index;
	address = address/blockSize;
	index = address % numSet;
	
	size_t tag;
	tag = address/numSet;
	
	block->tag = tag;
	block->index = index;
	block-> valid = 1;
	return block;
}

int numSet(int cacheSize, int blockSize, char* type){
	

	if(strcmp(type, "direct") == 0){ //direct

		return cacheSize/blockSize;
	}
	
	else if(strcmp(type, "assoc") == 0){ //assoc

		return 1;
	}
	
	else{ //set assoc
		//char* num = type[5];
		//int n = strtol(num);
		return (cacheSize/(3*blockSize));
	}
}

main(int argc, char *argv[]){

	Block** L1;
	Block** L2;
	Block** L3;
	int L1numSet;
	int L2numSet;
	int L3numSet;
	int L1hit=0;
	int L1miss=0;
	int L2hit=0;
	int L2miss=0;
	int L3hit=0;
	int L3miss=0;
	int L1cold=0;
	int L2cold=0;
	int L3cold=0;
	int L1n;
	int L2n;
	int L3n;
	int L1numElements;
	int L2numElements;
	int L3numElements;
	size_t num;
	
	/*
   * Error check for incorrect number of arguments.
   */
  
	if(argc != 16 && argc != 2){
		fprintf(stderr, "Error: Improperly formatted input arguments.\n");
		return;
	}

	if(argc == 2){
		if(strcmp(argv[1], "-h") == 0){
			printf("Error, please run program using these input: cache-sim [-h] -l1size <L1 size> -l1assoc <L1 assoc> -l2size <L2 size> -l2assoc <L2 assoc> -l3size <L3 size> -l3assoc <L3 assoc> <block size> <replace alg> <trace file>\n");
		}
	}

	else{
	/*
	*Declare some variables from arguments.
	*/
	int L1size = atoi(argv[2]);
	char* L1type = argv[4];
	int L2size = atoi(argv[6]);
	char* L2type = argv[8];
	int L3size = atoi(argv[10]);
	char* L3type = argv[12];
	int blockSize = atoi(argv[13]);
	char* replaceAlg = argv[14];
	char* file = argv[15];

	L1 = malloc(L1size* sizeof(Block*));
	L2 = malloc(L2size* sizeof(Block*));
	L3 = malloc(L3size* sizeof(Block*));
	
	L1numSet = numSet(L1size, blockSize, L1type);
	L2numSet = numSet(L2size, blockSize, L2type);
	L3numSet = numSet(L3size, blockSize, L3type);

	FILE *fp;
	fp = fopen(file, "r");
	
	/*
	Error check for when the file does not exist.
	*/
	if(fp == 0){
		fprintf(stderr, "Error. Could not open file.\n");
		return 0;
	}

	
	//first element
	fscanf(fp, "%zx", &num);
	Block *newBlock = (Block*)malloc(sizeof(Block));
	newBlock = initBlock(newBlock, L1numSet, blockSize, num);
	
	//add to L1
	if(strcmp(L1type, "direct") == 0){
	
		L1[newBlock->index] = newBlock;
		L1cold++;
		//printf("%d\n", L1cold);
	}
	else if(strcmp(L1type, "assoc") == 0){
		L1[newBlock->index] = newBlock;
		L1cold++;
	}
	else{
		L1[newBlock->index] = newBlock;
		L1cold++;
	
	}
	
	//add to L2
	if(strcmp(L2type, "direct") == 0){
	
		L2[newBlock->index] = newBlock;
		L2cold++;
		//printf("%d\n", L1cold);
	}
	else if(strcmp(L2type, "assoc") == 0){
		L2[newBlock->index] = newBlock;
		L2cold++;
	}
	else{
		L2[newBlock->index] = newBlock;
		L2cold++;
	
	}
	
	//add to L3
	if(strcmp(L3type, "direct") == 0){
	
		L3[newBlock->index] = newBlock;
		L3cold++;
		//printf("%d\n", L1cold);
	}
	else if(strcmp(L1type, "assoc") == 0){
		L3[newBlock->index] = newBlock;
		L3cold++;
	}
	else{
		L3[newBlock->index] = newBlock;
		L3cold++;
	
	}
	
	
	
		while(fscanf(fp, "%zx", &num) != EOF){
			Block *newBlock = (Block*)malloc(sizeof(Block));
			newBlock = initBlock(newBlock, L1numSet, blockSize, num);
			
			

		}





















	}



}
