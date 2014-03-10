//
//  main.c
//  QuadradosSucessivos
//
//  Created by Rafael Ferreira on 12/02/14.
//  Copyright (c) 2014 Rafael Ferreira. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

unsigned quadradosSucessivos(unsigned int);
int count = 0;

int main(int argc, const char * argv[]){
    unsigned int n, result;
    
    printf("-- sum quadrados sucessivos --\n");
    
    /* para estar completamente correto falta o do..while */
    printf("Valor de n:");
    scanf("%d", &n);
    scanf("%*[^\n]");
    scanf("%*c");
    
    for (int i = 0; i <= n; i++) {
        count = 0;
        result = quadradosSucessivos(i);
        printf(" sum(n, %2d^2) = %10u e custou %3d operações\n", i, result, count);
    }
    
    return 0;
}

unsigned quadradosSucessivos(unsigned int n){
    unsigned int result = 0;
    for(int i=1; i<=n; i++){
        result += i*i;
        count += 3;
    }
    return result;
}

