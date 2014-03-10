#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "set.h"

void WriteSet (PtSet);

int main (void)
{
	PtSet set1 = NULL, set2 = NULL, set3 = NULL;
	char filename[21], car; int st; 

	system ("clear");
	printf ("\nler conjunto do ficheiro\n");
	do
	{
  		printf ("Nome do ficheiro -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);

	set1 = SetCreateFile (filename);
	printf ("\nconjunto lido do ficheiro %s\n", filename);
	WriteSet (set1);

	printf ("\nler conjunto do teclado [# para terminar]\n");

	set2 = SetCreate ();
	do
	{
		do
		{
			printf ("Elemento do conjunto? "); st = scanf ("%c", &car);
			scanf ("%*[^\n]"); scanf ("%*c");
		} while (st == 0);
		car = toupper (car);
		if (isupper(car)) SetInsertElement (set2, car);
	} while (car != '#');

	printf ("\nconjunto lido do teclado\n");
	WriteSet (set2);

	printf ("\nescrever conjunto no ficheiro\n");
	do
	{
  		printf ("Nome do ficheiro -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);
	SetStoreFile (set2, filename);

	set3 = SetReunion (set1, set2);
	printf ("\nconjunto reuniao\n");
	WriteSet (set3);

	SetDestroy (&set3);
	set3 = SetIntersection (set1, set2);
	printf ("\nconjunto interseccao\n");
	WriteSet (set3);

	printf ("\ndestruir os conjuntos e terminar o programa\n");
	SetDestroy (&set1);
	SetDestroy (&set2);
	SetDestroy (&set3);

	WriteSet (set3);

	return 0;
}

void WriteSet (PtSet pset)
{
  unsigned int cardinal, i; 

  if (pset == NULL) return;  /* verifica se o conjunto existe */

  cardinal = SetCardinal (pset);

  printf ("{ ");
  /* escrita dos elementos do conjunto */
  for (i = 1; i <= cardinal; i++) printf ("%c ", SetObserveElement (pset, i));
  printf ("}\n");
}
