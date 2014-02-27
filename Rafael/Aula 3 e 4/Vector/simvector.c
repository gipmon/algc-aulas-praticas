/*******************************************************************************

 Programa gráfico de simulação da funcionalidade do TDA Vector


 Autor : António Manuel Adrego da Rocha    Data : Março de 2013

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "vector.h"  /* Ficheiro de interface do tipo de dados */


#define MAX_VECTORS 13
#define MAX_OPTIONS 10

void Menu (void);
void ReadOption (int *);
void ReadVectorIndex (int *, char *);
int ActiveVector (PtVector *, int);
int NotActiveVector (PtVector *, int);
void ReadFileName (char *);
void WriteErrorMessage (char *);
void WriteMessageResult (char *, int, int, double);
PtVector ReadVector (void); 
void WriteVector (PtVector);

int main (void)
{
  PtVector VectorArray[MAX_VECTORS];
  int Option, Index, Vector1, Vector2, Vector3, Equals;
  double ScalarProduct;
  char FileName[21];

  for (Index = 0; Index < MAX_VECTORS; Index++) VectorArray[Index] = NULL;
  
  do
  {
    /* limpar o ecran e apresentar menu */
    Menu ();

    /* inicializar o erro */
    VectorClearError ();

    /* apresentar os vectores activos */
    for (Index = 0; Index < MAX_VECTORS; Index++)
      if (VectorArray[Index] != NULL)
      {
        printf ("\e[1m\e[%d;47f", 5+Index); WriteVector (VectorArray[Index]);
        printf ("\e[0m");
      }

    /* ler opcao do utilizador */
    ReadOption (&Option);

    switch (Option)
    {
        case 1 :  ReadVectorIndex (&Vector1, "vector");
                  if (ActiveVector (VectorArray, Vector1)) break;
                  VectorArray[Vector1] = ReadVector ();
                  if (VectorError ()) WriteErrorMessage ("A criacao");
                  break;

        case 2 :  ReadVectorIndex (&Vector1, "vector");
                  if (ActiveVector (VectorArray, Vector1)) break;
                  ReadFileName (FileName);
                  VectorArray[Vector1] = VectorCreateFile (FileName);
                  if (VectorError ()) WriteErrorMessage ("A leitura");
                  break;

        case 3 :  ReadVectorIndex (&Vector1, "primeiro vector");
                  ReadVectorIndex (&Vector2, "segundo vector");
                  do
                  {
                      ReadVectorIndex (&Vector3, "vector soma");
                  } while (Vector3 == Vector1 || Vector3 == Vector2);
                  if (ActiveVector (VectorArray, Vector3)) break;
                  VectorArray[Vector3] = VectorAddition (VectorArray[Vector1], VectorArray[Vector2]);
                  if (VectorError ()) WriteErrorMessage ("A soma");
                  break;

        case 4 :  ReadVectorIndex (&Vector1, "primeiro vector");
                  ReadVectorIndex (&Vector2, "segundo vector");
                  do
                  {
                      ReadVectorIndex (&Vector3, "vector diferenca");
                  } while (Vector3 == Vector1 || Vector3 == Vector2);
                  if (ActiveVector (VectorArray, Vector3)) break;
                  VectorArray[Vector3] = VectorSubtraction (VectorArray[Vector1], VectorArray[Vector2]);
                  if (VectorError ()) WriteErrorMessage ("A diferenca");
                  break;

        case 5 :  ReadVectorIndex (&Vector1, "primeiro vector");
                  ReadVectorIndex (&Vector2, "segundo vector");
                  do
                  {
                      ReadVectorIndex (&Vector3, "vector produto");
                  } while (Vector3 == Vector1 || Vector3 == Vector2);
                  VectorArray[Vector3] = VectorMultiplication (VectorArray[Vector1], VectorArray[Vector2]);
                  if (VectorError ()) WriteErrorMessage ("O produto vectorial");
                  break;

        case 6 :  ReadVectorIndex (&Vector1, "primeiro vector");
                  ReadVectorIndex (&Vector2, "segundo vector");
                  ScalarProduct = VectorScalarMultiplication (VectorArray[Vector1], VectorArray[Vector2]);
                  if (VectorError ()) WriteErrorMessage ("O produto escalar");
                  else WriteMessageResult ("Produto escalar dos vectores", Vector1, Vector2, ScalarProduct);
                  break;

        case 7 :  ReadVectorIndex (&Vector1, "primeiro vector");
                  ReadVectorIndex (&Vector2, "segundo vector");
                  Equals = VectorEquals (VectorArray[Vector1], VectorArray[Vector2]);
                  if (VectorError ()) WriteErrorMessage ("A comparacao");
                  else
                  {
                    if (Equals) printf("\e[25;1f| \e[1mOs vectores %d e %d sao iguais", Vector1, Vector2);
                    else printf("\e[25;1f| \e[1mOs vectores %d e %d nao sao iguais", Vector1, Vector2);
                    printf("\e[0m\e[26;1f| Prima uma tecla para continuar ");
                    scanf ("%*[^\n]"); scanf ("%*c");
                  }
                  break;

        case 8 :  ReadVectorIndex (&Vector1, "vector origem");
                  if (NotActiveVector (VectorArray, Vector1)) break;
                  do
                  {
                      ReadVectorIndex (&Vector2, "vector destino");
                  } while (Vector2 == Vector1);
                  if (ActiveVector (VectorArray, Vector2)) break;
                  VectorArray[Vector2] = VectorCopy (VectorArray[Vector1]);
                  if (VectorError ()) WriteErrorMessage ("A copia do vector");
                  break;

        case 9 :  ReadVectorIndex (&Vector1, "vector");
                  if (NotActiveVector (VectorArray, Vector1)) break;
                  ReadFileName (FileName);
                  VectorStoreFile (VectorArray[Vector1], FileName);
                  if (VectorError ()) WriteErrorMessage ("O armazenamento");
                  break;
        
        case 10 : ReadVectorIndex (&Vector1, "vector");
                  if (NotActiveVector (VectorArray, Vector1)) break;
                  VectorDestroy (&VectorArray[Vector1]);
                  if (VectorError ()) WriteErrorMessage ("A eliminacao");
                  break;
    }

  } while (Option != 0);

  for (Index = 0; Index < MAX_VECTORS; Index++) 
    if (VectorArray[Index] != NULL) VectorDestroy (&VectorArray[Index]);

  printf ("\e[28;1f");

  return EXIT_SUCCESS;
}

void Menu (void)
{
  system ("clear");

  printf("\e[2;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[3;1f|                                  Programa Grafico Para Simular Operacoes Sobre Vectores                                  |\n");
  printf("\e[4;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[5;1f|  1 - Ler um vector (teclado)  | Vector  0 =                                                                              |\n");
  printf("\e[6;1f|  2 - Ler um vector (ficheiro) | Vector  1 =                                                                              |\n");
  printf("\e[7;1f|  3 - Somar vectores           | Vector  2 =                                                                              |\n");
  printf("\e[8;1f|  4 - Subtrair vectores        | Vector  3 =                                                                              |\n");
  printf("\e[9;1f|  5 - Produto vectorial        | Vector  4 =                                                                              |\n");
  printf("\e[10;1f|  6 - Produto escalar          | Vector  5 =                                                                              |\n");
  printf("\e[11;1f|  7 - Comparar vectores        | Vector  6 =                                                                              |\n");
  printf("\e[12;1f|  8 - Copiar um vector         | Vector  7 =                                                                              |\n");
  printf("\e[13;1f|  9 - Armazenar um vector      | Vector  8 =                                                                              |\n");
  printf("\e[14;1f| 10 - Apagar um vector         | Vector  9 =                                                                              |\n");
  printf("\e[15;1f|  0 - Terminar o programa      | Vector 10 =                                                                              |\n");
  printf("\e[16;1f|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| Vector 11 =                                                                              |\n");
  printf("\e[17;1f| Opcao ->                      | Vector 12 =                                                                              |\n");
  printf("\e[18;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[19;1f|                                               Janela de Aquisicao de Dados                                               |\n");
  printf("\e[20;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[21;1f|                                                                                                                          |\n");
  printf("\e[22;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[23;1f|                                        Janela de Mensagens de Erro e de Resultados                                       |\n");
  printf("\e[24;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[25;1f|                                                                                                                          |\n");
  printf("\e[26;1f|                                                                                                                          |\n");
  printf("\e[27;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void ReadOption (int *poption)
{
  do
  {  
    printf("\e[17;1f| Opcao ->                      |");
    printf("\e[17;12f"); scanf ("%d", poption);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*poption < 0 || *poption > MAX_OPTIONS);
}

void ReadVectorIndex (int *pnv, char *pmsg)
{
  unsigned int MsgLen = strlen (pmsg);

  do
  {
    *pnv = -1;
    printf("\e[21;1f| Indice do %s ->                               ", pmsg);
    printf("\e[21;%df", 17+MsgLen); scanf ("%d", pnv);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pnv < 0 || *pnv >= MAX_VECTORS);
}

int ActiveVector (PtVector pvecarray[], int pnvec)
{
  char Character;

  if (pvecarray[pnvec] != NULL)
  {
    do
    {
      printf("\e[1m\e[25;1f| O vector %d ja existe!                     ", pnvec);
      printf("\e[0m\e[26;1f| Deseja apaga-lo (s/n)? ");
      scanf ("%c", &Character); Character = tolower (Character);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (Character != 'n' && Character != 's');

    if (Character == 's') { VectorDestroy (&pvecarray[pnvec]); return 0; }
    else  return 1;
  }
  else return 0;
}

int NotActiveVector (PtVector pvecarray[], int pnvec)
{
  if (pvecarray[pnvec] == NULL)
  {
    printf("\e[1m\e[25;1f| O vector %d nao existe!                     ", pnvec);
    printf("\e[0m\e[26;1f| Prima uma tecla para continuar ");
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
    printf("\e[21;1f| Nome do ficheiro ->                               ");
    printf("\e[21;23f"); Status = scanf ("%20[^\n]", pfname);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Status == 0);
}

void WriteErrorMessage (char *pmsg)
{
  printf("\e[25;1f| %s de vectores nao foi efectuada devido a -> \e[1m%s", pmsg, VectorErrorMessage ());
  printf("\e[0m\e[26;1f| Prima uma tecla para continuar ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

void WriteMessageResult (char *pmsg, int pv1, int pv2, double pval)
{
  printf("\e[1m\e[25;1f| %s %d e %d = \e[1m%f", pmsg, pv1, pv2, pval);
  printf("\e[0m\e[26;1f| Prima uma tecla para continuar ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

PtVector ReadVector (void)
{
  PtVector Vector; unsigned int I, Dim; double Component;

  do
  {
    printf("\e[21;1f| Dimensao do vector ->                               ");
    printf("\e[21;25f"); scanf ("%d", &Dim);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Dim < 1 || Dim > 15);
    
  /* cria o vector nulo */
  if ((Vector = VectorCreate (Dim)) == NULL) return NULL;

  /* leitura das componentes do vector do teclado */
  for (I = 0; I < Dim; I++)
  {
    printf("\e[21;1f| Vector(%d) ->                               ", I);
    printf("\e[21;16f"); scanf ("%lf", &Component);
    scanf ("%*[^\n]"); scanf ("%*c");
    VectorModifyComponent (Vector, I, Component);
  }

  return Vector;  /* devolve o vector criado */
}

void WriteVector (PtVector pv)
{
  int I, Dim = VectorDimension (pv);

  if (pv != NULL && Dim != 0)
  {  /* escrita das componentes do vector no monitor */
    printf ("( ");
    for (I = 0; I < Dim-1; I++) printf ("%0.1f , ", VectorObserveComponent (pv, I));
    printf ("%0.1f )\n", VectorObserveComponent (pv, I));
  }
}
