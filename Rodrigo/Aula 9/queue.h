/************ Interface da Fila Dinâmica Genérica - queue.h ************/

#ifndef _QUEUE_GENERIC
#define _QUEUE_GENERIC

/************** Definição do Tipo Ponteiro para uma Fila **************/

typedef struct queue *PtQueue;

/********************* Definição de Códigos de Erro ********************/

#define	OK	0	/* operação realizada com sucesso */
#define	NO_QUEUE	1	/* fila inexistente */
#define	NO_MEM	2	/* memória esgotada */
#define	NULL_PTR	3	/* ponteiro nulo */
#define	QUEUE_EMPTY	4	/* fila vazia */

/********************* Protótipos dos Subprogramas *********************/
PtQueue QueueCreate (unsigned int psize);
/* Cria uma fila para armazenar elementos com psize bytes. Devolve a referência da fila criada ou NULL, no caso de inexistência de memória ou se psize for nulo. */

int QueueDestroy (PtQueue *pqueue);
/* Destrói a fila pqueue e coloca a referência a NULL. Valores de retorno: OK ou NO_QUEUE. */

int QueueEnqueue (PtQueue pqueue, void *pelem);
/* Coloca pelem na cauda da fila pqueue. Valores de retorno: OK, NO_QUEUE, NO_MEM ou NULL_PTR. */

int QueueDequeue (PtQueue pqueue, void *pelem);
/* Retira o elemento da cabeça da fila pqueue. Valores de retorno: OK, NO_QUEUE, NULL_PTR ou QUEUE_EMPTY. */

int QueueIsEmpty (PtQueue pqueue);
/* Verifica se a fila pqueue está vazia. Valores de retorno: OK, NO_QUEUE ou QUEUE_EMPTY. */

int QueueSize (PtQueue pqueue, unsigned int *pnelem);
/* Determina e coloca em pnelem o número de elementos armazenados na fila pqueue. Valores de retorno: OK, NO_QUEUE ou NULL_PTR. */

#endif
