/******* Implementação da Fila com Prioridade com um Amontoado Binário ********/
/***** Fila com Prioridade orientada aos mínimos Nome: pqueue_dijkstra.c  *****/

#include <stdio.h>
#include <stdlib.h>

#include "pqueue_dijkstra.h"  /* Interface */

/******* Definição do Estrutura de Dados da Fila com Prioridade ********/

struct pqueue  /* definição da Fila com Prioridade */
{
  unsigned int HeapSize;  /* capacidade de armazenamento da Fila */
  unsigned int NumElem;  /* número de elementos armazenados na Fila */
  VERTEX *Heap;  /* ponteiro para o monte a alocar dinamicamente */
};

/********************** Definição dos Subprogramas *********************/

PtPQueue PQueueCreate (unsigned int pdim)
{
  PtPQueue PQueue;

  if (pdim == 0) return NULL;

  /* alocar memória para a Fila com Prioridade */
  if ((PQueue = (PtPQueue) malloc (sizeof (struct pqueue))) == NULL) return NULL;

  if ((PQueue->Heap = (VERTEX *) calloc (pdim, sizeof (VERTEX))) == NULL)
  { free (PQueue); return NULL; }

  PQueue->HeapSize = pdim;  /* armazenar a dimensão da Fila */
  PQueue->NumElem = 0;  /* inicializar o número de elementos da Fila */

  return PQueue;  /* devolver a referência da Fila acabada de criar */
}


int PQueueDestroy (PtPQueue *ppqueue)
{
  PtPQueue TmpPQueue = *ppqueue;

  if (TmpPQueue == NULL) return NO_PQUEUE;

  free (TmpPQueue->Heap);  /* libertar a memória ocupada pelo amontoado */
  free (TmpPQueue);  /* libertar a memória ocupada pela Fila */

  *ppqueue = NULL;  /* colocar a referência da Fila a NULL */

  return OK;
}


int PQueueInsert (PtPQueue ppqueue, VERTEX *pelem)
{
  unsigned int I;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == ppqueue->HeapSize) return PQUEUE_FULL;

  /* ajustar o amontoado, descendo os pais com custo maior do que o custo do elemento */
  for (I = ppqueue->NumElem; I > 0 && ppqueue->Heap[(I+1)/2-1].Cost > (*pelem).Cost; I = (I+1)/2-1)
    ppqueue->Heap[I] = ppqueue->Heap[(I+1)/2-1];  /* descer o pai com custo maior do que o custo do novo elemento */

  ppqueue->Heap[I] = *pelem;  /* colocar o novo elemento no amontoado */
  ppqueue->NumElem++;  /* incrementar o número de elementos do amontoado */

  return OK;
}


int PQueueDeleteMin (PtPQueue ppqueue, VERTEX *pelem)
{
  unsigned int I, Filho;  /* posição do pai e do filho */

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  if (pelem == NULL) return NULL_PTR;
  
  *pelem = ppqueue->Heap[0];  /* retirar a raiz do amontoado */
  ppqueue->NumElem--;  /* decrementar o número de elementos do amontoado */

  /* ajustar o amontoado, subindo os filhos de custo menor do que o custo do elemento */
  for (I = 0; I*2+1 <= ppqueue->NumElem; I = Filho)
  {
    Filho = 2*I+1;  /* primeiro filho */

    /* determinar o menor dos filhos */
    if (Filho < ppqueue->NumElem && ppqueue->Heap[Filho].Cost > ppqueue->Heap[Filho+1].Cost)
      Filho++;

    /* subir o filho de custo menor do que o último elemento */
    if (ppqueue->Heap[Filho].Cost < ppqueue->Heap[ppqueue->NumElem].Cost)
         ppqueue->Heap[I] = ppqueue->Heap[Filho];
    else break;
  }

  /* recolocar o último elemento no amontoado */
  ppqueue->Heap[I] = ppqueue->Heap[ppqueue->NumElem];

  return OK;
}


int PQueueDecrease (PtPQueue ppqueue, VERTEX *pelem)
{
  unsigned int I;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  if (pelem == NULL) return NULL_PTR;

  /* procurar o elemento na fila com prioridade */  
  for (I = 0; I < ppqueue->NumElem; I++)
    if (ppqueue->Heap[I].Vertex == pelem->Vertex) break;

  if (I == ppqueue->NumElem) return NO_ELEM;

  /* ajustar o amontoado, descendo os pais com custo maior do que o novo custo do elemento */
  for (; I > 0 && ppqueue->Heap[(I+1)/2-1].Cost > (*pelem).Cost; I = (I+1)/2-1)
    ppqueue->Heap[I] = ppqueue->Heap[(I+1)/2-1];  /* descer o pai de custo maior do que o novo custo do elemento */

  ppqueue->Heap[I] = *pelem;  /* colocar o novo elemento no amontoado */

  return OK;
}


int PQueueIsEmpty (PtPQueue ppqueue)
{
  if (ppqueue == NULL) return 0;

  return ppqueue->NumElem == 0;
}

int PQueueDisplay (PtPQueue ppqueue)
{
  int I;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;

  for (I = 0; I < ppqueue->NumElem; I++)
    printf ("(%d-%d)  ", ppqueue->Heap[I].Vertex, ppqueue->Heap[I].Cost);
  printf ("\n");

  return OK;
}

