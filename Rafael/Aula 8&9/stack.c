/************** Implementação Dinâmica Genérica - stack.c **************/

#include <stdlib.h>
#include <string.h>
#include "stack.h"	/* ficheiro de interface da pilha */

/*************** Definição do Estrutura de Dados da Pilha **************/

typedef struct node *PtNode;

struct node	/* definição de um nó da lista */
{
	void *PtElem;	/* ponteiro para o elemento genérico */
	PtNode PtPrev;	/* ponteiro para o nó anterior */
};
 
struct stack	/* definição da pilha */
{
	unsigned int Size;	/* tamanho em número de bytes de cada elemento */
	PtNode Top;	/* topo da pilha */
};

/********************** Definição dos Subprogramas *********************/

PtStack StackCreate (unsigned int psize)
{
	PtStack Stack;

	if (psize == 0) return NULL;
	if ((Stack = (PtStack) malloc (sizeof (struct stack))) == NULL)
		return NULL;	/* alocar memória para a pilha */
	Stack->Size = psize;	/* armazenar o tamanho dos elementos */
	Stack->Top = NULL;	/* inicializar o topo da pilha */
	return Stack;	/* devolver a referência da pilha acabada de criar */
}

int StackDestroy (PtStack *pstack)
{
	PtStack TmpStack = *pstack; PtNode TmpNode;

	if (TmpStack == NULL) return NO_STACK;
	while (TmpStack->Top != NULL)
	{				/* libertar a memória ocupada pelos elementos da pilha */
		TmpNode = TmpStack->Top;
		TmpStack->Top = TmpStack->Top->PtPrev;
		free (TmpNode->PtElem);
		free (TmpNode);
	}
	free (TmpStack);	/* libertar a memória ocupada pela pilha */
	*pstack = NULL;	/* colocar a referência da pilha a NULL */
	return OK;
}

int StackPush (PtStack pstack, void *pelem)
{
	PtNode TmpNode;

	if (pstack == NULL) return NO_STACK;
	if ((TmpNode = (PtNode) malloc (sizeof (struct node))) == NULL)
		return NO_MEM;
	if ((TmpNode->PtElem = malloc (pstack->Size)) == NULL)
	{ free (TmpNode); return NO_MEM; }
	TmpNode->PtPrev = pstack->Top;
	pstack->Top = TmpNode;
	memcpy (pstack->Top->PtElem, pelem, pstack->Size);	/* colocar */
	return OK;
}

int StackPop (PtStack pstack, void *pelem)
{
	PtNode TmpNode;

	if (pstack == NULL) return NO_STACK;
	if (pstack->Top == NULL) return STACK_EMPTY;
	if (pelem == NULL) return NULL_PTR;
	memcpy (pelem, pstack->Top->PtElem, pstack->Size);	/* retirar */
	TmpNode = pstack->Top;
	pstack->Top = pstack->Top->PtPrev;
	free (TmpNode->PtElem);
	free (TmpNode);
	return OK;
}

int StackIsEmpty (PtStack pstack)
{
	if (pstack == NULL) return NO_STACK;
	if (pstack->Top == NULL) return STACK_EMPTY;
	return OK;
}

int StackTop (PtStack pstack, void *pelem)
{
	if (pstack == NULL) return NO_STACK;
	if (pstack->Top == NULL) return STACK_EMPTY;
	if (pelem == NULL) return NULL_PTR;
	memcpy (pelem, pstack->Top->PtElem, pstack->Size);	/* copiar */
	return OK;
}
