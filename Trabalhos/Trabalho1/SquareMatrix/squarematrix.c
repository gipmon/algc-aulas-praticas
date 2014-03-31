/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstrato MATRIZ QUADRADA (squarematrix.c).
 A estrutura de dados de suporte da matriz é uma estrutura, constituída pelo
 campo Size para armazenar o número de linhas e de colunas da matriz e o campo de
 tipo ponteiro para ponteiro Matrix para armazenar os seus elementos reais, que 
 vão ser armazenados numa sequência bidimensional atribuída dinamicamente.
 
 Autor : António Manuel Adrego da Rocha    Data : Março de 2014

*******************************************************************************/

/********** Implementação da Matriz Quadrada - squarematrix.c **********/

#include <stdio.h>
#include <stdlib.h>
#include "squarematrix.h"	/* Ficheiro de interface da Matriz Quadrada */

/********** Definição da Estrutura de Dados da Matriz Quadrada *********/

struct squarematrix
{
	unsigned int Size;	/* capacidade de armazenamento da matriz */
	double **Matrix;	/* sequência bidimensional que representa a matriz */
};

/******************** Controlo Centralizado de Erro ********************/

static unsigned int Error = OK;	/* inicialização do erro */

static char *ErrorMessages[] = { "sem erro", "matriz(es) inexistente(s)",
                                 "memoria esgotada", "ficheiro inexistente", 
                                 "dimensao errada", "elemento inexistente na matriz",
                                 "matrizes com dimensoes diferentes", "matrizes nao encadeadas",
                                 "ponteiro nulo", "dimensao incorrecta para strassen",
                                 "linha inexistente", "coluna inexistente" };

static char *AbnormalErrorMessage = "erro desconhecido";

/*********** Número de mensagens de erro previstas no módulo ***********/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/***************** Protótipos dos Subprogramas Internos ****************/

static int EqualDimensionMatrixes (PtSMatrix, PtSMatrix);
static double Determinant (double *, unsigned int, unsigned int);

/********************** Definição dos Subprogramas *********************/

void SMatrixClearError (void)
{
  Error = OK;
}

int SMatrixError (void)
{
  return Error;
}

char *SMatrixErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* não há mensagem de erro */
}

PtSMatrix SMatrixCreate (unsigned int psize)
{
  PtSMatrix Matrix;
  int i, j;
  if(psize < 1) {
    Error = BAD_SIZE;
    return NULL;
  }

  if((Matrix = (PtSMatrix) malloc(sizeof(struct matrix))) == NULL){
    Error = NO_MEM;
    return NULL;
  }

  for(i=0; i < psize; i++){
    if((Matrix->Matrix[i] = (int *) calloc (psize, sizeof(int)))==NULL){
      for (j = 0; j < i; j++){
        free(Matrix->Matrix[j]);
      }
      free(Matrix->Matrix);
      free(Matrix);
      Error=NO_MEM;
      return NULL;
    }
  }

  Matrix->Size = psize;

  Error = OK;

  return NULL;
}

PtSMatrix SMatrixCreateArray (unsigned int psize, double *array)
{
  PtSMatrix Matrix = SMatrixCreate(psize);

  for(i=0; i < Matrix->Size; i++){
    for (j = 0; j < Matrix->Size; j++){
      Matrix->Matrix[i][j] = array[i][j];
    }
  }

  return NULL;
}

PtSMatrix SMatrixCopy (PtSMatrix pmatrix)
{
  PtSMatrix Matrix;
  unsigned int i, j;

  if (pmatrix == NULL) {
    Error = NO_MATRIX;
    return NULL;
  }

  if ((Matrix = MatrixCreate(pmatrix->Size)) == NULL)
    return NULL;

  for(i=0; i < Matrix->Size; i++){
    for (j = 0; j < Matrix->Size; j++){
      Matrix->Matrix[i][j] = pmatrix->Matrix[i][j];
    }
  }

  Error = OK;
  return Matrix;
}

void SMatrixDestroy (PtSMatrix *pmatrix)
{
  if(*pmatrix==NULL){
    Error = NO_MATRIX;
    return;
  }

  unsigned int i;

  for (i = 0; i < (*pmatrix)->Size; i++){
    free((*pmatrix)->Matrix[i]);
  }

  free((*pmatrix)->Matrix);
  free(*pmatrix);
  *pmatrix = NULL;

  Error = OK;
}

unsigned int SMatrixSize (PtSMatrix pmatrix)
{
    if (pmatrix == NULL) { Error = NO_MATRIX; return 0; }

    Error = OK;
    return pmatrix->Size;
}

void SMatrixModifyElement (PtSMatrix pmatrix, unsigned int pl, unsigned int pc, double pvalue)
{
    if (pmatrix == NULL) { Error = NO_MATRIX; return; }
    if (pl < 0 || pl >= pmatrix->Size || pc < 0 || pc >= pmatrix->Size) { Error = BAD_INDEX; return; }

    Error = OK;
    pmatrix->Matrix[pl][pc] = pvalue;
}

double SMatrixObserveElement (PtSMatrix pmatrix, unsigned int pl, unsigned int pc)
{
    if (pmatrix == NULL) { Error = NO_MATRIX; return 0; }
    if (pl < 0 || pl >= pmatrix->Size || pc < 0 || pc >= pmatrix->Size) { Error = BAD_INDEX; return 0; }

    Error = OK;
    return pmatrix->Matrix[pl][pc];
}

PtSMatrix SMatrixTranspose (PtSMatrix pmatrix)
{
  PtSMatrix Matrix;
  unsigned int i, j;

  if (pmatrix == NULL) {
    Error = NO_MATRIX;
    return NULL;
  }

  if ((Matrix = MatrixCreate(pmatrix->Size)) == NULL)
    return NULL;

  for(i=0; i< Matrix->Size; i++){
    for (j = 0; j < Matrix->Size; j++){
      Matrix->Matrix[i][j] = pmatrix->Matrix[i][j];
    }
  }

  return Matrix;
}

PtSMatrix SMatrixAdd (PtSMatrix pmatrix1, PtSMatrix pmatrix2)
{
  if(!EqualDimensionMatrixes(pmatrix1, pmatrix2)){
    Error = BAD_SIZE;
    return NULL;
  }

  PtSMatrix Result;
  unsigned int i, j;

  if ((Result = MatrixCreate(pmatrix1->Size, pmatrix1->Size)) == NULL)
    return NULL;

  for(i=0; i<Result->Size; i++){
    for(j=0; j<Result->Size; j++){
      Result->Matrix[i][j] = MatrixObserveElement(pmatrix1, i, j) + MatrixObserveElement(pmatrix2, i, j);
    }
  }

  Error = OK;
  return Result;
}

PtSMatrix SMatrixSub (PtSMatrix pmatrix1, PtSMatrix pmatrix2)
{
  if(!EqualDimensionMatrixes(pmatrix1, pmatrix2)){
    Error = BAD_SIZE;
    return NULL;
  }

  PtSMatrix Result;
  unsigned int i, j;

  if ((Result = MatrixCreate(pmatrix1->Size, pmatrix1->Size)) == NULL)
    return NULL;

  for(i=0; i<Result->Size; i++){
    for(j=0; j<Result->Size; j++){
      Result->Matrix[i][j] = MatrixObserveElement(pmatrix1, i, j) - MatrixObserveElement(pmatrix2, i, j);
    }
  }

  Error = OK;
  return Result;
}

PtSMatrix SMatrixMult (PtSMatrix pmatrix1, PtSMatrix pmatrix2)
{
  PtSMatrix mul;
  int i, j, k;

  if ((pmatrix1 == NULL) || (pmatrix2 == NULL)){
    Error = NO_MATRIX;
    return 0;
  }

  if(!EqualDimensionMatrixes(pmatrix1, pmatrix2)){
    Error = NO_CHAINED;
    return NULL;
  }

  if ((mul = MatrixCreate (pmatrix1->Size, pmatrix1->Size)) == NULL)
    return NULL;

  for(k=0; k < pmatrix1->Size; k++){
    for(i=0; i < pmatrix1->Size; i++){
      for(j=0; j < pmatrix2->Size; j++){
        mul->Matrix[i][j] = pmatrix1->Matrix[i][k] * pmatrix2->Matrix[k][j];
      }
    }
  }

  Error = OK;
  return mul;
}

double SMatrixDeterminant (PtSMatrix pmatrix)
{
  double result;

  if (pmatrix == NULL){
    Error = NO_MATRIX;
    return 0.0;
  }

  result = Determinant(pmatrix->Matrix, pmatrix->Size, )
  
}

int SMatrixEquals (PtSMatrix pmatrix1, PtSMatrix pmatrix2)
{
   	unsigned int L, C;

	/* verificar se as matrizes existem */
	if (pmatrix1 == NULL || pmatrix2 == NULL) { Error = NO_MATRIX; return 0; }

    Error = OK;

    /* comparação da dimensão das matrizes */
	if (pmatrix1->Size != pmatrix2->Size) return 0;

    /* comparação das componentes das matrizes */
	for (L = 0; L < pmatrix1->Size; L++)
	  for (C = 0; C < pmatrix1->Size; C++)
        if (pmatrix1->Matrix[L][C] != pmatrix2->Matrix[L][C])	return 0;

    return 1;  /* as matrizes são iguais */
}

void SMatrixStoreFile (PtSMatrix pmatrix, char *pfname)
{
  FILE *PtF; unsigned int L, C;

  /* verifica se a matriz existe */
  if (pmatrix == NULL) { Error = NO_MATRIX; return ; }

  /* abertura com validacao do ficheiro para escrita */
  if ((PtF = fopen (pfname, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimensão da matriz no ficheiro */
  fprintf (PtF, "%u\t%u\n", pmatrix->Size, pmatrix->Size);

  /* escrita das componentes da matriz no ficheiro */
  for (L = 0; L < pmatrix->Size; L++)
  {
    for (C = 0; C < pmatrix->Size; C++)
      fprintf (PtF, "%f\t", pmatrix->Matrix[L][C]);
    fprintf (PtF, "\n");
  }

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro */
}

PtSMatrix SMatrixCreateFile (char *pfname)
{
  PtSMatrix Matrix; FILE *PtF; unsigned int Size, NL, NC, L, C;

  /* abertura com validacao do ficheiro para leitura */
  if ( (PtF = fopen (pfname, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimensão da matriz do ficheiro e criação da matriz */
  fscanf (PtF, "%u%u", &NL, &NC);
  
  if (NL != NC) { fclose (PtF); return NULL; }
  else Size = NL;

  if ((Matrix = SMatrixCreate (Size)) == NULL) { fclose (PtF); return NULL; }

  /* leitura das componentes da matriz do ficheiro */
  for (L = 0; L < Size; L++)
    for (C = 0; C < Size; C++)
      fscanf (PtF, "%lf", &Matrix->Matrix[L][C]);

  fclose (PtF);  /* fecho do ficheiro */

  Error = OK;
  return Matrix;  /* devolve a matriz criada */
}

PtSMatrix SMatrixCreateIdentity (unsigned int psize)
{
  /* insira o seu código */
  return NULL;
}

PtSMatrix SMatrixMultByScalar (PtSMatrix pmatrix, double pvalue)
{
  /* insira o seu código */
  return NULL;
}

int SMatrixIsSymetric (PtSMatrix pmatrix)
{
  /* insira o seu código */
  /* faça uma implementação eficiente */
  return 0;
}

void SMatrixExchangeRow (PtSMatrix pmatrix, unsigned int pk, unsigned int pl)
{
  /* insira o seu código */
  /* faça uma implementação eficiente */
}

void SMatrixExchangeColumn (PtSMatrix pmatrix, unsigned int pk, unsigned int pc)
{
  /* insira o seu código */
}

/*******************************************************************************
 Função auxiliar que verifica se as duas matrizes podem ser operadas ou
 comparadas, ou seja, se existem e se têm a mesma dimensão. Devolve 1 em caso
 afirmativo e 0 no caso contrário. Valores de erro: NO_MATRIX ou DIF_SIZE.
*******************************************************************************/
static int EqualDimensionMatrixes (PtSMatrix pmat1, PtSMatrix pmat2)
{
  /* verifica se as duas matrizes existem */
  if ((pmat1 == NULL) || (pmat2 == NULL)) { Error = NO_MATRIX; return 0; }

  /* verifica se as duas matrizes têm a mesma dimensão */
  if (pmat1->Size != pmat2->Size) { Error = DIF_SIZE; return 0; }

  /* as duas matrizes existem e têm a mesma dimensão */
  return 1;
}

/*******************************************************************************
 Função auxiliar que calcula efectivamente o determinante de uma matriz quadrada
 usando o algoritmo de eliminação de Gauss.
*******************************************************************************/
static double Determinant (double *pmatrix, unsigned int psize, unsigned int pn)
{
	unsigned int AuxCol, NC, NL, LC = pn-1; double Elem;

	if (pn == 1) return *pmatrix;	/* condição de paragem */
	else
	{
		AuxCol = LC;	/* procurar coluna com último elemento ? 0 */
		while (AuxCol >= 0 && *(pmatrix+LC*psize+AuxCol) == 0) AuxCol--;

		if (AuxCol >= 0)	/* se existir tal coluna */
		{
			if (AuxCol != LC)	/* se não for a última coluna */
				for (NL = 0; NL < pn; NL++)	/* trocar as colunas */
				{
					Elem = *(pmatrix+NL*psize+LC);
					*(pmatrix+NL*psize+LC) = *(pmatrix+NL*psize+AuxCol);
					*(pmatrix+NL*psize+AuxCol) = -Elem;
				}

			/* dividir a última coluna pelo último elemento */
			for (NL = 0; NL < LC; NL++) *(pmatrix+NL*psize+LC) = *(pmatrix+NL*psize+LC) / *(pmatrix+LC*psize+LC);

			/* subtrair todas as colunas menos a última pela última coluna */
			/* multiplicada pelo último elemento da coluna a processar */
			for (NC = 0; NC < LC; NC++)
				for (NL = 0; NL < LC; NL++)
					*(pmatrix+NL*psize+NC) = *(pmatrix+NL*psize+NC) - (*(pmatrix+NL*psize+LC) * *(pmatrix+LC*psize+NC));

			/* invocação recursiva para a matriz de dimensão N-1 */
			return *(pmatrix+LC*psize+LC) * Determinant (pmatrix, psize, pn-1);
		}
		else return 0.0;
	}
}
