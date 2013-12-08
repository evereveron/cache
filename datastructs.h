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
returns nothing.
*/
*Block addToQueue(Block* start, Block* add){
	
	//queue does not exist
	if(equals(start, add) = 1{
		
	}
	
	*Block temp = start;
	
	while(temp -> next != NULL){
		temp = temp -> next;
	}
	Queue *addq = (Queue*)malloc(sizeof(Queue))
	temp -> next = add;
	temp = temp -> next;
	temp -> next = NULL;
	
	
	return;
	
}

/*
removes first element from queue.
takes in pointer to start of queue.
returns the new head of the queue.

*/
*Queue removeFromQueue(){

}

printQueue(Queue* q){

	Block* temp = q;
	while(temp != NULL){
		printf("%d\n", temp -> block -> tag);
		temp = temp -> next;
	}
	
	return;
}
