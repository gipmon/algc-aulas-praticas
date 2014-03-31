//
//  main.c
//  Potencias
//
//  Created by Rodrigo Cunha on 13/02/14.
//  Copyright (c) 2014 Rodrigo Cunha. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

unsigned int potencias(unsigned int, unsigned int); /*alusão à função*/
int count; /*variável global*/

int main(void){
    unsigned int i, n, x, result; int test;
    
    do{
        printf("Valor de x?");
        test = scanf("%d", &x);
        scanf("%*[^\n]"); scanf("%*c");
        printf("Valor de n?");
        test = scanf("%d", &n);
        scanf("%*[^\n]"); scanf("%*c");
        
    }while(test == 0);
    
    for(i = 0; i <= n; i++){
        count = 0;
        result = potencias(x, i);
        printf("Somatorio %2d^%2d = %5u e custou %3d operações\n", x, i, result, count);
    }
    
    exit(0);
}

unsigned int potencias(unsigned int pn, unsigned int n){
    unsigned int i,res= 1, som=0;
    if(pn == 0){
        return 0;
    }
    
    for(i = 1; i<=n; i++){
        res *= pn;
        som += res;
        count+=2;
    }
    
    return som;
}

