#include<stdio.h>
#include<stdlib.h>
#include"sim.h"

int test(Block* b){
	printf("%d\n", b->tag);
	int a = b->tag;
	a++;
	b->tag = a;
	return a;
}

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
Block* addToQueue(Block* start, Block* add){
	
	//queue does not exist
	if(equals(start, add) == 1){
		return start;
	}
	
	Block* temp = start;
	
	while(temp -> next != NULL){
		temp = temp -> next;
	}
	temp -> next = add;
	temp = temp -> next;
	temp -> next = NULL;
	
	
	return start;
	
}

/*
No point in this, must return head of new queue,
as well as removed element =(

removes first element from queue.
takes in pointer to start of queue.
returns the new head of the queue.

Block* removeFromQueue(Block* start){


	return start;
}
*/

printQueue(Block* start){

	Block* temp = start;
	while(temp != NULL){
		printf("%d\n", temp -> tag);
		temp = temp -> next;
	}
	
	return;
}
