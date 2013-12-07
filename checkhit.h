#include<stdio.h>
#include<stdlib.h>
#include"sim.h"

/*
int* directHit(Block* L){



}
*/

int assocHit(Block* L, int tag, int index){
	
	/*
   *0 is hit
   *1 is cold
   *2 is cap
   */
	int hit;
	
	if(L[index].tag == tag){
		//hit
		hit = 1;
	}
	else{
		//miss
		
		if(L[index].valid == 0){
			//cold miss
			hit = 1;
		}
		else{
			hit = 2;
		}
	}
	return hit;
}

/*
int* nassocHit(Block*L){


}
*/
