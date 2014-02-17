//
//  main.c
//  somatorio
//
//  Created by Rodrigo Cunha on 17/02/14.
//  Copyright (c) 2014 Rafael Ferreira. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

unsigned int somatorio(unsigned int); /*alusão à função*/
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
        result = somatorio(i);
        printf("Somatório de %2d^2 = %5u e custou %3d operações", i, result, count);
    }
    
    exit(0);
}

unsigned int somatorio(unsigned int pn){
    unsigned int i,quad = 0, impar = 1, som = 0;
    
    if(pn == 0){
        return 0;
    }
    for(i = 1; i<=pn; i++){
        quad += impar;
        impar += 2;
        som += quad;
        count += 3;
    }
    
    return som;
}

