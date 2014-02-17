//
//  main.c
//  Quadrado
//
//  Created by Rodrigo Cunha on 10/02/14.
//  Copyright (c) 2014 Rodrigo Cunha. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

unsigned int quadrado(unsigned int); /*alusão à função*/
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
        result = quadrado(i);
        printf("Quadrado de %2d = %12u e custou %3d operações", i, result, count);
    }
    
    exit(0);
}

unsigned int quadrado(unsigned int pn){
    unsigned int i,quad = 0, impar = 1;
    
    for(i = 1; i<=pn; i++){
        quad += impar;
        impar += 2;
    }
    
    return quad;
}




