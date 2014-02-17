// main.c suma de elementos de um array

#include <stdio.h>
#include <stdlib.h>

unsigned int sumElemInArray(unsigned int[], int);
int count = 0;

int main(void){
	unsigned int array[] = {1, 2, 3, 4};
	printf("Sumatório: %2d\n", sumElemInArray(array, 4));
}

unsigned int sumElemInArray(unsigned int a[], int length){
	unsigned int sum = 0, i;
	for(i = 0; i<length; i++){
		sum += a[i];
	}
	return sum;
}