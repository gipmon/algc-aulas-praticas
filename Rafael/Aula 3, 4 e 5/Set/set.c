/*******************************************************************************

 Ficheiro de implementa��o do Tipo de Dados Abstracto CONJUNTO (set.c).
 A estrutura de dados de suporte do conjunto � uma estrutura, constitu�da pelo
 campo Cardinal para armazenar o n�mero de elementos existentes no conjunto e o
 campo Head que � a cabe�a da lista biligada dos elementos do conjunto. A lista
 de elementos do conjunto, que s�o caracteres alfab�ticos mai�sculos, est�
 ordenada por ordem crescente.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Janeiro de 2006

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "set.h"    /* Ficheiro de interface do TDA */

/************ Defini��o da Estrutura de Dados Interna do Conjunto ************/

typedef struct node *PtNode;

struct node       /* defini��o de um n� da lista biligada */
{
  char *PtElem;   /* ponteiro para o elemento */
  PtNode PtNext;  /* ponteiro para o n� seguinte */
  PtNode PtPrev;  /* ponteiro para o n� anterior */
};

struct set
{
  unsigned int Cardinal;   /* cardinal do conjunto */
  PtNode Head;             /* cabe�a da lista dos elementos do conjunto */
};

/*********************** Controlo Centralizado de Erro ************************/

static unsigned int Error = OK;  /* inicializa��o do erro */

static char *ErrorMessages[] = {
                                 "Sem erro",
                                 "O(s) conjunto(s) n�o existe(m)",
                                 "N�o h� mem�ria",
                                 "O ficheiro n�o existe",
                                 "O elemento n�o existe no conjunto",
                                 "O elemento j� existe no conjunto",
                                };

static char *AbnormalErrorMessage = "Erro desconhecido";

/************** N�mero de mensagens de erro previstas no m�dulo ***************/

#define N (sizeof (ErrorMessages) / sizeof (char *))

/************************ Alus�o �s Fun��es Auxiliares ************************/

static int ValidSets (PtSet, PtSet);
static PtNode CreateElement (char);
static void DestroyElement (PtNode *);
static PtNode PosInsert (PtSet, char);
static PtNode PosDelete (PtSet, char);

/*************************** Defini��o das Fun��es ****************************/

void SetClearError (void)
{
  Error = OK;
}

int SetError (void)
{
  return Error;
}

char *SetErrorMessage (void)
{
  if (Error < N) return ErrorMessages[Error];
  else return AbnormalErrorMessage;  /* n�o h� mensagem de erro */
}

PtSet SetCreate (void){
  PtSet Set;

  if ((Set = (PtSet) malloc (sizeof (struct set))) == NULL)
  {
    Error = NO_MEM;
    return NULL;
  }

  Set->Head = NULL;
  Set->Cardinal = 0;

  Error = OK;
  return Set;
}

void SetDestroy (PtSet *pset)
{
  PtSet tmp = *pset;

  if(tmp == NULL){
    Error = NO_SET;
    return;
  }

  while(tmp->Cardinal){
    char c = SetObserveElement(tmp, 1);
    SetDeleteElement(tmp, c);
  }

  free(tmp->Head);
  free(tmp);

  *pset = NULL;
  Error = OK;
}

PtSet SetCopy (PtSet pset)
{
  int i;
  PtSet copy;

  if(pset == NULL){
    Error = NO_SET;
    return NULL;
  }

  if((copy = SetCreate()) == NULL){
    return NULL;
  }

  for(i = 0; i < pset->Cardinal; i++){
    SetInsertElement(copy, SetObserveElement(pset, i));
  }

  Error = OK;
  return copy;
}

int SetCardinal (PtSet pset)
{
  if (pset == NULL)  /* verifica se o conjunto existe */
  {
    Error = NO_SET; return 0;
  }

  Error = OK;
  return pset->Cardinal;  /* devolve o cardinal */

}

int SetInsertElement (PtSet pset, char pelem)
{
  PtNode NoTmp, NoIns;

  if (pset == NULL)  /* verifica se o conjunto existe */
  {
    Error = NO_SET; return 0;
  }

  /* conjunto vazio ou elemento menor do que o primeiro elemento do conjunto */
  if (pset->Head == NULL || pelem < *pset->Head->PtElem)
  {
    if ((NoTmp  = CreateElement (pelem)) == NULL) return 0;
    /* inser��o sem sucesso, porque n�o � poss�vel criar o elemento */

    NoTmp->PtNext = pset->Head; pset->Head = NoTmp;
    if (NoTmp->PtNext != NULL) NoTmp->PtNext->PtPrev = NoTmp;
  }
  else
  {
    /* procurar se o elemento existe ou a sua posi��o de inser��o caso n�o exista */
    if ((NoIns = PosInsert (pset, pelem)) == NULL) return 0; 
    /* inser��o sem sucesso, porque o elemento j� existe no conjunto */

    if ((NoTmp = CreateElement (pelem)) == NULL) return 0;
    /* inser��o sem sucesso, porque n�o � poss�vel criar o elemento */

    /* inserir � frente do n� da lista */
    NoTmp->PtNext = NoIns->PtNext; 
    if (NoTmp->PtNext != NULL) NoTmp->PtNext->PtPrev = NoTmp;
    NoTmp->PtPrev = NoIns; NoIns->PtNext = NoTmp;
  }

  pset->Cardinal++;  /* incrementa o cardinal do conjunto */
  Error = OK;
  return 1;  /* inser��o com sucesso */
}

int SetDeleteElement (PtSet pset, char pelem)
{
  PtNode NoRem;

  if (pset == NULL)  /* verifica se o conjunto existe */
  {
    Error = NO_SET; return 0;
  }

  if ((NoRem = PosDelete (pset, pelem)) == NULL) return 0; 
  /* remo��o sem sucesso, porque o elemento ainda n�o existe no conjunto */

  if (NoRem == pset->Head)  /* primeiro elemento da lista */
  {
    if (NoRem->PtNext != NULL) NoRem->PtNext->PtPrev = NULL;
    pset->Head = NoRem->PtNext;
  }
  else  /* noutra posi��o da lista */
  {
    NoRem->PtPrev->PtNext = NoRem->PtNext;
    if (NoRem->PtNext != NULL) NoRem->PtNext->PtPrev = NoRem->PtPrev;
  }

  DestroyElement (&NoRem);  /* liberta a mem�ria ocupada pelo elemento */
  pset->Cardinal--;  /* decrementa o cardinal do conjunto */
  Error = OK;
  return 1;  /* remo��o com sucesso */
}

char SetObserveElement (PtSet pset, unsigned int ppos)
{
  PtNode NoTmp; unsigned int I;

  if (pset == NULL)  /* verifica se o conjunto existe */
  {
    Error = NO_SET; return 0;
  }

  if (ppos > pset->Cardinal)
  {
    Error = NO_ELEM; return 0;
  }

  NoTmp = pset->Head;
  for (I = 1; I < ppos; I++) NoTmp = NoTmp->PtNext;

  if (NoTmp == NULL) return ' ';
  else return *NoTmp->PtElem;
}

int SetSearchElement (PtSet pset, char pelem)
{
  if (pset == NULL)  /* verifica se o conjunto existe */
  {
    Error = NO_SET; return 0;
  }

  if (PosDelete (pset, pelem) != NULL) return 1;  /* o elemento existe */

  Error = OK;
  return 0;  /* o elemento n�o existe */
}

PtSet SetReunion (PtSet pset1, PtSet pset2)
{
  PtSet reuniao;
  int i;

  if(!ValidSets(pset1, pset2)){
    return NULL;
  }

  if((reuniao = SetCreate()) == NULL){
    return NULL;
  }

  for(i = 0; i < pset1->Cardinal; i++){
    if(SetInsertElement(reuniao, SetObserveElement(pset1, i)) == 0){
      SetDestroy(&reuniao);
      return NULL;
    }
  }

  for(i = 0; i < pset2->Cardinal; i++) {
    char c = SetObserveElement(pset2, i);
    if(!SetSearchElement(reuniao, c)){
      if(!SetInsertElement(reuniao, c)){
        SetDestroy(&reuniao);
        return NULL;
      }
    }
  }

  Error = OK;
  return reuniao;
}

PtSet SetIntersection (PtSet pset1, PtSet pset2)
{
  PtSet intersection;
  int i;
  char c;

  if(!ValidSets(pset1, pset2)){
    return NULL;
  }

  if((intersection = SetCreate()) == NULL){
    return NULL;
  }

  for(i = 0; i < pset1->Cardinal; i++){
    c = SetObserveElement(pset1, i);
    if(SetSearchElement(pset2, c)){
        if(!SetInsertElement(intersection, c)){
          SetDestroy(&intersection);
          return NULL;
        }
    }
  }

  Error = OK;
  return intersection;
}

PtSet SetSymmetricDifference (PtSet pset1, PtSet pset2)
{
  PtSet Symmetric;
  int i;

  if(!ValidSets(pset1, pset2)){
    return NULL;
  }

  if((Symmetric = SetCreate()) == NULL){
    return NULL;
  }

  for(i = 0; i < pset1->Cardinal; i++){
    if(SetSearchElement(pset2, SetObserveElement(pset1, i))==0){
      if(SetInsertElement(Symmetric, SetObserveElement(pset1, i))==0){
        SetDestroy(&Symmetric);
        return NULL;
      }
    }
  }

  for(i = 0; i < pset2->Cardinal; i++){
    if(SetSearchElement(pset1, SetObserveElement(pset2, i))==0){
      if(SetInsertElement(Symmetric, SetObserveElement(pset2, i))==0){
        SetDestroy(&Symmetric);
        return NULL;
      }
    }
  }

  Error = OK;
  return Symmetric;
}

int SetEquals (PtSet pset1, PtSet pset2)
{
  int i;

  if(!ValidSets(pset1, pset2)){
    return NULL;
  }

  for(i = 0; i < pset1->Cardinal; i++){
    if(SetObserveElement(pset1, i) != SetObserveElement(pset2,i)){
      Error = OK;
      return 0;
    }
  }

  Error = OK;
  return 1;
}

void SetStoreFile (PtSet pset, char *pnomef)
{
  FILE *PtF; PtNode NoTmp;

  /* verifica se o conjunto existe */
  if (pset == NULL) { Error = NO_SET; return ; }

  /* abertura com validacao do ficheiro para escrita */
  if ((PtF = fopen (pnomef, "w")) == NULL)
  { Error = NO_FILE; return ; }

  /* escrita do cardinal do conjunto no ficheiro */
  fprintf (PtF, "%u\n", pset->Cardinal);

  /* escrita dos elementos do conjunto no ficheiro */
  for (NoTmp = pset->Head; NoTmp != NULL; NoTmp = NoTmp->PtNext)
  fprintf (PtF, "%c\n", *NoTmp->PtElem);

  Error = OK;
  fclose (PtF);
}

PtSet SetCreateFile (char *pnomef)
{
  PtSet Conj; FILE *PtF; unsigned int Cardinal, I; char Elemento;

  /* abertura com validacao do ficheiro para leitura */
  if ( (PtF = fopen (pnomef, "r")) == NULL)
  { Error = NO_FILE; return NULL; }

  /* leitura do cardinal do conjunto do ficheiro e cria��o do conjunto vazio */
  fscanf (PtF, "%u", &Cardinal); fscanf (PtF, "%*c");

  if ((Conj = SetCreate ()) == NULL)
  { fclose (PtF); return NULL; }

  /* leitura dos elementos do conjunto do ficheiro */
  for (I = 0; I < Cardinal ; I++)
  {
    fscanf (PtF, "%c", &Elemento); fscanf (PtF, "%*c");
    if (!SetInsertElement (Conj, Elemento))
      {
        SetDestroy (&Conj); fclose (PtF); return NULL; 
      }
  }

  /* fecho do ficheiro */
  fclose (PtF);

  /* devolve o conjunto criado */
  return Conj;
}

/********************** Defini��o das Fun��es Auxiliares **********************/

/*******************************************************************************
 Fun��o auxiliar que verifica se os dois ponteiros s�o v�lidos. Devolve 1 em
 caso afirmativo e 0 em caso contr�rio.
*******************************************************************************/
static int ValidSets (PtSet pset1, PtSet pset2)
{
  /* verifica se os dois conjuntos existem */
  if ((pset1 == NULL) || (pset2 == NULL)) { Error = NO_SET; return 0; }

  /* os dois conjuntos existem */
  return 1;
}

/*******************************************************************************
 Fun��o auxiliar que cria o elemento do conjunto. Come�a por criar um n� da
 lista biligada e depois cria o elemento, para onde copia o valor que se
 pretende armazenar. Devolve a refer�ncia do n� criado ou NULL, caso n�o consiga
 criar o n� ou o elemento, por falta de mem�ria. Valores de erro: NO_MEM.
*******************************************************************************/
static PtNode CreateElement (char pelem)
{
  PtNode NoTmp;

  if ((NoTmp = (PtNode) malloc (sizeof (struct node))) == NULL)
  {
    Error = NO_MEM; return NULL;
  }

  if ((NoTmp->PtElem = malloc (sizeof (char))) == NULL)
  {
    free (NoTmp);
    Error = NO_MEM; return NULL;
  }

  *NoTmp->PtElem = pelem;  /* copia o valor */
  NoTmp->PtNext = NULL;  /* aponta para a frente para NULL */
  NoTmp->PtPrev = NULL;  /* aponta para a tr�s para NULL */

  return NoTmp;  /* devolver a refer�ncia do n� criado */
}

/*******************************************************************************
 Fun��o auxiliar que elimina o elemento do conjunto, indicando para esse feito
 o n� onde o elemento est� dependurado. Come�a por verificar se o n� � valido,
 ap�s o que liberta a mem�ria ocupada pelo elemento e pelo n� da lista. Como esta
 fun��o � correctamente invocada, ela n�o precisa de actualizar a vari�vel de erro.
*******************************************************************************/
static void DestroyElement (PtNode *pnode)
{
  if (*pnode == NULL) return;
  
  free ((*pnode)->PtElem);
  free (*pnode);
  *pnode = NULL;
}

/*******************************************************************************
 Fun��o auxiliar que pesquisa um elemento no conjunto, para determinar a sua
 posi��o para eventual remo��o do conjunto. Devolve o endere�o do n� onde deve
 ser feita a remo��o, ou NULL caso o elemento ainda n�o exista no conjunto.
*******************************************************************************/
static PtNode PosDelete (PtSet pset, char pelem)
{
  PtNode Tmp;

  if (pset->Head == NULL) return NULL;  /* conjunto vazio */

  for (Tmp = pset->Head; Tmp != NULL; Tmp = Tmp->PtNext)
    if (*Tmp->PtElem == pelem) return Tmp;  /* elemento encontrado */

  Error = NO_ELEM; 
  return NULL;  /* elemento n�o encontrado */
}

/*******************************************************************************
 Fun��o auxiliar que pesquisa um elemento no conjunto, para determinar a sua
 posi��o para eventual coloca��o no conjunto. Devolve o endere�o do n� � frente
 do qual deve ser feita a inser��o, ou NULL caso o elemento j� exista no
 conjunto. A fun��o � invocada sabendo � partida que o conjunto n�o est� vazio
 ou que o elemento n�o vai ser inserido no in�cio do conjunto. 
*******************************************************************************/
static PtNode PosInsert (PtSet pset, char pelem)
{
  PtNode Tmp, NodePrev;

  for (Tmp = pset->Head; Tmp != NULL; NodePrev = Tmp, Tmp = Tmp->PtNext)
    if (*Tmp->PtElem >= pelem) break;

  /* se o elemento n�o foi encontrado ent�o entra � frente do n� anterior */
  if (Tmp == NULL || *Tmp->PtElem > pelem) return NodePrev;
  else
  {
    Error = REP_ELEM; 
    return NULL;  /* o elemento foi encontrado */
  }
}
