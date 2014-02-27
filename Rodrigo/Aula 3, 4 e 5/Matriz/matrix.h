/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstracto Matriz (matrix.h). A matriz �
 identificada pela sua dimens�o, ou seja, pelo n�mero de linhas NL e pelo n�mero
 de colunas NC e armazena elementos inteiros. A implementa��o providencia um
 construtor para criar uma matriz nula. � da responsabilidade da aplica��o,
 invocar o destrutor, para libertar a mem�ria atribu�da ao objecto. O m�dulo
 providencia um controlo centralizado de erro, disponibilizando uma fun��o para
 obter o �ltimo erro ocorrido, uma fun��o para obter uma mensagem de erro
 elucidativa e uma fun��o para limpar o erro. Providencia tamb�m opera��es para
 armazenar e recuperar matrizes para ficheiros.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Mar�o de 2013

*******************************************************************************/

#ifndef _MATRIX
#define _MATRIX

/***************** Defini��o do Tipo Ponteiro para uma Matriz *****************/

typedef struct matrix *PtMatrix;

/************************ Defini��o de C�digos de Erro ************************/

#define  OK          0  /* opera��o realizada com sucesso */
#define  NO_MATRIX   1  /* a(s) matriz(es) n�o existe(m) */
#define  NO_MEM      2  /* mem�ria esgotada */
#define  NO_FILE     3  /* o ficheiro n�o existe */
#define  BAD_SIZE    4  /* dimens�o errada */
#define  BAD_INDEX   5  /* elemento inexistente na matriz */
#define  DIF_SIZE    6  /* matrizes com dimens�es diferentes */
#define  NO_CHAINED  7  /* matrizes n�o encadeadas */
#define  NULL_PTR    8  /* ponteiro nulo */

/*************************** Prot�tipos das Fun��es ***************************/

void MatrixClearError (void);
/*******************************************************************************
 Inicializa��o do erro.
*******************************************************************************/

int MatrixError (void);
/*******************************************************************************
 Devolve o c�digo do �ltimo erro ocorrido.
*******************************************************************************/

char *MatrixErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do �ltimo erro ocorrido.
*******************************************************************************/

PtMatrix MatrixCreate (unsigned int pnl, unsigned int pnc);
/*******************************************************************************
 Cria uma matriz nula, com pnl linhas e pnc colunas, para armazenar elementos
 inteiros. Devolve a refer�ncia da matriz criada ou NULL, caso n�o consiga criar
 a matriz. Valores de erro: OK, BAD_SIZE ou NO_MEM.
*******************************************************************************/

void MatrixDestroy (PtMatrix *pmatrix);
/*******************************************************************************
 Destr�i a matriz pmatrix, caso ela exista, e coloca a sua refer�ncia a NULL.
 Valores de erro: OK ou NO_MATRIX.
*******************************************************************************/

PtMatrix MatrixCopy (PtMatrix pmatrix);
/*******************************************************************************
 Copia a matriz pmatrix, caso ela exista. Devolve a refer�ncia da matriz criada ou 
 NULL, caso n�o consiga criar a matriz. Valores de erro: NO_MATRIX ou NO_MEM.
*******************************************************************************/

void MatrixSize (PtMatrix pmatrix, unsigned int *pnl, unsigned int *pnc);
/*******************************************************************************
 Devolve a dimens�o da matriz pmatrix, caso ela exista. Valores de erro: OK, 
 NO_MATRIX ou NULL_PTR.
*******************************************************************************/

void MatrixModifyElement (PtMatrix pmatrix, unsigned int pl, unsigned int pc, int pval);
/*******************************************************************************
 Armazena pval na linha pl e na coluna pc da matriz pmatrix. Valores de erro: OK, 
 NO_MATRIX ou BAD_INDEX.
*******************************************************************************/

int MatrixObserveElement (PtMatrix pmatrix, unsigned int pl, unsigned int pc);
/*******************************************************************************
 Devolve o valor armazenado na linha pl e na coluna pc da matriz pmatrix.
 Valores de erro: OK, NO_MATRIX ou BAD_INDEX.
*******************************************************************************/

PtMatrix MatrixTranspose (PtMatrix pmatrix);
/*******************************************************************************
 Calcula a matriz transposta da matriz pmatrix. Devolve a refer�ncia da matriz
 transposta ou NULL, caso n�o consiga fazer a opera��o. Valores de erro: OK, 
 NO_MATRIX ou NO_MEM.
*******************************************************************************/
 
PtMatrix MatrixAddition (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Soma as duas matrizes pmatrix1 e pmatrix2. Devolve a refer�ncia da matriz soma ou NULL,
 caso n�o consiga fazer a adi��o. Valores de erro: OK, NO_MATRIX, DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtMatrix MatrixSubtraction (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Subtrai as duas matrizes pmatrix1 e pmatrix2. Devolve a refer�ncia da matriz diferen�a
 ou NULL, caso n�o consiga fazer a subtrac��o. Valores de erro: OK, NO_MATRIX, 
 DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtMatrix MatrixMultiplication (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Multiplica as duas matrizes pmatrix1 e pmatrix2 usando o algoritmo directo. Devolve
 a refer�ncia da matriz produto ou NULL, caso n�o consiga fazer a multipli��o.
 Valores de erro: OK, NO_MATRIX, NO_CHAINED ou NO_MEM.
*******************************************************************************/

int MatrixEquals (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Compara se as duas matrizes pmatrix1 e pmatrix2 s�o id�nticas. Devolve 1 em caso 
 afirmativo e 0 em caso contr�rio. Valores de erro: OK, NO_MATRIX ou DIF_SIZE.
*******************************************************************************/

void MatrixStoreFile (PtMatrix pmatrix, char *pfname);
/*******************************************************************************
 Armazena a matriz pmatrix, caso ela exista, no ficheiro pfname. O ficheiro tem na 
 primeira linha o n�mero de linhas e o n�mero de colunas da matriz, seguido das 
 linhas de elementos da matrix. Valores de erro: OK, NO_MATRIX ou NO_FILE.
*******************************************************************************/

PtMatrix MatrixCreateFile (char *pfname);
/*******************************************************************************
 Cria uma matriz a partir de informa��o lida do ficheiro pfname. Devolve a
 refer�ncia da matriz criada ou NULL, caso n�o consiga criar a matriz.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.
*******************************************************************************/

#endif
