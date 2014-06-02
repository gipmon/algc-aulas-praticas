/********* Interface da Fila com Prioridade com um Amontoado Bin�rio *********/
/***** Fila com Prioridade orientada aos m�nimos Nome: pqueue_dijkstra.h *****/

#ifndef _PQUEUE_HEAP
#define _PQUEUE_HEAP

/************ Defini��o do elemento da Fila com Prioridade ************/
typedef struct dijkstra 
{
  unsigned int Vertex;	/* vertex number */
  int Cost;		/* path cost to vertex */
} VERTEX;

/******* Defini��o do Tipo Ponteiro para uma Fila com Prioridade *******/

typedef struct pqueue *PtPQueue;

/******************** Defini��o de C�digos de Erro ********************/

#define	OK            0  /* opera��o realizada com sucesso */
#define	NO_PQUEUE     1  /* fila com prioridade inexistente */
#define	NO_MEM        2  /* mem�ria esgotada */
#define	NULL_PTR      3  /* ponteiro nulo */
#define	PQUEUE_EMPTY  4  /* fila com prioridade vazia */
#define	PQUEUE_FULL   5  /* fila com prioridade cheia */
#define	NO_ELEM       6  /* elemento inexistente na fila com prioridade */

/********************* Prot�tipos dos Subprogramas ********************/

PtPQueue PQueueCreate (unsigned int pdim);
/* Cria uma fila com prioridade com capacidade para armazenar pdim elementos de tipo VERTICE. Devolve a refer�ncia da fila com prioridade criada ou NULL em caso de inexist�ncia de mem�ria ou se pdim for nulo. */

int PQueueDestroy (PtPQueue *ppqueue);
/* Destr�i a fila com prioridade referenciada por ppqueue e coloca a refer�ncia a NULL. Valores de retorno: OK ou NO_PQUEUE. */

int PQueueInsert (PtPQueue ppqueue, VERTEX *pelem);
/* Insere o elemento pelem, na fila com prioridade referenciada por ppqueue. Valores de retorno: OK, NO_PQUEUE, PQUEUE_FULL ou NULL_PTR. */

int PQueueDeleteMin (PtPQueue ppqueue, VERTEX *pelem);
/* Retira o menor elemento da fila com prioridade referenciada por ppqueue. Valores de retorno: OK, NO_PQUEUE, PQUEUE_EMPTY ou NULL_PTR. */

int PQueueDecrease (PtPQueue ppqueue, VERTEX *pelem);
/* Promove o elemento pelem da fila com prioridade referenciada por ppqueue, caso ele exista. Valores de retorno: OK, NO_PQUEUE, PQUEUE_EMPTY, NULL_PTR ou NO_ELEM. */

int PQueueIsEmpty (PtPQueue ppqueue);
/* Verifica se a fila com prioridade referenciada por ppqueue est� vazia. Devolve 1 em caso afirmativo e 0 caso contr�rio. */

int PQueueDisplay (PtPQueue ppqueue);
/* Imprime o conteudo da fila com prioridade referenciada por ppqueue. Valores de retorno: OK, NO_PQUEUE ou PQUEUE_EMPTY. */

#endif
