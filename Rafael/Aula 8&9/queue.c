/************** Implementa��o Din�mica Gen�rica - queue.c **************/

#include <stdlib.h>
#include <string.h>
#include "queue.h"	/* ficheiro de interface da fila */

/*************** Defini��o do Estrutura de Dados da Fila ***************/

typedef struct node *PtNode;
 
struct node	/* defini��o de um n� da lista */
{
	void *PtElem;	/* ponteiro para o elemento gen�rico */
	PtNode PtNext;	/* ponteiro para o n� seguinte */
};

struct queue	/* defini��o da fila */
{
	unsigned int Size;	/* tamanho em n�mero de bytes de cada elemento */
	PtNode Head, Tail;	/* cabe�a e cauda da fila */
};

/********************** Defini��o dos Subprogramas *********************/

PtQueue QueueCreate (unsigned int psize)
{
	PtQueue Queue;

	if (psize == 0) return NULL;
	if ((Queue = (PtQueue) malloc (sizeof (struct queue))) == NULL)
		return NULL;	/* alocar mem�ria para a fila */
	Queue->Size = psize;	/* armazenar o tamanho dos elementos */
	Queue->Head = NULL;	/* inicializar a cabe�a da fila */
	Queue->Tail = NULL;	/* inicializar a cauda da fila */
	return Queue;		/* devolver a refer�ncia da fila acabada de criar */
}

int QueueDestroy (PtQueue *pqueue)
{
	PtQueue TmpQueue = *pqueue; PtNode TmpNode;

	if (TmpQueue == NULL) return NO_QUEUE;
	while (TmpQueue->Head != NULL)
	{				/* libertar a mem�ria ocupada pelos elementos da fila */
		TmpNode = TmpQueue->Head;
		TmpQueue->Head = TmpQueue->Head->PtNext;
		free (TmpNode->PtElem);
		free (TmpNode);
	}
	free (TmpQueue);	/* libertar a mem�ria ocupada pela fila */
	*pqueue = NULL;	/* colocar a refer�ncia da fila a NULL */
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
