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

PtPQueue PQueueCreate (unsigned int pdim){
  PtPQueue PQueue;

  if (pdim == 0){
    return NULL;
  }

  /* alocar memória para a Fila com Prioridade */
  if ((PQueue = (PtPQueue) malloc (sizeof (struct pqueue))) == NULL){
    return NULL;
  }

  if ((PQueue->Heap = (VERTEX *) calloc (pdim, sizeof (VERTEX))) == NULL){
    free (PQueue);
    return NULL;
  }

  PQueue->HeapSize = pdim;  /* armazenar a dimensão da Fila */
  PQueue->NumElem = 0;  /* inicializar o número de elementos da Fila */

  return PQueue;  /* devolver a referência da Fila acabada de criar */
}


int PQueueDestroy (PtPQueue *ppqueue){
  PtPQueue TmpPQueue = *ppqueue;

  if (TmpPQueue == NULL){
    return NO_PQUEUE;
  }

  free (TmpPQueue->Heap);  /* libertar a memória ocupada pelo monte */
  free (TmpPQueue);  /* libertar a memória ocupada pela Fila */

  *ppqueue = NULL;  /* colocar a referência da Fila a NULL */

  return OK;
}


int PQueueInsert (PtPQueue ppqueue, VERTEX *pelem){
  unsigned int i;

  if (ppqueue == NULL){
    return NO_PQUEUE;
  }

  if (pelem == NULL){
    return NULL_PTR;
  }

  if (ppqueue->NumElem == ppqueue->HeapSize){
    return PQUEUE_FULL;
  }

  for (i = ppqueue->NumElem; i > 0 && ppqueue->Heap[(i-1)/2].Cost > pelem->Cost; i = (i-1)/2){
    ppqueue->Heap[i] = ppqueue->Heap[(i+1)/2-1];
  }

  ppqueue->Heap[i] = *pelem;
  ppqueue->NumElem++;  /* incrementar o número de elementos do monte */

  return OK;
}


int PQueueDeleteMin (PtPQueue ppqueue, VERTEX *pelem){
 unsigned int i, son;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  if (pelem == NULL) return NULL_PTR;

<<<<<<< 27e4516a5a564c441fa322e3e63c391d0f16185f
  *pelem = pqueue->Heap[0];
=======
  pelem = ppqueue->Heap[0];
>>>>>>> 3eed5f0c42a3a022ad115df8c1ee4febf19b13e2
  ppqueue->NumElem--;

  for (i = 0; i*2+1 <= ppqueue->NumElem; i = son){
    son = 2*i+1;

    if (son < ppqueue->NumElem && ppqueue->Heap[son].Cost > ppqueue->Heap[son+1].Cost){
      son++;
    }

    if (ppqueue->Heap[son].Cost < ppqueue->Heap[ppqueue->NumElem].Cost){
      ppqueue->Heap[i] = ppqueue->Heap[son];
    }else{
      break;
    }
  }

  ppqueue->Heap[i] = ppqueue->Heap[ppqueue->NumElem];

  return OK;
}


int PQueueDecrease (PtPQueue ppqueue, VERTEX *pelem){
  unsigned int i;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  if (pelem == NULL) return NULL_PTR;

  for (i = 0; i < ppqueue->NumElem; i++){
    if (ppqueue->Heap[i].Vertex == pelem->Vertex){
      break;
    }
  }

  if (i == ppqueue->NumElem) return NO_ELEM;

  for (; i > 0 && ppqueue->Heap[(i+1)/2-1].Cost > pelem->Cost; i = (i+1)/2-1){
    ppqueue->Heap[i] = ppqueue->Heap[(i+1)/2-1];
  }

  ppqueue->Heap[i] = *pelem;

  return OK;
}


int PQueueIsEmpty (PtPQueue ppqueue){
  if (ppqueue == NULL){
    return 0;
  }
  return ppqueue->NumElem == 0;
}

int PQueueDisplay (PtPQueue ppqueue)
{
  int i;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;

  for (i = 0; i < ppqueue->NumElem; i++)
    printf ("(%d-%d)  ", ppqueue->Heap[i].Vertex, ppqueue->Heap[i].Cost);
  printf ("\n");

  return OK;
}

