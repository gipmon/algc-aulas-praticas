#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

void DisplayPQueue(PtPQueue);

int main (void)
{
	PtPQueue pqueue; int status; char filename[21], car; int number;

	system ("clear");
	printf ("\nLer fila com prioridade do ficheiro\n");
	do
	{
  		printf ("Nome do ficheiro -> ");
		status = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (status == 0);

	if ((pqueue = PQueueCreateFile (filename)) == NULL)
	{
		printf ("O ficheiro %s nao existe\n", filename);
		exit (EXIT_FAILURE);
	}

	if (PQueueIsEmpty (pqueue)) printf ("\nfila com prioridade vazia!\n");

	DisplayPQueue(pqueue);

	printf ("\nRetirar elementos\n");
	while (!PQueueIsEmpty (pqueue))
	{
		if (PQueueDeleteMax (pqueue, &number) == OK) 
			printf ("\nMaximo da fila com prioridade = %d\n", number);

		DisplayPQueue(pqueue);

		printf ("\nDeseja retirar mais algum elemento da fila com prioridade? ");
		scanf ("%c", &car); scanf ("%*c");
		if (car != 's') break;
	}

	printf ("\nDestruir a fila com prioridade e terminar o programa\n\n");
	PQueueDestroy (&pqueue);

	return 0;
}


void DisplayPQueue(PtPQueue pfp)
{
	unsigned int dim; int i, elemento; 

	if (!PQueueIsEmpty (pfp))
	{
		PQueueSize (pfp, &dim);

		/* escrita dos elementos da fila com prioridade no monitor */
		printf ("\nConteudo da fila com prioridade\n");
		for (i= 0; i < dim; i++)
		{
			PQueueElement (pfp, &elemento, i);
			printf ("%d\t", elemento);
		}

		printf ("\n");
	}
	else printf ("Fila com prioridade vazia\n");
}

