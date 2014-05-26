/************ Interface da Pilha Din�mica Gen�rica - stack.h ***********/

#ifndef _STACK_GENERIC
#define _STACK_GENERIC

/************** Defini��o do Tipo Ponteiro para uma Pilha **************/

typedef struct stack *PtStack;
 
/********************* Defini��o de C�digos de Erro ********************/

#define	OK	0	/* opera��o realizada com sucesso */
#define	NO_STACK	1	/* pilha inexistente */
#define	NO_MEM	2	/* mem�ria esgotada */
#define	NULL_PTR	3	/* ponteiro nulo */
#define	STACK_EMPTY	4	/* pilha vazia */

/********************* Prot�tipos dos Subprogramas *********************/

PtStack StackCreate (unsigned int psize);
/* Cria uma pilha para armazenar elementos com psize bytes. Devolve a refer�ncia da pilha criada ou NULL, no caso de inexist�ncia de mem�ria ou se psize for nulo. */

int StackDestroy (PtStack *pstack);
/* Destr�i a pilha pstack e coloca a refer�ncia a NULL. Valores de retorno: OK ou NO_STACK. */

int StackPush (PtStack pstack, void *pelem);
/* Coloca pelem no topo da pilha pstack. Valores de retorno: OK, NO_STACK, NO_MEM ou NULL_PTR. */

int StackPop (PtStack pstack, void *pelem);
/* Retira o elemento do topo da pilha pstack. Valores de retorno: OK, NO_STACK, NULL_PTR ou STACK_EMPTY. */

int StackTop (PtStack pstack, void *pelem);
/* Copia o elemento do topo da pilha pstack. Valores de retorno: OK, NO_STACK, NULL_PTR ou STACK_EMPTY. */

int StackIsEmpty (PtStack pstack);
/* Verifica se a pilha pstack est� vazia. Valores de retorno: OK, NO_STACK ou STACK_EMPTY. */

int StackSize (PtStack pstack, unsigned int *pnelem);
/* Determina e coloca em pnelem o n�mero de elementos armazenados na pilha pstack. Valores de retorno: OK, NO_STACK ou NULL_PTR. */

#endif
