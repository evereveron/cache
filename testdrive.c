#include<stdio.h>
#include<stdlib.h>
#include"fullass.h"
#include"sim.h"

main(){
	Block *L;
		L = malloc(3* sizeof(Block*));
	Block *L0 = (Block*)malloc(sizeof(Block));
	Block *L1 = (Block*)malloc(sizeof(Block));
	Block *L2 = (Block*)malloc(sizeof(Block));
	
	L[0] = &L0;
	L[1] = &L1;
	L[2] = &L2;
	
	//tag = 0x00
	//index = 2
	int hit = assocHit(L, 0x00, 2);
	
	printf("%d\n", hit);




}
