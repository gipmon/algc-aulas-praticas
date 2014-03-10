/*******************************************************************************

 Ficheiro de implementa��o do Tipo de Dados Abstracto VETOR (vector.c).
 A estrutura de dados de suporte do vector � uma estrutura, constitu�da pelo
 campo de tipo inteiro NElem para armazenar o n�mero de componentes do vector
 e o campo de tipo ponteiro Vector, para representar a sequ�ncia atribu�da 
 dinamicamente, que vai armazenar as suas componentes reais.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Janeiro de 2006

*******************************************************************************/

#include <stdio.h>  
#include <stdlib.h>

#include "vector.h"  /* Ficheiro de interface do TDA */

/************** Defini��o da Estrutura de Dados Interna do Vector *************/

struct vector
{
  unsigned int NElem;  /* n�mero de componentes do vector */
  double *Vector;    /* ponteiro para a sequencia de componentes */
};

/*********************** Controlo Centralizado de Error ************************/

static unsigned int Error = OK;  /* inicializa��o do erro */

static char *ErrorMessages[] = {
                                 "Sem erro",
                                 "O(s) vector(es) n�o existe(m)",
                                 "N�o h� mem�ria",
                                 "O ficheiro n�o existe",
                                 "Dimens�o do vector errada",
                                 "Componente inexistente no vector",
                                 "Vectores com dimens�es diferentes"
                               };

static char *AbnormalErrorMessage = "Erro desconhecido";

/************** N�mero de mensagens de erro previstas no m�dulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alus�o �s Fun��es Auxiliares ************************/

static int ValidVectors (PtVector, PtVector);

/*************************** Defini��o das Fun��es ****************************/

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
  else return AbnormalErrorMessage;  /* n�o h� mensagem de erro */
}

PtVector VectorCreate (unsigned int pdim)
{
  PtVector Vector;

  /* valida a dimens�o do vector */
  if (pdim < 1) { Error = BAD_SIZE; return NULL; }

  /* cria o vector nulo */
  if ((Vector = (PtVector) malloc (sizeof (struct vector))) == NULL)
  { Error = NO_MEM; return NULL; }
  
  if ((Vector->Vector = (double *) calloc (pdim, sizeof (double))) == NULL)
  { free (Vector); Error = NO_MEM; return NULL; }

  Vector->NElem = pdim;     /* armazenamento da dimens�o */

  Error = OK;
  return Vector;    /* devolve o vector criado */
}

void VectorDestroy (PtVector *pvec)
{
  PtVector TmpVector = *pvec;

  /* verifica se o vector existe */
  if (TmpVector == NULL) { Error = NO_VECTOR; return ; }

  /* liberta��o da mem�ria din�mica */
  free (TmpVector->Vector);  /* liberta a mem�ria ocupada pelas componentes */
  free (TmpVector);    /* liberta a mem�ria ocupada pelo vector */

  Error = OK;
  *pvec = NULL;  /* coloca a refer�ncia a nulo */
}

PtVector VectorCopy (PtVector pvec)
{
  PtVector Copy; int I;

  /* verifica se o vector existe */
  if (pvec == NULL) { Error = NO_VECTOR; return NULL; }

  /* cria��o do vector copia nulo */
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

  /* valida��o do elemento pretendido */
  if ((ppos < 0) || (ppos >= pvec->NElem)) { Error = BAD_INDEX; return ; }

  Error = OK;
  /* escrita do valor na componente pretendida do vector */
  pvec->Vector[ppos] = pval;
}

double VectorObserveComponent (PtVector pvec, unsigned int ppos)
{
  /* verifica se o vector existe */
  if (pvec == NULL) { Error = NO_VECTOR; return 0; }

  /* valida��o do elemento pretendido */
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

  /* verifica��o das componentes do vector */
  for (I = 0; I < pvec->NElem; I++)
    if (pvec->Vector[I]) return 0;

  return 1;  /* o vector � um vector nulo */
}

PtVector  VectorAddition (PtVector pvec1, PtVector pvec2)
{
  PtVector Add; int I;

  /* valida��o dos vectores */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* cria��o do vector soma nulo */
  if ((Add = VectorCreate (pvec1->NElem)) == NULL) return NULL;

  /* soma dos dois vectores */
  for (I = 0; I < pvec1->NElem; I++)
    Add->Vector[I] = pvec1->Vector[I] + pvec2->Vector[I];

  return Add;  /* devolve o vector soma */
}

PtVector  VectorSubtraction (PtVector pvec1, PtVector pvec2)
{
  PtVector Sub; int I;

  /* valida��o dos vectores */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* cria��o do vector diferen�a nulo */
  if ((Sub = VectorCreate (pvec1->NElem)) == NULL) return NULL;

  /* diferen�a dos dois vectores */
  for (I = 0; I < pvec1->NElem; I++)
    Sub->Vector[I] = pvec1->Vector[I] - pvec2->Vector[I];

  return Sub;  /* devolve o vector diferen�a */
}

PtVector  VectorMultiplication (PtVector pvec1, PtVector pvec2)
{
  PtVector Mult; int I;

  /* valida��o dos vectores */
  if (!ValidVectors (pvec1, pvec2)) return NULL;

  /* cria��o do vector produto nulo */
  if ((Mult = VectorCreate (pvec1->NElem)) == NULL) return NULL;

  /* produto dos dois vectores */
  for (I = 0; I < pvec1->NElem; I++)
    Mult->Vector[I] = pvec1->Vector[I] * pvec2->Vector[I];

  return Mult;  /* devolve o vector produto */
}

double  VectorScalarMultiplication (PtVector pvec1, PtVector pvec2)
{
  int I; double Prod = 0.0;

  /* valida��o dos vectores */
  if (!ValidVectors (pvec1, pvec2)) return 0;

  /* c�lculo do produto escalar */
  for (I = 0; I < pvec1->NElem; I++)
    Prod += pvec1->Vector[I] * pvec2->Vector[I];

  Error = OK;
  return Prod;  /* devolve o produto escalar */
}

int  VectorEquals (PtVector pvec1, PtVector pvec2)
{
  int I;

  /* valida��o dos vectores */
  if (!ValidVectors (pvec1, pvec2)) return 0;
  Error = OK;

  /* compara��o das componentes dos dois vectores */
  for (I = 0; I < pvec1->NElem; I++)
    if (pvec1->Vector[I] != pvec2->Vector[I]) return 0;

  return 1;  /* os vectores s�o iguais */
}

void VectorStoreFile (PtVector pvec, char *pnomef)
{
  FILE *PtF; unsigned int I;

  /* verifica se o vector existe */
  if (pvec == NULL) { Error = NO_VECTOR; return ; }

  /* abertura com validacao do ficheiro para escrita */
  if ((PtF = fopen (pnomef, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimens�o do vector no ficheiro */
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

  /* leitura da dimens�o do vector do ficheiro e cria��o do vector */
  fscanf (PtF, "%u", &NElem);
  if (NElem < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  if ((Vector = VectorCreate (NElem)) == NULL) { fclose (PtF); return NULL; }

  /* leitura das componentes do vector do ficheiro */
  for (I = 0; I < NElem; I++) fscanf (PtF, "%lf", Vector->Vector+I);

  fclose (PtF);  /* fecho do ficheiro */

  return Vector;  /* devolve o vector criado */
}

/*******************************************************************************
 Fun��o auxiliar que verifica se os dois vectores podem ser operados, ou seja,
 se existem e se t�m a mesma dimens�o. Devolve 1 em caso afirmativo e 0 em caso
 contr�rio. Valores de erro: NO_VECTOR ou DIF_SIZE.
*******************************************************************************/
static int ValidVectors (PtVector pvec1, PtVector pvec2)
{
  /* verifica se os dois vectores existem */
  if ((pvec1 == NULL) || (pvec2 == NULL)) { Error = NO_VECTOR; return 0; }

  /* verifica se a dimens�o dos dois vectores � igual */
  if (pvec1->NElem != pvec2->NElem) { Error = DIF_SIZE; return 0; }

  return 1;  /* os dois vectores existem e t�m a mesma dimens�o */
}
