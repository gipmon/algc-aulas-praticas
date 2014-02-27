/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstracto Conjunto (set.h).
 O conjunto � composto pela seu cardinal e pelos seus elementos de tipo car�cter.
 A implementa��o providencia um construtor para criar um conjunto vazio. � da
 responsabilidade da aplica��o, invocar o destrutor, para libertar a mem�ria
 atribu�da ao objecto. O m�dulo providencia um controlo centralizado de erro,
 disponibilizando uma fun��o para obter o �ltimo erro ocorrido, uma fun��o para
 obter uma mensagem de erro elucidativa e uma fun��o para limpar o erro.
 Providencia tamb�m opera��es para armazenar e recuperar conjuntos para ficheiros.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Mar�o de 2013

*******************************************************************************/

#ifndef _SET
#define _SET

/**************** Defini��o do Tipo Ponteiro para um Conjunto *****************/

typedef struct set *PtSet;

/************************ Defini��o de C�digos de Erro ************************/

#define  OK        0  /* opera��o realizada com sucesso */
#define  NO_SET    1  /* o(s) conjunto(s) n�o existe(m) */
#define  NO_MEM    2  /* mem�ria esgotada */
#define  NO_FILE   3  /* o ficheiro n�o existe */
#define  NO_ELEM   4  /* o elemento n�o existe no conjunto */
#define  REP_ELEM  5  /* o elemento j� existe no conjunto */

/*************************** Prot�tipos das Fun��es ***************************/

void SetClearError (void);
/*******************************************************************************
 Inicializa��o do erro.
*******************************************************************************/

int SetError (void);
/*******************************************************************************
 Devolve o c�digo do �ltimo erro ocorrido.
*******************************************************************************/

char *SetErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do �ltimo erro ocorrido.
*******************************************************************************/

PtSet SetCreate (void);
/*******************************************************************************
 Cria um conjunto nulo. Devolve a refer�ncia do conjunto criado ou NULL, caso
 n�o consiga criar o conjunto, por falta de mem�ria. Valores de erro: OK ou NO_MEM.
*******************************************************************************/

void SetDestroy (PtSet *pset);
/*******************************************************************************
 Destr�i o conjunto pset, caso ele exista, e coloca a sua refer�ncia a NULL.
 Valores de erro: OK ou NO_SET.
*******************************************************************************/

PtSet SetCopy (PtSet pset);
/*******************************************************************************
 Copia o conjunto pset, caso ele exista. Devolve a refer�ncia do conjunto c�pia 
 ou NULL, caso n�o consiga fazer a c�pia. Valores de erro: OK, NO_SET ou NO_MEM.
*******************************************************************************/

int SetCardinal (PtSet pset);
/*******************************************************************************
 Determina o cardinal do conjunto pset. Valores de erro: OK ou NO_SET.
*******************************************************************************/

int SetInsertElement (PtSet pset, char pelem);
/*******************************************************************************
 Insere pelem no conjunto pset, caso ele ainda n�o exista no conjunto. Devolve 1
 no caso da inser��o ser realizada com sucesso e 0 no caso contr�rio.
 Valores de erro: OK, NO_SET, REP_ELEM ou NO_MEM.
*******************************************************************************/

int SetDeleteElement (PtSet pset, char pelem);
/*******************************************************************************
 Remove pelem do conjunto pset, caso ele exista no conjunto. Devolve 1 no caso
 da remo��o ser realizada com sucesso e 0 no caso contr�rio.
 Valores de erro: OK, NO_SET ou NO_ELEM.
*******************************************************************************/

char SetObserveElement (PtSet pset, unsigned int ppos);
/*******************************************************************************
 Devolve o elemento armazenado na posi��o ppos do conjunto pset.
 Valores de erro: OK, NO_SET ou NO_ELEM.
*******************************************************************************/

int SetSearchElement (PtSet pset, char pelem);
/*******************************************************************************
 Verifica se pelem existe no conjunto pset. Devolve 1 em caso afirmativo e 0 em 
 caso contr�rio. Valores de erro: OK ou NO_SET.
*******************************************************************************/

PtSet SetReunion (PtSet pset1, PtSet pset2);
/*******************************************************************************
 Faz a reuni�o dos dois conjuntos pset1 e pset2. Devolve a refer�ncia do conjunto
 criado ou NULL, caso n�o consiga realizar a reuni�o por falta de mem�ria.
 Valores de erro: OK, NO_SET ou NO_MEM.
*******************************************************************************/

PtSet SetIntersection (PtSet pset1, PtSet pset2);
/*******************************************************************************
 Faz a intersec��o dos dois conjuntos pset1 e pset2. Devolve a refer�ncia do 
 conjunto criado ou NULL, caso n�o consiga realizar a intersec��o por falta de
 mem�ria. Valores de erro: OK, NO_SET ou NO_MEM.
*******************************************************************************/

PtSet SetSymmetricDifference (PtSet pset1, PtSet pset2);
/*******************************************************************************
 Faz a diferen�a sim�trica dos dois conjuntos pset1 e pset2 (a reuni�o menos a 
 intersec��o ). Devolve a refer�ncia do conjunto criado ou NULL, caso n�o consiga
 realizar a intersec��o por falta de mem�ria. Valores de erro: OK, NO_SET ou NO_MEM.
*******************************************************************************/

int SetEquals (PtSet pset1, PtSet pset2);
/*******************************************************************************
 Compara se os dois conjuntos pset1 e pset2 s�o id�nticos. Devolve 1 em caso 
 afirmativo e 0 em caso contr�rio. Valores de erro: OK ou NO_SET.
*******************************************************************************/

void SetStoreFile (PtSet pset, char *pfname);
/*******************************************************************************
 Armazena o conjunto pset, caso ele exista, no ficheiro pfname. O ficheiro tem
 na primeira linha o cardinal do conjunto, seguido dos elementos, um por linha.
 Valores de erro: OK, NO_SET ou NO_FILE.
*******************************************************************************/

PtSet SetCreateFile (char *pfname);
/*******************************************************************************
 Cria um conjunto a partir de informacao lida do ficheiro pfname. Devolve a
 refer�ncia do conjunto criado ou NULL, caso n�o consiga criar o conjunto, por
 falta de mem�ria. Valores de erro: OK, NO_FILE ou NO_MEM.
*******************************************************************************/

#endif
