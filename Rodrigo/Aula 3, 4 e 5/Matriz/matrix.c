/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstracto MATRIZ (matrix.c).
 A estrutura de dados de suporte da matriz é uma estrutura, constituída pelo
 campo NL para armazenar o número de linhas da matriz, o campo NC para armazenar
 o número de colunas da matriz e o campo de tipo ponteiro para ponteiro Matriz
 para armazenar os seus NLxNC elementos inteiros, que vão ser armazenados numa
 sequência bidimensional atribuída dinamicamente.

 Autor : António Manuel Adrego da Rocha    Data : Janeiro de 2006

*******************************************************************************/

#include <stdio.h>  
#include <stdlib.h>

#include "matrix.h"  /* Ficheiro de interface do TDA */

/************* Definição da Estrutura de Dados Interna da MATRIZ **************/

struct matrix
{
  unsigned int NL;  /* numero de linhas da matriz */
  unsigned int NC;  /* numero de colunas da matriz */
  int **Matrix;     /* ponteiro para a matriz a ser alocada */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;  /* inicialização do erro */

static char *ErrorMessages[] = {
                                 "Sem erro",
                                 "A(s) matriz(es) não existe(m)",
                                 "Não há memória",
                                 "O ficheiro não existe",
                                 "Dimensão da matriz errada", 
                                 "Elemento inexistente na matriz",
                                 "Matrixes com dimensões diferentes",
                                 "Matrixes não encadeadas"
                               };

static char *AbnormalErrorMessage = "Erro desconhecido";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alusão às Funções Auxiliares ************************/

static int EqualDimensionMatrixes (PtMatrix, PtMatrix);
static int ChainedMatrixes (PtMatrix, PtMatrix);

/*************************** Definição das Funções ****************************/

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
  else return AbnormalErrorMessage;  /* não há mensagem de erro */
}

PtMatrix MatrixCreate (unsigned int pnl, unsigned int pnc)
{
  /* insira o seu código */
}

void MatrixDestroy (PtMatrix *pmat)
{
  /* insira o seu código */
}

PtMatrix MatrixCopy (PtMatrix pmat)
{
  /* insira o seu código */
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

  /* validação do elemento pretendido */
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

  /* validação do elemento pretendido */
  if ((pl < 0) || (pl >= pmat->NL) || (pc < 0) || (pc >= pmat->NC))
  { Error = BAD_INDEX; return 0; }

  Error = OK;
  /* devolve o valor armazenado na componente pretendida da matriz */
  return pmat->Matrix[pl][pc];
}

PtMatrix MatrixTranspose (PtMatrix pmat)
{
  /* insira o seu código */
}

PtMatrix MatrixAddition (PtMatrix pmat1, PtMatrix pmat2)
{
  /* insira o seu código */
}

PtMatrix MatrixSubtraction (PtMatrix pmat1, PtMatrix pmat2)
{
  /* insira o seu código */
}

PtMatrix MatrixMultiplication (PtMatrix pmat1, PtMatrix pmat2)
{
  /* insira o seu código */
}

int MatrixEquals (PtMatrix pmat1, PtMatrix pmat2)
{
  unsigned int I, J;

  /* validação das matrizes */
  if (!EqualDimensionMatrixes (pmat1, pmat2)) return 0;

  Error = OK;
  /* comparação das componentes dos dois matrizes */
  for (I = 0; I < pmat1->NL; I++)
    for (J = 0; J < pmat1->NC; J++)
      if (pmat1->Matrix[I][J] != pmat2->Matrix[I][J]) return 0;

  return 1;  /* as matrizes são iguais */
}

void MatrixStoreFile (PtMatrix pmat, char *pnomef)
{
  FILE *PtF; unsigned int I, J;

  /* verifica se a matriz existe */
  if (pmat == NULL) { Error = NO_MATRIX; return ; }

  /* abertura com validacao do ficheiro para escrita */
  if ((PtF = fopen (pnomef, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimensão da matriz no ficheiro */
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

  /* leitura da dimensão da matriz do ficheiro e criação da matriz */
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
 Função auxiliar que verifica se as duas matrizes podem ser somadas ou
 comparadas, ou seja, se existem e se têm a mesma dimensão. Devolve 1 em caso
 afirmativo e 0 em caso contrário. Valores de erro: NO_MATRIX ou DIF_SIZE.
*******************************************************************************/
static int EqualDimensionMatrixes (PtMatrix pmat1, PtMatrix pmat2)
{
  /* verifica se as duas matrizes existem */
  if ((pmat1 == NULL) || (pmat2 == NULL)) { Error = NO_MATRIX; return 0; }

  /* verifica se as duas matrizes têm a mesma dimensão */
  if ((pmat1->NL != pmat2->NL) || (pmat1->NC != pmat2->NC))
  { Error = DIF_SIZE; return 0; }

  /* as duas matrizes existem e têm a mesma dimensão */
  return 1;
}

/*******************************************************************************
 Função auxiliar que verifica se as duas matrizes podem ser multiplicadas, ou
 seja, se existem e se são encadeadas. Devolve 1 em caso afirmativo e 0 em caso
 contrário. Valores de erro: NO_MATRIX ou NO_CHAINED.
*******************************************************************************/
static int ChainedMatrixes (PtMatrix pmat1, PtMatrix pmat2)
{
  /* verifica se as duas matrizes existem */
  if ((pmat1 == NULL) || (pmat2 == NULL)) { Error = NO_MATRIX; return 0; }

  /* verifica se as duas matrizes são encadeadas */
  if (pmat1->NC != pmat2->NL) { Error = NO_CHAINED; return 0; }

  /* as duas matrizes existem e são encadeadas */
  return 1;
}
