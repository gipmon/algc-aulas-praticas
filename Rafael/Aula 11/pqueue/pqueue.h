/******** Interface da Fila com Prioridade com um Amontoado Binário ********/
/******** Fila com Prioridade orientada aos máximos Nome: pqueue.h ********/

#ifndef _PQUEUE_HEAP
#define _PQUEUE_HEAP

/******* Definição do Tipo Ponteiro para uma Fila com Prioridade *******/

typedef struct pqueue *PtPQueue;

/******************** Definição de Códigos de Erro ********************/

#define	OK            0  /* operação realizada com sucesso */
#define	NO_PQUEUE     1  /* fila com prioridade inexistente */
#define	NO_MEM        2  /* memória esgotada */
#define	NULL_PTR      3  /* ponteiro nulo */
#define	PQUEUE_EMPTY  4  /* fila com prioridade vazia */
#define	PQUEUE_FULL   5  /* fila com prioridade cheia */
#define	NO_ELEM       6  /* elemento inexistente na fila com prioridade */
#define	WRONG_VALUE   7  /* novo valor do elemento incorrecto */
#define	NO_FILE       8  /* ficheiro inexistente */

/********************* Protótipos dos Subprogramas ********************/

PtPQueue PQueueCreate (unsigned int pdim);
/* Cria uma fila com prioridade com capacidade para armazenar pdim elementos inteiros. Devolve a referência da fila com prioridade criada ou NULL em caso de inexistência de memória ou se pdim for nulo. */

int PQueueDestroy (PtPQueue *ppqueue);
/* Destrói a fila com prioridade referenciada por ppqueue e coloca a referência a NULL. Valores de retorno: OK ou NO_PQUEUE. */

int PQueueInsert (PtPQueue ppqueue, int pelem);
/* Insere o elemento pelem, na fila com prioridade referenciada por ppqueue. Valores de retorno: OK, NO_PQUEUE ou PQUEUE_FULL. */

int PQueueDeleteMax (PtPQueue ppqueue, int *pelem);
/* Retira o elemento com a maior chave da fila com prioridade referenciada por ppqueue. Valores de retorno: OK, NO_PQUEUE, PQUEUE_EMPTY ou NULL_PTR. */

int PQueueIncrease (PtPQueue ppqueue, int pelem, int pval);
/* Promove o elemento pelem da fila com prioridade referenciada por ppqueue, caso ele exista, para o novo valor valor pval, que tem de ser maior do que o valor antigo. Valores de retorno: OK, NO_PQUEUE, PQUEUE_EMPTY, WRONG_VALUE ou NO_ELEM. */

int PQueueDecrease (PtPQueue ppqueue, int pelem, int pval);
/* Despromove o elemento pelem da fila com prioridade referenciada por ppqueue, caso ele exista, para o novo valor valor pval, que tem de ser menor do que o valor antigo. Valores de retorno: OK, NO_PQUEUE, PQUEUE_EMPTY, WRONG_VALUE ou NO_ELEM. */

int PQueueDimension (PtPQueue ppqueue, unsigned int *pdim);
/* Determina a capacidade de armazenamento da fila com prioridade referenciada por ppqueue. Valores de retorno: OK ou NO_PQUEUE. */

int PQueueSize (PtPQueue ppqueue, unsigned int *pnelem);
/* Determina o número de elementos armazenados na fila com prioridade referenciada por ppqueue. Valores de retorno: OK, NO_PQUEUE ou PQUEUE_EMPTY. */

int PQueueElement (PtPQueue ppqueue, int *pelem, int ppos);
/* Copia o elemento que se encontra na posição ppos da fila com prioridade referenciada por ppqueue, caso ele exista. Valores de retorno: OK, NO_PQUEUE, PQUEUE_EMPTY ou NO_ELEM. */

int PQueueIsEmpty (PtPQueue ppqueue);
/* Verifica se a fila com prioridade referenciada por ppqueue está vazia. Devolve 1 em caso afirmativo e 0 caso contrário. */

int PQueueStoreFile (PtPQueue ppqueue, char *pnomef);
/* Armazena a fila com prioridade referenciada por ppqueue no ficheiro pnomef. O ficheiro tem na primeira linha a capacidade de armazenamento da fila com prioridade, na segunda linha o número de elementos armazenados, seguido dos elementos, um por linha. Valores de retorno: OK, NO_PQUEUE, PQUEUE_EMPTY ou NO_FILE. */

PtPQueue PQueueCreateFile (char *pnomef);
/* Recupera a fila com prioridade referenciada por ppqueue do ficheiro pnomef, caso ele exista. Devolve a referência da fila com prioridade criada ou NULL em caso de inexistência de memória ou inexistência do ficheiro. */

#endif
