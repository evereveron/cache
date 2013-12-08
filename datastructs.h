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
	if(equals(queue, add) == 1){
		return queue;
	}
	
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


printQueue(Block* start){

	Block* temp = start;
	while(temp != NULL){
		printf("%d\n", temp -> tag);
		temp = temp -> next;
	}
	
	return;
}
