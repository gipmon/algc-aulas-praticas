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
        printf("Fibonacci de %2d = %12u e custou %3d operações\n", i, result, count);
    }
    
    exit(0);
}

unsigned int fibonacci(unsigned int pn){
    if(pn == 0){
        return 0;
    }else if(pn == 1){
        return 1;
    }else{
        count++;
        return fibonacci(pn-1)+fibonacci(pn-2);

    }
}


