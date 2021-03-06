#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include"sim.h"

/*
checks equality.
1 is equal.
0 is not equal.
*/
int equals(Block* a, Block* b){
	if(a -> tag == b-> tag){
		if(a -> index == b-> index){
				return 1;
		}
		else
			return 0;
	}
	else
		return 0;

}

/*
adds to end of queue.
if queue does not exist, creates new queue.
takes in pointer to start of queue and Block to be added.
returns Block
*/
Block* addToQueue(Block* queue, Block* add){
	
	Block* temp = (Block*)malloc(sizeof(Block));
	temp = queue;
	
	while(temp -> next != NULL){
		temp = temp -> next;
	}
	temp -> next = add;
	temp = temp -> next;
	temp -> next = NULL;
	
	
	return queue;
	
}

/*
updates queue for LRU in case of hit
takes in pointer to start of queue
takes in Block pointer to be updated
returns Block*

MAY CAUSE PROBLEMS WITH FREEING
*/
Block* updateQueue(Block* queue, Block* lastUsed){

	Block* temp = (Block*)malloc(sizeof(Block));
	temp = queue;
	Block* head = (Block*)malloc(sizeof(Block));

	if(equals(queue, lastUsed) == 1){

		head = queue->next;
		while(temp->next != NULL){
			temp = temp->next;
		}

		temp->next = lastUsed;
		lastUsed->next = NULL;

		return head;
	}

	while(temp->next->next != NULL){
		if(equals(temp->next, lastUsed) == 1){
			//found the block to update in queue
			break;
		}
		temp = temp->next;
	}

	Block* update = (Block*)malloc(sizeof(Block));
	update = temp->next;
		if(temp->next->next == NULL){
			//block is already in place
			return queue;
		}
	temp->next = temp->next->next;
	update->next = NULL;

	//traverse to end and add update
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = update;
	
	return queue;

}

/*
removes first element from queue.
takes in pointer to start of queue.
returns the new head of the queue.
*/

Block* removeFromQueue(Block* queue){

	Block* removed = queue;
	queue = queue -> next;
	removed->next = NULL;

	return removed;
}


void printList(Block* start){

	Block* temp = start;
	while(temp != NULL){
		printf("%zx\n", temp -> tag);
		temp = temp -> next;
	}
	
	return;
}

/*
int cap is 0 for LRU
else FIFO
*/
int directHit(Block** L, Block* newBlock){

	/*
	0 is hit
	1 is cold
	2 is con/cap
	*/
	
	int hit;
	
	if(L[newBlock->index] == NULL){ //cold miss
		hit = 1;
	
	}
	
	else{
		if(L[newBlock->index] -> tag == newBlock->tag){
			//hit
			hit = 0;
		}
		else{
			hit = 2;
		}
	}
	
	
	
	
	return hit;
}



void directAdd(Block **L, Block* toAdd){
	
	L[toAdd->index] = toAdd;

}


/*
checks if there is a hit

int qType=1 for LRU
else
	FIFO

also updates queues
assoc hit do we use full address instead???
*/
int assocHit(Block** L, Block* toAdd, int Lsize){
	
	/*
   *0 is hit
   *1 is cold
   *2 is cap
   */
	int hit;
	
	int i;
	for(i=0; i<Lsize; i++){
		
		if(L[i] == NULL){
			//cold miss
			hit = 1;
			break;
		}
		
		else if(equals(L[i], toAdd) == 1){ //hit
				hit = 0;
				break;
		}
		
	}

	if(hit != 1 && hit != 0){
		hit = 2;
	}
	return hit;
}

/*
adds a Block to the cache once it's been determined that it was a miss.

takes in several parameters:
	Block** L is the cache level
	Block* toAdd is the block to be added
	int missType gives info about the kind of miss it was
	char* type gives info about FIFO/LRU
	Block* queue is the pointer to the start of the queue
	int Lsize is the size of the cache
	
LRU and FIFO add actually same algorithm??
*/
Block* assocAdd(Block **L, Block* toAdd, Block* queue, int missType, int Lsize){
	int i;

  for(i=0; i<Lsize; i++){
    if(L[i] == NULL){
      L[i] = toAdd;
      return queue;
    }
  }
	
  Block* evict = (Block*)malloc(sizeof(Block));
  evict = queue;
  queue = queue->next;
  for(i=0; i<Lsize; i++){
    if(equals(evict, L[i])== 1){
      L[i] = toAdd;
      break;
    }

  }

	return queue;

}

/*
checks if there is a hit in set associative cache
*/
int nassocHit(Block** L, Block* newBlock, int Lsize, char* qType, int n){
	/*
	0_ hit
	1_ cold miss
	2_ miss
	*/

	
	int hit;

	
	if(L[newBlock->index] == NULL){

		return 1;
	
	}
	else{
		
		Block* temp = (Block*)malloc(sizeof(Block));
		temp = L[newBlock->index];
		int count = 0;
		while(temp != NULL && count<=n){
			//if(equals(temp, newBlock)==1){			
			if(temp->tag == newBlock->tag){	
				if(strcmp(qType, "LRU") == 0){
					L[newBlock->index] = updateQueue(L[newBlock->index], newBlock);
				
				}
				return 0;
			}
			temp = temp->next;
			count++;
		
		}

		if(count < n){
		
			return 1;
		}
		else
		return 2;
	}

}

void nassocAdd(Block** L, Block* newBlock, int n){
	
	if(L[newBlock->index] == NULL){
		//empty, also start of queue

		L[newBlock->index] = newBlock;
		return;
	
	}
	
	else{

		Block* temp = (Block*)malloc(sizeof(Block));
		temp = L[newBlock->index];
		int count = 1;
		
		while(temp->next != NULL){
			temp = temp->next;
			count++;
		
		}

		if(count == n){
			//full. evict first one

			L[newBlock->index] = L[newBlock->index]->next;
			temp = L[newBlock->index];		
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = newBlock;
			
		}
		else{

			//not full
			temp->next = newBlock;
		
		}
	
	
	
	
	}
	

}

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

int numSet(int cacheSize, int blockSize, char* type, int n){
	

	if(strcmp(type, "direct") == 0){ //direct

		return cacheSize/blockSize;
	}
	
	else if(strcmp(type, "assoc") == 0){ //assoc

		return 1;
	}
	
	else{ //set assoc

		return (cacheSize/(n*blockSize));
	}
}

void recurseFree(Block* root){
	if(root != NULL){
		recurseFree(root->next);
	}
	free(root);

}

main(int argc, char *argv[]){


	int numMem =0;
	Block** L1;
	Block** L2;
	Block** L3;
	int L1numSet;
	int L2numSet;
	int L3numSet;
	int L1hitnum = 0;
	int L1miss = 0;
	int L2hitnum = 0;
	int L2miss = 0;
	int L3hitnum = 0;
	int L3miss = 0;
	int L1cold = 0;
	int L2cold = 0;
	int L3cold = 0;
	int L1n;
	int L2n;
	int L3n;
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
	
  	int L1sets = L1size/blockSize;
  	int L2sets = L2size/blockSize;
  	int L3sets = L3size/blockSize;
  	
  	//extract n
	L1n = atoi(argv[4] + 6);
  	L2n = atoi(argv[8] + 6);
  	L3n = atoi(argv[12] + 6);
  	
	Block *L1queue = (Block*)malloc(sizeof(Block));
	Block *L2queue = (Block*)malloc(sizeof(Block));
	Block *L3queue = (Block*)malloc(sizeof(Block));

	L1 = malloc(L1size* sizeof(Block*));
	L2 = malloc(L2size* sizeof(Block*));
	L3 = malloc(L3size* sizeof(Block*));
	
	L1numSet = numSet(L1size, blockSize, L1type, L1n);
	L2numSet = numSet(L2size, blockSize, L2type, L2n);
	L3numSet = numSet(L3size, blockSize, L3type, L3n);

	FILE *fp;
	fp = fopen(argv[15], "r");
	
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
	
	numMem++;
	
	//add to L1
	if(strcmp(L1type, "direct") == 0){
	
		L1[newBlock->index] = newBlock;
		L1cold++;
		L1miss++;
		L1queue = newBlock;
		//printf("%d\n", L1cold);
	}
	else if(strcmp(L1type, "assoc") == 0){
		L1[0] = newBlock;
		L1queue = newBlock;
		L1miss++;
		L1cold++;
	}
	else{

		L1[newBlock->index] = newBlock;
		L1miss++;
		L1cold++;
	
	}
	Block *newBlock2 = (Block*)malloc(sizeof(Block));
	newBlock2 = initBlock(newBlock2, L2numSet, blockSize, num);
	//add to L2
	if(strcmp(L2type, "direct") == 0){
	
		L2[newBlock2->index] = newBlock2;
		L2cold++;
		//printf("%d\n", L1cold);
	}
	else if(strcmp(L2type, "assoc") == 0){
		L2[0] = newBlock2;
		L2queue = newBlock2;
		L2miss++;
		L2cold++;
	}
	else{
		
		L2[newBlock2->index] = newBlock2;
		L2miss++;
		L2cold++;
	
	}

	
	Block *newBlock3 = (Block*)malloc(sizeof(Block));
	newBlock3 = initBlock(newBlock3, L3numSet, blockSize, num);
	//add to L3
	if(strcmp(L3type, "direct") == 0){
	
		L3[newBlock3->index] = newBlock3;
		L3miss++;
		L3cold++;
	}
	else if(strcmp(L3type, "assoc") == 0){
		L3[0] = newBlock3;
		L3queue = newBlock3;
		L3miss++;
		L3cold++;
	}
	else{
		//extract n
		
		L3[newBlock3->index] = newBlock3;
		L3miss++;
		L3cold++;
	
	}
	
	int L1hit;
	int L2hit;
	int L3hit;
	
	
		while(fscanf(fp, "%zx", &num) != EOF){
			
			numMem++;

			
			Block *newBlock = (Block*)malloc(sizeof(Block));
			newBlock = initBlock(newBlock, L1numSet, blockSize, num);
			
			//search L1 for hit;

			
			if(strcmp(L1type, "direct") == 0){
				L1hit = directHit(L1, newBlock);
			}
				
			else if(strcmp(L1type, "assoc") == 0){

				L1hit = assocHit(L1, newBlock, L1sets);	
				if(strcmp(replaceAlg, "LRU") == 0 && L1hit == 0){
					//LRU. update list
					L1queue = updateQueue(L1queue, newBlock);
				}	
			}
			
			else{

				L1hit = nassocHit(L1, newBlock, L1size, replaceAlg, L1n);
			}

			if(L1hit != 0){ //miss

				L1miss++;
				if(L1hit == 1){ //cold miss
					L1cold++;
				}

				
				Block *newBlock2 = (Block*)malloc(sizeof(Block));
				newBlock2 = initBlock(newBlock2, L2numSet, blockSize, num);
				
				//search L2 for hit
				if(strcmp(L2type, "direct") == 0){

					L2hit = directHit(L2, newBlock2);

				}
				else if(strcmp(L2type, "assoc") == 0){

					L2hit = assocHit(L2, newBlock2, L2sets);
					if(strcmp(replaceAlg, "LRU") == 0 && L2hit == 0){

					//LRU. must update list
						L2queue = updateQueue(L2queue, newBlock2);
					}	
				}
				
				else{

					L2hit = nassocHit(L2, newBlock2, L2size, replaceAlg, L2n);
				}
				

				
				if(L2hit != 0){ //miss
				
				
					L2miss++;
					if(L2hit == 1)
						L2cold++;
					
					Block *newBlock3 = (Block*)malloc(sizeof(Block));
					newBlock3 = initBlock(newBlock3, L3numSet, blockSize, num);
			
					//search L3 for hit
					if(strcmp(L3type, "direct") == 0){
					L3hit = directHit(L3, newBlock3);
				
					}
					else if(strcmp(L3type, "assoc") == 0){
						L3hit = assocHit(L3, newBlock3, L3sets);
						if(strcmp(replaceAlg, "LRU") == 0 && L3hit == 0){
							//LRU. update list
							L3queue = updateQueue(L3queue, newBlock3);
						}	
					}
					else{
						L3hit = nassocHit(L3, newBlock3, L3size, replaceAlg, L3n);
					}
					
					if(L3hit != 0){ //miss
						L3miss++;
						if(L3hit == 1)
							L3cold++;
						//add to L3, L2 and L1
						//add to L3
						if(strcmp(L3type, "direct") == 0){
							directAdd(L3, newBlock3);						
						}
						else if(strcmp(L3type, "assoc") == 0){
							L3queue = assocAdd(L3, newBlock3, L3queue, L3hit, L3sets);
							L3queue = addToQueue(L3queue, newBlock3);							
						}
						else{
							nassocAdd(L3, newBlock3, L3n);						
						}
						
						//add to L2
						if(strcmp(L2type, "direct") == 0){
							directAdd(L2, newBlock2);						
						}
						else if(strcmp(L2type, "assoc") == 0){
							L2queue = assocAdd(L2, newBlock2, L2queue, L2hit, L2sets);
							L2queue = addToQueue(L2queue, newBlock2);							
						}
						else{
							nassocAdd(L2, newBlock2, L2n);						
						}
					
						//add to L1
						if(strcmp(L1type, "direct") == 0){
							directAdd(L1, newBlock);
						}
						else if(strcmp(L1type, "assoc") == 0){
							L1queue = assocAdd(L1, newBlock, L1queue, L1hit, L1sets);
							L1queue = addToQueue(L1queue, newBlock);
							
						}
						else{
							nassocAdd(L1, newBlock, L1n);
						
						}
					}
					else{
						L3hitnum++;
						//add to L2
						if(strcmp(L2type, "direct") == 0){
							directAdd(L2, newBlock2);						
						}
						else if(strcmp(L2type, "assoc")  == 0){
							L2queue = assocAdd(L2, newBlock2, L2queue, L2hit, L2sets);
							L2queue = addToQueue(L2queue, newBlock2);							
						}
						else{
							nassocAdd(L2, newBlock2, L2n);						
						}
					
						//add to L1
						if(strcmp(L1type, "direct") == 0){
							directAdd(L1, newBlock);
						}
						else if(strcmp(L1type, "assoc") == 0){
							L1queue = assocAdd(L1, newBlock, L1queue, L1hit, L1sets);
							L1queue = addToQueue(L1queue, newBlock);
							
						}
						else{
							nassocAdd(L1, newBlock, L1n);
						
						}
					}
				}
				else{ //hit L2
				
					L2hitnum++;
					
					//add to L1;
					if(strcmp(L1type, "direct") == 0){
						directAdd(L1, newBlock);
						
					}
					else if(strcmp(L1type, "assoc")  == 0){
						L1queue = assocAdd(L1, newBlock, L1queue, L1hit, L1sets);
						L1queue = addToQueue(L1queue, newBlock);
					}
					else{
						nassocAdd(L1, newBlock, L1n);
						
					}
				}
			}
			else{ //hit L1
				L1hitnum++;
			}

		}
	
		
		printf("Memory accesses: %d\n", numMem);
		printf("L1 Cache hits: %d\n", L1hitnum);
		printf("L1 Cache miss: %d\n", L1miss);
		printf("L2 Cache hits: %d\n", L2hitnum);
		printf("L2 Cache miss: %d\n", L2miss);
		printf("L3 Cache hits: %d\n", L3hitnum);
		printf("L3 Cache miss: %d\n", L3miss);
		printf("L1 Cold misses: %d\n", L1cold);
		printf("L2 Cold misses: %d\n", L2cold);
		printf("L3 Cold misses: %d\n", L3cold);
		printf("L1 Conflict misses: %d\n", 0);
		printf("L1 Capacity misses: %d\n", 0);

		//free queues
		recurseFree(L1queue);
		recurseFree(L2queue);
		recurseFree(L3queue);

		//close file
		fclose(fp);
	}
 	

        return;
}
