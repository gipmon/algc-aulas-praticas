/*******************************************************************************

 Ficheiro de implementação do Tipo de Dados Abstracto POLINOMIO (polynomial.c).
 A estrutura de dados de suporte do polinómio é uma estrutura, constituída pelo
 campo de tipo inteiro Grau para armazenar o grau do polinómio e o campo de tipo
 ponteiro Pol, para representar a sequência atribuída dinamicamente, que vai
 armazenar os seus coeficientes reais.
 
 Autor : António Manuel Adrego da Rocha    Data : Janeiro de 2006

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
                                 "Sem erro",
                                 "O(s) polinómio(s) não existe(m)",
                                 "Não há memória",
                                 "O ficheiro não existe",
                                 "Degree do polinómio errado",
                                 "Coeficiente inexistente no polinómio"
                               };

static char *AbnormalErrorMessage = "Erro desconhecido";

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

PtPoly PolyCreate (unsigned int pgrau)
{
  PtPoly Poly;

  /* valida grau do polinomio */
  if(pgrau < 0) {
    Error = BAD_SIZE;
    return NULL;
  }

  /* criar o polinomio nulo */
  if((Poly = (PtPoly) malloc(sizeof (struct poly))) == NULL) {
    Error = NO_MEM;
    return NULL;
  }

  if((Poly->Poly = (double *) calloc(pgrau+1, (sizeof (double)))) == NULL) {
    free(Poly);
    Error = NO_MEM;
    return NULL;
  }

  /* Guardar grau do polinomio */
  Poly->Degree = pgrau;

  /* Nao ocorreram erros */
  Error = OK;

  /* Devolver polinomio criado */
  return Poly;
}

void PolyDestroy (PtPoly *ppol)
{
  PtPoly TmpPoly = *ppol;

  /* Polinomio nao existe */
  if(TmpPoly == NULL) {
    Error = NO_POLY;
    return;
  }

  /* Libertar memoria alocada */
  free(TmpPoly->Poly);
  free(TmpPoly);

  Error = OK;
  *ppol = NULL;
}

PtPoly PolyCopy (PtPoly ppol)
{
  PtPoly Copy;
  int I;

  /* Verifica se o polinomio existe */
  if(ppol == NULL) {
    Error = NO_POLY;
    return NULL;
  }

  /* Criar polinomio */
  if((Copy = PolyCreate(ppol->Degree)) == NULL) {
    return NULL;
  }

  for(I = 0; I < ppol->Degree+1; ++I) {
    Copy->Poly[I] = ppol->Poly[I];
  }

  Error = OK;
  return Copy;
}

int PolyDegree (PtPoly ppol)
{
  /* Verifica se o polinomio existe */
  if(ppol == NULL) {
    Error = NO_POLY;
    return 0;
  }

  Error = OK;
  return ppol->Degree;
}

void PolyModifyCoefficient (PtPoly ppol, unsigned int ppos, double pval)
{
  /* Verifica se o polinomio existe */
  if(ppol == NULL) {
    Error = NO_POLY;
    return;
  }

  if(ppos < 0 || ppos > ppol->Degree) {
    Error = BAD_INDEX;
    return;
  }

  Error = OK;
  ppol->Poly[ppos] = pval;
}

double PolyObserveCoefficient (PtPoly ppol, unsigned int ppos)
{
  if(ppol == NULL) {
    Error = NO_POLY;
    return 0;
  }

  if(ppos < 0 || ppos > ppol->Degree) {
    Error = BAD_INDEX;
    return 0;
  }

  Error = OK;
  return ppol->Poly[ppos];
}

int PolyIsNull (PtPoly ppol)
{
  int I;

  if(ppol == NULL) {
    Error = NO_POLY;
    return 0;
  }

  Error = OK;

  for(I = 0; I < ppol->Degree+1; ++I) {
    if(ppol->Poly[I]) return 0;
  }

  return 1;
}


PtPoly PolyAddition (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Add;
  int I;
  int Degree;

  if(!ValidPolys(ppol1, ppol2)) {
    return NULL;
  }

  if(ppol1->Degree > ppol2->Degree) {
    Degree = ppol1->Degree;
  } else {
    Degree = ppol2->Degree;
  }

  if((Add = PolyCreate(Degree)) == NULL) {
    return NULL;
  }

  for(I = 0; I < Degree+1; ++I) {
    if(I < ppol1->Degree+1) {
      Add->Poly[I] += ppol1->Poly[I];
    }
    if(I < ppol2->Degree+1) {
      Add->Poly[I] += ppol2->Poly[I];
    }
  }

  return Add;
}

PtPoly PolySubtraction (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Sub;
  int I;
  int Degree;

  if(!ValidPolys(ppol1, ppol2)) {
    return NULL;
  }

  if(ppol1->Degree > ppol2->Degree) {
    Degree = ppol1->Degree;
  } else {
    Degree = ppol2->Degree;
  }

  if((Sub = PolyCreate(Degree)) == NULL) {
    return NULL;
  }

  for(I = 0; I < Degree+1; ++I) {
    if(I < ppol1->Degree+1) {
      Sub->Poly[I] += ppol1->Poly[I];
    }
    if(I < ppol2->Degree+1) {
      Sub->Poly[I] -= ppol2->Poly[I];
    }
  }

  return Sub;
}

PtPoly PolyMultiplication (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Mul;
  int I, J;
  int Degree;

  if(!ValidPolys(ppol1, ppol2)) {
    return NULL;
  }

  Degree = ppol1->Degree + ppol2->Degree;

  if((Mul = PolyCreate(Degree)) == NULL) {
    return NULL;
  }

  for(I = 0; I < ppol1->Degree+1; ++I) {
    for(J = 0; J < ppol2->Degree+1; ++J) {
      Mul->Poly[I+J] += ppol1->Poly[I] * ppol2->Poly[J];
    }
  }

  return Mul;
}

int PolyEquals (PtPoly ppol1, PtPoly ppol2)
{
  int I;

  if(!ValidPolys(ppol1, ppol2)) {
    return 0;
  }

  if(ppol1->Degree != ppol2->Degree) {
    return 0;
  }

  for(I = 0; I < ppol1->Degree+1; ++I) {
    if(ppol1->Poly[I] != ppol2->Poly[I]) {
      return 0;
    }
  }

  return 1;
}

void PolyStoreFile (PtPoly ppol, char *pnomef)
{
  FILE *PtF;
  unsigned int I;

  /* verifica se o polinomio existe */
  if (ppol == NULL) { 
    Error = NO_POLY;
    return ;
  }

  /* abertura com validacao do ficheiro para escrita */
  if ((PtF = fopen (pnomef, "w")) == NULL) {
    Error = NO_FILE;
    return ;
  }

  /* escrita da dimensão do vector no ficheiro */
  fprintf (PtF, "%u\n", ppol->Degree);

  /* escrita das componentes do vector no ficheiro */
  for (I = 0; I < ppol->Degree+1; I++) fprintf (PtF, "%lf\n", ppol->Poly[I]);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro */
}

PtPoly PolyCreateFile (char *pnomef)
{
  PtPoly Poly;
  FILE *PtF;
  unsigned int Degree, I;

  /* abertura com validacao do ficheiro para leitura */
  if ( (PtF = fopen (pnomef, "r")) == NULL) {
    Error = NO_FILE;
    return NULL;
  }

  /* leitura da dimensão do vector do ficheiro e criação do vector */
  fscanf (PtF, "%u", &Degree);
  if (Degree < 0) {
    Error = BAD_SIZE;
    fclose (PtF);
    return NULL;
  }

  if ((Poly = PolyCreate (Degree)) == NULL) {
    fclose (PtF);
    return NULL;
  }

  /* leitura das componentes do vector do ficheiro */
  for (I = 0; I < Degree+1; I++) {
    fscanf (PtF, "%lf", Poly->Poly+I);
  }

  fclose (PtF);  /* fecho do ficheiro */

  return Poly;  /* devolve o vector criado */
}

/*******************************************************************************
  Função auxiliar que verifica se os dois polinómios existem. Devolve 1 em caso
  afirmativo e 0 em caso contrário.
*******************************************************************************/
static int ValidPolys (PtPoly ppol1, PtPoly ppol2)
{
  /* verifica se os dois polinómios existem */
  if ((ppol1 == NULL) || (ppol2 == NULL)) {
    Error = NO_POLY;
    return 0;
  }

  return 1;  /* os dois polinómios existem */
}
