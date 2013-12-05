#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include"sim.h"

/*
 *Global variables
 */
Block* L1;
Block* L2;
Block* L3;
int memNum;
int L1hit;
int L1miss;
int L2hit;
int L2miss;
int L3hit;
int L3miss;
int L1cold;
int L2cold;
int L3cold;
int L1con;
int L2con;
int L3con;
int L1cap;
int L2cap;
int L3cap;
int L1numElements;
int L2numElements;
int L3numElements;

main(int argc, char* argv[]){

  FILE *trace;

  /*
   * Error check for incorrect number of arguments.
   */
  if(argv[]){
    fprintf(stderr, "Error: Improperly formatted input arguments.\n");
    return;
  }
  
  /*
   *Help.
   */
  if(argv[1] = h){
    printf("\n");
    return;
  }

  /*
   *Declare some variables from arguments.
   */
  int L1size = argv[3]
  char* L1assoc = argv[4];
  int L2size = argv[7];
  char* L2assoc = argv[8];
  int L3size = argv[11];
  char* L3assoc = argv[12];
  int blockSize = argv[13];
  char* replaceAlg = argv[14];

  /*
   *Open file.
   */
  trace = fopen(argv[15], "r");

  /*
   *Check for nonexistent file.
   */
  if(trace == 0){
    fprintf(stderr, "Error: Could not open file.\n");
    return;
  }
  
  /*
   *While loop scans addresses from file.
   */
  while(fscanf(trace, "%lx", %num) != EOF){
   
   /*
    *L1 direct mapped cache.
    */
   if(strcmp(L1assoc, "direct\n") = 0){
      

    }
    /*
     *L1 fully associative cache.
     */
    else if(strcmp(L1assoc, "assoc\n") = 0){
      int i = 0;
      while(L1[i] != NULL){
        i++;
      }
      L1[i] = (Block*)malloc(sizeof(Block));

    }
    /*
     *L1 n-way associative cache.
     */
    else{

    }
  }



}
