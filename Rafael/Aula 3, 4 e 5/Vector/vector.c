/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstracto VETOR (vector.c).
 A estrutura de dados de suporte do vector é uma estrutura, constituída pelo
 campo de tipo inteiro NElem para armazenar o número de componentes do vector
 e o campo de tipo ponteiro Vector, para representar a sequência atribuída 
 dinamicamente, que vai armazenar as suas componentes reais.

 Autor : António Manuel Adrego da Rocha    Data : Janeiro de 2006

*******************************************************************************/

#include <stdio.h>  
#include <stdlib.h>

#include "vector.h"  /* Ficheiro de interface do TDA */

/************** Definição da Estrutura de Dados Interna do Vector *************/

struct vector
{
  unsigned int NElem;  /* número de componentes do vector */
  double *Vector;    /* ponteiro para a sequencia de componentes */
};

/*********************** Controlo Centralizado de Error ************************/

static unsigned int Error = OK;  /* inicialização do erro */

static char *ErrorMessages[] = {
                                 "Sem erro",
                                 "O(s) vector(es) não existe(m)",
                                 "Não há memória",
                                 "O ficheiro não existe",
                                 "Dimensão do vector errada",
                                 "Componente inexistente no vector",
                                 "Vectores com dimensões diferentes"
                               };

static char *AbnormalErrorMessage = "Erro desconhecido";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alusão às Funções Auxiliares ************************/

static int ValidVectors (PtVector, PtVector);

/*************************** Definição das Funções ****************************/

void VectorClearError (void)
{
  Error = OK;
}

int VectorError (void)
{
  return Error;
}

char *VectorErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* não há mensagem de erro */
}

PtVector VectorCreate (unsigned int pdim)
{
  PtVector Vector;

  /* valida a dimensão do vector */
  if (pdim < 1) { Error = BAD_SIZE; return NULL; }

  /* cria o vector nulo */
  if ((Vector = (PtVector) malloc (sizeof (struct vector))) == NULL)
  { Error = NO_MEM; return NULL; }
  
  if ((Vector->Vector = (double *) calloc (pdim, sizeof (double))) == NULL)
  { free (Vector); Error = NO_MEM; return NULL; }

  Vector->NElem = pdim;     /* armazenamento da dimensão */

  Error = OK;
  return Vector;    /* devolve o vector criado */
}

void VectorDestroy (PtVector *pvec)
{
  PtVector TmpVector = *pvec;

  /* verifica se o vector existe */
  if (TmpVector == NULL) { Error = NO_VECTOR; return ; }

  /* libertação da memória dinâmica */
  free (TmpVector->Vector);  /* liberta a memória ocupada pelas componentes */
  free (TmpVector);    /* liberta a memória ocupada pelo vector */

  Error = OK;
  *pvec = NULL;  /* coloca a referência a nulo */
}

PtVector VectorCopy (PtVector pvec)
{
  PtVector Copy; int I;

  /* verifica se o vector existe */
  if (pvec == NULL) { Error = NO_VECTOR; return NULL; }

  /* criação do vector copia nulo */
  if ((Copy = VectorCreate (pvec->NElem)) == NULL) return NULL;

  /* fazer a copia do vector */
  for (I = 0; I < pvec->NElem; I++) Copy->Vector[I] = pvec->Vector[I];

  return Copy;  /* devolve o vector copia */
}

int VectorDimension (PtVector pvec)
{
  /* verifica se o vector existe */
  if (pvec == NULL) { Error = NO_VECTOR; return 0; }

  Error = OK;
  return pvec->NElem;
}

void VectorModifyComponent (PtVector pvec, unsigned int ppos, double pval)
{
  /* verifica se o vector existe */
  if (pvec == NULL) { Error = NO_VECTOR; return ; }

  /* validação do elemento pretendido */
  if ((ppos < 0) || (ppos >= pvec->NElem)) { Error = BAD_INDEX; return ; }

  Error = OK;
  /* escrita do valor na componente pretendida do vector */
  pvec->Vector[ppos] = pval;
}

double VectorObserveComponent (PtVector pvec, unsigned int ppos)
{
  /* verifica se o vector existe */
  if (pvec == NULL) { Error = NO_VECTOR; return 0; }

  /* validação do elemento pretendido */
  if ((ppos < 0) || (ppos >= pvec->NElem)) { Error = BAD_INDEX; return 0; }

  Error = OK;
  /* devolve o valor armazenado na componente pretendida do vector */
  return pvec->Vector[ppos];
}

int VectorIsNull (PtVector pvec)
{
  int I;

  /* verifica se o vector existe */
  if (pvec == NULL) { Error = NO_VECTOR; return 0; }
  Error = OK;

  /* verificação das componentes do vector */
  for (I = 0; I < pvec->NElem; I++)
    if (pvec->Vector[I]) return 0;

  return 1;  /* o vector é um vector nulo */
}

PtVector  VectorAddition (PtVector pvec1, PtVector pvec2)
{
  PtVector Add; int I;

  /* validação dos vectores */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* criação do vector soma nulo */
  if ((Add = VectorCreate (pvec1->NElem)) == NULL) return NULL;

  /* soma dos dois vectores */
  for (I = 0; I < pvec1->NElem; I++)
    Add->Vector[I] = pvec1->Vector[I] + pvec2->Vector[I];

  return Add;  /* devolve o vector soma */
}

PtVector  VectorSubtraction (PtVector pvec1, PtVector pvec2)
{
  PtVector Sub; int I;

  /* validação dos vectores */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* criação do vector diferença nulo */
  if ((Sub = VectorCreate (pvec1->NElem)) == NULL) return NULL;

  /* diferença dos dois vectores */
  for (I = 0; I < pvec1->NElem; I++)
    Sub->Vector[I] = pvec1->Vector[I] - pvec2->Vector[I];

  return Sub;  /* devolve o vector diferença */
}

PtVector  VectorMultiplication (PtVector pvec1, PtVector pvec2)
{
  PtVector Mult; int I;

  /* validação dos vectores */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* criação do vector produto nulo */
  if ((Mult = VectorCreate (pvec1->NElem)) == NULL) return NULL;

  /* produto dos dois vectores */
  for (I = 0; I < pvec1->NElem; I++)
    Mult->Vector[I] = pvec1->Vector[I] * pvec2->Vector[I];

  return Mult;  /* devolve o vector produto */
}

double  VectorScalarMultiplication (PtVector pvec1, PtVector pvec2)
{
  int I; double Prod = 0.0;

  /* validação dos vectores */
  if (!ValidVectors (pvec1, pvec2)) return 0;

  /* cálculo do produto escalar */
  for (I = 0; I < pvec1->NElem; I++)
    Prod += pvec1->Vector[I] * pvec2->Vector[I];

  Error = OK;
  return Prod;  /* devolve o produto escalar */
}

int  VectorEquals (PtVector pvec1, PtVector pvec2)
{
  int I;

  /* validação dos vectores */
  if (!ValidVectors (pvec1, pvec2)) return 0;
  Error = OK;

  /* comparação das componentes dos dois vectores */
  for (I = 0; I < pvec1->NElem; I++)
    if (pvec1->Vector[I] != pvec2->Vector[I]) return 0;

  return 1;  /* os vectores são iguais */
}

void VectorStoreFile (PtVector pvec, char *pnomef)
{
  FILE *PtF; unsigned int I;

  /* verifica se o vector existe */
  if (pvec == NULL) { Error = NO_VECTOR; return ; }

  /* abertura com validacao do ficheiro para escrita */
  if ((PtF = fopen (pnomef, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimensão do vector no ficheiro */
  fprintf (PtF, "%u\n", pvec->NElem);

  /* escrita das componentes do vector no ficheiro */
  for (I = 0; I < pvec->NElem; I++) fprintf (PtF, "%lf\n", pvec->Vector[I]);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro */
}

PtVector VectorCreateFile (char *pnomef)
{
  PtVector Vector; FILE *PtF; unsigned int NElem, I;

  /* abertura com validacao do ficheiro para leitura */
  if ( (PtF = fopen (pnomef, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimensão do vector do ficheiro e criação do vector */
  fscanf (PtF, "%u", &NElem);
  if (NElem < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  if ((Vector = VectorCreate (NElem)) == NULL) { fclose (PtF); return NULL; }

  /* leitura das componentes do vector do ficheiro */
  for (I = 0; I < NElem; I++) fscanf (PtF, "%lf", Vector->Vector+I);

  fclose (PtF);  /* fecho do ficheiro */

  return Vector;  /* devolve o vector criado */
}

/*******************************************************************************
 Função auxiliar que verifica se os dois vectores podem ser operados, ou seja,
 se existem e se têm a mesma dimensão. Devolve 1 em caso afirmativo e 0 em caso
 contrário. Valores de erro: NO_VECTOR ou DIF_SIZE.
*******************************************************************************/
static int ValidVectors (PtVector pvec1, PtVector pvec2)
{
  /* verifica se os dois vectores existem */
  if ((pvec1 == NULL) || (pvec2 == NULL)) { Error = NO_VECTOR; return 0; }

  /* verifica se a dimensão dos dois vectores é igual */
  if (pvec1->NElem != pvec2->NElem) { Error = DIF_SIZE; return 0; }

  return 1;  /* os dois vectores existem e têm a mesma dimensão */
}
