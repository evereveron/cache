#include<stdio.h>
#include<stdlib.h>
#include"sim.h"


*Queue buildQueue(*Block first){
	Queue *q = (Queue*)malloc(sizeof(Queue));
	
	q -> block = first;
	q -> next = NULL;

}

/*
adds to end of queue.
if queue does not exist, creates new queue.
takes in pointer to start of queue.
returns nothing.
*/
addToQueue(*Queue q, *Block add){
	*Queue temp = q;
	
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

printQueue(*Queue q){

	*Queue temp = q;
	while(temp != NULL){
		printf("%d\n", temp -> block -> tag);
		temp = temp -> next;
	}
	
	return;
}
