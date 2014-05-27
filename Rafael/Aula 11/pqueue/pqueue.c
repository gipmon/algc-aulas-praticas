/****** *Implementação da Fila com Prioridade com um Amontoado Binário *******/
/***** Fila com Prioridade orientada máximos Nome: pqueue.c *****/

#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"  /* Interface */

/******* Definição do Estrutura de Dados da Fila com Prioridade ********/

struct pqueue  /* definição da Fila com Prioridade */
{
  unsigned int HeapSize;  /* capacidade de armazenamento da Fila */
  unsigned int NumElem;  /* número de elementos armazenados na Fila */
  int *Heap;  /* ponteiro para o monte a alocar dinamicamente */
};

/********************** Definição dos Subprogramas *********************/

PtPQueue PQueueCreate (unsigned int pdim)
{
  PtPQueue PQueue;

  if (pdim == 0) return NULL;

  /* alocar memória para a Fila com Prioridade */
  if ((PQueue = (PtPQueue) malloc (sizeof (struct pqueue))) == NULL) return NULL;

  if ((PQueue->Heap = (int *) calloc (pdim, sizeof (int))) == NULL)
  { free (PQueue); return NULL; }

  PQueue->HeapSize = pdim;  /* armazenar a dimensão da Fila */
  PQueue->NumElem = 0;  /* inicializar o número de elementos da Fila */

  return PQueue;  /* devolver a referência da Fila acabada de criar */
}

int PQueueDestroy (PtPQueue *ppqueue)
{
  PtPQueue TmpPQueue = *ppqueue;

  if (TmpPQueue == NULL) return NO_PQUEUE;

  free (TmpPQueue->Heap);  /* libertar a memória ocupada pelo monte */
  free (TmpPQueue);  /* libertar a memória ocupada pela Fila */

  *ppqueue = NULL;  /* colocar a referência da Fila a NULL */

  return OK;
}

int PQueueInsert (PtPQueue ppqueue, int pelem)
{
  unsigned int i;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == ppqueue->HeapSize) return PQUEUE_FULL;

  /* ajustar o monte, descendo os pais menores do que o elemento */
  for (i = ppqueue->NumElem; i > 0 && ppqueue->Heap[(i-1)/2] < pelem; i = (i-1)/2)
    ppqueue->Heap[i] = ppqueue->Heap[(i-1)/2];  /* descer o pai menor do que o novo elemento */
		
  ppqueue->Heap[i] = pelem;  /* colocar o novo elemento no monte */
  ppqueue->NumElem++;  /* incrementar o número de elementos do monte */

  return OK;
}

int PQueueDeleteMax (PtPQueue ppqueue, int *pelem)
{
  unsigned int i, Son;  /* posição do pai e do Son */

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  if (pelem == NULL) return NULL_PTR;

  *pelem = ppqueue->Heap[0];  /* retirar a raiz do monte */
  ppqueue->NumElem--;  /* decrementar o número de elementos do monte */

  /* ajustar o monte, subindo os filhos maiores do que o elemento */
  for (i = 0; i*2+1 <= ppqueue->NumElem; i = Son)
  {
    Son = 2*i+1;  /* primeiro filho */

    /* determinar o maior dos filhos */
    if (Son < ppqueue->NumElem && ppqueue->Heap[Son] < ppqueue->Heap[Son+1])
      Son++;

    /* subir o Son maior do que o último elemento */
    if (ppqueue->Heap[Son] > ppqueue->Heap[ppqueue->NumElem])
      ppqueue->Heap[i] = ppqueue->Heap[Son];
    else break;
  }

  /* recolocar o último elemento no monte */
  ppqueue->Heap[i] = ppqueue->Heap[ppqueue->NumElem];

  return OK;
}

int PQueueIncrease (PtPQueue ppqueue, int pelem, int pvalue)
{
  unsigned int i;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  if (pvalue <= pelem) return WRONG_VALUE;

  /* procurar o elemento na fila com prioridade */  
  for (i = 0; i < ppqueue->NumElem; i++)
	if (ppqueue->Heap[i] == pelem) break;

  if (i == ppqueue->NumElem) return NO_ELEM;

			/* descer os pais menores do que o novo valor do elemento */
  for ( ; i > 0 && ppqueue->Heap[(i-1)/2] < pvalue; i = (i-1)/2)
	ppqueue->Heap[i] = ppqueue->Heap[(i-1)/2];

  ppqueue->Heap[i] = pvalue;	/* colocar o novo valor do elemento */

  return OK;
}

int PQueueDecrease (PtPQueue ppqueue, int pelem, int pvalue)
{
  unsigned int i, Son;  /* posição do pai e do Son */

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  if (pvalue >= pelem) return WRONG_VALUE;

  /* procurar o elemento na fila com prioridade */  
  for (i = 0; i < ppqueue->NumElem; i++)
	  if (ppqueue->Heap[i] == pelem) break;

  if (i == ppqueue->NumElem) return NO_ELEM;
    
  for ( ; i*2+1 < ppqueue->NumElem; i = Son)
  {		/* subir os filhos maiores do que o novo valor do elemento */
    Son = 2*i+1;	/* determinar o maior dos filhos */
	if (Son < ppqueue->NumElem && ppqueue->Heap[Son] < ppqueue->Heap[Son+1]) Son++;
			/* trocar o maior dos filhos com o pai */
		if (ppqueue->Heap[Son] > pvalue) ppqueue->Heap[i] = ppqueue->Heap[Son];
		else break;
	}

	ppqueue->Heap[i] = pvalue;	/* colocar o novo valor do elemento */

  return OK;
}

int PQueueDimension (PtPQueue ppqueue, unsigned int *pdim)
{
  if (ppqueue == NULL) return NO_PQUEUE;

  *pdim = ppqueue->HeapSize;

  return OK;
}

int PQueueSize (PtPQueue ppqueue, unsigned int *pnelem)
{
  if (ppqueue == NULL) return NO_PQUEUE;

  *pnelem = ppqueue->NumElem;

  if (*pnelem == 0) return PQUEUE_EMPTY;
  else return OK;
}

int PQueueElement (PtPQueue ppqueue, int *pelem, int ppos)
{
  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem == 0) return PQUEUE_EMPTY;
  if ((ppos < 0) || (ppos >= ppqueue->NumElem)) return NO_ELEM;
  
  *pelem = ppqueue->Heap[ppos];

  return OK;
}

int PQueueIsEmpty (PtPQueue ppqueue)
{
  if (ppqueue == NULL) return 0;

  return ppqueue->NumElem == 0;
}

int PQueueStoreFile (PtPQueue ppqueue, char *pnomef)
{
  FILE *PtF; int I;

  if (ppqueue == NULL) return NO_PQUEUE;
  if (ppqueue->NumElem  == 0) return PQUEUE_EMPTY;

  /* abertura com validação do ficheiro */
  if ((PtF = fopen (pnomef, "w")) == NULL) return NO_FILE;

  /* escrita da dimensão da fila com prioridade no ficheiro */
  fprintf (PtF, "%d\n", ppqueue->HeapSize);

  /* escrita do número de elementos da fila com prioridade */
  fprintf (PtF, "%d\n", ppqueue->NumElem);

  /* escrita dos valores da RAM no ficheiro */
  for (I = 0; I < ppqueue->NumElem; I++)
    fprintf (PtF, "%d\n", ppqueue->Heap[I]);

  fclose (PtF);	/* fecho do ficheiro */

  return OK;
}

PtPQueue PQueueCreateFile (char *pnomef)
{
  FILE *PtF; int Dim, NElem, I, Val; PtPQueue PQueue;

  /* abertura com validação do ficheiro */
  if ((PtF = fopen (pnomef, "r")) == NULL) return NULL;

  fscanf (PtF, "%d", &Dim);	/* leitura da dimensão da fila com prioridade */

  if ((PQueue = PQueueCreate (Dim)) == NULL)	/* criação da fila com prioridade */
  {
    fclose (PtF); return NULL;
  }

  fscanf (PtF, "%d", &NElem);	/* leitura do número de elementos da fila com prioridade */

  /* leitura dos valores do ficheiro e carregamento da fila com prioridade */
  for (I = 0; I < NElem; I++)
  {
    fscanf (PtF, "%d", &Val);
    if (PQueueInsert (PQueue, Val) == PQUEUE_FULL)
    {
      PQueueDestroy (&PQueue); fclose (PtF); return NULL;
    }
  }

  fclose (PtF);	/* fecho do ficheiro */

  return PQueue;
}

