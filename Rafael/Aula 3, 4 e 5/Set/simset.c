/*******************************************************************************

 Programa gráfico de simulação da funcionalidade do TDA Set


 Autor : António Manuel Adrego da Rocha    Data : Março de 2013

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "set.h"  /* Ficheiro de interface do tipo de dados */

#define MAX_SETS 14 
#define MAX_OPTIONS 11

void Menu (void);
void ReadOption (int *);
void ReadSetIndex (int *, char *);
int ActiveSet (PtSet *, int);
int NotActiveSet (PtSet *, int);
void ReadFileName (char *);
void WriteErrorMessage (char *);
void ReadElement (char *);
void ReadNextInquiry (char *, char *);
PtSet ReadSet (void);
void WriteSet (PtSet);

int main (void)
{
  PtSet SetArray[MAX_SETS];
  int Option, Index, Set1, Set2, Set3, Equals;
  char FileName[21], Character;

  for (Index = 0; Index < MAX_SETS; Index++) SetArray[Index] = NULL;
  
  do
  {
    /* limpar o ecran e apresentar menu */
    Menu ();

    /* limpar o erro entretanto ocorrido */
    SetClearError ();

    /* apresentar os conjuntos activos */
    for (Index = 0; Index < MAX_SETS; Index++)
      if (SetArray[Index] != NULL)
      {
        printf ("\e[1m\e[%d;47f", 5+Index); WriteSet (SetArray[Index]);
        printf ("\e[0m");
      }

    /* ler opcao do utilizador */
    ReadOption (&Option);

    switch (Option)
    {
        case 1 :  ReadSetIndex (&Set1, "conjunto");
                  if (ActiveSet (SetArray, Set1)) break;
                  SetArray[Set1] = ReadSet ();
                  if (SetError ()) WriteErrorMessage ("A criacao");
                  break;

        case 2 :  ReadSetIndex (&Set1, "conjunto");
                  if (ActiveSet (SetArray, Set1)) break;
                  ReadFileName (FileName);
                  SetArray[Set1] = SetCreateFile (FileName);
                  if (SetError ()) WriteErrorMessage ("A leitura");
                  break;

        case 3 :  ReadSetIndex (&Set1, "conjunto");
                  if (NotActiveSet (SetArray, Set1)) break;
                  do
                  {
                    ReadElement (&Character);
                    if (Character != '#')
                    {
                      SetClearError ();
                      SetInsertElement (SetArray[Set1], Character);
                      if (SetError ())
                      {
                        WriteErrorMessage ("A insercao");
                        if (SetError () == NO_MEM) break;
                      }
                    }
                    ReadNextInquiry (&Character, "inserir");
                  } while (Character == 'S');
                  break;
          
        case 4 :  ReadSetIndex (&Set1, "conjunto");
                  if (NotActiveSet (SetArray, Set1)) break;
                  do
                  {
                    ReadElement (&Character);
                    if (Character != '#')
                    {
                      SetClearError ();
                      SetDeleteElement (SetArray[Set1], Character);
                      if (SetError ()) WriteErrorMessage ("A remocao");
                    }
                    ReadNextInquiry (&Character, "retirar");
                  } while (Character == 'S');
                  break;

        case 5 :  ReadSetIndex (&Set1, "primeiro conjunto");
                  ReadSetIndex (&Set2, "segundo conjunto");
                  do
                  {
                      ReadSetIndex (&Set3, "conjunto reuniao");
                  } while (Set3 == Set1 || Set3 == Set2);
                  if (ActiveSet (SetArray, Set3)) break;
                  SetArray[Set3] = SetReunion (SetArray[Set1], SetArray[Set2]);
                  if (SetError ()) WriteErrorMessage ("A reuniao");
                  break;

        case 6 :  ReadSetIndex (&Set1, "primeiro conjunto");
                  ReadSetIndex (&Set2, "segundo conjunto");
                  do
                  {
                      ReadSetIndex (&Set3, "conjunto interseccao");
                  } while (Set3 == Set1 || Set3 == Set2);
                  if (ActiveSet (SetArray, Set3)) break;
                  SetArray[Set3] = SetIntersection (SetArray[Set1], SetArray[Set2]);
                  if (SetError ()) WriteErrorMessage ("A interseccao");
                  break;

        case 7 :  ReadSetIndex (&Set1, "primeiro conjunto");
                  ReadSetIndex (&Set2, "segundo conjunto");
                  do
                  {
                      ReadSetIndex (&Set3, "conjunto diferenca simetrica");
                  } while (Set3 == Set1 || Set3 == Set2);
                  if (ActiveSet (SetArray, Set3)) break;
                  SetArray[Set3] = SetSymmetricDifference (SetArray[Set1], SetArray[Set2]);
                  if (SetError ()) WriteErrorMessage ("A diferenca simetrica");
                  break;

        case 8 :  ReadSetIndex (&Set1, "primeiro conjunto");
                  ReadSetIndex (&Set2, "segundo conjunto");
                  Equals = SetEquals (SetArray[Set1], SetArray[Set2]);
                  if (SetError ()) WriteErrorMessage ("A comparacao");
                  else
                  {
                    if (Equals) printf("\e[25;1f| \e[1mOs conjuntos %d e %d sao iguais", Set1, Set2);
                    else printf("\e[25;1f| \e[1mOs conjuntos %d e %d nao sao iguais", Set1, Set2);
                    printf("\e[0m\e[26;1f| Prima uma tecla para continuar ");
                    scanf ("%*[^\n]"); scanf ("%*c");
                  }
                  break;

        case 9 :  ReadSetIndex (&Set1, "conjunto origem");
                  if (NotActiveSet (SetArray, Set1)) break;
                  do
                  {
                      ReadSetIndex (&Set2, "conjunto destino");
                  } while (Set2 == Set1);
                  if (ActiveSet (SetArray, Set2)) break;
                  SetArray[Set2] = SetCopy (SetArray[Set1]);
                  if (SetError ()) WriteErrorMessage ("A copia");
                  break;

        case 10 :  ReadSetIndex (&Set1, "conjunto");
                  if (NotActiveSet (SetArray, Set1)) break;
                  ReadFileName (FileName);
                  SetStoreFile (SetArray[Set1], FileName);
                  if (SetError ()) WriteErrorMessage ("O armazenamento");
                  break;

        case 11 : ReadSetIndex (&Set1, "conjunto");
                  if (NotActiveSet (SetArray, Set1)) break;
                  SetDestroy (&SetArray[Set1]);
                  if (SetError ()) WriteErrorMessage ("A eliminacao");
                  break;
    }

  } while (Option != 0);

  for (Index = 0; Index < MAX_SETS; Index++) 
    if (SetArray[Index] != NULL) SetDestroy (&SetArray[Index]);

  printf ("\e[29;1f");

  return 0;
}

void Menu (void)
{
  system ("clear");

  printf("\e[2;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[3;1f|                       Programa Grafico Para Simular Operacoes Sobre Conjuntos                        |\n");
  printf("\e[4;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[5;1f|  1 - Ler um conjunto (teclado)  | Conjunto  0 =                                                      |\n");
  printf("\e[6;1f|  2 - Ler um conjunto (ficheiro) | Conjunto  1 =                                                      |\n");
  printf("\e[7;1f|  3 - Inserir elemento           | Conjunto  2 =                                                      |\n");
  printf("\e[8;1f|  4 - Retirar elemento           | Conjunto  3 =                                                      |\n");
  printf("\e[9;1f|  5 - Reuniao de conjuntos       | Conjunto  4 =                                                      |\n");
  printf("\e[10;1f|  6 - Interseccao de conjuntos   | Conjunto  5 =                                                      |\n");
  printf("\e[11;1f|  7 - Diferença de conjuntos     | Conjunto  6 =                                                      |\n");
  printf("\e[12;1f|  8 - Comparar conjuntos         | Conjunto  7 =                                                      |\n");
  printf("\e[13;1f|  9 - Copiar um conjunto         | Conjunto  8 =                                                      |\n");
  printf("\e[14;1f| 10 - Armazenar um conjunto      | Conjunto  9 =                                                      |\n");
  printf("\e[15;1f| 11 - Apagar um conjunto         | Conjunto 10 =                                                      |\n");
  printf("\e[16;1f|  0 - Terminar o programa        | Conjunto 11 =                                                      |\n");
  printf("\e[17;1f|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| Conjunto 12 =                                                      |\n");
  printf("\e[18;1f| Opcao ->                        | Conjunto 13 =                                                      |\n");
  printf("\e[19;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[20;1f|                                     Janela de Aquisicao de Dados                                     |\n");
  printf("\e[21;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[22;1f|                                                                                                      |\n");
  printf("\e[23;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[24;1f|                              Janela de Mensagens de Erro e de Resultados                             |\n");
  printf("\e[25;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[26;1f|                                                                                                      |\n");
  printf("\e[27;1f|                                                                                                      |\n");
  printf("\e[28;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void ReadOption (int *poption)
{
  do
  {  
    printf("\e[18;1f| Opcao ->                        |");
    printf("\e[18;12f"); scanf ("%d", poption);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*poption < 0 || *poption > MAX_OPTIONS);
}

void ReadSetIndex (int *pns, char *pmsg)
{
  int MsgLen = strlen (pmsg);

  do
  {
    *pns = -1;
    printf("\e[22;1f| Indice do %s ->                               ", pmsg);
    printf("\e[22;%df", 17+MsgLen); scanf ("%d", pns);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pns < 0 || *pns >= MAX_SETS);
}

int ActiveSet (PtSet psetarray[], int pnset)
{
  char Character;

  if (psetarray[pnset] != NULL)
  {
    do
    {
      printf("\e[1m\e[26;1f| O conjunto %d ja existe!                     ", pnset);
      printf("\e[0m\e[27;1f| Deseja apaga-lo (s/n)? ");
      scanf ("%c", &Character); Character = tolower (Character);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (Character != 'n' && Character != 's');

    if (Character == 's') { SetDestroy (&psetarray[pnset]); return 0; }
    else  return 1;
  }
  else return 0;
}

int NotActiveSet (PtSet psetarray[], int pnset)
{
  if (psetarray[pnset] == NULL)
  {
    printf("\e[1m\e[26;1f| O conjunto %d nao existe!                     ", pnset);
    printf("\e[0m\e[27;1f| Prima uma tecla para continuar ");
    scanf ("%*[^\n]"); scanf ("%*c");
    return 1;
  }
  else return 0;
}

void ReadFileName (char *pfname)
{
  int Status;

  do
  {
    printf("\e[22;1f| Nome do ficheiro ->                               ");
    printf("\e[22;23f"); Status = scanf ("%20[^\n]", pfname);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Status == 0);
}

void WriteErrorMessage (char *pmsg)
{
  printf("\e[26;1f| %s de conjuntos nao foi efectuada devido a -> \e[1m%s", pmsg, SetErrorMessage ());
  printf("\e[0m\e[27;1f| Prima uma tecla para continuar ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

void ReadElement (char *pc)
{
  do
  {
    printf("\e[22;1f| Elemento para o conjunto [A-Z ou # para terminar] ->                               ");
    printf("\e[22;56f"); scanf ("%c", pc); *pc = toupper (*pc);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while ((*pc < 'A' || *pc > 'Z') && (*pc != '#'));
}

void ReadNextInquiry (char *pcar, char *pmsg)
{
  do
  {
    printf("\e[22;1f| Deseja %s mais algum elemento do conjunto (s/n)?           ", pmsg);
    printf("\e[22;57f"); scanf ("%c", pcar); *pcar = toupper (*pcar);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pcar != 'N' && *pcar != 'S');
}

PtSet ReadSet (void)
{
  PtSet Set; char Character;
    
  if ((Set = SetCreate ()) == NULL) return NULL;

  ReadElement (&Character);
  while (Character != '#')
  {
    SetInsertElement (Set, Character);
    if (SetError ())
    {
      WriteErrorMessage ("A insercao");
      if (SetError () == NO_MEM) break;
    }
    ReadElement (&Character);
  }

  return Set;  /* devolve o conjunto criado */
}

void WriteSet (PtSet pset)
{
  unsigned int Cardinal, I; 

  if (pset == NULL) return;  /* verifica se o conjunto existe */

  Cardinal = SetCardinal (pset);

  printf ("{ ");
  /* escrita dos elementos do conjunto */
  for (I = 1; I <= Cardinal; I++) printf ("%c ", SetObserveElement (pset, I));
  printf ("}\n");
}

