#include<stdio.h>
#include<stdlib.h>
#include<sim.h>

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

main(){
	
	error checks

	open file
  
  while(fscanf()!=EOF){
    compute mapping index, tag, etc
    search L1 for hit{
      if(direct)
      if(assoc)
      if(nassoc)
    }

    if(!= hit){ //not in L3
      L1miss++;

      search L2 for hit{
        if(direct)
        if(assoc)
        if(nassoc)

        if(!=hit){ //not in L2
          L2miss++

          search L3 for hit{
            if(direct)
            if(assoc)
            if(nassoc)

            if(!= hit){//not in cache
              L3miss++;
             // add to cache
              if(FIFO)
                //on all 3 levels
              else LRU
                //on all 3 levels
            }
            else{ //in cache L3
              L3hit++;
              if(FIFO)
                //on L1, L2 levels
              else LRU
                //on L1, L2 levels
            }

          }

        }

      }
    }

  }
	


}
