#include<stdio.h>
#include<stdlib.h>


typedef struct Block{
  unsigned int tag;
  unsigned int index;
  unsigned int valid;

}Block;

int* checkHit(char* assoc, int level);
