//
//  main.c
//  Factorial
//
//  Created by Rodrigo Cunha on 10/02/14.
//  Copyright (c) 2014 Rodrigo Cunha. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

unsigned int factorial(unsigned int); /*alusão à função*/
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
        result = factorial(i);
        printf("Factorial de %2d = %12u e custou %3d operações\n", i, result, count);
    }
    
    exit(0);
}

unsigned int factorial(unsigned int pn){
    unsigned int fact = 1;
    
    if(pn == 0 || pn == 1){
        return 1;
    }else{
        fact = pn*factorial(pn-1);
        count++;
    }
    
    return fact;
    
}

