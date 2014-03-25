/* Aulas práticas - Rafael Ferreira */

#include <stdio.h>
#include <stdlib.h>

int TernarySearchV1 (int[], int, int);
int TernarySearchV2 (int[], int, int);
int TernarySearchV3 (int[], int, int);
int TernarySearchV4 (int[], int, int);

int count;

int main(int argc, char* argv[]){
	/* inicializacao do array */
	int n;
	sscanf(argv[1], "%d", &n);
	int array[n];
	int i;
	double media;

	/* preenchimento do array */
	for (i = 0; i < n; i++)
	{
		array[i] = (i+1)*2;
	}

	/* pesquisa de 2 ate 2N */
	/* TernarySearchV1 */
	count = 0;
	for (i = 2; i <= 2*n; i+=2){
		TernarySearchV1(array, n, i);
	}
	media = (double)count/n;
	printf("TernarySearchV1 100 = %2f\n", media);

	/* TernarySearchV2 */
	count = 0;
	for (i = 2; i <= 2*n; i+=2){
		TernarySearchV2(array, n, i);
	}
	media = (double)count/n;
	printf("TernarySearchV2 100 = %2f\n", media);

	/* TernarySearchV3 */
	count = 0;
	for (i = 2; i <= 2*n; i+=2){
		TernarySearchV3(array, n, i);
	}
	media = (double)count/n;
	printf("TernarySearchV3 100 = %2f\n", media);

	/* TernarySearchV4 */
	count = 0;
	for (i = 2; i <= 2*n; i+=2){
		TernarySearchV4(array, n, i);
	}
	media = (double)count/n;
	printf("TernarySearchV4 100 = %2f\n", media);

	return 0;
}


int TernarySearchV1 (int array[], int n, int value)
{
    int min, max, nelem, fpivot, spivot;

	min = 0;
	max = n-1;

	while (min <= max)
	{
		nelem = max - min + 1;

		if (nelem % 3 == 0){
			fpivot = min + (nelem / 3) - 1;
			spivot = min + (2 * nelem / 3) - 1;
		}else{
			fpivot = min + (nelem / 3);
			spivot = min + (2 * nelem / 3);
		}

		count++;
		if (array[fpivot] == value){
			return fpivot;
		}else{
			count++;
			if (array[fpivot] > value){
				max = fpivot - 1;
			}else{
				count++;
				if (array[spivot] == value){
					return spivot;
				}else{
					count++;
					if (array[spivot] > value){
						min = fpivot + 1; max = spivot - 1;
					}else{
					 	min = spivot + 1;
					}
				}
			}
		}
	}

	return -1;
}

int TernarySearchV2 (int array[], int n, int value)
{
    int min, max, nelem, fpivot, spivot;

	min = 0;
	max = n-1;

	while (min < max)
	{
		nelem = max - min + 1;
		fpivot = min + (nelem / 3);
		spivot = min + (2 * nelem / 3);

		count++;
		if (array[fpivot] > value){
			max = fpivot - 1;
		}else{
			count++;
			if(array[spivot] > value){
				min = fpivot;
				max = spivot - 1;
			}else{
				min = spivot;
			}
		}
	}

	count++;
	if (array[min] == value)
		return min;
	else
		return -1;
}

int TernarySearchV3 (int array[], int n, int value)
{
    int min, max, nelem, fpivot, spivot;

	min = 0;
	max = n-1;

	while (min <= max)
	{
		nelem = max - min + 1;
		if (nelem % 3 == 0)
		{
			fpivot = min + (nelem / 3) - 1;
			spivot = min + (2 * nelem / 3) - 1;
		}
		else
		{
			fpivot = min + (nelem / 3);
			spivot = min + (2 * nelem / 3);
		}

		count++;
		if (array[fpivot] == value){
			return fpivot;
		}else{
			count++;
			if(array[fpivot] > value){
				max = fpivot - 1;
			}else{
				count++;
				if (array[spivot] > value){
					min = fpivot + 1; max = spivot - 1;
				}else{
					count++;
					if (array[spivot]  == value)
						return spivot;
					else
						min = spivot + 1;
				}
			}
		}
	}

	return -1;
}

int TernarySearchV4 (int array[], int n, int value)
{
    int min, max, nelem, fpivot, spivot;

	min = 0;
	max = n-1;

	while (min <= max)
	{
		nelem = max - min + 1;
		if (nelem % 3 == 0)
		{
			fpivot = min + (nelem / 3) - 1;
			spivot = min + (2 * nelem / 3) - 1;
		}
		else
		{
			fpivot = min + (nelem / 3);
			spivot = min + (2 * nelem / 3);
		}

		count++;
		if (array[fpivot] >= value){
			count++;
			if (array[fpivot] == value)
				return fpivot;
			max = fpivot - 1;
		}else{
			count++;
			if (array[spivot] >= value)
			{
				count++;
				if (array[spivot] == value) return spivot;
				min = fpivot + 1; max = spivot - 1;
			}
			else min = spivot + 1;
		}
	}

	return -1;
}