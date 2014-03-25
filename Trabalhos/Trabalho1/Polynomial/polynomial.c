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

  /*if(pdegree < 0){
    Error = BAD_SIZE; return NULL;
  }*/

  if((Poly = (PtPoly) malloc (sizeof (struct poly))) == NULL){
    Error = NO_MEM; return NULL;
  }

  if((Poly->Poly = (double *) calloc (pdegree+1, sizeof (double))) == NULL){
    free(Poly);
    Error = NO_MEM;
    return NULL;
  }

  Poly->Degree = pdegree;

  Error = OK;
  return Poly;
}

void PolyDestroy (PtPoly *ppol)
{
  PtPoly TmpPoly = *ppol;

  if(TmpPoly == NULL){
    Error = NO_POLY;
    return ;
  }

  free(TmpPoly->Poly);
  free(TmpPoly);

  Error = OK;
  *ppol = NULL;
}

PtPoly PolyCopy (PtPoly ppol)
{
  PtPoly Copy;
  int i;

  if(ppol == NULL){
    Error = NO_POLY;
    return NULL;
  }

  if((Copy = PolyCreate(ppol->Degree)) == NULL){
    return NULL;
  }

  for(i = 0; i <= ppol->Degree; i++) {
    Copy->Poly[i] = ppol->Poly[i];
  }

  Error = OK;
  return Copy;
}

int PolyDegree (PtPoly ppol)
{
  if(ppol == NULL){
    Error = NO_POLY;
    return -1;
  }

  Error = OK;
  return ppol->Degree;
}

void PolyModifyCoefficient (PtPoly ppol, unsigned int ppos, double pvalue)
{
  if(ppol == NULL){
    Error = NO_POLY;
    return ;
  }

  if(ppos > ppol->Degree){
    Error = BAD_INDEX;
    return ;
  }

  Error = OK;
  ppol->Poly[ppos] = pvalue;
}

double PolyObserveCoefficient (PtPoly ppol, unsigned int ppos)
{
  if(ppol == NULL){
    Error = NO_POLY;
    return 0.0;
  }

  if(ppos > ppol->Degree){
    Error = BAD_INDEX;
    return 0.0;
  }

  Error = OK;

  return ppol->Poly[ppos];
}

int PolyIsNull (PtPoly ppol)
{
  int i;

  if(ppol == NULL){
    Error = NO_POLY;
    return 0;
  }

  Error = OK;

  for(i = 0; i <= ppol->Degree; i++){
    if (ppol->Poly[i]){
      return 0;
    }
  }

  return 1;
}

PtPoly PolyAddition (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Add;
  int i, degree;

  if(!ValidPolys(ppol1, ppol2)) {
    return NULL;
  }

  if(ppol1->Degree > ppol2->Degree) {
    degree = ppol1->Degree;
  } else {
    degree = ppol2->Degree;
  }

  if((Add = PolyCreate(degree)) == NULL) {
    return NULL;
  }

  for(i = 0; i <= degree; i++){
    if(i < ppol1->Degree) {
      Add->Poly[i] += ppol1->Poly[i];
    }
    if(i < ppol2->Degree) {
      Add->Poly[i] += ppol2->Poly[i];
    }
  }

  return Add;
}

PtPoly PolySubtraction (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Sub;
  int i, degree;

  if(!ValidPolys(ppol1, ppol2)) {
    return NULL;
  }

  if(ppol1->Degree > ppol2->Degree) {
    degree = ppol1->Degree;
  } else {
    degree = ppol2->Degree;
  }

  if((Sub = PolyCreate(degree)) == NULL) {
    return NULL;
  }

  for(i = 0; i <= degree; i++){
    if(i < ppol1->Degree) {
      Sub->Poly[i] += ppol1->Poly[i];
    }
    if(i < ppol2->Degree) {
      Sub->Poly[i] -= ppol2->Poly[i];
    }
  }

  return Sub;
}

PtPoly PolyMultiplication (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Mul;
  int i, j;

  if(!ValidPolys(ppol1, ppol2)){
    return NULL;
  }

  if((Mul = PolyCreate(ppol1->Degree + ppol2->Degree)) == NULL){
    return NULL;
  }

  for(i=0; i<=ppol1->Degree; i++){
    for (j=0; j <= ppol2->Degree; j++){
      Mul->Poly[i+j] += ppol1->Poly[i] * ppol2->Poly[j];
    }
  }

  return Mul;
}

int PolyEquals (PtPoly ppol1, PtPoly ppol2)
{
  int i;

  if(!ValidPolys(ppol1, ppol2)){
    return 0;
  }

  if(ppol1->Degree != ppol2->Degree){
    return 0;
  }

  for(i = 0; i <= ppol1->Degree; i++){
    if(ppol1->Poly[i] != ppol2->Poly[i]){
      return 0;
    }
  }

  return 1;
}

void PolyStoreFile (PtPoly ppol, char *pnomef)
{
  FILE *PtF;
  unsigned int i;

  if(ppol == NULL){
    Error = NO_POLY;
    return ;
  }

  if((PtF = fopen (pnomef, "w")) == NULL){
    Error = NO_FILE;
    return ;
  }

  fprintf (PtF, "%u\n", ppol->Degree);

  for (i = 0; i <= ppol->Degree; i++){
    fprintf (PtF, "%lf\n", ppol->Poly[i]);
  }

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro */
}

PtPoly PolyCreateFile (char *pnomef)
{
  PtPoly Poly;
  FILE *PtF;
  unsigned int degree, i;

  if((PtF = fopen (pnomef, "r")) == NULL){
    Error = NO_FILE;
    return NULL;
  }

  fscanf (PtF, "%u", &degree);
  if(degree < 1){
    Error = BAD_SIZE;
    fclose (PtF);
    return NULL;
  }

  if((Poly = PolyCreate (degree)) == NULL){
    fclose (PtF);
    return NULL;
  }

  for (i = 0; i <= degree; i++){
    fscanf (PtF, "%lf", Poly->Poly+i);
  }

  fclose (PtF);
  return Poly;
}

double PolyEvaluation (PtPoly ppoly, double px)
{
  int i;
  double result = ppoly->Poly[ppoly->Degree];

  if(ppoly == NULL){
    Error = NO_POLY;
    return 0;
  }

  for(i = ppoly->Degree-1; i>=0; i--){
    result *= px;
    result += ppoly->Poly[i];
  }

  Error = OK;
  return result;
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
