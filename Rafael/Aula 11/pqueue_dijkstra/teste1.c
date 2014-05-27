#include <stdio.h>
#include <stdlib.h>
#include "pqueue_dijkstra.h"

int main (void)
{
	PtPQueue pqueue; VERTEX vert;

	if ((pqueue = PQueueCreate (30)) == NULL)
	{
		printf ("Erro na criacao da fila com prioridade\n");
		exit (EXIT_FAILURE);
	}

	printf ("Inserir elementos\n");
	vert.Vertex = 3; vert.Cost = 5;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);
	vert.Vertex = 2; vert.Cost = 4;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);
	vert.Vertex = 1; vert.Cost = 5;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);
	vert.Vertex = 4; vert.Cost = 3;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);
	vert.Vertex = 5; vert.Cost = 2;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);
	vert.Vertex = 6; vert.Cost = 0;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	printf ("\nRetirar elementos\n");
	PQueueDeleteMin (pqueue, &vert);
	printf ("\nRetirado o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);
	PQueueDeleteMin (pqueue, &vert);
	printf ("\nRetirado o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	printf ("\nPromover elementos\n");
	vert.Vertex = 3; vert.Cost = 1;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);
	vert.Vertex = 2; vert.Cost = 2;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);

	printf ("\nDestruir a fila com prioridade e terminar o programa\n\n");
	PQueueDestroy (&pqueue);

	return 0;
}

