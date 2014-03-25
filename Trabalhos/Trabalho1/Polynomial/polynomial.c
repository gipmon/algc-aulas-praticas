/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstrato POLINOMIO (polynomial.c).
 A estrutura de dados de suporte do polinómio é uma estrutura, constituída pelo
 campo de tipo inteiro Degree para armazenar o grau do polinómio e o campo de
 tipo ponteiro Poly, para representar a sequência atribuída dinamicamente, que
 vai armazenar os seus coeficientes reais.
 
 Autor : António Manuel Adrego da Rocha    Data : Março de 2014

*******************************************************************************/

#include <stdio.h>  
#include <stdlib.h>
#include <math.h>

#include "polynomial.h"    /* Ficheiro de interface do TDA */

/************ Definição da Estrutura de Dados Interna do POLINOMIO ************/

struct poly
{
  unsigned int Degree;  /* grau do polinómio */
  double *Poly;      /* ponteiro para os coeficientes do polinómio */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;  /* inicialização do erro */

static char *ErrorMessages[] = {
                                 "Sem erro", "polinomio(s) inexistente(s)",
                                 "memoria esgotada", "ficheiro inexistente",
                                 "grau errado", "coeficiente inexistente"
                               };

static char *AbnormalErrorMessage = "erro desconhecido";

/************** Número de mensagens de erro previstas no módulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alusão às Funções Auxiliares ************************/

static int ValidPolys (PtPoly, PtPoly);

/*************************** Definição das Funções ****************************/

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
  else return AbnormalErrorMessage;    /* não há mensagem de erro */
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
  PtPoly TmpPoly = *ppol;

  if (TmpPoly == NULL) { 
    Error = NO_POLY; 
    return ; 
  }

  free (TmpPoly->Poly);
  free (TmpPoly);

  Error = OK;
  *ppol = NULL;
}

PtPoly PolyCopy (PtPoly ppol)
{
  /* insira o seu código */
  return NULL;
}

int PolyDegree (PtPoly ppol)
{
  /* insira o seu código */
  return 0;
}

void PolyModifyCoefficient (PtPoly ppol, unsigned int ppos, double pvalue)
{
  /* insira o seu código */
}

double PolyObserveCoefficient (PtPoly ppol, unsigned int ppos)
{
  /* insira o seu código */
  return 0.0;
}

int PolyIsNull (PtPoly ppol)
{
  /* insira o seu código */
  return 0;
}

PtPoly PolyAddition (PtPoly ppol1, PtPoly ppol2)
{
  /* insira o seu código */
  return NULL;
}

PtPoly PolySubtraction (PtPoly ppol1, PtPoly ppol2)
{
  /* insira o seu código */
  return NULL;
}

PtPoly PolyMultiplication (PtPoly ppol1, PtPoly ppol2)
{
  /* insira o seu código */
  return NULL;
}

int PolyEquals (PtPoly ppol1, PtPoly ppol2)
{
  /* insira o seu código */
  return 0;
}

void PolyStoreFile (PtPoly ppol, char *pnomef)
{
  /* insira o seu código */
}

PtPoly PolyCreateFile (char *pnomef)
{
  /* insira o seu código */
  return NULL;
}

double PolyEvaluation (PtPoly ppoly, double px)
{
  /* insira o seu código */
  return 0.0;
}

/*******************************************************************************
  Função auxiliar que verifica se os dois polinómios existem. Devolve 1 em caso
  afirmativo e 0 no caso contrário.
*******************************************************************************/
static int ValidPolys (PtPoly ppol1, PtPoly ppol2)
{
  /* verifica se os dois polinómios existem */
  if ((ppol1 == NULL) || (ppol2 == NULL)) { Error = NO_POLY; return 0; }

  return 1;  /* os dois polinómios existem */
}
