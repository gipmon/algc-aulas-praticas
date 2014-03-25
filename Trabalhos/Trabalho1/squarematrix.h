/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstrato MATRIZ QUADRADA (squarematrix.h).
 A matriz quadrada é identificada pela sua dimensão e armazena elementos reais.
 A implementação providencia dois construtores: um para criar uma matriz nula, e 
 outro para criar uma matriz a partir de uma sequência unidimensional de reais.
 É da responsabilidade da aplicação, invocar o destrutor, para libertar a memória 
 atribuída ao objecto. O módulo providencia um controlo centralizado de erro, 
 disponibilizando uma função para obter o último erro ocorrido, uma função para 
 obter uma mensagem de erro elucidativa e uma função para limpar o erro. Providencia
 também operações para armazenar e recuperar matrizes quadradas para ficheiros.

 Autor : António Manuel Adrego da Rocha    Data : Março de 2014

*******************************************************************************/

#ifndef _SQUARE_MATRIX
#define _SQUARE_MATRIX

/************ Definição do Tipo Ponteiro para uma Matriz Quadrada *************/

typedef struct squarematrix *PtSMatrix;

/************************ Definição de Códigos de Erro ************************/

#define  OK            0  /* operação realizada com sucesso */
#define  NO_MATRIX     1  /* a(s) matriz(es) não existe(m) */
#define  NO_MEM        2  /* memória esgotada */
#define  NO_FILE       3  /* o ficheiro não existe */
#define  BAD_SIZE      4  /* dimensão errada */
#define  BAD_INDEX     5  /* elemento inexistente na matriz */
#define  DIF_SIZE      6  /* matrizes com dimensões diferentes */
#define  NO_CHAINED    7  /* matrizes não encadeadas */
#define  NULL_PTR      8  /* ponteiro nulo */
#define  NO_POWERTWO   9  /* a dimensão da matriz não é uma potência de 2 */
#define  BAD_ROW      10  /* linha inexistente */
#define  BAD_COLUMN   11  /* coluna inexistente */

/*************************** Protótipos das Funções ***************************/

void SMatrixClearError (void);
/*******************************************************************************
 Inicialização do erro.
*******************************************************************************/

int SMatrixError (void);
/*******************************************************************************
 Devolve o código do último erro ocorrido.
*******************************************************************************/

char *SMatrixErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do último erro ocorrido.
*******************************************************************************/

PtSMatrix SMatrixCreate (unsigned int psize);
/*******************************************************************************
 Cria uma matriz quadrada nula com dimensão psize para armazenar elementos reais.
 Devolve a referência da matriz criada ou NULL, caso não consiga criar a matriz.
 Valores de erro: OK, BAD_SIZE ou NO_MEM.
*******************************************************************************/

PtSMatrix SMatrixCreateArray (unsigned int pn, double parray[]);
/*******************************************************************************
 Cria uma matriz quadrada a partir de uma sequência (com pn x pn) elementos 
 que representa uma matriz. Devolve a referência da matriz criada ou NULL, caso
 não consiga criar a matriz. Valores de erro: OK, BAD_SIZE, NULL_PTR ou NO_MEM.
*******************************************************************************/

void SMatrixDestroy (PtSMatrix *pmatrix);
/*******************************************************************************
 Destrói a matriz pmatrix, caso ela exista, e coloca a sua referência a NULL.
 Valores de erro: OK ou NO_MATRIX.
*******************************************************************************/

PtSMatrix SMatrixCopy (PtSMatrix pmatrix);
/*******************************************************************************
 Copia a matriz pmatrix, caso ela exista. Devolve a referência da matriz criada ou 
 NULL, caso não consiga criar a matriz. Valores de erro: OK, NO_MATRIX ou NO_MEM.
*******************************************************************************/

unsigned int SMatrixSize (PtSMatrix pmatrix);
/*******************************************************************************
 Devolve a dimensão da matriz pmatrix, caso ela exista.
 Valores de erro: OK ou NO_MATRIX.
*******************************************************************************/

void SMatrixModifyElement (PtSMatrix pmatrix, unsigned int pl, unsigned int pc, double pvalue);
/*******************************************************************************
 Armazena pvalue na linha pl e na coluna pc da matriz pmatrix.
 Valores de erro: OK, NO_MATRIX ou BAD_INDEX.
*******************************************************************************/

double SMatrixObserveElement (PtSMatrix pmatrix, unsigned int pl, unsigned int pc);
/*******************************************************************************
 Devolve o valor armazenado na linha pl e na coluna pc da matriz pmatrix.
 Valores de erro: OK, NO_MATRIX ou BAD_INDEX.
*******************************************************************************/

PtSMatrix SMatrixTranspose (PtSMatrix pmatrix);
/*******************************************************************************
 Cria a matriz transposta da matriz pmatrix. Devolve a referência da matriz
 transposta ou NULL, caso não consiga fazer a operação.
 Valores de erro: OK, NO_MATRIX ou NO_MEM.
*******************************************************************************/
 
PtSMatrix SMatrixAdd (PtSMatrix pmatrix1, PtSMatrix pmatrix2);
/*******************************************************************************
 Soma as as matrizes pmatrix1 e pmatrix2. Devolve a referência da matriz soma ou NULL,
 caso não consiga fazer a adição. Valores de erro: OK, NO_MATRIX, DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtSMatrix SMatrixSub (PtSMatrix pmatrix1, PtSMatrix pmatrix2);
/*******************************************************************************
 Subtrai as matrizes pmatrix1 e pmatrix2. Devolve a referência da matriz diferença
 ou NULL, caso não consiga fazer a subtracção.
 Valores de erro: OK, NO_MATRIX, DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtSMatrix SMatrixMult (PtSMatrix pmatrix1, PtSMatrix pmatrix2);
/*******************************************************************************
 Multiplica as matrizes pmatrix1 e pmatrix2. Devolve a referência da matriz
 produto ou NULL, caso não consiga fazer a multiplição.
 Valores de erro: OK, NO_MATRIX, NO_CHAINED ou NO_MEM.
*******************************************************************************/

double SMatrixDeterminant (PtSMatrix pmatrix);
/*******************************************************************************
 Calcula e devolve o determinante da matriz pmatrix usando o algoritmo de eliminação
 de Gauss. Valores de erro: OK ou NO_MATRIX.
*******************************************************************************/

int SMatrixEquals (PtSMatrix pmatrix1, PtSMatrix pmatrix2);
/*******************************************************************************
 Compara se as duas matrizes pmatrix1 e pmatrix2 são idênticas. Devolve 1 em caso 
 afirmativo e 0 no caso contrário. Valores de erro: OK, NO_MATRIX ou DIF_SIZE.
*******************************************************************************/

void SMatrixStoreFile (PtSMatrix pmatrix, char *pfname);
/*******************************************************************************
 Armazena a matriz pmatrix, caso ela exista, no ficheiro pfname. O ficheiro tem na 
 primeira linha o número de linhas e o número de colunas da matriz, seguido das 
 linhas de elementos da matrix. Valores de erro: OK, NO_MATRIX ou NO_FILE.
*******************************************************************************/

PtSMatrix SMatrixCreateFile (char *pfname);
/*******************************************************************************
 Cria uma matriz a partir de informação lida do ficheiro pfname. Devolve a
 referência da matriz criada ou NULL, caso não consiga criar a matriz.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.
*******************************************************************************/

PtSMatrix SMatrixCreateIdentity (unsigned int psize);
/*******************************************************************************
 Cria uma matriz quadrada identidade com dimensão psize. Devolve a referência
 da matriz criada ou NULL, caso não consiga criar a matriz.
 Valores de erro: OK, BAD_SIZE ou NO_MEM.
*******************************************************************************/

PtSMatrix SMatrixMultByScalar (PtSMatrix pmatrix, double pvalue);
/*******************************************************************************
 Multiplica a matriz pmatrix pelo escalar pvalue. Devolve a referência da matriz
 produto ou NULL, caso não consiga fazer a multiplição.
 Valores de erro: OK, NO_MATRIX ou NO_MEM.
*******************************************************************************/

int SMatrixIsSymetric (PtSMatrix pmatrix);
/*******************************************************************************
 Determina se a matriz por pmatrix é uma matriz simétrica. Devolve 1 em caso 
 afirmativo e 0 no caso contrário. Valores de erro: OK ou NO_MATRIX.
*******************************************************************************/

void SMatrixExchangeRow (PtSMatrix pmatrix, unsigned int pk, unsigned int pl);
/*******************************************************************************
 Altera a matriz pmatrix, permutando as linhas pk e pl, tendo em atenção que as
 linhas devem ser referenciadas de 1 a Size.
 Valores de erro: OK, NO_MATRIX ou BAD_ROW.
*******************************************************************************/

void SMatrixExchangeColumn (PtSMatrix pmatrix, unsigned int pk, unsigned int pc);
/*******************************************************************************
 Altera a matriz pmatrix, permutando as colunas pk e pc, tendo em atenção que as
 colunas devem ser referenciadas de 1 a Size.
 Valores de erro: OK, NO_MATRIX ou BAD_COLUMN.
*******************************************************************************/

#endif
