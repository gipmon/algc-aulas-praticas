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

  /* valida a dimensão do vector */
  if (pgrau < 0) { Error = BAD_SIZE; return NULL; }

  /* cria o vector nulo para os polinómios*/
  if ((Poly = (PtPoly) malloc (sizeof (struct poly))) == NULL)
  { Error = NO_MEM; return NULL; }
  
  if ((Poly->Poly = (double *) calloc (pgrau+1, sizeof (double))) == NULL)
  { free (Poly); Error = NO_MEM; return NULL; }

  Poly->Degree = pgrau;     /* armazenamento da dimensão */

  Error = OK;
  return Poly;    /* devolve o vector criado */
}

void PolyDestroy (PtPoly *ppol)
{
  PtPoly TmpPoly = *ppol;

  /* verifica se o vector existe */
  if (TmpPoly == NULL) { Error = NO_POLY; return ; }

  /* libertação da memória dinâmica */
  free (TmpPoly->Poly);  /* liberta a memória ocupada pelas componentes */
  free (TmpPoly);    /* liberta a memória ocupada pelo polinomio */

  Error = OK;
  *ppol = NULL;  /* coloca a referência a nulo */
}

PtPoly PolyCopy (PtPoly ppol)
{
  PtPoly Copy; int i;

  /* verifica se o Poly existe */
  if(ppol == NULL) { Error = NO_POLY; return NULL;}

  /* criação do poly copy a null */
  if((Copy = PolyCreate(ppol->Degree)) == NULL) return NULL;

  /*fazer cópia do ppol */
  for(i = 0; i <= ppol->Degree; i++) Copy->Poly[i] = ppol->Poly[i];

  return Copy;

}

int PolyDegree (PtPoly ppol)
{
  /* verifica se ppol existe */
  if(ppol == NULL) { Error = NO_POLY; return -1; }

  Error = OK;
  return ppol->Degree;
}

void PolyModifyCoefficient (PtPoly ppol, unsigned int ppos, double pval)
{
  /* verifica se ppol existe */
  if(ppol == NULL) { Error = NO_POLY; return ; }

  /* validação do indice */
  if(ppos > ppol->Degree) { Error = BAD_INDEX; return ;}

  Error = OK;
  /* modifica valor */

  ppol->Poly[ppos] = pval;

}

double PolyObserveCoefficient (PtPoly ppol, unsigned int ppos)
{
  /* verifica se ppol existe */
  if(ppol == NULL) { Error = NO_POLY; return -1; }

  /* validação do indice */
  if(ppos > ppol->Degree) { Error = BAD_INDEX; return -1;}

  Error = OK;

  return ppol->Poly[ppos];
}

int PolyIsNull (PtPoly ppol)
{
  int i;

  if(ppol == NULL) { Error = NO_POLY; return 0;}
  Error = OK;

  for(i = 0; i<= ppol->Degree; i++){
    if(ppol->Poly[i]) return 0;
  }
  return 1;

}


PtPoly PolyAddition (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Add; int I;

  /* validação dos vectores */
  if (!ValidPolys (ppol1, ppol2)) return NULL;

  /* criação do vector soma nulo */
  if ((Add = PolyCreate (ppol1->Degree)) == NULL) return NULL;

  /* soma dos dois vectores */
  for (I = 0; I <= ppol1->Degree; I++)
    Add->Poly[I] = ppol1->Poly[I] + ppol2->Poly[I];

  return Add;  /* devolve o vector soma */
}

PtPoly PolySubtraction (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Sub; int I;

  /* validação dos vectores */
  if (!ValidPolys (ppol1, ppol2)) return NULL;

  /* criação do vector diferença nulo */
  if ((Sub = PolyCreate (ppol1->Degree)) == NULL) return NULL;

  /* diferença dos dois vectores */
  for (I = 0; I <= ppol1->Degree; I++)
    Sub->Poly[I] = ppol1->Poly[I] - ppol2->Poly[I];

  return Sub;  /* devolve o vector diferença */
}

PtPoly PolyMultiplication (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Mult; int I, j;

  /* validação dos vectores */
  if (!ValidPolys (ppol1, ppol2)) return NULL;

  /* criação do vector produto nulo */
  if ((Mult = PolyCreate (ppol1->Degree+ppol2->Degree)) == NULL) return NULL;

  /* produto dos dois vectores */
  
  for (I = 0; I <=ppol1->Degree; I++)
      for(j = 0; j<=ppol2->Degree; j++)
        Mult->Poly[I+j] = ppol1->Poly[I] * ppol2->Poly[j];

  return Mult;  /* devolve o vector produto */
}

int PolyEquals (PtPoly ppol1, PtPoly ppol2)
{
  int I;

  /* validação dos vectores */
  if (!ValidPolys (ppol1, ppol2)) return 0;
  Error = OK;

  /* comparação das componentes dos dois vectores */
  for (I = 0; I < ppol1->Degree; I++)
    if (ppol1->Poly[I] != ppol2->Poly[I]) return 0;

  return 1;  /* os vectores são iguais */
}

void PolyStoreFile (PtPoly ppol, char *pnomef)
{
  FILE *PtF; unsigned int I;

  /* verifica se o vector existe */
  if (ppol == NULL) { Error = NO_POLY; return ; }

  /* abertura com validacao do ficheiro para escrita */
  if ((PtF = fopen (pnomef, "w")) == NULL) { Error = NO_FILE; return ; }

  /* escrita da dimensão do vector no ficheiro */
  fprintf (PtF, "%u\n", ppol->Degree);

  /* escrita das componentes do vector no ficheiro */
  for (I = 0; I <= ppol->Degree; I++) fprintf (PtF, "%lf\n", ppol->Poly[I]);

  Error = OK;
  fclose (PtF);  /* fecho do ficheiro */
}

PtPoly PolyCreateFile (char *pnomef)
{
  PtPoly Poly; FILE *PtF; unsigned int DEGREE, I;

  /* abertura com validacao do ficheiro para leitura */
  if ( (PtF = fopen (pnomef, "r")) == NULL) { Error = NO_FILE; return NULL; }

  /* leitura da dimensão do vector do ficheiro e criação do vector */
  fscanf (PtF, "%u", &DEGREE);
  if (DEGREE < 1) { Error = BAD_SIZE; fclose (PtF); return NULL; }

  if ((Poly = PolyCreate (DEGREE)) == NULL) { fclose (PtF); return NULL; }

  /* leitura das componentes do vector do ficheiro */
  for (I = 0; I <= DEGREE; I++) fscanf (PtF, "%lf", Poly->Poly+I);

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
  if ((ppol1 == NULL) || (ppol2 == NULL)) { Error = NO_POLY; return 0; }

  return 1;  /* os dois polinómios existem */
}
