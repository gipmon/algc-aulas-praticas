#include <stdio.h>
#include <stdlib.h>

int nMults;
int catalanRecursive(unsigned int);
int catalanDinamic(unsigned int);

int main(void){
    int n,i;

    do{
        printf("Insira o valor de n: ");
        scanf("%d", &n);
    }while(n<0);

    printf("\n");
    printf(" %-5s |%-8s |%-14s |%-14s \n","n","Catalan (n)","M(n) Rec","M(n) Din");
    printf("------------------------------------------------\n");

    for (i=0;i<=n;i++){
        nMults = 0;
        printf(" %-6d| %-11d", i, catalanRecursive(i));
        printf("| %-14d", nMults);

        nMults = 0;
        catalanDinamic(i);
        printf("| %-14d\n",nMults);
    }

    return 0;
}

int catalanRecursive(unsigned int n){
    int i;
    int sum = 0;

    if (n == 0) {
        return 1;
    }else{
        for(i = 0; i < n; i++){
            nMults++;
            sum += catalanRecursive(i) * catalanRecursive(n - i - 1);
        }
    }

    return sum;
}

int catalanDinamic(unsigned int n){
    int i, j;
    int array[n];

    array[0] = 1;
    for(i = 1; i <= n; i++){
        array[i] = 0;
        for(j = 0; j < i; j++){
            nMults++;
            array[i] += array[j] * array[i - j - 1];
        }
    }
    return array[n];
}
