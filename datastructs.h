#ifndef _DATASTRUCTSH_
#define _DATASTRUCTSH_
#include<stdio.h>
#include<stdlib.h>
#include"sim.h"
#include"globals.h"

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
Block* updateQueue(Block* lastUsed){

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
			printf("temp is tag %lx\n", temp->tag);
			temp = temp->next;
		}
		printf("after while temp is tag %lx\n", temp->tag);
		printf("after while lastUsed is tag %lx\n", lastUsed->tag);
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

#endif
