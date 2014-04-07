#include <stdio.h>
#include <stdlib.h>

unsigned int somatorio(unsigned int, unsigned int); /*alusão à função*/
int count; /*variável global*/

int main(void){
    unsigned int i, n, x, result=0; int test;
    
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
        result += somatorio(x, i);
        printf("Somatorio %2d^%2d = %5u e custou %3d operações\n", x, i, result, count);
    }
    
    exit(0);
}

unsigned int somatorio(unsigned int pn, unsigned int n){
    int som = 0;
    if(n == 0){
        return 1;
    }else if(n == 1){
        return pn;
    }else if(n%2 == 0){
        count += 2;
        som += somatorio(pn*pn, n/2);
    }else{
        count += 3;
        som = som + (pn * (somatorio(pn*pn, n/2)));
    }

    return som;
  
}

