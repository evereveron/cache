#ifndef _DATASTRUCTSH_
#define _DATASTRUCTSH_
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

	if(queue == NULL){
		printf("first\n");
		return add;
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
updates queue for LRU in case of hit
takes in pointer to start of queue
takes in Block pointer to be updated
returns nothing
*/
updateQueue(Block* queue, Block* lastUsed){

	Block* temp = queue;
	
	//account for head
	if(equals(temp, lastUsed) == 1){
		queue = queue->next;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = lastUsed;
		lastUsed->next = NULL;
		return;
	}
	
	while(temp->next != NULL){
		if(equals(temp->next, lastUsed) == 1){
			//found the block to update in queue
			break;
		}
		temp = temp->next;
	}
	Block* update = temp->next;
		if(temp->next->next == NULL){
			//block is already in place
			return;
		}
	temp->next = temp->next->next;
	update->next = NULL;
	
	//traverse to end and add update
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = update;
	

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


printList(Block* start){

	Block* temp = start;
	while(temp != NULL){
		printf("%d\n", temp -> tag);
		temp = temp -> next;
	}
	
	return;
}

#endif
