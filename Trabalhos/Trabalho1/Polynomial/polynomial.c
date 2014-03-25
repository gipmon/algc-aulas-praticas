/*******************************************************************************

 Ficheiro de implementa��o do Tipo de Dados Abstrato POLINOMIO (polynomial.c).
 A estrutura de dados de suporte do polin�mio � uma estrutura, constitu�da pelo
 campo de tipo inteiro Degree para armazenar o grau do polin�mio e o campo de
 tipo ponteiro Poly, para representar a sequ�ncia atribu�da dinamicamente, que
 vai armazenar os seus coeficientes reais.
 
 Autor : Ant�nio Manuel Adrego da Rocha    Data : Mar�o de 2014

*******************************************************************************/

#include <stdio.h>  
#include <stdlib.h>
#include <math.h>

#include "polynomial.h"    /* Ficheiro de interface do TDA */

/************ Defini��o da Estrutura de Dados Interna do POLINOMIO ************/

struct poly
{
  unsigned int Degree;  /* grau do polin�mio */
  double *Poly;      /* ponteiro para os coeficientes do polin�mio */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;  /* inicializa��o do erro */

static char *ErrorMessages[] = {
                                 "Sem erro", "polinomio(s) inexistente(s)",
                                 "memoria esgotada", "ficheiro inexistente",
                                 "grau errado", "coeficiente inexistente"
                               };

static char *AbnormalErrorMessage = "erro desconhecido";

/************** N�mero de mensagens de erro previstas no m�dulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alus�o �s Fun��es Auxiliares ************************/

static int ValidPolys (PtPoly, PtPoly);

/*************************** Defini��o das Fun��es ****************************/

void PolyClearError (void)
{
  Error = OK;
}

int PolyError (void)
{
  return Error;
}

char *PolyErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;    /* n�o h� mensagem de erro */
}

PtPoly PolyCreate (unsigned int pdegree)
{
  PtPoly Poly;

  if(pDegree < 0){
    Error = BAD_SIZE; return NULL;
  }

  if((Poly = (PtPoly) malloc (sizeof (struct poly))) == NULL){
    Error = NO_MEM; return NULL;
  }

  if((Poly->Poly = (double *) calloc (pDegree+1, sizeof (double))) == NULL){
    free (Poly);
    Error = NO_MEM;
    return NULL;
  }

  Poly->Degree = pDegree;

  Error = OK;
  return Poly;
}

void PolyDestroy (PtPoly *ppol)
{
  /* insira o seu c�digo */
}

PtPoly PolyCopy (PtPoly ppol)
{
  /* insira o seu c�digo */
  return NULL;
}

int PolyDegree (PtPoly ppol)
{
  /* insira o seu c�digo */
  return 0;
}

void PolyModifyCoefficient (PtPoly ppol, unsigned int ppos, double pvalue)
{
  /* insira o seu c�digo */
}

double PolyObserveCoefficient (PtPoly ppol, unsigned int ppos)
{
  /* insira o seu c�digo */
  return 0.0;
}

int PolyIsNull (PtPoly ppol)
{
  /* insira o seu c�digo */
  return 0;
}

PtPoly PolyAddition (PtPoly ppol1, PtPoly ppol2)
{
  /* insira o seu c�digo */
  return NULL;
}

PtPoly PolySubtraction (PtPoly ppol1, PtPoly ppol2)
{
  /* insira o seu c�digo */
  return NULL;
}

PtPoly PolyMultiplication (PtPoly ppol1, PtPoly ppol2)
{
  /* insira o seu c�digo */
  return NULL;
}

int PolyEquals (PtPoly ppol1, PtPoly ppol2)
{
  /* insira o seu c�digo */
  return 0;
}

void PolyStoreFile (PtPoly ppol, char *pnomef)
{
  /* insira o seu c�digo */
}

PtPoly PolyCreateFile (char *pnomef)
{
  /* insira o seu c�digo */
  return NULL;
}

double PolyEvaluation (PtPoly ppoly, double px)
{
  /* insira o seu c�digo */
  return 0.0;
}

/*******************************************************************************
  Fun��o auxiliar que verifica se os dois polin�mios existem. Devolve 1 em caso
  afirmativo e 0 no caso contr�rio.
*******************************************************************************/
static int ValidPolys (PtPoly ppol1, PtPoly ppol2)
{
  /* verifica se os dois polin�mios existem */
  if ((ppol1 == NULL) || (ppol2 == NULL)) { Error = NO_POLY; return 0; }

  return 1;  /* os dois polin�mios existem */
}
