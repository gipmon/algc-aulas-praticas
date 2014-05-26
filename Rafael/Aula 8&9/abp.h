
/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstrato Arvore Binaria de Pesquisa (ABP)
 (abp.h). A implementação tem capacidade de múltipla instanciação, sendo
 providenciado um construtor para criar uma arvore vazia. É da responsabilidade
 da aplicação, invocar o destructor, para libertar a memória atribuída ao objecto.
 O módulo providencia um controlo centralizado de erro, disponibilizando uma função
 para obter o último erro ocorrido e uma função para obter uma mensagem de erro
 elucidativa.

 Autor : António Manuel Adrego da Rocha    Data : Abril de 2014


*******************************************************************************/

#ifndef _ABP
#define _ABP

/****************** Definição do Tipo Ponteiro para uma ABP *******************/

typedef struct abpnode *PtABPNode;

/************************ Definição de Códigos de Erro ************************/

#define	OK		    0	/* operação realizada com sucesso */
#define	NO_ABP		1	/* a ABP não existe */
#define	NO_MEM		2	/* memória esgotada */
#define	NULL_PTR	3	/* ponteiro nulo */
#define	ABP_EMPTY	4	/* ABP vazia */
#define	REP_ELEM	5	/* já existe o elemento */
#define	NO_ELEM		6	/* o elemento não existe */
#define	NO_FILE		7	/* o ficheiro não existe */

/*************************** Protótipos das Funções ***************************/

int ABPErrorCode (void);
/*******************************************************************************
 Função que devolve o código do último erro ocorrido.
*******************************************************************************/

char *ABPErrorMessage (void);
/*******************************************************************************
 Função que devolve uma mensagem esclarecedora da causa do último erro ocorrido.
*******************************************************************************/

PtABPNode ABPCreate (void);
/*******************************************************************************
 Cria uma arvore vazia. Devolve um ponteiro a NULL. 
*******************************************************************************/

void ABPDestroy (PtABPNode *proot);
/*******************************************************************************
 Destrói a arvore e coloca a referência a NULL. Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

void ABPInsertRec (PtABPNode *proot, int pelem);  /* versão recursiva */
void ABPInsertRep (PtABPNode *proot, int pelem);  /* versão repetitiva */
/*******************************************************************************
 Coloca pelem na arvore. Não insere elementos repetidos.
 Valores de erro: OK, NO_MEM ou REP_ELE.
*******************************************************************************/

void ABPDeleteRec (PtABPNode *proot, int pelem);  /* versão recursiva */
void ABPDeleteRep (PtABPNode *proot, int pelem);  /* versão repetitiva */
/*******************************************************************************
 Retira pelem da arvore. Valores de erro: OK ou NO_ELEM.
*******************************************************************************/

int ABPSearch (PtABPNode proot, int pelem);
/*******************************************************************************
 Pesquisa se pelem existe na arvore. Devolve 1 em caso afirmativo e 0 em caso 
 contrário. Valores de erro: OK, ABP_EMPTY ou NO_ELEM.
*******************************************************************************/

PtABPNode ABPMinRec (PtABPNode proot);  /* pesquisa de mínimo recursiva */
PtABPNode ABPMinRep (PtABPNode proot);  /* pesquisa de mínimo repetitiva */
/*******************************************************************************
 Pesquisa o menor elemento da arvore. Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

PtABPNode ABPMaxRec (PtABPNode proot);  /* pesquisa de máximo recursiva */
/*******************************************************************************
 Pesquisa o maior elemento da arvore. Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

PtABPNode ABPKMin (PtABPNode proot, unsigned int pk);  /* pesquisa de K-mínimo */
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
 Cria uma arvore a partir do ficheiro pnomef. Devolve a referência da arvore criada
 ou NULL, caso não consiga criar a arvore por falta de memória.
*******************************************************************************/

void ABPStoreFile (PtABPNode proot, char *nomef);
/*******************************************************************************
 Armazena a arvore, caso ela exista, no ficheiro pnomef. O ficheiro tem na
 primeira linha o número de elementos da arvore, seguido dos elementos, um por
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
 Lista a arvore em ordem (versão recursiva). Valores de erro: OK.
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
 Cria uma uma nova arvore balanceada. Devolve a referência da ABP criada ou NULL
 em caso de inexistência de memória (NO_MEM). Valores de erro: OK, ABP_EMPTY ou NO_MEM.
*******************************************************************************/

void ABPDisplay (PtABPNode proot);
/*******************************************************************************
 Imprime no monitor os elementos da arvore de forma hierárquica.
 Valores de erro: OK ou ABP_EMPTY.
*******************************************************************************/

/* trabalho da aula 9 */

int ABPEmpty (PtABPNode proot); /* Verifica se a arvore esta ou nao vazia. */
int ABPElement (PtABPNode pnode); /* obtem o elemento armazenado em pnode */
PtABPNode ABPMaxRep (PtABPNode proot); /* pesquisa de máximo repetitiva */

PtABPNode ABPCopy (PtABPNode proot);
/*******************************************************************************
 Copia a arvore. Devolve a referência da ABP criada ou NULL em caso de
 inexistência de memória. Valores de erro: OK ou NO_MEM.
*******************************************************************************/

int ABPTotalSum (PtABPNode pnode); /* soma total repetitiva */
unsigned int ABPMult5Count (PtABPNode proot); /* contagem recursiva dos múltiplos de 5 */
unsigned int ABPEvenCount (PtABPNode proot); /* contagem repetitiva dos pares */
int ABPOddSum (PtABPNode proot); /* soma dos ímpares recursiva */
int ABPEvenOrderSum (PtABPNode proot); /* soma dos elementos com número de ordem par */
int ABPEquals (PtABPNode proot1, PtABPNode proot2); /* verifica se duas arvores sao iguais */

#endif
