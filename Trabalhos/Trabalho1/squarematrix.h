/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstrato MATRIZ QUADRADA (squarematrix.h).
 A matriz quadrada � identificada pela sua dimens�o e armazena elementos reais.
 A implementa��o providencia dois construtores: um para criar uma matriz nula, e 
 outro para criar uma matriz a partir de uma sequ�ncia unidimensional de reais.
 � da responsabilidade da aplica��o, invocar o destrutor, para libertar a mem�ria 
 atribu�da ao objecto. O m�dulo providencia um controlo centralizado de erro, 
 disponibilizando uma fun��o para obter o �ltimo erro ocorrido, uma fun��o para 
 obter uma mensagem de erro elucidativa e uma fun��o para limpar o erro. Providencia
 tamb�m opera��es para armazenar e recuperar matrizes quadradas para ficheiros.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Mar�o de 2014

*******************************************************************************/

#ifndef _SQUARE_MATRIX
#define _SQUARE_MATRIX

/************ Defini��o do Tipo Ponteiro para uma Matriz Quadrada *************/

typedef struct squarematrix *PtSMatrix;

/************************ Defini��o de C�digos de Erro ************************/

#define  OK            0  /* opera��o realizada com sucesso */
#define  NO_MATRIX     1  /* a(s) matriz(es) n�o existe(m) */
#define  NO_MEM        2  /* mem�ria esgotada */
#define  NO_FILE       3  /* o ficheiro n�o existe */
#define  BAD_SIZE      4  /* dimens�o errada */
#define  BAD_INDEX     5  /* elemento inexistente na matriz */
#define  DIF_SIZE      6  /* matrizes com dimens�es diferentes */
#define  NO_CHAINED    7  /* matrizes n�o encadeadas */
#define  NULL_PTR      8  /* ponteiro nulo */
#define  NO_POWERTWO   9  /* a dimens�o da matriz n�o � uma pot�ncia de 2 */
#define  BAD_ROW      10  /* linha inexistente */
#define  BAD_COLUMN   11  /* coluna inexistente */

/*************************** Prot�tipos das Fun��es ***************************/

void SMatrixClearError (void);
/*******************************************************************************
 Inicializa��o do erro.
*******************************************************************************/

int SMatrixError (void);
/*******************************************************************************
 Devolve o c�digo do �ltimo erro ocorrido.
*******************************************************************************/

char *SMatrixErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do �ltimo erro ocorrido.
*******************************************************************************/

PtSMatrix SMatrixCreate (unsigned int psize);
/*******************************************************************************
 Cria uma matriz quadrada nula com dimens�o psize para armazenar elementos reais.
 Devolve a refer�ncia da matriz criada ou NULL, caso n�o consiga criar a matriz.
 Valores de erro: OK, BAD_SIZE ou NO_MEM.
*******************************************************************************/

PtSMatrix SMatrixCreateArray (unsigned int pn, double parray[]);
/*******************************************************************************
 Cria uma matriz quadrada a partir de uma sequ�ncia (com pn x pn) elementos 
 que representa uma matriz. Devolve a refer�ncia da matriz criada ou NULL, caso
 n�o consiga criar a matriz. Valores de erro: OK, BAD_SIZE, NULL_PTR ou NO_MEM.
*******************************************************************************/

void SMatrixDestroy (PtSMatrix *pmatrix);
/*******************************************************************************
 Destr�i a matriz pmatrix, caso ela exista, e coloca a sua refer�ncia a NULL.
 Valores de erro: OK ou NO_MATRIX.
*******************************************************************************/

PtSMatrix SMatrixCopy (PtSMatrix pmatrix);
/*******************************************************************************
 Copia a matriz pmatrix, caso ela exista. Devolve a refer�ncia da matriz criada ou 
 NULL, caso n�o consiga criar a matriz. Valores de erro: OK, NO_MATRIX ou NO_MEM.
*******************************************************************************/

unsigned int SMatrixSize (PtSMatrix pmatrix);
/*******************************************************************************
 Devolve a dimens�o da matriz pmatrix, caso ela exista.
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
 Cria a matriz transposta da matriz pmatrix. Devolve a refer�ncia da matriz
 transposta ou NULL, caso n�o consiga fazer a opera��o.
 Valores de erro: OK, NO_MATRIX ou NO_MEM.
*******************************************************************************/
 
PtSMatrix SMatrixAdd (PtSMatrix pmatrix1, PtSMatrix pmatrix2);
/*******************************************************************************
 Soma as as matrizes pmatrix1 e pmatrix2. Devolve a refer�ncia da matriz soma ou NULL,
 caso n�o consiga fazer a adi��o. Valores de erro: OK, NO_MATRIX, DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtSMatrix SMatrixSub (PtSMatrix pmatrix1, PtSMatrix pmatrix2);
/*******************************************************************************
 Subtrai as matrizes pmatrix1 e pmatrix2. Devolve a refer�ncia da matriz diferen�a
 ou NULL, caso n�o consiga fazer a subtrac��o.
 Valores de erro: OK, NO_MATRIX, DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtSMatrix SMatrixMult (PtSMatrix pmatrix1, PtSMatrix pmatrix2);
/*******************************************************************************
 Multiplica as matrizes pmatrix1 e pmatrix2. Devolve a refer�ncia da matriz
 produto ou NULL, caso n�o consiga fazer a multipli��o.
 Valores de erro: OK, NO_MATRIX, NO_CHAINED ou NO_MEM.
*******************************************************************************/

double SMatrixDeterminant (PtSMatrix pmatrix);
/*******************************************************************************
 Calcula e devolve o determinante da matriz pmatrix usando o algoritmo de elimina��o
 de Gauss. Valores de erro: OK ou NO_MATRIX.
*******************************************************************************/

int SMatrixEquals (PtSMatrix pmatrix1, PtSMatrix pmatrix2);
/*******************************************************************************
 Compara se as duas matrizes pmatrix1 e pmatrix2 s�o id�nticas. Devolve 1 em caso 
 afirmativo e 0 no caso contr�rio. Valores de erro: OK, NO_MATRIX ou DIF_SIZE.
*******************************************************************************/

void SMatrixStoreFile (PtSMatrix pmatrix, char *pfname);
/*******************************************************************************
 Armazena a matriz pmatrix, caso ela exista, no ficheiro pfname. O ficheiro tem na 
 primeira linha o n�mero de linhas e o n�mero de colunas da matriz, seguido das 
 linhas de elementos da matrix. Valores de erro: OK, NO_MATRIX ou NO_FILE.
*******************************************************************************/

PtSMatrix SMatrixCreateFile (char *pfname);
/*******************************************************************************
 Cria uma matriz a partir de informa��o lida do ficheiro pfname. Devolve a
 refer�ncia da matriz criada ou NULL, caso n�o consiga criar a matriz.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.
*******************************************************************************/

PtSMatrix SMatrixCreateIdentity (unsigned int psize);
/*******************************************************************************
 Cria uma matriz quadrada identidade com dimens�o psize. Devolve a refer�ncia
 da matriz criada ou NULL, caso n�o consiga criar a matriz.
 Valores de erro: OK, BAD_SIZE ou NO_MEM.
*******************************************************************************/

PtSMatrix SMatrixMultByScalar (PtSMatrix pmatrix, double pvalue);
/*******************************************************************************
 Multiplica a matriz pmatrix pelo escalar pvalue. Devolve a refer�ncia da matriz
 produto ou NULL, caso n�o consiga fazer a multipli��o.
 Valores de erro: OK, NO_MATRIX ou NO_MEM.
*******************************************************************************/

int SMatrixIsSymetric (PtSMatrix pmatrix);
/*******************************************************************************
 Determina se a matriz por pmatrix � uma matriz sim�trica. Devolve 1 em caso 
 afirmativo e 0 no caso contr�rio. Valores de erro: OK ou NO_MATRIX.
*******************************************************************************/

void SMatrixExchangeRow (PtSMatrix pmatrix, unsigned int pk, unsigned int pl);
/*******************************************************************************
 Altera a matriz pmatrix, permutando as linhas pk e pl, tendo em aten��o que as
 linhas devem ser referenciadas de 1 a Size.
 Valores de erro: OK, NO_MATRIX ou BAD_ROW.
*******************************************************************************/

void SMatrixExchangeColumn (PtSMatrix pmatrix, unsigned int pk, unsigned int pc);
/*******************************************************************************
 Altera a matriz pmatrix, permutando as colunas pk e pc, tendo em aten��o que as
 colunas devem ser referenciadas de 1 a Size.
 Valores de erro: OK, NO_MATRIX ou BAD_COLUMN.
*******************************************************************************/

#endif
