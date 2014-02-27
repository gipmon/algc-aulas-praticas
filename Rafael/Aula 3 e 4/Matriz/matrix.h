/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstracto Matriz (matrix.h). A matriz é
 identificada pela sua dimensão, ou seja, pelo número de linhas NL e pelo número
 de colunas NC e armazena elementos inteiros. A implementação providencia um
 construtor para criar uma matriz nula. É da responsabilidade da aplicação,
 invocar o destrutor, para libertar a memória atribuída ao objecto. O módulo
 providencia um controlo centralizado de erro, disponibilizando uma função para
 obter o último erro ocorrido, uma função para obter uma mensagem de erro
 elucidativa e uma função para limpar o erro. Providencia também operações para
 armazenar e recuperar matrizes para ficheiros.

 Autor : António Manuel Adrego da Rocha    Data : Março de 2013

*******************************************************************************/

#ifndef _MATRIX
#define _MATRIX

/***************** Definição do Tipo Ponteiro para uma Matriz *****************/

typedef struct matrix *PtMatrix;

/************************ Definição de Códigos de Erro ************************/

#define  OK          0  /* operação realizada com sucesso */
#define  NO_MATRIX   1  /* a(s) matriz(es) não existe(m) */
#define  NO_MEM      2  /* memória esgotada */
#define  NO_FILE     3  /* o ficheiro não existe */
#define  BAD_SIZE    4  /* dimensão errada */
#define  BAD_INDEX   5  /* elemento inexistente na matriz */
#define  DIF_SIZE    6  /* matrizes com dimensões diferentes */
#define  NO_CHAINED  7  /* matrizes não encadeadas */
#define  NULL_PTR    8  /* ponteiro nulo */

/*************************** Protótipos das Funções ***************************/

void MatrixClearError (void);
/*******************************************************************************
 Inicialização do erro.
*******************************************************************************/

int MatrixError (void);
/*******************************************************************************
 Devolve o código do último erro ocorrido.
*******************************************************************************/

char *MatrixErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do último erro ocorrido.
*******************************************************************************/

PtMatrix MatrixCreate (unsigned int pnl, unsigned int pnc);
/*******************************************************************************
 Cria uma matriz nula, com pnl linhas e pnc colunas, para armazenar elementos
 inteiros. Devolve a referência da matriz criada ou NULL, caso não consiga criar
 a matriz. Valores de erro: OK, BAD_SIZE ou NO_MEM.
*******************************************************************************/

void MatrixDestroy (PtMatrix *pmatrix);
/*******************************************************************************
 Destrói a matriz pmatrix, caso ela exista, e coloca a sua referência a NULL.
 Valores de erro: OK ou NO_MATRIX.
*******************************************************************************/

PtMatrix MatrixCopy (PtMatrix pmatrix);
/*******************************************************************************
 Copia a matriz pmatrix, caso ela exista. Devolve a referência da matriz criada ou 
 NULL, caso não consiga criar a matriz. Valores de erro: NO_MATRIX ou NO_MEM.
*******************************************************************************/

void MatrixSize (PtMatrix pmatrix, unsigned int *pnl, unsigned int *pnc);
/*******************************************************************************
 Devolve a dimensão da matriz pmatrix, caso ela exista. Valores de erro: OK, 
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
 Calcula a matriz transposta da matriz pmatrix. Devolve a referência da matriz
 transposta ou NULL, caso não consiga fazer a operação. Valores de erro: OK, 
 NO_MATRIX ou NO_MEM.
*******************************************************************************/
 
PtMatrix MatrixAddition (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Soma as duas matrizes pmatrix1 e pmatrix2. Devolve a referência da matriz soma ou NULL,
 caso não consiga fazer a adição. Valores de erro: OK, NO_MATRIX, DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtMatrix MatrixSubtraction (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Subtrai as duas matrizes pmatrix1 e pmatrix2. Devolve a referência da matriz diferença
 ou NULL, caso não consiga fazer a subtracção. Valores de erro: OK, NO_MATRIX, 
 DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtMatrix MatrixMultiplication (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Multiplica as duas matrizes pmatrix1 e pmatrix2 usando o algoritmo directo. Devolve
 a referência da matriz produto ou NULL, caso não consiga fazer a multiplição.
 Valores de erro: OK, NO_MATRIX, NO_CHAINED ou NO_MEM.
*******************************************************************************/

int MatrixEquals (PtMatrix pmatrix1, PtMatrix pmatrix2);
/*******************************************************************************
 Compara se as duas matrizes pmatrix1 e pmatrix2 são idênticas. Devolve 1 em caso 
 afirmativo e 0 em caso contrário. Valores de erro: OK, NO_MATRIX ou DIF_SIZE.
*******************************************************************************/

void MatrixStoreFile (PtMatrix pmatrix, char *pfname);
/*******************************************************************************
 Armazena a matriz pmatrix, caso ela exista, no ficheiro pfname. O ficheiro tem na 
 primeira linha o número de linhas e o número de colunas da matriz, seguido das 
 linhas de elementos da matrix. Valores de erro: OK, NO_MATRIX ou NO_FILE.
*******************************************************************************/

PtMatrix MatrixCreateFile (char *pfname);
/*******************************************************************************
 Cria uma matriz a partir de informação lida do ficheiro pfname. Devolve a
 referência da matriz criada ou NULL, caso não consiga criar a matriz.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.
*******************************************************************************/

#endif
