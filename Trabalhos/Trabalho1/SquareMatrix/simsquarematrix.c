/*******************************************************************************

 Programa gráfico de simulação da funcionalidade do TDA Matriz Quadrada


 Autor : António Manuel Adrego da Rocha    Data : Março de 2014

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "squarematrix.h"  /* Ficheiro de interface do tipo de dados */

#define MAX_MATRIXES 21
#define MAX_OPTIONS 18

void Menu (void);
void ReadOption (int *);
void ReadMatrixIndex (int *, char *);
int ActiveMatrix (PtSMatrix *, int);
int NotActiveMatrix (PtSMatrix *, int);
void ReadMatrixSize (unsigned int *);
void ReadFilename (char *);
void WriteErrorMessage (char *);
void WriteMessageResult (char *, double);
PtSMatrix ReadMatrix (unsigned int);
void WriteMatrix (PtSMatrix *, int);
void ChangeMatrix (PtSMatrix);
double ReadValue (void);
unsigned int ReadRow (char *, unsigned int);
unsigned int ReadColumn (char *, unsigned int);

int main (void)
{
  PtSMatrix MatrixArray[MAX_MATRIXES];
  int Option, l, Matrix1, Matrix2, Matrix3, Equals, Sym;
  unsigned Size, K, R, C; char FileName[21]; double Value;

  for (l = 0; l < MAX_MATRIXES; l++) MatrixArray[l] = NULL;
  
  do
  {

    /* limpar o ecran e apresentar menu */
    Menu ();

    /* limpar o erro entretanto ocorrido */
    SMatrixClearError ();

    /* apresentar as matrizes activas */
    for (l = 0; l < MAX_MATRIXES; l++)
      if (MatrixArray[l] != NULL)
      {
        Size = SMatrixSize (MatrixArray[l]);
        printf ("\e[1m\e[%d;47f Matriz %d x %d", 5+l, Size, Size);
        printf ("\e[0m");
      }

    /* ler opcao do utilizador */
    ReadOption (&Option);

    switch (Option)
    {
        case 1 :  ReadMatrixIndex (&Matrix1, "matriz");
                  if (ActiveMatrix (MatrixArray, Matrix1)) break;
                  ReadMatrixSize (&Size);
                  MatrixArray[Matrix1] = ReadMatrix (Size);
                  if (SMatrixError ()) WriteErrorMessage ("A criacao");
                  break;

        case 2 :  ReadMatrixIndex (&Matrix1, "matriz");
                  if (ActiveMatrix (MatrixArray, Matrix1)) break;
                  ReadFilename (FileName);
                  MatrixArray[Matrix1] = SMatrixCreateFile (FileName);
                  if (SMatrixError ()) WriteErrorMessage ("A leitura");
                  break;

        case 3 :  ReadMatrixIndex (&Matrix1, "matriz origem");
                  do
                  {
                      ReadMatrixIndex (&Matrix2, "matriz destino");
                  } while (Matrix2 == Matrix1);
                  if (ActiveMatrix (MatrixArray, Matrix2)) break;
                  MatrixArray[Matrix2] = SMatrixTranspose (MatrixArray[Matrix1]);
                  if (SMatrixError ()) WriteErrorMessage ("A transposicao");
                  break;

        case 4 :  ReadMatrixIndex (&Matrix1, "primeira matriz");
                  ReadMatrixIndex (&Matrix2, "segunda matriz");
                  do
                  {
                      ReadMatrixIndex (&Matrix3, "matriz soma");
                  } while (Matrix3 == Matrix1 || Matrix3 == Matrix2);
                  if (ActiveMatrix (MatrixArray, Matrix3)) break;
                  MatrixArray[Matrix3] = SMatrixAdd (MatrixArray[Matrix1], MatrixArray[Matrix2]);
                  if (SMatrixError ()) WriteErrorMessage ("A soma");
                  break;

        case 5 :  ReadMatrixIndex (&Matrix1, "primeira matriz");
                  ReadMatrixIndex (&Matrix2, "segunda matriz");
                  do
                  {
                      ReadMatrixIndex (&Matrix3, "matriz diferenca");
                  } while (Matrix3 == Matrix1 || Matrix3 == Matrix2);
                  if (ActiveMatrix (MatrixArray, Matrix3)) break;
                  MatrixArray[Matrix3] = SMatrixSub (MatrixArray[Matrix1], MatrixArray[Matrix2]);
                  if (SMatrixError ()) WriteErrorMessage ("A diferenca");
                  break;

        case 6 :  ReadMatrixIndex (&Matrix1, "primeira matriz");
                  ReadMatrixIndex (&Matrix2, "segunda matriz");
                  do
                  {
                      ReadMatrixIndex (&Matrix3, "matriz produto");
                  } while (Matrix3 == Matrix1 || Matrix3 == Matrix2);
                  if (ActiveMatrix (MatrixArray, Matrix3)) break;

                  MatrixArray[Matrix3] = SMatrixMult (MatrixArray[Matrix1], MatrixArray[Matrix2]);
                  if (SMatrixError ()) WriteErrorMessage ("A multiplicacao");
                  break;

        case 7 :  ReadMatrixIndex (&Matrix1, "matriz");
                  Value = SMatrixDeterminant (MatrixArray[Matrix1]);
                  if (SMatrixError ()) WriteErrorMessage ("O calculo do determinante");
                  else WriteMessageResult ("O determinante e igual a", Value);
                  break;

        case 8 :  ReadMatrixIndex (&Matrix1, "primeira matriz");
                  ReadMatrixIndex (&Matrix2, "segunda matriz");
                  Equals = SMatrixEquals (MatrixArray[Matrix1], MatrixArray[Matrix2]);
                  if (SMatrixError ()) WriteErrorMessage ("A comparacao");
                  else
                  {
                    if (Equals) printf("\e[33;1f| \e[1mAs matrizes %d e %d sao iguais", Matrix1, Matrix2);
                    else printf("\e[33;1f| \e[1mAs matrizes %d e %d nao sao iguais", Matrix1, Matrix2);
                    printf("\e[0m\e[34;1f| Prima uma tecla para continuar ");
                    scanf ("%*[^\n]"); scanf ("%*c");
                  }
                  break;

        case 9 :  ReadMatrixIndex (&Matrix1, "matriz origem");
                  if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                  do
                  {
                      ReadMatrixIndex (&Matrix2, "matriz destino");
                  } while (Matrix2 == Matrix1);
                  if (ActiveMatrix (MatrixArray, Matrix2)) break;
                  MatrixArray[Matrix2] = SMatrixCopy (MatrixArray[Matrix1]);
                  if (SMatrixError ()) WriteErrorMessage ("A copia");
                  break;

        case 10 : ReadMatrixIndex (&Matrix1, "matriz");
                  if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                  ReadFilename (FileName);
                  SMatrixStoreFile (MatrixArray[Matrix1], FileName);
                  if (SMatrixError ()) WriteErrorMessage ("O armazenamento");
                  break;

        case 11 : ReadMatrixIndex (&Matrix1, "matriz");
                  if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                  ChangeMatrix (MatrixArray[Matrix1]);
                  break;

        case 12 : ReadMatrixIndex (&Matrix1, "matriz");
                  if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                  WriteMatrix (MatrixArray, Matrix1);
                  printf("\e[1m\e[33;1f| Matriz %d                     ", Matrix1);
                  printf("\e[0m\e[34;1f| Prima uma tecla para continuar ");
                  scanf ("%*[^\n]"); scanf ("%*c");
                  break;

        case 13 : ReadMatrixIndex (&Matrix1, "matriz");
                  if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                  SMatrixDestroy (&MatrixArray[Matrix1]);
                  if (SMatrixError ()) WriteErrorMessage ("A eliminacao");
                  break;

        case 14 : ReadMatrixIndex (&Matrix1, "matriz");
        	      if (ActiveMatrix (MatrixArray, Matrix1)) break;
        	      ReadMatrixSize (&Size);
        	      MatrixArray[Matrix1] = SMatrixCreateIdentity (Size);
        	      if (SMatrixError ()) WriteErrorMessage ("A criacao da identidade");
       	          break;

        case 15 : ReadMatrixIndex (&Matrix1, "matriz origem");
                  if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                  do
                  {
                      ReadMatrixIndex (&Matrix2, "matriz destino");
                  } while (Matrix2 == Matrix1);
                  if (ActiveMatrix (MatrixArray, Matrix2)) break;
                  Value = ReadValue ();
                  MatrixArray[Matrix2] = SMatrixMultByScalar (MatrixArray[Matrix1], Value);
                  if (SMatrixError ()) WriteErrorMessage ("A multiplicacao por escalar");
                  break;

        case 16 : ReadMatrixIndex (&Matrix1, "matriz");
                  if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                  Sym = SMatrixIsSymetric (MatrixArray[Matrix1]);
                  if (SMatrixError ()) WriteErrorMessage ("A verificacao");
                  else
                  {
                    if (Sym) printf("\e[33;1f| \e[1mA matriz %d e simetrica", Matrix1);
                    else printf("\e[33;1f| \e[1mA matriz %d nao e simetrica", Matrix1);
                    printf("\e[0m\e[34;1f| Prima uma tecla para continuar ");
                    scanf ("%*[^\n]"); scanf ("%*c");
                  }
                  break;

        case 17 : ReadMatrixIndex (&Matrix1, "matriz");
                  if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                  K = ReadRow ("inicial", SMatrixSize (MatrixArray[Matrix1]));
                  R = ReadRow (" final ", SMatrixSize (MatrixArray[Matrix1]));
  		  SMatrixExchangeRow (MatrixArray[Matrix1], K, R);
                  if (SMatrixError ()) WriteErrorMessage ("A permutacao de linhas");
                  break;

         case 18 : ReadMatrixIndex (&Matrix1, "matriz");
                  if (NotActiveMatrix (MatrixArray, Matrix1)) break;
                  K = ReadColumn ("inicial", SMatrixSize (MatrixArray[Matrix1]));
                  C = ReadColumn (" final ", SMatrixSize (MatrixArray[Matrix1]));
                  SMatrixExchangeColumn (MatrixArray[Matrix1], K, C);
                  if (SMatrixError ()) WriteErrorMessage ("A permutacao de colunas");
                  break;
    }

  } while (Option != 0);

  for (l = 0; l < MAX_MATRIXES; l++) 
    if (MatrixArray[l] != NULL) SMatrixDestroy (&MatrixArray[l]);

  printf ("\e[31;1f");

  return 0;
}

void Menu (void)
{
  system ("clear");

  printf("\e[2;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[3;1f|                             Programa Grafico Para Simular Operacoes Sobre Matrizes Quadradas                             |\n");
  printf("\e[4;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[5;1f|  1 - Ler uma matriz (teclado)  | Matriz  0 =                |                                                            |\n");
  printf("\e[6;1f|  2 - Ler uma matriz (ficheiro) | Matriz  1 =                |                                                            |\n");
  printf("\e[7;1f|  3 - Transpor uma matriz       | Matriz  2 =                |                                                            |\n");
  printf("\e[8;1f|  4 - Somar matrizes            | Matriz  3 =                |                                                            |\n");
  printf("\e[9;1f|  5 - Subtrair matrizes         | Matriz  4 =                |                                                            |\n");
  printf("\e[10;1f|  6 - Multiplicar matrizes      | Matriz  5 =                |                                                            |\n");
  printf("\e[11;1f|  7 - Calcular determinante     | Matriz  6 =                |                                                            |\n");
  printf("\e[12;1f|  8 - Comparar matrizes         | Matriz  7 =                |                                                            |\n");
  printf("\e[13;1f|  9 - Copiar uma matriz         | Matriz  8 =                |                                                            |\n");
  printf("\e[14;1f| 10 - Armazenar uma matriz      | Matriz  9 =                |                                                            |\n");
  printf("\e[15;1f| 11 - Alterar uma matriz        | Matriz 10 =                |                                                            |\n");
  printf("\e[16;1f| 12 - Mostrar uma matriz        | Matriz 11 =                |                                                            |\n");
  printf("\e[17;1f| 13 - Apagar uma matriz         | Matriz 12 =                |                                                            |\n");
  printf("\e[18;1f| 14 - Criar matriz identidade   | Matriz 13 =                |                                                            |\n");
  printf("\e[19;1f| 15 - Multiplicar por escalar   | Matriz 14 =                |                                                            |\n");
  printf("\e[20;1f| 16 - Verificar simetrica       | Matriz 15 =                |                                                            |\n");
  printf("\e[21;1f| 17 - Permutar linhas           | Matriz 16 =                |                                                            |\n");
  printf("\e[22;1f| 18 - Permutar colunas          | Matriz 17 =                |                                                            |\n");
  printf("\e[23;1f|  0 - Terminar o programa       | Matriz 18 =                |                                                            |\n");
  printf("\e[24;1f|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| Matriz 19 =                |                                                            |\n");
  printf("\e[25;1f| Opcao ->                       | Matriz 20 =                |                                                            |\n");
  printf("\e[26;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[27;1f|                                               Janela de Aquisicao de Dados                                               |\n");
  printf("\e[28;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[29;1f|                                                                                                                          |\n");
  printf("\e[30;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[31;1f|                                        Janela de Mensagens de Erro e de Resultados                                       |\n");
  printf("\e[32;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[33;1f|                                                                                                                          |\n");
  printf("\e[34;1f|                                                                                                                          |\n");
  printf("\e[35;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void ReadOption (int *poption)
{
  do
  {  
    printf("\e[25;1f| Opcao ->                       |");
    printf("\e[25;12f"); scanf ("%d", poption);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*poption < 0 || *poption > MAX_OPTIONS);
}

void ReadMatrixIndex (int *pnm, char *pmsg)
{
  int MsgLen = strlen (pmsg);

  do
  {
    *pnm = -1;
    printf("\e[29;1f| Indice da %s ->                               ", pmsg);
    printf("\e[29;%df", 17+MsgLen); scanf ("%d", pnm);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pnm < 0 || *pnm >= MAX_MATRIXES);
}

int ActiveMatrix (PtSMatrix pmatarray[], int pnmat)
{
  char Character;

  if (pmatarray[pnmat] != NULL)
  {
    do
    {
      printf("\e[1m\e[33;1f| A matriz %d ja existe!                     ", pnmat);
      printf("\e[0m\e[34;1f| Deseja apaga-la (s/n)? ");
      scanf ("%c", &Character); Character = tolower (Character);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (Character != 'n' && Character != 's');

    if (Character == 's') { SMatrixDestroy (&pmatarray[pnmat]); return 0; }
    else  return 1;
  }
  else return 0;
}

int NotActiveMatrix (PtSMatrix pmatarray[], int pnmat)
{
  if (pmatarray[pnmat] == NULL)
  {
    printf("\e[1m\e[33;1f| A matriz %d nao existe!                     ", pnmat);
    printf("\e[0m\e[34;1f| Prima uma tecla para continuar ");
    scanf ("%*[^\n]"); scanf ("%*c");
    return 1;
  }
  else return 0;
}

void ReadMatrixSize (unsigned int *psize)
{
  do
  {
    *psize = 0;
    printf("\e[29;1f| Nº de linhas e de colunas da matriz ->                    ");
    printf("\e[29;42f"); scanf ("%d", psize);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*psize < 1 || *psize > 10);
}

void ReadFilename (char *pfname)
{
  int Status;

  do
  {
    printf("\e[29;1f| Nome do ficheiro ->                               ");
    printf("\e[29;23f"); Status = scanf ("%20[^\n]", pfname);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Status == 0);
}

void WriteErrorMessage (char *pmsg)
{
  printf("\e[33;1f| %s de matrizes nao foi efectuada devido a -> \e[1m%s", pmsg, SMatrixErrorMessage ());
  printf("\e[0m\e[34;1f| Prima uma tecla para continuar ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

PtSMatrix ReadMatrix (unsigned int psize)
{
  PtSMatrix Mat; unsigned int L, C; double Element; int Status;
    
  /* cria a matriz nula */
  if ((Mat = SMatrixCreate (psize)) == NULL) return NULL;

  /* leitura das componentes da matriz do teclado */
  for (L = 0; L < psize; L++)
  {
    for (C = 0; C < psize; C++)
    {
      do
      {
        printf("\e[29;1f| Matriz[%d,%d]?                                          ", L+1, C+1);
        printf("\e[29;16f"); Status = scanf ("%lf", &Element);
        scanf ("%*[^\n]"); scanf ("%*c");
      } while (Status == 0);
      SMatrixModifyElement (Mat, L, C, Element);
    }
  }

  return Mat;  /* devolve a matriz criada */
}

void WriteMatrix (PtSMatrix pmatarray[], int pnm)
{
  unsigned int L, C, Size;

  Size = SMatrixSize (pmatarray[pnm]);

  printf("\e[1m");
  for (L = 0; L < Size; L++)
  {
    printf("\e[%d;65f ", 6+L);
    for (C = 0; C < Size; C++)
     printf ("%7.2f ", SMatrixObserveElement (pmatarray[pnm], L, C));
  }
  printf("\e[0m");
}

void ChangeMatrix (PtSMatrix pmat)
{
  unsigned int L, C, Size; char Character; double Element; int Status;

  Size = SMatrixSize (pmat);

  do
  {
    do
    {
      L = -1;
      printf("\e[29;1f| Nº da linha do elemento da matriz ->                    ");
      printf("\e[29;40f"); scanf ("%d", &L);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (L < 1 || L > Size);
        
    do
    {
      C = -1;
      printf("\e[29;1f| Nº da coluna do elemento da matriz ->                   ");
      printf("\e[29;41f"); scanf ("%d", &C);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (C < 1 || C > Size);
        
    do
    {
      printf("\e[29;1f| Matriz[%d,%d]?                                          ", L, C);
      printf("\e[29;16f"); Status = scanf ("%lf", &Element);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (Status == 0);

    SMatrixModifyElement (pmat, L-1, C-1, Element);

    do
    {
      printf("\e[29;1f| Deseja alterar mais algum elemento da matriz (s/n)?     ");
      printf("\e[29;55f"); scanf ("%c", &Character); Character = tolower (Character);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (Character != 'n' && Character != 's');
  } while (Character == 's');
}

void WriteMessageResult (char *pmsg, double pval)
{
  printf("\e[1m\e[33;1f| %s \e[1m%f", pmsg, pval);
  printf("\e[0m\e[34;1f| Prima uma tecla para continuar ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

double ReadValue (void)
{
  int Status; double Value;
  
  do
  {
	printf("\e[29;1f| Escalar a multiplicar ->                            ");
	printf("\e[29;28f"); Status = scanf ("%lf", &Value);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Status == 0);

  return Value;
}

unsigned int ReadRow (char *pmsg, unsigned int psize)
{
  unsigned int Row = 0;

  do
  {
    printf("\e[29;1f| Nº da linha (%s) da matriz ->                    ", pmsg);
    printf("\e[29;38f"); scanf ("%d", &Row);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Row < 1 || Row > psize);
  
  return Row;
}

unsigned int ReadColumn (char *pmsg, unsigned int psize)
{
  unsigned int Col = 0;

  do
  {
    printf("\e[29;1f| Nº da coluna (%s) da matriz ->                   ", pmsg);
    printf("\e[29;39f"); scanf ("%d", &Col);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Col < 1 || Col > psize);
  
  return Col;
}
