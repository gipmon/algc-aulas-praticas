/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstrato Árvore Binária de Pesquisa
 ordenada por ordem crescente. Os nos da arvore são compactos e armazenam 
 elementos inteiros.

 Autor : António Manuel Adrego da Rocha    Data : Abril de 2014

*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include "abp.h"
#include "stack.h"
#include "queue.h"

struct abpnode /* estrutura do no compacto */
{
  PtABPNode PtLeft;  /* ponteiro para o no esquerdo da arvore */
  PtABPNode PtRight;  /* ponteiro para o no direito da arvore */
  int Elem;  /* elemento inteiro armazenado na ABP */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;    /* inicialização do erro */

static char *ErrorMsg[] = { "sem erro", "abp inexistente", "sem memoria",
                            "ponteiro nulo", "arvore vazia", "elemento existente",
                            "elemento inexistente", "ficheiro inexistente" };

static char *AbnormalErrorMsg = "erro desconhecido";

/******* N representa o número de mensagens de erro previstas no módulo *******/

#define N (sizeof (ErrorMsg) / sizeof (char *))

/************************ Alusão às Funções Auxiliares ************************/

static PtABPNode ABPNodeCreate (int);
static void ABPNodeDestroy (PtABPNode *);
static PtABPNode SearchRec (PtABPNode, int);
static PtABPNode SearchRep (PtABPNode, int);
static PtABPNode KMinRec (PtABPNode, unsigned int);
static void NodeDelete (PtABPNode *);
static int FindMin (PtABPNode);
static void ListInOrder (PtABPNode, int [], unsigned int *);
static void Balance (PtABPNode *, int [], int , int);
static void Display (PtABPNode, unsigned int);
static void StoreFilePreOrder (PtABPNode, FILE *);

/*************************** Definição das Funções ****************************/ 

int ABPErrorCode (void)
{
    return Error;
}

/******************************************************************************/

char *ABPErrorMessage (void)
{
    if (Error < N) return ErrorMsg[Error];
    else return AbnormalErrorMsg;    /* não há mensagem de erro */
}

/******************************************************************************/

PtABPNode ABPCreate (void)
{
    return NULL;
}

/******************************************************************************/

void ABPDestroy (PtABPNode *proot)
{
	if (*proot != NULL)
	{
		ABPDestroy (&(*proot)->PtLeft);	/* destruir a subarvore esquerda */
		ABPDestroy (&(*proot)->PtRight);	/* destruir a subarvore direita */
		ABPNodeDestroy (proot);	/* eliminar o elemento */
	}
}

/******************************************************************************/

unsigned int ABPSize (PtABPNode proot)  /* cálculo do número de elementos recursiva */                                     
{
	if (proot == NULL) return 0;	/* arvore vazia */
	else return 1 + ABPSize (proot->PtLeft) + ABPSize (proot->PtRight);
}

/******************************************************************************/

unsigned int ABPHeight (PtABPNode proot)
{
	unsigned int LeftHeight, RightHeight;

	if (proot == NULL) return 0;	/* no externo no nível 0 */
	else
	{
		LeftHeight = ABPHeight (proot->PtLeft);	/* subarvore esquerda */
		RightHeight = ABPHeight (proot->PtRight);	/* subarvore direita */

		if (LeftHeight > RightHeight) return LeftHeight + 1;
		else return RightHeight + 1;
	}
}

/******************************************************************************/

int ABPSearch (PtABPNode abp, int pelem)
{
    if (abp == NULL) { Error = ABP_EMPTY; return 0; }

    if (SearchRec (abp, pelem) == NULL) { Error = NO_ELEM; return 0; }
    else { Error = OK; return 1; }
}

/******************************************************************************/

PtABPNode ABPMinRec (PtABPNode proot)  /* pesquisa de mínimo recursiva */
{
	if (proot == NULL) return NULL;
	else if (proot->PtLeft == NULL) return proot;
			else return ABPMinRec (proot->PtLeft);
}

/******************************************************************************/

PtABPNode ABPMaxRec (PtABPNode proot)  /* pesquisa de máximo recursiva */
{
	if (proot == NULL) return NULL;
	else if (proot->PtRight == NULL) return proot;
			else return ABPMaxRec (proot->PtRight);
}

/******************************************************************************/

PtABPNode ABPMinRep (PtABPNode proot)  /* pesquisa de mínimo repetitiva */
{
	if (proot == NULL) return NULL;

	while (proot->PtLeft != NULL) proot = proot->PtLeft;
	return proot;
}

/******************************************************************************/

PtABPNode ABPKMin (PtABPNode proot, unsigned int pk)  /* operação de arranque */
{			/* K inválido ou arvore com menos elementos do que K */
	if (pk < 1 || ABPSize (proot) < pk) return NULL;
	else return KMinRec (proot, pk);
}

/******************************************************************************/

void ABPInsertRec (PtABPNode *proot, int pelem)  /* inserção recursiva */
{
	if (*proot == NULL)	/* inserir o elemento */
	{ if ((*proot = ABPNodeCreate (pelem)) == NULL) return; }
	else if ((*proot)->Elem > pelem)	/* subarvore esquerda */
				ABPInsertRec (&(*proot)->PtLeft, pelem);
			else if ((*proot)->Elem < pelem)	/* subarvore direita */
						ABPInsertRec (&(*proot)->PtRight, pelem);
					else return;	/* o elemento já existe */
}

/******************************************************************************/

void ABPInsertRep (PtABPNode *proot, int pelem)	/* inserção repetitiva */
{
	PtABPNode Node = *proot, Prev = NULL;

				/* arvore vazia - no colocado na raiz desta arvore */
	if (*proot == NULL) { *proot = ABPNodeCreate (pelem); return; }

	while (Node != NULL)	/* travessia até ao local de inserção */
	{
		Prev = Node;
		if (Node->Elem > pelem) Node = Node->PtLeft;
		else if (Node->Elem < pelem) Node = Node->PtRight;
				else return;	/* repetido não é inserido */
	}
				/* inserir folha à esquerda ou à direita */
	if (Prev->Elem > pelem) Prev->PtLeft = ABPNodeCreate (pelem);
	else Prev->PtRight = ABPNodeCreate (pelem);
}

/******************************************************************************/

void ABPDeleteRec (PtABPNode *proot, int pelem)	/* remoção recursiva */
{
	if (*proot == NULL) return;	/* arvore vazia ou elemento inexistente */

	if ((*proot)->Elem > pelem)
			ABPDeleteRec (&(*proot)->PtLeft, pelem);
	else if ((*proot)->Elem < pelem)
				ABPDeleteRec (&(*proot)->PtRight, pelem);
			else NodeDelete (proot);	/* eliminar o elemento */
}

/******************************************************************************/

void ABPDeleteRep (PtABPNode *proot, int pelem)	/* remoção repetitiva */
{
	PtABPNode Del = *proot, Prev = NULL, Node, Temp, PrevTemp;

	if (*proot == NULL) return;	/* arvore vazia*/
	while (Del != NULL && Del->Elem != pelem)
	{			/* travessia até encontrar o elemento a remover */
		Prev = Del;
		if (Del->Elem > pelem) Del = Del->PtLeft;
		else Del = Del->PtRight;
	}

	if (Del == NULL) return;	/* elemento inexistente na arvore */
	Node = Del;

	if (Node->PtRight == NULL) Node = Node->PtLeft;	/* à esquerda */
	else	if (Node->PtLeft == NULL) Node = Node->PtRight;	/* à direita */
			else	/* com subarvores esquerda e direita */
			{	/* procurar menor elemento da subarvore direita */
				Temp = Node->PtRight; PrevTemp = Node;
				while (Temp->PtLeft != NULL)
				{ PrevTemp = Temp; Temp = Temp->PtLeft; }

				Node->Elem = Temp->Elem;	/* substituir pelo menor */
					/* elemento, desligá-lo e ajustar as ligações */
				if (PrevTemp == Node) PrevTemp->PtRight = Temp->PtRight;
				else PrevTemp->PtLeft = Temp->PtRight;
				ABPNodeDestroy (&Temp); return;
			}
	/* ajustar o pai do elemento removido que só tem um filho */
	if (Del == *proot) *proot = Node;	/* se foi eliminado da raiz */
	else	if (Prev->PtLeft == Del) Prev->PtLeft = Node;
			else Prev->PtRight = Node;
	ABPNodeDestroy (&Del);
}

/******************************************************************************/

PtABPNode ABPCreateFile (char *nomef)
{
    PtABPNode ABP; FILE *PtF; unsigned int NElem, I, Elem;

    /* abertura com validacao do ficheiro para leitura */
    if ( (PtF = fopen (nomef, "r")) == NULL) { Error = NO_FILE; return NULL; }

    ABP = ABPCreate ();    /* criação da arvore */

    /* leitura do número de elementos da arvore do ficheiro */
    fscanf (PtF, "%u", &NElem);
    if (NElem < 1) { Error = OK; fclose (PtF); return NULL; }

    /* leitura dos valores do ficheiro e carregamento da ABP */
    for (I = 0; I < NElem; I++)
    {
        fscanf (PtF, "%d", &Elem);
        ABPInsertRec (&ABP, Elem);
        if (ABPErrorCode () == NO_MEM)
        { ABPDestroy (&ABP); Error = NO_MEM; return NULL; }
    }

    fclose (PtF);  /* fecho do ficheiro */

    Error = OK;
    return ABP;  /* devolve a arvore criada */
}
/******************************************************************************/

void ABPStoreFile (PtABPNode abp, char *nomef)
{
    FILE *PtF; unsigned int NElem;

    /* abertura com validacao do ficheiro para escrita */
    if ((PtF = fopen (nomef, "w")) == NULL) { Error = NO_FILE; return ; }

    NElem = ABPSize (abp);
    /* escrita do número de elementos da arvore no ficheiro */
    fprintf (PtF, "%u\n", NElem);

    /* escrita dos elementos da arvore no ficheiro */
    StoreFilePreOrder (abp, PtF);

    Error = OK;
    fclose (PtF);  /* fecho do ficheiro */
}

/******************************************************************************/

void ABPPreOrderRec (PtABPNode proot)  /* travessia em pré-ordem recursiva */
{
	if (proot != NULL)
	{
		printf ("%d ", proot->Elem);	/* imprimir o elemento */
		ABPPreOrderRec (proot->PtLeft);
		ABPPreOrderRec (proot->PtRight);
	}
}

/******************************************************************************/

void ABPInOrderRec (PtABPNode proot)  /* travessia em ordem recursiva */
{
	if (proot != NULL)
	{
		ABPInOrderRec (proot->PtLeft);
		printf ("%d ", proot->Elem);	/* imprimir o elemento */
		ABPInOrderRec (proot->PtRight);
	}
}

/******************************************************************************/

void ABPPostOrderRec (PtABPNode proot)  /* travessia em pós-ordem recursiva */
{
	if (proot != NULL)
	{
		ABPPostOrderRec (proot->PtLeft);
		ABPPostOrderRec (proot->PtRight);
		printf ("%d ", proot->Elem);	/* imprimir o elemento */
	}
}

/******************************************************************************/

unsigned int ABPSizeRep (PtABPNode proot)
{
	PtABPNode Node = proot; PtStack Stack; unsigned int Number = 0;

	if (proot == NULL) return 0;	/* arvore vazia */
	if ((Stack = StackCreate (sizeof (PtABPNode))) == NULL) return 0;
	StackPush (Stack, &Node);	/* armazenar a raiz */

	while (!StackIsEmpty (Stack))	/* enquanto existirem nos */
	{
		StackPop (Stack, &Node);	/* recuperar o no */
		Number++;	/* contar o no */

		/* armazenar a raiz da subarvore esquerda */
		if (Node->PtLeft != NULL) StackPush (Stack, &Node->PtLeft);

		/* armazenar a raiz da subarvore direita */
		if (Node->PtRight != NULL) StackPush (Stack, &Node->PtRight);
	}

	StackDestroy (&Stack);	/* destruir a pilha */

	return Number;
}

/******************************************************************************/

void ABPPreOrderRep (PtABPNode proot)
{
	PtABPNode Node = proot; PtStack Stack;

	if (proot == NULL) return;	/* arvore vazia */
	if ((Stack = StackCreate (sizeof (PtABPNode))) == NULL) return;

	StackPush (Stack, &Node);	/* armazenar a raiz */
	while (!StackIsEmpty (Stack))	/* enquanto existirem nos */
	{
		StackPop (Stack, &Node);	/* recuperar o no */
		printf ("%d ", Node->Elem);	/* imprimir o elemento */

				/* colocar a raiz da subarvore direita, caso exista */
		if (Node->PtRight != NULL) StackPush (Stack, &Node->PtRight);

				/* colocar a raiz da subarvore esquerda, caso exista */
		if (Node->PtLeft != NULL) StackPush (Stack, &Node->PtLeft);
	}

	StackDestroy (&Stack);	/* destruir a pilha */
}

/******************************************************************************/

void ABPInOrderRep (PtABPNode proot)
{
	PtABPNode Node = proot; PtStack Stack;

	if (proot == NULL) return;	/* arvore vazia */
	if ((Stack = StackCreate (sizeof (PtABPNode))) == NULL) return;
	StackPush (Stack, &Node);	/* armazenar a raiz */

	while (!StackIsEmpty (Stack))
	{
		if (Node != NULL)	/* não é um no externo */
		{
			Node = Node->PtLeft;
			StackPush (Stack, &Node);	/* subarvore esquerda */
		}
		else	/* é um no externo */
		{
			StackPop (Stack, &Node);	/* retirar e descartar o no externo */	
			if (!StackIsEmpty (Stack))
			{
				StackPop (Stack, &Node);	/* recuperar o no anterior */
				printf ("%d ", Node->Elem);	/* imprimir o elemento */
				Node = Node->PtRight;	/* subarvore direita */
				StackPush (Stack, &Node);
			}
		}
	}

	StackDestroy (&Stack);	/* destruir a pilha */
}

/******************************************************************************/

void ABPPostOrderRep (PtABPNode proot)
{
	PtABPNode Node = proot, Last = proot; PtStack Stack;

	if (proot == NULL) return;	/* arvore vazia */
	if ((Stack = StackCreate (sizeof (PtABPNode))) == NULL) return;

	while (1)	/* enquanto houver elementos para visitar */
	{
			/* travessia pela esquerda até atingir a folha mais à esquerda */
		while (Node->PtLeft != NULL)
		{ StackPush (Stack, &Node); Node = Node->PtLeft; }

		/* se não tem subarvore direita ou já completou a sua travessia */
		while (Node->PtRight == NULL || Node->PtRight == Last)
		{
			printf ("%d ", Node->Elem);	/* imprimir o elemento */
			Last = Node;	/* assinalar último elemento visitado */
					/* terminar quando não há mais elementos na pilha */
			if (StackIsEmpty (Stack)) { StackDestroy (&Stack); return; }

			StackPop (Stack, &Node);	/* retirar o elemento anterior */
		}

		StackPush (Stack, &Node);	/* recolocar o elemento na pilha */
		Node = Node->PtRight;	/* iniciar travessia da subarvore direita */
	}
}

/******************************************************************************/

void ABPByLevel (PtABPNode proot)
{
	PtABPNode Node = proot; PtQueue Queue;

	if (proot == NULL) return;	/* arvore vazia */
	if ((Queue = QueueCreate (sizeof (PtABPNode))) == NULL) return;

	QueueEnqueue (Queue, &Node);	/* armazenar a raiz */

	while (!QueueIsEmpty (Queue))
	{
		QueueDequeue (Queue, &Node);	/* retirar o no */
		printf ("%d ", Node->Elem);	/* imprimir o elemento */

		/* armazenar a raiz da subarvore esquerda */
		if (Node->PtLeft != NULL) QueueEnqueue (Queue, &Node->PtLeft);

		/* armazenar a raiz da subarvore direita */
		if (Node->PtRight != NULL) QueueEnqueue (Queue, &Node->PtRight);
	}

	QueueDestroy (&Queue);	/* destruir a fila */
}

/******************************************************************************/

PtABPNode ABPBalance (PtABPNode proot)
{
	int *List; PtABPNode NewABP = NULL;
	unsigned int Count = 0, n = ABPSize (proot);	/* número de nos */

	if (proot == NULL) return NULL;	/* a arvore está vazia */	
				/* criar a sequência */
	if ((List = (int *) calloc (n, sizeof (int))) == NULL)	return NULL;	

	ListInOrder (proot, List, &Count);	/* preencher a sequência */
	Balance (&NewABP, List, 0, n-1);	/* balancear a arvore */
	free (List);	/* libertar a sequência */

	return NewABP;
}

/******************************************************************************/

void ABPDisplay (PtABPNode abp)
{
    if (abp == NULL)
    { Error = ABP_EMPTY; return; }

    Error = OK;
    Display (abp, 1);
}

/******************************************************************************/

int ABPEmpty (PtABPNode proot){
	return proot == NULL;
}

/******************************************************************************/

/******************************************************************************/

int ABPElement (PtABPNode pnode){
	if(pnode==NULL){
		Error=NO_ABP;
		return 0;
	}
	return pnode->Elem;
}

/******************************************************************************/

/******************************************************************************/

PtABPNode ABPMaxRep (PtABPNode proot){
	if(proot==NULL){
		Error=NO_ABP;
		return NULL;
	}

	PtABPNode p = proot;

	while(p->PtRight != NULL){
		p = p->PtRight;
	}

	return p;
}

/******************************************************************************/

/******************************************************************************/

PtABPNode ABPCopy (PtABPNode proot){
	PtABPNode Copy;

	Error = OK;

	if(proot==NULL){
		return NULL;
	}

	Copy = CopyRec(proot);

	if(Error){
		ABPDestroy(&Copy);
	}
	return Copy;
}

static PtABPNode CopyRec(PtABPNode proot){
	PtABPNode Node;
	if(proot==NULL){
		return NULL;
	}
	if((Node=ABPNodeCreate(proot->Elem))==NULL){
		Error = NO_MEM;
		return NULL;
	}
	if(proot->PtLeft!=NULL){
		Node->PtLeft = CopyRec(proot->PtLeft);
	}
	if(!Error && proot->PtRight != NULL){
		Node->PtRight = CopyRec(proot->PtRight);
	}
	return Node;
}
/******************************************************************************/

/******************************************************************************/

int ABPTotalSum (PtABPNode pnode){
	PtABPNode No = pnode;
	PtQueue Fila;
	int sum = 0;

    if (pnode == NULL){
    	Error = ABP_EMPTY;
    	return 0;
    }

    if ((Fila = QueueCreate (sizeof (PtABPNode))) == NULL){
    	Error = NO_MEM;
    	return 0;
    }

    QueueEnqueue (Fila, &No);

    while (!QueueEmpty (Fila)){
        QueueDequeue (Fila, &No);
        sum += No->Elem;

        if (No->PtLeft != NULL){
        	QueueEnqueue (Fila, &No->PtLeft);
        }
        if (No->PtRight != NULL){
        	QueueEnqueue (Fila, &No->PtRight);
        }
    }

    QueueDestroy (&Fila);

    Error = OK;
    return sum;
}

/******************************************************************************/

/******************************************************************************/

unsigned int ABPMult5Count (PtABPNode proot){
	unsigned int count = 0;

	if(proot == NULL) {
		Error = ABP_EMPTY;
		return 0;
	}

	Error = OK;

	if(proot->Elem % 5 == 0){
		count++;
	}

	if(proot->PtEsq != NULL){
		count += ABPMult5Count(pabp->PtEsq);
	}

	if(proot->PtDir != NULL){
		count += ABPMult5Count(proot->PtDir);
	}

	return count;
}

/******************************************************************************/

/******************************************************************************/

unsigned int ABPEvenCount (PtABPNode proot){
	PtABPNode No = proot;
	PtQueue Fila;
	unsigned int even = 0;

	 if (proot == NULL){
	 	Error = ABP_EMPTY;
	 	return 0;
	 }

	  if ((Fila = QueueCreate(sizeof (PtABPNode))) == NULL){
	  	Error = NO_MEM;
	  	return 0;
	  }

	  QueueEnqueue(Fila, &No);

	  while (!QueueEmpty(Fila))
	  {
	      QueueDequeue(Fila, &No);
	      if(No->Elem % 2 == 0) even++;

	      if (No->PtLeft != NULL){
	      	QueueEnqueue(Fila, &No->PtLeft);
	      }
	      if (No->PtRight != NULL){
	      	QueueEnqueue(Fila, &No->PtRight);
	      }
	  }

	  QueueDestroy(&Fila);

	  Error = OK;
	  return even;
}

/******************************************************************************/

/******************************************************************************/
int ABPOddSum (PtABPNode proot){
	if(proot == NULL){
		return 0;
	}

	if(ABPElement(proot)%2 != 0){
		return ABPElement(proot) + ABPOddSum(proot->PtRight) + ABPOddSum(proot->PtRight);
	}else{
		return ABPOddSum(proot->PtLeft) + ABPOddSum(proot->PtRight);
	}
}
/******************************************************************************/

/******************************************************************************/
int ABPEvenOrderSum(PtABPNode proot){
	PtABPNode pnode = proot;
	PtStack stack;

	int index=1, soma=0;
	if(proot==NULL){
		return 0;
	}
	if((stack=StackCreate(sizeof(PtABPNode*)))==NULL){
		return 0;
	}

	StackPush(stack, &pnode);

	while(!StackEmpty(stack)){
		if(pnode != NULL){
			pnode=pnode->PtLeft;
			StackPush(stack, &pnode);
		}else{
			StackPop(stack, &pnode);
			if(!StackEmpty(stack)){
				StackPop(stack, &pnode);
				if(index%2==0){
					soma += pnode->Elem;
				}
				index++;
				pnode=pnode->PtRight;
				StackPush(stack, &pnode);
			}
		}
	}

	StackDestroy(&stack);
	Error=OK;
	return soma;
}
/******************************************************************************/

/******************************************************************************/
int ABPEquals(PtABPNode proot1, PtABPNode proot2){
	return proot1->Elem==proot2->Elem;
}
/******************************************************************************/

/*******************************************************************************
  Função que cria o no compacto da arvore binária de pesquisa.
*******************************************************************************/
static PtABPNode ABPNodeCreate (int pelem)	/* alocação do no compacto */
{
	PtABPNode Node;

	if ((Node = (PtABPNode) malloc (sizeof (struct abpnode))) == NULL)
		return NULL;

	Node->Elem = pelem;	/* copiar a informação */
	Node->PtLeft = NULL;	/* apontar para a esquerda para NULL */
	Node->PtRight = NULL;	/* apontar para a direita para NULL */

	return Node;
}

/*******************************************************************************
  Função que liberta a memoria do no compacto da arvore binária de pesquisa.
*******************************************************************************/
static void ABPNodeDestroy (PtABPNode *pelem)	/* libertação do no compacto */
{
	free (*pelem);	/* libertação do no */
	*pelem = NULL;	/* colocar o ponteiro a nulo */
}

/*******************************************************************************
  Função recursiva que pesquisa o elemento pretendido na arvore.
*******************************************************************************/
static PtABPNode SearchRec (PtABPNode proot, int pelem)   /* pesquisa recursiva */
{
	if (proot == NULL) return NULL;	/* pesquisa sem sucesso */

	if (proot->Elem == pelem) return proot;	/* pesquisa com sucesso */
	else	if (proot->Elem > pelem)
				return SearchRec (proot->PtLeft, pelem);
			else	return SearchRec (proot->PtRight, pelem);
}

/*******************************************************************************
  Função repetitiva que pesquisa o elemento pretendido na arvore.
*******************************************************************************/
static PtABPNode SearchRep (PtABPNode proot, int pelem)  /* pesquisa repetitiva */
{
	while (proot != NULL && proot->Elem != pelem)
		if (proot->Elem > pelem) proot = proot->PtLeft;
		else proot = proot->PtRight;

	return proot;	/* devolver o resultado da pesquisa */
}

/*******************************************************************************
  Função recursiva que pesquisa o K-menor elemento da arvore.
*******************************************************************************/
static PtABPNode KMinRec (PtABPNode proot, unsigned int pk) /* operação recursiva */
{ 
	unsigned int NLeft = ABPSize (proot->PtLeft);

	if (pk == NLeft+1) return proot;
	else	if (pk <= NLeft) return KMinRec (proot->PtLeft, pk);
			else return KMinRec (proot->PtRight, pk-NLeft-1);
}

/*******************************************************************************
  Função que remove efectivamente um no da arvore.
*******************************************************************************/
static void NodeDelete (PtABPNode *proot)
{
	PtABPNode Node = *proot;

	if ((*proot)->PtLeft == NULL && (*proot)->PtRight == NULL)
			ABPNodeDestroy (proot);	/* no folha - eliminar o elemento */
	else if ((*proot)->PtLeft == NULL)	/* com subarvore direita */
			{
				*proot = (*proot)->PtRight;	/* ligar à direita */
				ABPNodeDestroy (&Node);	/* eliminar o elemento */
			}
			else if ((*proot)->PtRight == NULL)	/* com subarvore esquerda */
					{
						*proot = (*proot)->PtLeft;	/* ligar à esquerda */
						ABPNodeDestroy (&Node);	/* eliminar o elemento */
					}
					else	/* com subarvores direita e esquerda */
					{	/* substituir pelo menor elemento da subarvore direita */
						(*proot)->Elem = FindMin ((*proot)->PtRight);
							/* remover o menor elemento da subarvore direita */
						ABPDeleteRec (&(*proot)->PtRight, (*proot)->Elem);
					}
}

/*******************************************************************************
  Função repetitiva que pesquisa o no minimo que se encontra na arvore a
  partir do no indicado.
*******************************************************************************/
static int FindMin (PtABPNode proot)
{
	PtABPNode Node = proot;

	while (Node->PtLeft != NULL) Node = Node->PtLeft;

	return Node->Elem;	/* devolver o elemento */
}

/*******************************************************************************
  Função recursiva que escreve os elementos da arvoe em pre-ordem num ficheiro.
*******************************************************************************/
static void StoreFilePreOrder (PtABPNode abp, FILE *fich)
{
    if (abp != NULL)
    {
        fprintf (fich, "%d\n", abp->Elem);

        StoreFilePreOrder (abp->PtLeft, fich);
        StoreFilePreOrder (abp->PtRight, fich);
    }
}

/*******************************************************************************
  Função recursiva que armazena os elementos da arvore em ordem num array.
*******************************************************************************/
static void ListInOrder (PtABPNode proot, int plist[], unsigned int *pcount)
{
	if (proot != NULL)
	{
		ListInOrder (proot->PtLeft, plist, pcount);	/* arvore esquerda */
		plist[(*pcount)++] = proot->Elem;	/* colocar elemento */
		ListInOrder (proot->PtRight, plist, pcount);	/* arvore direita */
	}
}

/*******************************************************************************
  Função recursiva que insere os elementos de uma lista numa arvore de modo que
  ela fique balanceada.
*******************************************************************************/
static void Balance (PtABPNode *proot, int plist[], int pbegin, int pend)
{
	unsigned int Median;

	if (pbegin <= pend)
	{
		Median = (pbegin + pend) >> 1;	/* (pbegin+pend)/2 */
		ABPInsertRec (proot, plist[Median]);	/* inserir elemento central */
		Balance (proot, plist, pbegin, Median-1);	/* subarvore esquerda */
		Balance (proot, plist, Median+1, pend);	/* subarvore direita */
	}
}

/*******************************************************************************
  Função recursiva que escreve os elementos da arvore de forma hierarquica.
*******************************************************************************/
static void Display (PtABPNode proot, unsigned int plevel)
{
	unsigned int i;

	if (proot == NULL)
	{
		for (i = 0; i < plevel; i++) printf ("\t");
		printf ("*\n");
        return;
	}

	Display (proot->PtRight, plevel+1);

	for (i = 0; i < plevel; i++) printf ("\t");

	printf ("%d\n", proot->Elem);	/* imprimir o elemento */

	Display (proot->PtLeft, plevel+1);
}
