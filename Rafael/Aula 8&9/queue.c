/************** Implementação Dinâmica Genérica - queue.c **************/

#include <stdlib.h>
#include <string.h>
#include "queue.h"	/* ficheiro de interface da fila */

/*************** Definição do Estrutura de Dados da Fila ***************/

typedef struct node *PtNode;
 
struct node	/* definição de um nó da lista */
{
	void *PtElem;	/* ponteiro para o elemento genérico */
	PtNode PtNext;	/* ponteiro para o nó seguinte */
};

struct queue	/* definição da fila */
{
	unsigned int Size;	/* tamanho em número de bytes de cada elemento */
	PtNode Head, Tail;	/* cabeça e cauda da fila */
};

/********************** Definição dos Subprogramas *********************/

PtQueue QueueCreate (unsigned int psize)
{
	PtQueue Queue;

	if (psize == 0) return NULL;
	if ((Queue = (PtQueue) malloc (sizeof (struct queue))) == NULL)
		return NULL;	/* alocar memória para a fila */
	Queue->Size = psize;	/* armazenar o tamanho dos elementos */
	Queue->Head = NULL;	/* inicializar a cabeça da fila */
	Queue->Tail = NULL;	/* inicializar a cauda da fila */
	return Queue;		/* devolver a referência da fila acabada de criar */
}

int QueueDestroy (PtQueue *pqueue)
{
	PtQueue TmpQueue = *pqueue; PtNode TmpNode;

	if (TmpQueue == NULL) return NO_QUEUE;
	while (TmpQueue->Head != NULL)
	{				/* libertar a memória ocupada pelos elementos da fila */
		TmpNode = TmpQueue->Head;
		TmpQueue->Head = TmpQueue->Head->PtNext;
		free (TmpNode->PtElem);
		free (TmpNode);
	}
	free (TmpQueue);	/* libertar a memória ocupada pela fila */
	*pqueue = NULL;	/* colocar a referência da fila a NULL */
	return OK;
}

int QueueEnqueue (PtQueue pqueue, void *pelem)
{
	PtNode TmpNode;

	if (pqueue == NULL) return NO_QUEUE;
	if ((TmpNode = (PtNode) malloc (sizeof (struct node))) == NULL)
		return NO_MEM;
	if ((TmpNode->PtElem = malloc (pqueue->Size)) == NULL)
	{ free (TmpNode); return NO_MEM; }
	TmpNode->PtNext = NULL;
	if (pqueue->Tail == NULL) pqueue->Head = TmpNode;
	else pqueue->Tail->PtNext = TmpNode;
	pqueue->Tail = TmpNode;
	memcpy (pqueue->Tail->PtElem, pelem, pqueue->Size);	/* colocar */
	return OK;
}

int QueueDequeue (PtQueue pqueue, void *pelem)
{
	PtNode TmpNode;

	if (pqueue == NULL) return NO_QUEUE;
	if (pqueue->Head == NULL) return QUEUE_EMPTY;
	if (pelem == NULL) return NULL_PTR;
	memcpy (pelem, pqueue->Head->PtElem, pqueue->Size);	/* retirar */
	TmpNode = pqueue->Head;
	pqueue->Head = pqueue->Head->PtNext;
	if (pqueue->Head == NULL) pqueue->Tail = NULL;
	free (TmpNode->PtElem);
	free (TmpNode);
	return OK;
}

int QueueIsEmpty (PtQueue pqueue)
{
	if (pqueue == NULL) return NO_QUEUE;
	if (pqueue->Head == NULL) return QUEUE_EMPTY;
	return OK;
}
