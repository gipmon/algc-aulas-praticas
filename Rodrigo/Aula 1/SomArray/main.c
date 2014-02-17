#include <stdio.h>
#include <stdlib.h>

unsigned int array(int*, unsigned int);
int count;

int main(void){
	unsigned int i, n, result, length;
	int num[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	count = 0;
	length = 10;
	result = array(num, length);		
	printf("Soma dos elementos do array é %2d e custou %5u operações.\n", result, count);
	
}

unsigned int array(int array[], unsigned int length){
	unsigned int i, som = 0;
	for(i = 0; i<length; i++){
		som += array[i];
		count++;
	}
	return som;
}