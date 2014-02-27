/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstracto Vector (vector.h). O vector é
 composto pela sua dimensão e pelas suas componentes reais. A implementação
 providencia um construtor para criar um vector nulo com a dimensão pretendida.
 É da responsabilidade da aplicação, invocar o destrutor, para libertar a
 memória atribuída ao objecto. O módulo providencia um controlo centralizado de
 erro, disponibilizando uma função para obter o último erro ocorrido, uma função
 para obter uma mensagem de erro elucidativa e uma função para limpar o erro.
 Providencia também operações para armazenar e recuperar vectores para ficheiros.

 Autor : António Manuel Adrego da Rocha    Data : Março de 2013

*******************************************************************************/

#ifndef _VECTOR
#define _VECTOR

/****************** Definição do Tipo Ponteiro para um VECTOR *****************/

typedef struct vector *PtVector;

/************************ Definição de Códigos de Erro ************************/

#define  OK         0  /* operação realizada com sucesso */
#define  NO_VECTOR  1  /* o(s) vector(es) não existe(m) */
#define  NO_MEM     2  /* memória esgotada */
#define  NO_FILE    3  /* o ficheiro não existe */
#define  BAD_SIZE   4  /* dimensão do vector errada */
#define  BAD_INDEX  5  /* elemento inexistente no vector */
#define  DIF_SIZE   6  /* vectores com dimensões diferentes */

/*************************** Protótipos das Funções ***************************/

void VectorClearError (void);
/*******************************************************************************
 Inicialização do erro.
*******************************************************************************/

int VectorError (void);
/*******************************************************************************
 Devolve o código do último erro ocorrido.
*******************************************************************************/

char *VectorErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do último erro ocorrido.
*******************************************************************************/

PtVector VectorCreate (unsigned int pdim);
/*******************************************************************************
 Cria um vector nulo, de componentes reais, com a dimensão indicada por pdim.
 Devolve a referência do vector criado ou NULL, caso não consiga criar o vector,
 por falta de memória. Valores de erro: OK, BAD_SIZE ou NO_MEM.
*******************************************************************************/

void VectorDestroy (PtVector *pvector);
/*******************************************************************************
 Destrói o vector pvector, caso ele exista, e coloca a sua
 referência a NULL. Valores de erro: OK ou NO_VECTOR.
*******************************************************************************/

PtVector VectorCopy (PtVector pvector);
/*******************************************************************************
 Copia o vector pvector, caso ele exista. Devolve a referência do vector cópia ou 
 NULL, caso não consiga fazer a cópia. Valores de erro: OK, NO_VECTOR ou NO_MEM.
*******************************************************************************/

int VectorDimension (PtVector pvector);
/*******************************************************************************
 Devolve a dimensão do vector pvector. Valores de erro: OK ou NO_VECTOR.
*******************************************************************************/

void VectorModifyComponent (PtVector pvector, unsigned int ppos, double pval);
/*******************************************************************************
 Armazena pval no índice ppos do vector pvector.
 Valores de erro: OK, NO_VECTOR ou BAD_INDEX.
*******************************************************************************/

double VectorObserveComponent (PtVector pvector, unsigned int ppos);
/*******************************************************************************
 Devolve o valor armazenado no índice ppos do vector pvector.
 Valores de erro: OK, NO_VECTOR ou BAD_INDEX.
*******************************************************************************/

int VectorIsNull (PtVector pvector);
/*******************************************************************************
 Verifica se o vector pvector é um vector nulo. Devolve 1 em caso afirmativo e 0
 em caso contrário. Valores de erro: OK ou NO_VECTOR.
*******************************************************************************/

PtVector VectorAddition (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Soma os dois vectores pvector1 e pvector2. Devolve a referência do vector soma ou NULL,
 caso não consiga fazer a adição. Valores de erro: OK, NO_VECTOR, DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtVector VectorSubtraction (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Subtrai os dois vectores pvector1 e pvector2. Devolve a referência do vector 
 diferença ou NULL, caso não consiga fazer a subtracção. Valores de erro: OK, 
 NO_VECTOR, DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtVector VectorMultiplication (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Faz o produto vectorial dos dois vectores pvector1 e pvector2. Devolve a referência 
 do vector produto ou NULL, caso não consiga fazer a multiplicação. Valores de 
 erro: OK, NO_VECTOR ou DIF_SIZE.
*******************************************************************************/

double VectorScalarMultiplication (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Devolve o produto escalar dos dois vectores pvector1 e pvector2, ou 0, caso não 
 possa realizar o produto. Valores de erro: OK, NO_VECTOR ou DIF_SIZE.
*******************************************************************************/

int VectorEquals (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Compara se os dois vectores pvector1 e pvector2 são idênticos. Devolve 1 em caso 
 afirmativo e 0 em caso contrário. Valores de erro: OK, NO_VECTOR ou DIF_SIZE.
*******************************************************************************/

void VectorStoreFile (PtVector pvector, char *pfname);
/*******************************************************************************
 Armazena o vector pvector, caso ele exista, no ficheiro pfname. O ficheiro tem na 
 primeira linha o número de componentes do vector, seguido das componentes, uma 
 por linha. Valores de erro: OK, NO_VECTOR ou NO_FILE.
*******************************************************************************/

PtVector VectorCreateFile (char *pfname);
/*******************************************************************************
 Cria um vector a partir de informação lida do ficheiro pfname. Devolve a
 referência do vector criado ou NULL, caso não consiga criar o vector.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.
*******************************************************************************/

#endif
