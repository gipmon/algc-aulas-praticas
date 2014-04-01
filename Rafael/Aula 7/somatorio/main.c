#include <stdio.h>
#include <stdlib.h>

unsigned int somatorio(unsigned int, unsigned int);
unsigned int potencias(unsigned int, unsigned int);
int count;

int main(void){
    unsigned int i, pn, n, test, result;

    do{
        printf("Valor de n?");
        test = scanf("%d", &n);
        scanf("%*[^\n]"); scanf("%*c");
    }while(test == 0);
    do{
        printf("Valor de n?");
        test = scanf("%d", &pn);
        scanf("%*[^\n]"); scanf("%*c");
    }while(test == 0);

    for(i = 0; i <= n; i++){
        count = 0;
        result = somatorio(pn, n);
        printf("Somatório de %2d^2 = %5u e custou %3d operações\n", i, result, count);
    }

    exit(0);
}

unsigned int somatorio(unsigned int pn, unsigned int n){
    if(pn == 0){
        return 0;
    }

    int i, sum = 0;
    for(i = 0; i<=pn; i++){
        sum += potencias(pn, i);
    }

    return sum;
}

unsigned int potencias(unsigned int pn, unsigned int n){
    if(n==0){
        return 1;
    }else if(n==1){
        return pn;
    }else if(n%2==0){
        count += 2;
        return potencias(pn*pn, n/2);
    }else{
        count += 3;
        return pn * potencias(pn*pn, n/2);
    }
}
