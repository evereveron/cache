#include<stdio.h>
#include<stdlib.h>
#include"sim.h"
#include"datastructs.h"

/*
int* directHit(Block* L){



}
*/

int assocHit(Block** L, int tag, int index){
	
	/*
   *0 is hit
   *1 is cold
   *2 is cap
   */
	int hit;
	
	if(L[index] -> tag == tag){
		//hit
		hit = 1;
	}
	else{
		//miss
		
		if(L[index] ->valid == 0){
			//cold miss
			hit = 1;
		}
		else{
			hit = 2;
		}
	}
	return hit;
}


assocAdd(Block **L, int newtag, int newindex, int newhit, int cap, Block* queue){
	int i;
	
	if(hit == 1){ //cold miss
		for(i=0; i<Lsize; i++){
			if(L[i]->valid == 0){
				break;
			}
		}
		L[i]->tag = newtag;
		L[i]->index = newindex;
		L[i]->valid = 1;
		queue = addToQueue(queue, L[i]);
	}
	else{ //capacity miss
		if(cap == 1){ //LRU
		
		
		}
		else{ //FIFO
			//remove from queue
			Block* removed = removeFromQueue(queue);
			int i;
			for(i=0; i<Lsize; i++){
				if(L[i]->tag == removed->tag && L[i]->index == removed->index){
					L[i]->tag = newtag;
					L[i]->index = newindex;
					queue = addToQueue(queue, L[i]);
				}
				else{
					printf("error: fullass.h, assocAdd fifo add\n");
				}
			}
		}
	}
	

}

/*
int* nassocHit(Block*L){


}
*/
