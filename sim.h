#ifndef SIM_H_
#define SIM_H_


typedef struct Block{
	size_t tag;
  unsigned int index;
  
  //0 is invalid (empty). 
  //1 is valid.
  //Blocks initialized at 0.
  unsigned int valid;
  struct Block *next;
  struct Block *qnext;

}Block;

/*
typedef struct Queue{
	struct Block *block;
	struct Block *next;
}
*/

int directHit(Block** L, Block* newBlock, char* replace, Block* queue, int cold);
directAdd(Block **L, Block* toAdd);
int assocHit(Block** L, Block* toAdd, int Lsize, Block* queue, int qType, int cold);
assocAdd(Block **L, Block* toAdd, int missType, int cap, Block* queue, int Lsize);
int nassocHit(Block** L, Block* newBlock, int Lsize, int qType, Block* queue, int cold);
nassocAdd(Block** L, Block* newBlock, int Lsize, int qType, Block* queue);

int equals(Block* a, Block* b);
Block* addToQueue(Block* add, Block* queue);
printList(Block* queue);
Block* removeFromQueue();
Block* updateQueue(Block* queue, Block* lastUsed);


#endif
