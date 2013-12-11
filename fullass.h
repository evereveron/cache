#ifndef FULLASS_H_
#define FULLASS_H_


#include<stdio.h>
#include<stdlib.h>
#include"sim.h"
#include"datastructs.h"


int directHit(Block** L, int setIndex, int tag){

	/*
	0 is hit
	1 is cold
	2 is con/cap
	*/
	
	int hit;
	
	if(L[index] -> tag == tag){
		//hit
		hit = 1;
	}
	else{
		//miss
		if(L[index]->valid == 0){
			//cold miss
			hit = 1;
		}
		else{
			hit = 2;
		}
	}
	return hit;
}


/*
checks if there is a hit

int qType=1 for LRU
else
	FIFO

also updates queues
assoc hit do we use full address instead???
*/
int assocHit(Block** L, Block* toAdd, int Lsize, Block* queue, int qType){
	
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
	int cap gives info about FIFO/LRU
	Block* queue is the pointer to the start of the queue
	int Lsize is the size of the cache
	
LRU and FIFO add actually same algorithm??
*/
assocAdd(Block **L, Block* toAdd, int missType, int cap, Block* queue, int Lsize){
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
		if(cap == 1){ //LRU
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
int* nassocHit(Block*L){


}
*/
#endif
