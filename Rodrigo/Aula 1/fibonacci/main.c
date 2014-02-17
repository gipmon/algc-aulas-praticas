//
//  main.c
//  Fibonacci
//
//  Created by Rodrigo Cunha on 10/02/14.
//  Copyright (c) 2014 Rodrigo Cunha. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

unsigned int fibonacci(unsigned int); /*alusão à função*/
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
        result = fibonacci(i);
        printf("Fibonacci de %2d = %12u e custou %3d operações", i, result, count);
    }
    
    exit(0);
}

unsigned int fibonacci(unsigned int pn){
    unsigned int i, preview = 0, actual = 1, next;
    if(pn == 0){
        return 0;
    }
    for(i = 2; i <= pn; i++){
        next = preview + actual;
        preview = actual;
        actual = next;
        count++;
    }
    
    return actual;
}


