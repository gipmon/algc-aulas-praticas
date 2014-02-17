//  main.c
//  xn
//
//  Created by Rafael Ferreira on 10/02/14.
//  Copyright (c) 2014 Rafael Ferreira. All rights reserved.

#include <stdio.h>
#include <stdlib.h>

unsigned int xn(unsigned int, unsigned int);
int main(void);
int count;

int main(void){
    unsigned int i, x, n, result;
    
    printf("-- x^n --\n");
    
    /* para estar completamente correto falta o do..while */
    printf("Valor de x:");
    scanf("%d", &x);
    scanf("%*[^\n]");
    scanf("%*c");
    
    printf("Valor de n:");
    scanf("%d", &n);
    scanf("%*[^\n]");
    scanf("%*c");
    
    
    for (i = 0; i <= x; i++) {
        count = 0;
        result = xn(i, n);
        printf(" %2d^%2d = %5u e custou %3d operações\n",i, n, result, count);
    }
    
    return 0;
}

unsigned int xn(unsigned int x, unsigned int n){
    int i, number=1;
    
    for (i=1; i <= n; i++) {
        number *= x;
        count ++;
    }
    
    return number;
}