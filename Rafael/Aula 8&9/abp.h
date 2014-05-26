
/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstrato Arvore Binaria de Pesquisa (ABP)
 (abp.h). A implementa��o tem capacidade de m�ltipla instancia��o, sendo
 providenciado um construtor para criar uma arvore vazia. � da responsabilidade
 da aplica��o, invocar o destructor, para libertar a mem�ria atribu�da ao objecto.
 O m�dulo providencia um controlo centralizado de erro, disponibilizando uma fun��o
 para obter o �ltimo erro ocorrido e uma fun��o para obter uma mensagem de erro
 elucidativa.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Abril de 2014


*******************************************************************************/

#ifndef _ABP
#define _ABP

/****************** Defini��o do Tipo Ponteiro para uma ABP *******************/

typedef struct abpnode *PtABPNode;

/************************ Defini��o de C�digos de Erro ************************/

#define	OK		    0	/* opera��o realizada com sucesso */
#define	NO_ABP		1	/* a ABP n�o existe */
#define	NO_MEM		2	/* mem�ria esgotada */
#define	NULL_PTR	3	/* ponteiro nulo */
#define	ABP_EMPTY	4	/* ABP vazia */
#define	REP_ELEM	5	/* j� existe o elemento */
#define	NO_ELEM		6	/* o elemento n�o existe */
#define	NO_FILE		7	/* o ficheiro n�o existe */

/*************************** Prot�tipos das Fun��es ***************************/

int ABPErrorCode (void);
/*******************************************************************************
 Fun��o que devolve o c�digo do �ltimo erro ocorrido.
*******************************************************************************/

char *ABPErrorMessage (void);
/*******************************************************************************
 Fun��o que devolve uma mensagem esclarecedora da causa do �ltimo erro ocorrido.
*******************************************************************************/

PtABPNode ABPCreate (void);
/*******************************************************************************
 Cria uma arvore vazia. Devolve um ponteiro a NULL. 
*******************************************************************************/

void ABPDestroy (PtABPNode *proot);
/*******************************************************************************
 Destr�i a arvore e coloca a refer�ncia a NULL. Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

void ABPInsertRec (PtABPNode *proot, int pelem);  /* vers�o recursiva */
void ABPInsertRep (PtABPNode *proot, int pelem);  /* vers�o repetitiva */
/*******************************************************************************
 Coloca pelem na arvore. N�o insere elementos repetidos.
 Valores de erro: OK, NO_MEM ou REP_ELE.
*******************************************************************************/

void ABPDeleteRec (PtABPNode *proot, int pelem);  /* vers�o recursiva */
void ABPDeleteRep (PtABPNode *proot, int pelem);  /* vers�o repetitiva */
/*******************************************************************************
 Retira pelem da arvore. Valores de erro: OK ou NO_ELEM.
*******************************************************************************/

int ABPSearch (PtABPNode proot, int pelem);
/*******************************************************************************
 Pesquisa se pelem existe na arvore. Devolve 1 em caso afirmativo e 0 em caso 
 contr�rio. Valores de erro: OK, ABP_EMPTY ou NO_ELEM.
*******************************************************************************/

PtABPNode ABPMinRec (PtABPNode proot);  /* pesquisa de m�nimo recursiva */
PtABPNode ABPMinRep (PtABPNode proot);  /* pesquisa de m�nimo repetitiva */
/*******************************************************************************
 Pesquisa o menor elemento da arvore. Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

PtABPNode ABPMaxRec (PtABPNode proot);  /* pesquisa de m�ximo recursiva */
/*******************************************************************************
 Pesquisa o maior elemento da arvore. Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

PtABPNode ABPKMin (PtABPNode proot, unsigned int pk);  /* pesquisa de K-m�nimo */
/*******************************************************************************
 Pesquisa o K-menor elemento da arvore. Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

unsigned int ABPSize (PtABPNode proot);
/*******************************************************************************
 Calcula o numero de nos da arvore. Valores de erro: OK.
*******************************************************************************/

unsigned int ABPHeight (PtABPNode proot);
/*******************************************************************************
 Calcula a altura da arvore. Valores de erro: OK.
*******************************************************************************/

PtABPNode ABPCreateFile (char *pnomef);
/*******************************************************************************
 Cria uma arvore a partir do ficheiro pnomef. Devolve a refer�ncia da arvore criada
 ou NULL, caso n�o consiga criar a arvore por falta de mem�ria.
*******************************************************************************/

void ABPStoreFile (PtABPNode proot, char *nomef);
/*******************************************************************************
 Armazena a arvore, caso ela exista, no ficheiro pnomef. O ficheiro tem na
 primeira linha o n�mero de elementos da arvore, seguido dos elementos, um por
 linha. Valores de erro: OK, ABP_EMPTY ou NO_FILE.
*******************************************************************************/

void ABPPreOrderRec (PtABPNode proot);  /* travessia recursiva */
void ABPPreOrderRep (PtABPNode proot);  /* travessia repetitiva */
/*******************************************************************************
 Lista a arvore em pre-ordem. Valores de erro: OK.
*******************************************************************************/

void ABPInOrderRec (PtABPNode proot);  /* travessia recursiva */
void ABPInOrderRep (PtABPNode proot);  /* travessia repetitiva */
/*******************************************************************************
 Lista a arvore em ordem (vers�o recursiva). Valores de erro: OK.
*******************************************************************************/

void ABPPostOrderRec (PtABPNode proot);  /* travessia recursiva */
void ABPPostOrderRep (PtABPNode proot);  /* travessia repetitiva */
/*******************************************************************************
 Lista a arvore em pos-ordem. Valores de erro: OK.
*******************************************************************************/

void ABPByLevel (PtABPNode proot);
/*******************************************************************************
 Lista a arvore por niveis. Valores de erro: OK, ABP_EMPTY ou NO_MEM.
*******************************************************************************/

PtABPNode ABPBalance (PtABPNode proot);
/*******************************************************************************
 Cria uma uma nova arvore balanceada. Devolve a refer�ncia da ABP criada ou NULL
 em caso de inexist�ncia de mem�ria (NO_MEM). Valores de erro: OK, ABP_EMPTY ou NO_MEM.
*******************************************************************************/

void ABPDisplay (PtABPNode proot);
/*******************************************************************************
 Imprime no monitor os elementos da arvore de forma hier�rquica.
 Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

/* trabalho da aula 9 */

int ABPEmpty (PtABPNode proot); /* Verifica se a arvore esta ou nao vazia. */
int ABPElement (PtABPNode pnode); /* obtem o elemento armazenado em pnode */
PtABPNode ABPMaxRep (PtABPNode proot); /* pesquisa de m�ximo repetitiva */

PtABPNode ABPCopy (PtABPNode proot);
/*******************************************************************************
 Copia a arvore. Devolve a refer�ncia da ABP criada ou NULL em caso de
 inexist�ncia de mem�ria. Valores de erro: OK ou NO_MEM.
*******************************************************************************/

int ABPTotalSum (PtABPNode pnode); /* soma total repetitiva */
unsigned int ABPMult5Count (PtABPNode proot); /* contagem recursiva dos m�ltiplos de 5 */
unsigned int ABPEvenCount (PtABPNode proot); /* contagem repetitiva dos pares */
int ABPOddSum (PtABPNode proot); /* soma dos �mpares recursiva */
int ABPEvenOrderSum (PtABPNode proot); /* soma dos elementos com n�mero de ordem par */
int ABPEquals (PtABPNode proot1, PtABPNode proot2); /* verifica se duas arvores sao iguais */

#endif
