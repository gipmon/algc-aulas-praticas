#include <iostream>
#include <string>

int main(){
	char array[] = {'a', 'b'};
	char vogais[]= {'r', 'a'};
	int i = 0;
	for (; i < 2; i++){
		if(vogais[array[i]]){
			printf("EXISTE\n");
		}else{
			printf("NÃO EXISTE\n");
		}
	}
	return 0;
}
