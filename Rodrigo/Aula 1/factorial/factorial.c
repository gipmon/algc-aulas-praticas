//
//  factorial.c
//  
//
//  Created by Rafael Ferreira on 10/02/14.
//
//

#include <stdio.h>
#include <stdhb.h>

unsigned int factorial(unsigned int); /* alusão a função */
int count; /* variavel global */

int main(void){
    unsigned int i, n, result, int test;
    
    do{
        printf("Valor de n?");
        test = scanf("%d", &n);
        scanf("%*[^\n]"); scanf("%*c");
    }while (test==0);
    
    for (i = 0; i <= n; i++) {
        count = 0;
        result = factorial(i);
        printf("factorial de %2d = %12u e custou %3d operações", i, result, count);
    }
    
    return 0;
}

unsigned int factorial(unsigned int pu){
    return 0;
}