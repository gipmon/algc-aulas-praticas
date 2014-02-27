/*******************************************************************************

 Ficheiro de implementa��o do Tipo de Dados Abstracto POLINOMIO (polynomial.c).
 A estrutura de dados de suporte do polin�mio � uma estrutura, constitu�da pelo
 campo de tipo inteiro Degree para armazenar o Degree do polin�mio e o campo de tipo
 ponteiro Pol, para representar a sequ�ncia atribu�da dinamicamente, que vai
 armazenar os seus coeficientes reais.
 
 Autor : Ant�nio Manuel Adrego da Rocha    Data : Janeiro de 2006

*******************************************************************************/

#include <stdio.h>  
#include <stdlib.h>
#include <math.h>

#include "polynomial.h"    /* Ficheiro de interface do TDA */

/************ Defini��o da Estrutura de Dados Interna do POLINOMIO ************/

struct poly
{
  unsigned int Degree;  /* Degree do polin�mio */
  double *Poly;      /* ponteiro para os coeficientes do polin�mio */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;  /* inicializa��o do erro */

static char *ErrorMessages[] = {
                                 "Sem erro",
                                 "O(s) polin�mio(s) n�o existe(m)",
                                 "N�o h� mem�ria",
                                 "O ficheiro n�o existe",
                                 "Degree do polin�mio errado",
                                 "Coeficiente inexistente no polin�mio"
                               };

static char *AbnormalErrorMessage = "Erro desconhecido";

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

PtPoly PolyCreate (unsigned int pDegree)
{
  PtPoly Poly;

  /* valida a dimens�o do vector */
  if (pDegree < 0) { Error = BAD_SIZE; return NULL; }

  /* cria o vector nulo para os polin�mios*/
  if ((Poly = (PtPoly) malloc (sizeof (struct poly))) == NULL)
  { Error = NO_MEM; return NULL; }

  if ((Poly->Poly = (double *) calloc (pDegree+1, sizeof (double))) == NULL)
  { free (Poly); Error = NO_MEM; return NULL; }

  Poly->Degree = pDegree;     /* armazenamento da dimens�o */

  Error = OK;
  return Poly;    /* devolve o vector criado */
}

void PolyDestroy (PtPoly *ppol)
{
  PtPoly TmpPoly = *ppol;

  /* verifica se o poly existe */
  if (TmpPoly == NULL) { 
    Error = NO_POLY; 
    return ; 
  }

  /* liberta��o da mem�ria din�mica */
  free (TmpPoly->Poly);  /* liberta a mem�ria ocupada pelas componentes */
  free (TmpPoly);    /* liberta a mem�ria ocupada pelo poly */

  Error = OK;
  *ppol = NULL;  /* coloca a refer�ncia a nulo */
}

PtPoly PolyCopy (PtPoly ppol)
{
  PtPoly Copy; 
  int I;

  /* verifica se o poly existe */
  if (ppol == NULL) { 
    Error = NO_POLY;
    return NULL; 
  }

  /* cria��o do poly copia nulo */
  if ((Copy = PolyCreate (ppol->Degree)) == NULL)
    return NULL;

  /* fazer a copia do poly */
  for (I = 0; I <= ppol->Degree; I++) 
    Copy->Poly[I] = ppol->Poly[I];

  return Copy;  /* devolve o poly copia */
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

void PolyModifyCoefficient (PtPoly ppol, unsigned int ppos, double pval)
{
  if(ppol == NULL){
    Error = NO_POLY;
    return ;
  }

  /* valida��o do poly pretendido */
  if (ppos > ppol->Degree) { 
    Error = BAD_INDEX; 
    return ; 
  }

  Error = OK;
  /* escrita do valor na componente pretendida do poly */
  ppol->Poly[ppos] = pval;
}

double PolyObserveCoefficient (PtPoly ppol, unsigned int ppos)
{
  /* verifica se o poly existe */
  if (ppol == NULL) { 
    Error = NO_POLY; 
    return 0; 
  }

  /* valida��o do elemento pretendido */
  if (ppos > ppol->Degree) { 
    Error = BAD_INDEX; 
    return 0; 
  }

  Error = OK;
  /* devolve o valor armazenado na componente pretendida do vector */
  return ppol->Poly[ppos];
}

int PolyIsNull (PtPoly ppol)
{
  int I;

  /* verifica se o poly existe */
  if (ppol == NULL) { 
    Error = NO_POLY; 
    return 0; 
  }
  
  Error = OK;

  /* verifica��o das componentes do poly */
  for (I = 0; I <= ppol->Degree; I++)
    if (ppol->Poly[I]) 
      return 0;

  return 1;  /* o vector � um poly nulo */
}


PtPoly PolyAddition (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Add; 
  int I;

  /* valida��o dos poly */
  if (!ValidPolys (ppol1, ppol2)) 
    return NULL;

  /* cria��o do poly soma nulo */
  if ((Add = PolyCreate (ppol1->Degree)) == NULL) 
    return NULL;

  /* soma dos dois poly */
  for (I = 0; I <= ppol1->Degree; I++)
    Add->Poly[I] = ppol1->Poly[I] + ppol2->Poly[I];

  return Add;  /* devolve o poly soma */
}

PtPoly PolySubtraction (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly Sub; int I;

  /* valida��o dos poly */
  if (!ValidPolys (ppol1, ppol2)) 
    return NULL;

  /* cria��o do vector diferen�a nulo */
  if ((Sub = PolyCreate (ppol1->Degree)) == NULL) 
    return NULL;

  /* diferen�a dos dois poly */
  for (I = 0; I <= ppol1->Degree; I++)
    Sub->Poly[I] = ppol1->Poly[I] - ppol2->Poly[I];

  return Sub;  /* devolve o poly diferen�a */
}

PtPoly PolyMultiplication (PtPoly ppol1, PtPoly ppol2)
{
  PtPoly multiplication_result;
  int i, j;

  if(!ValidPolys(ppol1, ppol2)){
    return NULL;
  }

  for(i=0; i<=ppol1->Degree; i++){
    for (j=0; j <= ppol2->Degree; j++){
      multiplication_result->Poly[i+j] = ppol1->Poly[i] * ppol2->Poly[j];
    }
  }

  return multiplication_result;
}

int PolyEquals (PtPoly ppol1, PtPoly ppol2){
  int i;

  for (i = 0; i <= ppol1->Degree ; i++){
    if(ppol1->Poly[i]!=ppol2->Poly[i]){
      return 0;
    }
  }
  return 1;
}

void PolyStoreFile (PtPoly ppol, char *pnomef)
{
  FILE *PtF;
  unsigned int I;

  /* verifica se o poly existe */
  if (ppol == NULL){
    Error = NO_POLY;
    return ;
  }

  /* abertura com validacao do ficheiro para escrita */
  if ((PtF = fopen (pnomef, "w")) == NULL) {
    Error = NO_FILE;
    return ;
  }

  /* escrita do Degree do poly no ficheiro */
  fprintf (PtF, "%u\n", ppol->Degree);

  /* escrita das componentes do poly no ficheiro */
  for (I = 0; I <= ppol->Degree; I++)
    fprintf (PtF, "%lf\n", ppol->Poly[I]);

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

  fscanf (PtF, "%u", &Degree);
  if (Degree < 1) {
    Error = BAD_SIZE;
    fclose (PtF);
    return NULL;
  }

  if ((Poly = PolyCreate (Degree)) == NULL) { fclose (PtF); return NULL; }

  for (I = 0; I <= Degree; I++) fscanf (PtF, "%lf", Poly->Poly+I);

  fclose (PtF);  /* fecho do ficheiro */

  return Poly;  /* devolve o poly criado */
}

/*******************************************************************************
  Fun��o auxiliar que verifica se os dois polin�mios existem. Devolve 1 em caso
  afirmativo e 0 em caso contr�rio.
*******************************************************************************/
static int ValidPolys (PtPoly ppol1, PtPoly ppol2)
{
  /* verifica se os dois polin�mios existem */
  if ((ppol1 == NULL) || (ppol2 == NULL)) { Error = NO_POLY; return 0; }

  return 1;  /* os dois polin�mios existem */
}
