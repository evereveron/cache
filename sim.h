#ifndef SIM_H_
#define SIM_H_


typedef struct Block{
  unsigned int tag;
  unsigned int index;
  
  //0 is invalid (empty). 
  //1 is valid.
  //Blocks initialized at 0.
  unsigned int valid;
  struct Block *next;

}Block;

/*
typedef struct Queue{
	struct Block *block;
	struct Block *next;
}
*/

int assocHit(Block** L, int tag, int index);
int equals(Block* a, Block* b);
Block* addToQueue(Block* add, Block* queue);
printList(Block* queue);
Block* removeFromQueue(Block* queue);


#endif
