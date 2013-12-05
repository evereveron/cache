#include<stdlib.h>
#include<stdio.h>
#include"sim.h"

int* checkHit(char* assoc, int level){
  /*
   *0_ is hit/miss
   *1_ is cold
   *2_ is cap
   *3_ is conflict
   */
   int hit[4];
  
  /*
   *Level 1.
   */
  if(level = 1){
   /*
    *Direct map.
    */
    if(strcmp(assoc, "direct\n") = 0){
      

    }
    /*
     * Fully associative.
     */
    else if(strcmp(assoc, "assoc\n") = 0){
      
    }
    /*
     *n-way associative.
     */
    else{

    }

  }
  
  /*
   *Level 2.
   */
  if(level = 2){

  }
  
  /*
   *Level 3.
   */
  if(level = 3){

  }

  return hit;
}
