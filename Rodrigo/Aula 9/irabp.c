#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "abp.h"

int main (void)
{
	PtABPNode abp; int st, value, error; char op;

	system ("clear");
	abp = ABPCreate ();

	do
	{
  		printf ("Valor -> ");
		st = scanf ("%d", &value);
		scanf ("%*[^\n]"); scanf ("%*c");

		if (st)
		{
  			printf ("Inserir/Remover-> ");
			scanf ("%c", &op);
			scanf ("%*[^\n]"); scanf ("%*c");
			op = toupper (op);
		}

		if (st)
		{
			if (op == 'I')
			{
				ABPInsertRec (&abp, value);
				if ((error = ABPErrorCode ()) != OK) printf ("Erro a inserir -> %s\n", ABPErrorMessage ());
			}
			else	if (op == 'R')
				{
					ABPDeleteRec (&abp, value);
					if ((error = ABPErrorCode ()) != OK) printf ("Erro a remover -> %s\n", ABPErrorMessage ());
				}
				else
				{
					printf ("Erro na operacao escolhida\n");
					error = 1;
				}

			if (!error)
			{
				printf ("--------------------------------------------------------------------------------------------\n");
				if (ABPEmpty (abp)) printf ("\nArvore vazia!\n");
				else ABPDisplay (abp);
  				printf ("--------------------------------------------------------------------------------------------\n");
			}
		}
	} while (st);

	ABPDestroy (&abp);

	return 0;
}

