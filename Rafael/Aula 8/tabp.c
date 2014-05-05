#include <stdio.h>
#include <stdlib.h>
#include "abp.h"

int main (void)
{
	PtABPNode abp1, abp2, abp3; int st; char filename[21];

	system ("clear");
	printf ("\nLer arvore binaria de pesquisa do ficheiro\n");
	do
	{
  		printf ("Nome do ficheiro -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);

	abp1 = ABPCreateFile (filename);

	/*
	if (ABPEmpty (abp1)) printf ("\nArvore vazia!\n");
	*/

	printf ("\nNumero de nos da arvore = %d\n", ABPSize (abp1));

	printf ("\nAltura da arvore = %d\n", ABPHeight (abp1));

	printf ("\nArvore listada em pre-ordem (versao recursiva)\n");
	ABPPreOrderRec (abp1);
	printf ("\n");

	printf ("\nArvore listada em ordem (versao recursiva)\n");
	ABPInOrderRec (abp1);
	printf ("\n");

	printf ("\nArvore listada em pos-ordem (versao recursiva)\n");
	ABPPostOrderRec (abp1);
	printf ("\n");

	printf ("\nArvore listada em pre-ordem (versao repetitiva)\n");
	ABPPreOrderRep (abp1);
	printf ("\n");

	printf ("\nArvore listada em ordem (versao repetitiva)\n");
	ABPInOrderRep (abp1);
	printf ("\n");

	printf ("\nArvore listada em pos-ordem (versao repetitiva)\n");
	ABPPostOrderRep (abp1);
	printf ("\n");

	printf ("\nArvore listada por niveis\n");
	ABPByLevel (abp1);
	printf ("\n");

	printf ("\nArvore listada hierarquicamente\n");
	ABPDisplay (abp1);
	printf ("\n");

	printf ("\nBalanceamento da arvore\n");
	abp2 = ABPBalance (abp1);

	printf ("\nNumero de nos da arvore = %d\n", ABPSize (abp2));

	printf ("\nAltura da arvore = %d\n", ABPHeight (abp2));

	printf ("\nArvore listada hierarquicamente\n");
	ABPDisplay (abp2);
	printf ("\n");

	/* printf ("\nCopia da arvore\n");
	   abp3 = ABPCopy (abp1); */

	printf ("\nNumero de nos da arvore = %d\n", ABPSize (abp3));

	printf ("\nAltura da arvore = %d\n", ABPHeight (abp3));

	printf ("\nArvore listada em ordem (versao recursiva)\n");
	ABPInOrderRec (abp3);
	printf ("\n");

	printf ("\nDestruir as arvores e terminar o programa\n\n");
	ABPDestroy (&abp1);
	ABPDestroy (&abp2);
	ABPDestroy (&abp3);

	return 0;
}

