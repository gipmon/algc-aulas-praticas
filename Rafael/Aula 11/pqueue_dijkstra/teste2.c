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

	vert.Vertex = 1; vert.Cost = 0;
	PQueueInsert (pqueue, &vert);
	printf ("Inserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 2; vert.Cost = 100;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 3; vert.Cost = 100;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 4; vert.Cost = 100;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 5; vert.Cost = 100;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 6; vert.Cost = 100;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 7; vert.Cost = 100;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 8; vert.Cost = 100;
	PQueueInsert (pqueue, &vert);
	printf ("\nInserido o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	PQueueDeleteMin (pqueue, &vert);
	printf ("\nRetirado o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 2; vert.Cost = 10;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);

	vert.Vertex = 3; vert.Cost = 5;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);

	vert.Vertex = 6; vert.Cost = 5;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);

	PQueueDeleteMin (pqueue, &vert);
	printf ("\nRetirado o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 2; vert.Cost = 9;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);

	vert.Vertex = 4; vert.Cost = 8;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);

	PQueueDeleteMin (pqueue, &vert);
	printf ("\nRetirado o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 4; vert.Cost = 6;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);

	vert.Vertex = 8; vert.Cost = 7;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);

	PQueueDeleteMin (pqueue, &vert);
	printf ("\nRetirado o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 2; vert.Cost = 8;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);

	PQueueDeleteMin (pqueue, &vert);
	printf ("\nRetirado o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	vert.Vertex = 5; vert.Cost = 10;
	printf ("\nPromovido o vertice %d com novo custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDecrease (pqueue, &vert);
	PQueueDisplay(pqueue);

	PQueueDeleteMin (pqueue, &vert);
	printf ("\nRetirado o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	PQueueDeleteMin (pqueue, &vert);
	printf ("\nRetirado o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	PQueueDeleteMin (pqueue, &vert);
	printf ("\nRetirado o vertice %d com custo %d --- Fila -> ", vert.Vertex, vert.Cost);
	PQueueDisplay(pqueue);

	if (!PQueueIsEmpty (pqueue)) 
		printf ("\nAsneira a fila com prioridade devia estar vazia\n\n");

	printf ("\n\nDestruir a fila com prioridade e terminar o programa\n\n");
	PQueueDestroy (&pqueue);

	return 0;
}

