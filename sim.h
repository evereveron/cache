#include<stdio.h>
#include<stdlib.h>


typedef struct Block{
  unsigned int tag;
  unsigned int index;

}Block;

int* checkHit(char* assoc, int level);
