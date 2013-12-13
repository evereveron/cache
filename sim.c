#include<stdio.h>
#include<stdlib.h>
#include"sim.h"

/*
checks equality.
1 is equal.
0 is not equal.
*/
int equals(Block* a, Block* b){
	if(a -> tag == b-> tag){
		if(a -> index == b-> index){
			if(a-> valid == b ->valid){
				return 1;
			}
			else
				return 0;
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
returns Block* bc of empty queue case
*/
Block* addToQueue(Block* queue, Block* add){
	
	//queue does not exist
	//if(equals(queue, add) == 1){
		
		//printf("%d\n", queue->tag);
		//printf("%d\n", add->tag);
	/*
	if(queue == NULL){
		printf("first\n");
		queue = add;
		printf("%d\n", queue->tag);
		return queue;
	}
	*/
	Block* temp = queue;
	
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
returns nothing

MAY CAUSE PROBLEMS WITH FREEING
*/
Block* updateQueue(Block* queue, Block* lastUsed){

	Block* temp = queue;
	Block* head;
	
	printf("queue tag %d\n", queue->tag);
	printf("queue index %d\n", queue->index);
	printf("lastUsed tag %d\n", lastUsed->tag);
	printf("lastUsed index %d\n", lastUsed->index);
	
	//account for head
	//if(queue->tag == lastUsed->tag && queue->index == lastUsed->index){
	if(equals(queue, lastUsed) == 1){
		printList(queue);
		printf("first\n");
		head = queue->next;
		while(temp->next != NULL){
			printf("temp is tag %zx\n", temp->tag);
			temp = temp->next;
		}
		printf("after while temp is tag %zx\n", temp->tag);
		printf("after while lastUsed is tag %zx\n", lastUsed->tag);
		temp->next = lastUsed;
		lastUsed->next = NULL;
		printList(head);
		return head;
	}
	printf("1x\n");
	while(temp->next != NULL){
		if(equals(temp->next, lastUsed) == 1){
			//found the block to update in queue
			break;
		}
		temp = temp->next;
	}
	
	printf("2x\n");
	Block* update = temp->next;
		if(temp->next->next == NULL){
			//block is already in place
			return queue;
		}
	temp->next = temp->next->next;
	update->next = NULL;
	
	printf("3x\n");
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

Block* removeFromQueue(){

	Block* removed = queue;
	queue = queue -> next;
	removed->next = NULL;

	return removed;
}


printList(Block* start){
	printf("printlist \n");
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
int directHit(Block** L, Block* newBlock, char* replace, Block* queue, int cold){

	/*
	0 is hit
	1 is cold
	2 is con/cap
	*/
	
	int hit;
	
	if(L[newBlock->index] -> tag == newBlock->tag){
		//hit
		hit = 1;
		if(strcmp(replace, "LRU")==0){
			updateQueue(queue, newBlock);
		}
	}
	else{
		//miss
		if(L[newBlock->index]->valid == 0){
			//cold miss
			hit = 1;
			addToQueue(queue, newBlock);
			cold++;
		}
		else{
			hit = 2;
			addToQueue(queue, newBlock);
		}
	}
	return hit;
}



directAdd(Block **L, Block* toAdd){
	
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
int assocHit(Block** L, Block* toAdd, int Lsize, Block* queue, int qType, int cold){
	
	/*
   *0 is hit
   *1 is cold
   *2 is cap
   */
	int hit;
	
	int i;
	for(i=0; i<Lsize; i++){
		//miss
		
		if(L[i]->valid == 1){
			//something in Block
			if(equals(L[i], toAdd) == 1){
				hit = 0;
				if(qType == 1){
					//LRU. must update list
					updateQueue(queue, toAdd);
					break;
				}
			}
				
		}
		else if(L[i]->valid == 0){
			//cold miss
			hit = 1;
			cold++;
			addToQueue(queue, toAdd);
			break;
		}
	}

	if(hit != 1 && hit != 0){
		//capacity miss
		hit = 2;
		addToQueue(queue, toAdd);
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
assocAdd(Block **L, Block* toAdd, int missType, char* type, Block* queue, int Lsize){
	int i;
	
	if(missType == 1){ //cold miss
		for(i=0; i<Lsize; i++){
			if(L[i]->valid == 0){
				break;
			}
		}
		L[i] = toAdd;
		L[i]->valid = 1;
		queue = addToQueue(queue, L[i]);
	}
	else{ //capacity miss
		if(strcmp(type, ""){ //LRU
			//remove from queue
			Block* removed = removeFromQueue(queue);
			int i;
			for(i=0; i<Lsize; i++){
				if(L[i]->tag == removed->tag && L[i]->index == removed->index){
					L[i] = toAdd;
					queue = addToQueue(queue, L[i]);
				}
				else{
					printf("error: not in cache, method fullass.h, assocAdd LRU add\n");
				}
			}
		
		}
		else{ //FIFO
			//remove from queue
			Block* removed = removeFromQueue(queue);
			int i;
			for(i=0; i<Lsize; i++){
				if(L[i]->tag == removed->tag && L[i]->index == removed->index){
					L[i] = toAdd;
					queue = addToQueue(queue, L[i]);
				}
				else{
					printf("error: not in cache, method fullass.h, assocAdd fifo add\n");
				}
			}
		}
	}
	

}

/*
checks if there is a hit in set associative cache
*/
int nassocHit(Block** L, Block* newBlock, int Lsize, int qType, Block* queue, int cold){
	/*
	0_ hit
	1_ cold miss
	2_ miss
	*/

	int hit;
	if(L[newBlock->index]->valid == 1){
		Block* temp = L[newBlock->index];
		while(temp != NULL){
			if(equals(temp, newBlock) == 1){
				//hit
				hit = 0;
				if(qType == 0){
					updateQueue(queue, newBlock);
				}
				break;
			}
		}
		//miss
		hit = 2;
		addToQueue(queue, newBlock);
	}
	else{
		//cold miss
		hit = 1;
		cold++;
		addToQueue(queue, newBlock);
	}

}

nassocAdd(Block** L, Block* newBlock, int Lsize, char* qType, Block* queue, int n){
	
	if(L[newBlock->index]->valid == 0){
		//nothing in that index yet
		L[newBlock->index] = newBlock;
		//THIS IS ALSO START OF QUEUE;
	}
	else{
		//already something in index
		Block* temp = (Block*)malloc(sizeof(Block));
		int count = 0;
		while(temp != NULL && count <= n){
			temp = temp->next;
			count++;
		}
		if(count<n){
			//still room in list
			temp->next = newBlock;
			//no need to update queue;
		}
		else{
			//no room in list, must evict
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

	int numMem =0;
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
	
	Block *L1queue = (Block*)malloc(sizeof(Block));
	Block *L2queue = (Block*)malloc(sizeof(Block));
	Block *L3queue = (Block*)malloc(sizeof(Block));

	L1 = malloc(L1size* sizeof(Block*));
	L2 = malloc(L2size* sizeof(Block*));
	L3 = malloc(L3size* sizeof(Block*));
	
	L1numSet = numSet(L1size, blockSize, L1type);
	L2numSet = numSet(L2size, blockSize, L2type);
	L3numSet = numSet(L3size, blockSize, L3type);

	//extract n
	//n = atoi(argv[6]+6);

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
	
	numMem++;
	//add to L1
	if(strcmp(L1type, "direct") == 0){
	
		L1[newBlock->index] = newBlock;
		L1cold++;
		L1queue = newBlock;
		//printf("%d\n", L1cold);
	}
	else if(strcmp(L1type, "assoc") == 0){
		assocAdd(L1, newBlock, 1, 
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
	
	int L1hit;
	int L2hit;
	int L3hit;
	
	
		while(fscanf(fp, "%zx", &num) != EOF){
		
			numMem++;
			
			Block *newBlock = (Block*)malloc(sizeof(Block));
			newBlock = initBlock(newBlock, L1numSet, blockSize, num);
			
			//search L1 for hit;
			if(strcmp(L1type, "direct" == 0)){
				L1hit = directHit(L1, newBlock, replaceAlg, queueL1, L1cold);
				
			}
			else if(strcmp(L2type, "assoc" == 0)){
				L1hit = assocHit(L1, newBlock, replaceAlg, queueL1, L1cold);
			}
			else{
				L1hit = nassocHit(L1, newBlock, replaceAlg, queueL1, L1cold);
			}
			
			if(L1hit != 0){ //miss
				L1miss++
				
				//search L2 for hit
				if(strcmp(L2type, "direct" == 0)){
					L2hit = directHit(L2, newBlock, replaceAlg, queueL2, L2cold);
				
				}
				else if(strcmp(L2type, "assoc" == 0)){
					L2hit = assocHit(L2, newBlock, replaceAlg, queueL2, L2cold);
				}
				else{
					L2hit = nassocHit(L2, newBlock, replaceAlg, queueL2, L2cold);
				}
				
				if(L2hit != 0){ //miss
					L2miss++;
					
					//search L3 for hit
					if(strcmp(L3type, "direct" == 0)){
					L3hit = directHit(L3, newBlock, replaceAlg, queueL3, L3cold);
				
					}
					else if(strcmp(L3type, "assoc" == 0)){
						L3hit = assocHit(L3, newBlock, replaceAlg, queueL3, L3cold);
					}
					else{
						L3hit = nassocHit(L3, newBlock, replaceAlg, queueL3, L3cold);
					}
					
					if(L3hit != 0){ //miss
						L3miss++;
						//add to L2 and L1
					
					}
					else{
						L3hit++;
						//add to L2
						if(strcmp(L2type, "direct")) == 0){
							directAdd(L2, newBlock);
						
						}
						else if(strcmp(L2type, "assoc"))  == 0){
							assocAdd(L2, newBlock);
							
						}
						else{
							nassocAdd(L2, newBlock);
						
						}
					
						//add to L1
						if(strcmp(L1type, "direct")) == 0){
							directAdd(L1, newBlock);
						
						}
						else if(strcmp(L2type, "assoc"))  == 0){
							assocAdd(L1, newBlock);
							
						}
						else{
							nassocAdd(L1, newBlock);
						
						}
					}
				}
				else{ //hit L2
					L2hit++;
					
					//add to L1;
					if(strcmp(L1type, "direct")) == 0){
						directAdd(L1, newBlock);
						
					}
					else if(strcmp(L2type, "assoc"))  == 0){
						assocAdd(L1, newBlock);
							
					}
					else{
						nassocAdd(L1, newBlock);
						
					}
				}
			}
			else{ //hit L1
				L1hit++;
			}

		}
		
		printf("Memory accesses: %d\n", numMem);
		printf("L1 Cache hits: %d\n", L1hit);
		printf("L1 Cache miss: %d\n", L1miss);
		printf("L2 Cache hits: %d\n", L2hit);
		printf("L2 Cache miss: %d\n", L2miss);
		printf("L3 Cache hits: %d\n", L3hit);
		printf("L3 Cache miss: %d\n", L3miss);
		printf("L1 Cold misses: %d\n", L1cold);
		printf("L2 Cold misses: %d\n", L2cold);
		printf("L3 Cold misses: %d\n", L3cold);
		printf("L1 Conflict misses: %d\n", 0);
		printf("L1 Capacity misses: %d\n", 0);



	}
 	fclose(fp);

        return;
}

