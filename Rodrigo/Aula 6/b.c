#include <stdio.h>
#include <stdlib.h>

int TernarySearchV1 (int[], int, int);
int TernarySearchV2 (int[], int, int);
int TernarySearchV3 (int[], int, int);
int TernarySearchV4 (int[], int, int);

int count;

int main(int argc, char* argv[]){
	int n,i;
	sscanf(argv[1],"%d",&n);
	int array[n];
	double media;

	count = 0;

	/* preenchimento do array */

	for(i = 0; i<n; i++){
		array[i] = (i+1)*2;
	}

	/* pesquisa no array de 2 até 2N */

	/* TernarySearchV1 */
	for(i = 1; i<= (n*2)+1; i++){
		TernarySearchV1(array,n,i);
	}
	media = (double)count/((2*n)+1);
	printf("TernarySearchV1 (100) = %2f\n", media);
	count = 0;

	/* TernarySearchV2 */
	for(i = 1; i<= (n*2)+1; i++){
		TernarySearchV2(array,n,i);
	}
	media = (double)count/((2*n)+1);
	printf("TernarySearchV2 (100) = %2f\n", media);
	count = 0;

	/* TernarySearchV3 */
	for(i = 1; i<= (n*2)+1; i++){
		TernarySearchV3(array,n,i);
	}
	media = (double)count/((2*n)+1);
	printf("TernarySearchV3 (100) = %2f\n", media);
	count = 0;

	/* TernarySearchV4 */
	for(i = 1; i<= (n*2)+1; i++){
		TernarySearchV4(array,n,i);
	}
	media = (double)count/((2*n)+1);
	printf("TernarySearchV4 (100) = %2f\n", media);


}

int TernarySearchV1 (int array[], int n, int value)
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
		}
		else{
			count++;
			if (array[fpivot] > value)
		 		max = fpivot - 1;
			else{
				count++;
				if (array[spivot] == value) 
					return spivot;
				else {
					count++;
					if (array[spivot] > value)
					{
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
		if (array[fpivot] > value) max = fpivot - 1;
		else{
			count++;
			if (array[spivot] > value)
				{
					min = fpivot;
					max = spivot - 1;
				}
				else min = spivot;
		} 
	}

	if (array[min] == value) return min;
	else return -1;
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
		if (array[fpivot] == value) return fpivot;
		else{
			count++;
			if (array[fpivot] > value) max = fpivot - 1;
			else
			{
				count++;
				if (array[spivot] > value)
				{
						min = fpivot + 1; max = spivot - 1;
				}
				else
				{
					count++;
					if (array[spivot]  == value) return spivot;
					else min = spivot + 1;
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
		if (array[fpivot] >= value)
		{
			count++;
			if (array[fpivot] == value) return fpivot;
			max = fpivot - 1;
		}
		else
		{
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

