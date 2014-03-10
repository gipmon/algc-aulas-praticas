/*******************************************************************************

 Ficheiro de implementa��o do Tipo de Dados Abstracto MATRIZ (matrix.c).
 A estrutura de dados de suporte da matriz � uma estrutura, constitu�da pelo
 campo NL para armazenar o n�mero de linhas da matriz, o campo NC para armazenar
 o n�mero de colunas da matriz e o campo de tipo ponteiro para ponteiro Matriz
 para armazenar os seus NLxNC elementos inteiros, que v�o ser armazenados numa
 sequ�ncia bidimensional atribu�da dinamicamente.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Janeiro de 2006

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"  /* Ficheiro de interface do TDA */

/************* Defini��o da Estrutura de Dados Interna da MATRIZ **************/

struct matrix
{
  unsigned int NL;  /* numero de linhas da matriz */
  unsigned int NC;  /* numero de colunas da matriz */
  int **Matrix;     /* ponteiro para a matriz a ser alocada */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;  /* inicializa��o do erro */

static char *ErrorMessages[] = {
                                 "Sem erro",
                                 "A(s) matriz(es) n�o existe(m)",
                                 "N�o h� mem�ria",
                                 "O ficheiro n�o existe",
                                 "Dimens�o da matriz errada", 
                                 "Elemento inexistente na matriz",
                                 "Matrixes com dimens�es diferentes",
                                 "Matrixes n�o encadeadas"
                               };

static char *AbnormalErrorMessage = "Erro desconhecido";

/************** N�mero de mensagens de erro previstas no m�dulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alus�o �s Fun��es Auxiliares ************************/

static int EqualDimensionMatrixes (PtMatrix, PtMatrix);
static int ChainedMatrixes (PtMatrix, PtMatrix);

/*************************** Defini��o das Fun��es ****************************/

void MatrixClearError (void)
{
  Error = OK;
}

int MatrixError (void)
{
  return Error;
}

char *MatrixErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* n�o h� mensagem de erro */
}

PtMatrix MatrixCreate (unsigned int pnl, unsigned int pnc)
{
  PtMatrix Matrix;
  unsigned int l, i;

  if((Matrix=(PtMatrix) malloc (sizeof(struct matrix)))==NULL)
  {
    Error = NO_MEM; return NULL;
  }
  if((Matrix->Matrix=(int **) calloc (pnl, sizeof(int*)))==NULL){
    free (Matrix);
    Error=NO_MEM;
    return NULL;
  }
  for(l=0; l<pnl; l++){
    if((Matrix->Matrix[l]=(int *) calloc (pnc, sizeof(int)))==NULL){
      for (i = 0; i < l; ++i)
      {
        free(Matrix->Matrix[i]);
      }
      free(Matrix->Matrix);
      free(Matrix);
      Error=NO_MEM;
      return NULL;
    }
  }
  Matrix->NL = pnl;
  Matrix->NC = pnc;
  Error = OK;
  return Matrix;
}

void MatrixDestroy (PtMatrix *pmat)
{
  if(*pmat==NULL){
    Error = NO_MATRIX;
    return;
  }

  unsigned int i;

  for (i = 0; i < (*pmat)->NL; ++i)
  {
    free((*pmat)->Matrix[i]);
  }

  free((*pmat)->Matrix);
  free(*pmat);
  *pmat = NULL;
  Error = OK;
}

PtMatrix MatrixCopy (PtMatrix pmat){
  PtMatrix Matrix;
  unsigned int l, i;

  /* verifica se a matrix existe */
  if (pmat == NULL) {
    Error = NO_MATRIX;
    return NULL;
  }

  /* cria��o do matrix copia nulo */
  if ((Matrix = MatrixCreate(pmat->NL, pmat->NC)) == NULL)
    return NULL;

  for(l=0; l<Matrix->NL; l++){
    for (i = 0; i < Matrix->NC; ++i){
      Matrix->Matrix[l][i] = pmat->Matrix[l][i];
    }
  }

  return Matrix;
}

void MatrixSize (PtMatrix pmat, unsigned int *pnl, unsigned int *pnc)
{
  /* verifica se a matriz existe */
  if (pmat == NULL)
  {
    Error = NO_MATRIX;
    *pnl = *pnc = 0;
  }
  else
  {
    Error = OK;
    *pnl = pmat->NL;
    *pnc = pmat->NC;
  }
}

void MatrixModifyElement (PtMatrix pmat, unsigned int pl, unsigned int pc, int pval)
{
  /* verifica se a matriz existe */
  if (pmat == NULL) { Error = NO_MATRIX; return ; }

  /* valida��o do elemento pretendido */
  if ((pl < 0) || (pl >= pmat->NL) || (pc < 0) || (pc >= pmat->NC))
  { Error = BAD_INDEX; return ; }

  Error = OK;
  /* escrita do valor na componente pretendida da matriz */
  pmat->Matrix[pl][pc] = pval;
}

int MatrixObserveElement (PtMatrix pmat, unsigned int pl, unsigned int pc)
{
  /* verifica se a matriz existe */
  if (pmat == NULL) { Error = NO_MATRIX; return 0; }

  /* valida��o do elemento pretendido */
  if ((pl < 0) || (pl >= pmat->NL) || (pc < 0) || (pc >= pmat->NC))
  { Error = BAD_INDEX; return 0; }

  Error = OK;
  /* devolve o valor armazenado na componente pretendida da matriz */
  return pmat->Matrix[pl][pc];
}

PtMatrix MatrixTranspose (PtMatrix pmat)
{
  PtMatrix Matrix;
  unsigned int l, i;

  /* verifica se a matrix existe */
  if (pmat == NULL) {
    Error = NO_MATRIX;
    return NULL;
  }

  /* cria��o do matrix copia nulo */
  if ((Matrix = MatrixCreate(pmat->NC, pmat->NL)) == NULL)
    return NULL;

  for(l=0; l<Matrix->NC; l++){
    for (i = 0; i < Matrix->NL; ++i){
      Matrix->Matrix[i][l] = pmat->Matrix[l][i];
    }
  }

  return Matrix;
}

PtMatrix MatrixAddition (PtMatrix pmat1, PtMatrix pmat2)
{

  if(!EqualDimensionMatrixes(pmat1,pmat2)){
    Error = BAD_SIZE;
    return NULL;
  }

  PtMatrix Result;
  unsigned int l, c;

  /* cria��o do matrix copia nulo */
  if ((Result = MatrixCreate(pmat1->NC, pmat1->NL)) == NULL)
    return NULL;

  for(l=0; l<Result->NL; l++){
    for(c=0; c<Result->NC; c++){
      Result->Matrix[l][c] = MatrixObserveElement(pmat1, l, c) + MatrixObserveElement(pmat1, c, l);
    }
  }

  Error = OK;
  return Result;
}

PtMatrix MatrixSubtraction (PtMatrix pmat1, PtMatrix pmat2)
{
  if(!EqualDimensionMatrixes(pmat1,pmat2)){
    Error = BAD_SIZE;
    return NULL;
  }

  PtMatrix Result;
  unsigned int l, c;

  /* cria��o do matrix copia nulo */
  if ((Result = MatrixCreate(pmat1->NC, pmat1->NL)) == NULL)
    return NULL;

  for(l=0; l<Result->NL; l++){
    for(c=0; c<Result->NC; c++){
      Result->Matrix[l][c] = MatrixObserveElement(pmat1, l, c) - MatrixObserveElement(pmat1, c, l);
    }
  }

  Error = OK;
  return Result;
}

PtMatrix MatrixMultiplication (PtMatrix pmat1, PtMatrix pmat2)
{
  PtMatrix multiplication_result;
  int i, j, k;

  /* V� se as matrizes existem */
  if ((pmat1 == NULL) || (pmat2 == NULL)) { Error = NO_MATRIX; return 0; }

  /* Ver se pmat1->NC == pmat2->NL */
  if(pmat1->NC==pmat2->NL){
    Error = BAD_SIZE;
    return 0;
  }

  if ((multiplication_result = MatrixCreate (pmat1->NL, pmat1->NC)) == NULL)
    return NULL;

  for(k=0; k < pmat1->NC; k++){
    for(i=0; i < pmat1->NL; i++){
      for(j=0; j < pmat2->NC; j++){
        multiplication_result->Matrix[i][j] = pmat1->Matrix[i][k] * pmat2->Matrix[k][j];
      }
    }
  }

  Error = OK;
  return multiplication_result;
}

int MatrixEquals (PtMatrix pmat1, PtMatrix pmat2)
{
  unsigned int I, J;

  /* valida��o das matrizes */
  if (!EqualDimensionMatrixes (pmat1, pmat2)) return 0;

  Error = OK;
  /* compara��o das componentes dos dois matrizes */
  for (I = 0; I < pmat1->NL; I++)
    for (J = 0; J < pmat1->NC; J++)
      if (pmat1->Matrix[I][J] != pmat2->Matrix[I][J]) return 0;

  return 1;  /* as matrizes s�o iguais */
}

void MatrixStoreFile (PtMatrix pmat, char *pnomef)
{
  FILE *PtF; unsigned int I, J;

  /* verifica se a matriz existe */
  if (pmat == NULL) { Error = NO_MATRIX; return ; }

  /* abertura com validacao do ficheiro para escrita */
  if ((PtF = fopen (pnomef, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimens�o da matriz no ficheiro */
  fprintf (PtF, "%d\t%d\n", pmat->NL, pmat->NC);

  /* escrita das componentes da matriz no ficheiro */
  for (I = 0; I < pmat->NL; I++)
  {
    for (J = 0; J < pmat->NC; J++) fprintf (PtF, "%d\t", pmat->Matrix[I][J]);
    fprintf (PtF, "\n");
  }

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro */
}

PtMatrix MatrixCreateFile (char *pnomef)
{
  PtMatrix Mat; FILE *PtF; unsigned int NL, NC, I, J;

  /* abertura com validacao do ficheiro para leitura */
  if ( (PtF = fopen (pnomef, "r")) == NULL)
  { Error = NO_FILE; return NULL; }

  /* leitura da dimens�o da matriz do ficheiro e cria��o da matriz */
  fscanf (PtF, "%d%d", &NL, &NC);
  if ((NL < 1) || (NC < 1)) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  if ((Mat = MatrixCreate (NL, NC)) == NULL)
  { fclose (PtF); return NULL; }

  /* leitura das componentes da matriz do ficheiro */
  for (I = 0; I < NL; I++) 
  {
    for (J = 0; J < NC; J++) fscanf (PtF, "%d", &Mat->Matrix[I][J]);
    fscanf (PtF, "%*[^\n]"); fscanf (PtF, "%*c");
  }

  fclose (PtF);  /* fecho do ficheiro */

  return Mat;  /* devolve a matriz criada */
}

/*******************************************************************************
 Fun��o auxiliar que verifica se as duas matrizes podem ser somadas ou
 comparadas, ou seja, se existem e se t�m a mesma dimens�o. Devolve 1 em caso
 afirmativo e 0 em caso contr�rio. Valores de erro: NO_MATRIX ou DIF_SIZE.
*******************************************************************************/
static int EqualDimensionMatrixes (PtMatrix pmat1, PtMatrix pmat2)
{
  /* verifica se as duas matrizes existem */
  if ((pmat1 == NULL) || (pmat2 == NULL)) { Error = NO_MATRIX; return 0; }

  /* verifica se as duas matrizes t�m a mesma dimens�o */
  if ((pmat1->NL != pmat2->NL) || (pmat1->NC != pmat2->NC))
  { Error = DIF_SIZE; return 0; }

  /* as duas matrizes existem e t�m a mesma dimens�o */
  return 1;
}

/*******************************************************************************
 Fun��o auxiliar que verifica se as duas matrizes podem ser multiplicadas, ou
 seja, se existem e se s�o encadeadas. Devolve 1 em caso afirmativo e 0 em caso
 contr�rio. Valores de erro: NO_MATRIX ou NO_CHAINED.
*******************************************************************************/
static int ChainedMatrixes (PtMatrix pmat1, PtMatrix pmat2)
{
  /* verifica se as duas matrizes existem */
  if ((pmat1 == NULL) || (pmat2 == NULL)) { Error = NO_MATRIX; return 0; }

  /* verifica se as duas matrizes s�o encadeadas */
  if (pmat1->NC != pmat2->NL) { Error = NO_CHAINED; return 0; }

  /* as duas matrizes existem e s�o encadeadas */
  return 1;
}
