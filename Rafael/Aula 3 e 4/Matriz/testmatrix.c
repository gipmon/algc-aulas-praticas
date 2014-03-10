#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void WriteMatrix (PtMatrix);

int main (void)
{
	PtMatrix mat1 = NULL, mat2 = NULL, mat3 = NULL;
	char filename[21]; unsigned int nl, nc, l, c; int st, elem;

	system ("clear");
	printf ("\nler matriz do ficheiro\n");
	do
	{
  		printf ("Nome do ficheiro -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);
	mat1 = MatrixCreateFile (filename);
	MatrixSize (mat1, &nl, &nc);

	printf ("\nmatriz lida do ficheiro %s com %d linhas e %d colunas\n", filename, nl, nc);
	WriteMatrix (mat1);

	printf ("\nler matriz do teclado\n");
	do
	{
		printf ("Número de linhas da matriz? "); scanf ("%d", &nl);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (nl <= 0) ;

	do
	{
		printf ("Número de colunas da matriz? "); scanf ("%d", &nc);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (nc <= 0) ;

	mat2 = MatrixCreate (nl, nc);

  	for (l = 0; l < nl; l++)
    		for (c = 0; c < nc; c++)
        	{
			do
			{
				printf("Matriz[%d,%d] = ", l+1, c+1);
				st = scanf ("%d", &elem);
				scanf ("%*[^\n]"); scanf ("%*c");
			} while (st == 0);
			MatrixModifyElement (mat2, l, c, elem);
		}

	printf ("\nmatriz lida do teclado\n");
	WriteMatrix (mat2);

	printf ("\nescrever matriz no ficheiro\n");
	do
	{
  		printf ("Nome do ficheiro -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);
	MatrixStoreFile (mat2, filename);

	mat3 = MatrixTranspose (mat2);
	printf ("\nmatriz transposta da matriz lida do telado\n");
	WriteMatrix (mat3);

	MatrixDestroy (&mat3);
	mat3 = MatrixAddition (mat1, mat2);
	printf ("\nmatriz soma\n");
	WriteMatrix (mat3);
	
	MatrixDestroy (&mat3);
	mat3 = MatrixSubtraction (mat1, mat2);
	printf ("\nmatriz soma\n");
	WriteMatrix (mat3);


	MatrixDestroy (&mat3);
	mat3 = MatrixMultiplication (mat1, mat2);
	printf ("\nmatriz produto\n");
	WriteMatrix (mat3);

	printf ("\ndestruir as matrizes e terminar o programa\n");
	MatrixDestroy (&mat1);
	MatrixDestroy (&mat2);
	MatrixDestroy (&mat3);

	WriteMatrix (mat3);

	return 0;
}

void WriteMatrix (PtMatrix pmat)
{
  unsigned int l, c, nl, nc;

  MatrixSize (pmat, &nl, &nc);

  for (l = 0; l < nl; l++)
    for (c = 0; c < nc; c++)
      printf ("%4d ", MatrixObserveElement (pmat, l, c));
}
