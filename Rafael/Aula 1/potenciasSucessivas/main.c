//
//  main.c
//  QuadradosSucessivos
//
//  Created by Rafael Ferreira on 12/02/14.
//  Copyright (c) 2014 Rafael Ferreira. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

unsigned potenciasSucessivas(unsigned int, unsigned int);
unsigned int xn(unsigned int, unsigned int);
int count = 0;

int main(int argc, const char * argv[]){
    unsigned int n, x;
    
    printf("-- sum potencias sucessivas --\n");
    
    /* para estar completamente correto falta o do..while */
    printf("Valor de n:");
    scanf("%d", &n);
    scanf("%*[^\n]");
    scanf("%*c");
    
    printf("Valor de x:");
    scanf("%d", &x);
    scanf("%*[^\n]");
    scanf("%*c");
    
    for (int i = 0; i <= n; i++) {
        count = 0;
        printf(" sum(%2d, %2d^i) = %10u e custou %3d operações\n", n, i, potenciasSucessivas(n, i), count);
    }
    
    return 0;
}

unsigned potenciasSucessivas(unsigned int n, unsigned int x){
    unsigned int result = 0;
    for(int i=1; i<=n; i++){
        result += xn(x, i);
        count += 1;
    }
    return result;
}

unsigned int xn(unsigned int x, unsigned int n){
    int i, number=1;
    
    for (i=1; i <= n; i++) {
        number *= x;
        count ++;
    }
    
    return number;
}

