/*******************************************************************************

 Algoritmos de pesquisa ternária (quatro versões repetitivas).

 Autor : António Manuel Adrego da Rocha    Data : Março de 2014

*******************************************************************************/

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

		if (array[fpivot] == value) return fpivot;
		else	if (array[fpivot] > value) max = fpivot - 1;
				else	if (array[spivot] == value) return spivot;
					else	if (array[spivot] > value)
						{
							min = fpivot + 1; max = spivot - 1;
						}
						else min = spivot + 1;
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

		if (array[fpivot] > value) max = fpivot - 1;
		else	if (array[spivot] > value)
				{
					min = fpivot;
					max = spivot - 1;
				}
				else min = spivot;
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

		if (array[fpivot] == value) return fpivot;
		else	if (array[fpivot] > value) max = fpivot - 1;
				else
				{
					if (array[spivot] > value)
					{
						min = fpivot + 1; max = spivot - 1;
					}
					else
					{
						if (array[spivot]  == value) return spivot;
						else min = spivot + 1;
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

		if (array[fpivot] >= value)
		{
			if (array[fpivot] == value) return fpivot;
			max = fpivot - 1;
		}
		else
		{
			if (array[spivot] >= value)
			{
				if (array[spivot] == value) return spivot;
				min = fpivot + 1; max = spivot - 1;
			}
			else min = spivot + 1;
		}
	}

	return -1;
}

