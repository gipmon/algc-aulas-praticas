#include <stdio.h>
#include <stdlib.h>

unsigned int potencias(unsigned int, unsigned int); /*alusão à função*/
int count; /*variável global*/

int main(void){
    unsigned int i, n, x, result; int test;

    do{
        printf("Valor de x?");
        test = scanf("%d", &x);
        scanf("%*[^\n]"); scanf("%*c");
        printf("Valor de n?");
        test = scanf("%d", &n);
        scanf("%*[^\n]"); scanf("%*c");
    }while(test == 0);

    for(i = 0; i <= n; i++){
        count = 0;
        result = potencias(x, i);
        printf("Somatorio %2d^%2d = %5u e custou %3d operações\n", x, i, result, count);
    }

    return 0;
}

unsigned int potencias(unsigned int pn, unsigned int n){
    if(n==0){
        return 1;
    }else if(n==1){
        return pn;
    }else{
        count ++;
        return pn * potencias(pn, n-1);
    }
}

