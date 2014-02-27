//
//  main.c
//  Fibonacci
//
//  Created by Rafael Ferreira on 10/02/14.
//  Copyright (c) 2014 Rafael Ferreira. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

unsigned int fibonacci(unsigned int);
int main(void);
int count;

int main(void){
    unsigned int i, n, result;
    int test;
    
    do{
        printf("Valor de n:");
        test = scanf("%d", &n);
        scanf("%*[^\n]"); scanf("%*c");
    }while (test==0);
    
    for (i = 0; i <= n; i++) {
        count = 0;
        result = fibonacci(i);
        printf("fibonacci de %2d = %3u e custou %3d operações\n", i, result, count);
    }
    
    return 0;
}

unsigned int fibonacci(unsigned int number){
    unsigned int i, next, preview = 0, atual = 1;
    
    if(number==0){
        return 0;
    }
    
    for (i = 2; i <= number; i++) {
        next = preview + atual;
        preview = atual;
        atual = next;
        count++;
    }
    
    return atual;
}