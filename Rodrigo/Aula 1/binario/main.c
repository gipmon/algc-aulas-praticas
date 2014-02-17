//
//  main.c
//  Binario
//
//  Created by Rodrigo Cunha on 11/02/14.
//  Copyright (c) 2014 Rodrigo Cunha. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

unsigned int binario(unsigned int); /*alusão à função*/
int count; /*variável global*/

int main(void){
    unsigned int i, n, result; int test;
    
    do{
        printf("Valor de n?");
        test = scanf("%d", &n);
        scanf("%*[^\n]"); scanf("%*c");
    }while(test == 0);
    
    for(i = 0; i <= n; i++){
        count = 0;
        result = binario(i);
        printf("%2d em binário -> %12u e custou %3d operações\n", i, result, count);
    }
    
    exit(0);
}

unsigned int binario(unsigned int pn){
    unsigned int res=0, bit, shift = 1;
    
    if(pn == 0 || pn == 1){
        return pn;
    }
    
    do{
        bit = pn % 2;
        pn /= 2;
        res += bit * shift;
        shift *= 10;
        count+=5;
    }while(pn >= 1);
    
    return res;
}

