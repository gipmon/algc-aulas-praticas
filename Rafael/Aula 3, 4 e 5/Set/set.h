/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstracto Conjunto (set.h).
 O conjunto é composto pela seu cardinal e pelos seus elementos de tipo carácter.
 A implementação providencia um construtor para criar um conjunto vazio. É da
 responsabilidade da aplicação, invocar o destrutor, para libertar a memória
 atribuída ao objecto. O módulo providencia um controlo centralizado de erro,
 disponibilizando uma função para obter o último erro ocorrido, uma função para
 obter uma mensagem de erro elucidativa e uma função para limpar o erro.
 Providencia também operações para armazenar e recuperar conjuntos para ficheiros.

 Autor : António Manuel Adrego da Rocha    Data : Março de 2013

*******************************************************************************/

#ifndef _SET
#define _SET

/**************** Definição do Tipo Ponteiro para um Conjunto *****************/

typedef struct set *PtSet;

/************************ Definição de Códigos de Erro ************************/

#define  OK        0  /* operação realizada com sucesso */
#define  NO_SET    1  /* o(s) conjunto(s) não existe(m) */
#define  NO_MEM    2  /* memória esgotada */
#define  NO_FILE   3  /* o ficheiro não existe */
#define  NO_ELEM   4  /* o elemento não existe no conjunto */
#define  REP_ELEM  5  /* o elemento já existe no conjunto */

/*************************** Protótipos das Funções ***************************/

void SetClearError (void);
/*******************************************************************************
 Inicialização do erro.
*******************************************************************************/

int SetError (void);
/*******************************************************************************
 Devolve o código do último erro ocorrido.
*******************************************************************************/

char *SetErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do último erro ocorrido.
*******************************************************************************/

PtSet SetCreate (void);
/*******************************************************************************
 Cria um conjunto nulo. Devolve a referência do conjunto criado ou NULL, caso
 não consiga criar o conjunto, por falta de memória. Valores de erro: OK ou NO_MEM.
*******************************************************************************/

void SetDestroy (PtSet *pset);
/*******************************************************************************
 Destrói o conjunto pset, caso ele exista, e coloca a sua referência a NULL.
 Valores de erro: OK ou NO_SET.
*******************************************************************************/

PtSet SetCopy (PtSet pset);
/*******************************************************************************
 Copia o conjunto pset, caso ele exista. Devolve a referência do conjunto cópia 
 ou NULL, caso não consiga fazer a cópia. Valores de erro: OK, NO_SET ou NO_MEM.
*******************************************************************************/

int SetCardinal (PtSet pset);
/*******************************************************************************
 Determina o cardinal do conjunto pset. Valores de erro: OK ou NO_SET.
*******************************************************************************/

int SetInsertElement (PtSet pset, char pelem);
/*******************************************************************************
 Insere pelem no conjunto pset, caso ele ainda não exista no conjunto. Devolve 1
 no caso da inserção ser realizada com sucesso e 0 no caso contrário.
 Valores de erro: OK, NO_SET, REP_ELEM ou NO_MEM.
*******************************************************************************/

int SetDeleteElement (PtSet pset, char pelem);
/*******************************************************************************
 Remove pelem do conjunto pset, caso ele exista no conjunto. Devolve 1 no caso
 da remoção ser realizada com sucesso e 0 no caso contrário.
 Valores de erro: OK, NO_SET ou NO_ELEM.
*******************************************************************************/

char SetObserveElement (PtSet pset, unsigned int ppos);
/*******************************************************************************
 Devolve o elemento armazenado na posição ppos do conjunto pset.
 Valores de erro: OK, NO_SET ou NO_ELEM.
*******************************************************************************/

int SetSearchElement (PtSet pset, char pelem);
/*******************************************************************************
 Verifica se pelem existe no conjunto pset. Devolve 1 em caso afirmativo e 0 em 
 caso contrário. Valores de erro: OK ou NO_SET.
*******************************************************************************/

PtSet SetReunion (PtSet pset1, PtSet pset2);
/*******************************************************************************
 Faz a reunião dos dois conjuntos pset1 e pset2. Devolve a referência do conjunto
 criado ou NULL, caso não consiga realizar a reunião por falta de memória.
 Valores de erro: OK, NO_SET ou NO_MEM.
*******************************************************************************/

PtSet SetIntersection (PtSet pset1, PtSet pset2);
/*******************************************************************************
 Faz a intersecção dos dois conjuntos pset1 e pset2. Devolve a referência do 
 conjunto criado ou NULL, caso não consiga realizar a intersecção por falta de
 memória. Valores de erro: OK, NO_SET ou NO_MEM.
*******************************************************************************/

PtSet SetSymmetricDifference (PtSet pset1, PtSet pset2);
/*******************************************************************************
 Faz a diferença simétrica dos dois conjuntos pset1 e pset2 (a reunião menos a 
 intersecção ). Devolve a referência do conjunto criado ou NULL, caso não consiga
 realizar a intersecção por falta de memória. Valores de erro: OK, NO_SET ou NO_MEM.
*******************************************************************************/

int SetEquals (PtSet pset1, PtSet pset2);
/*******************************************************************************
 Compara se os dois conjuntos pset1 e pset2 são idênticos. Devolve 1 em caso 
 afirmativo e 0 em caso contrário. Valores de erro: OK ou NO_SET.
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
 referência do conjunto criado ou NULL, caso não consiga criar o conjunto, por
 falta de memória. Valores de erro: OK, NO_FILE ou NO_MEM.
*******************************************************************************/

#endif
