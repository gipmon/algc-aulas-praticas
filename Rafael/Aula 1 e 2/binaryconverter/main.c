//  main.c
//  xn
//
//  Created by Rafael Ferreira on 10/02/14.
//  Copyright (c) 2014 Rafael Ferreira. All rights reserved.

#include <stdio.h>
#include <stdlib.h>

unsigned int dectobin(unsigned int);
int main(void);
int count;

int main(void){
    unsigned int n, result;
    
    printf("-- base10 to binary --\n");
    
    /* para estar completamente correto falta o do..while */
    printf("Valor de n:");
    scanf("%d", &n);
    scanf("%*[^\n]");
    scanf("%*c");
    
    for (int i = 0; i <= n; i++) {
        count = 0;
        result = dectobin(i);
        printf(" %2d = %10u e custou %3d operações\n", i, result, count);
    }
    
    return 0;
}

unsigned int dectobin(unsigned int dec){
    if(dec==0 || dec==1){
        return dec;
    }
    
    unsigned int result=0, bit, shift = 1;
    
    do{
        bit = dec%2;
        dec /= 2;
        
        result += bit*shift;
        shift *= 10;
        count+=5;
    }while(dec >= 1);
 
    return  result;
}