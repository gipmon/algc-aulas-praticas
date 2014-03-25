/*******************************************************************************

 Programa gráfico de simulação da funcionalidade do TDA Polinómio


 Autor : António Manuel Adrego da Rocha    Data : Março de 2014

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "polynomial.h"  /* Ficheiro de interface do tipo de dados */

#define MAX_POLYS 14
#define MAX_OPTIONS 11

void Menu (void);
void ReadOption (int *);
void ReadPolyIndex (int *, char *);
int ActivePoly (PtPoly *, int);
int NotActivePoly (PtPoly *, int);
void ReadFileName (char *);
void WriteErrorMessage (char *);
PtPoly ReadPoly (void); 
void WritePoly (PtPoly);
void ChangePoly (PtPoly);
double ReadX (void);
void WriteMessageResult (char *, double);

int main (void)
{
  PtPoly PolyArray[MAX_POLYS];
  int Option, Indice, Poly1, Poly2, Poly3, Equals;
  char FileName[21]; double X, Value;

  for (Indice = 0; Indice < MAX_POLYS; Indice++) PolyArray[Indice] = NULL;
  
  do
  {
    /* limpar o ecran e apresentar menu */
    Menu ();

    /* limpar o erro entretanto ocorrido */
    PolyClearError ();

    /* apresentar os polinómios activos */
    for (Indice = 0; Indice < MAX_POLYS; Indice++)
      if (PolyArray[Indice] != NULL)
      {
        printf ("\e[1m\e[%d;48f", 5+Indice); WritePoly (PolyArray[Indice]);
        printf ("\e[0m");
      }

    /* ler opcao do utilizador */
    ReadOption (&Option);

    switch (Option)
    {
        case 1 :  ReadPolyIndex (&Poly1, "polinomio");
                  if (ActivePoly (PolyArray, Poly1)) break;
                  PolyArray[Poly1] = ReadPoly ();
                  if (PolyError ()) WriteErrorMessage ("A criacao");
                  break;

        case 2 :  ReadPolyIndex (&Poly1, "polinomio");
                  if (ActivePoly (PolyArray, Poly1)) break;
                  ReadFileName (FileName);
                  PolyArray[Poly1] = PolyCreateFile (FileName);
                  if (PolyError ()) WriteErrorMessage ("A leitura");
                  break;

        case 3 :  ReadPolyIndex (&Poly1, "primeiro polinomio");
                  ReadPolyIndex (&Poly2, "segundo polinomio");
                  do
                  {
                      ReadPolyIndex (&Poly3, "polinomio soma");
                  } while (Poly3 == Poly1 || Poly3 == Poly2);
                  if (ActivePoly (PolyArray, Poly3)) break;
                  PolyArray[Poly3] = PolyAddition (PolyArray[Poly1], PolyArray[Poly2]);
                  if (PolyError ()) WriteErrorMessage ("A adicao");
                  break;

        case 4 :  ReadPolyIndex (&Poly1, "primeiro polinomio");
                  ReadPolyIndex (&Poly2, "segundo polinomio");
                  do
                  {
                      ReadPolyIndex (&Poly3, "polinomio diferenca");
                  } while (Poly3 == Poly1 || Poly3 == Poly2);
                  if (ActivePoly (PolyArray, Poly3)) break;
                  PolyArray[Poly3] = PolySubtraction (PolyArray[Poly1], PolyArray[Poly2]);
                  if (PolyError ()) WriteErrorMessage ("A diferenca");
                  break;

        case 5 :  ReadPolyIndex (&Poly1, "primeiro polinomio");
                  ReadPolyIndex (&Poly2, "segundo polinomio");
                  do
                  {
                      ReadPolyIndex (&Poly3, "polinomio produto");
                  } while (Poly3 == Poly1 || Poly3 == Poly2);
                  PolyArray[Poly3] = PolyMultiplication (PolyArray[Poly1], PolyArray[Poly2]);
                  if (PolyError ()) WriteErrorMessage ("A multiplicacao");
                  break;

        case 6 :  ReadPolyIndex (&Poly1, "primeiro polinomio");
                  ReadPolyIndex (&Poly2, "segundo polinomio");
                  Equals = PolyEquals (PolyArray[Poly1], PolyArray[Poly2]);
                  if (PolyError ()) WriteErrorMessage ("A comparacao");
                  else
                  {
                    if (Equals) printf("\e[26;1f| \e[1mOs polinomios %d e %d sao iguais", Poly1, Poly2);
                    else printf("\e[26;1f| \e[1mOs polinomios %d e %d nao sao iguais", Poly1, Poly2);
                    printf("\e[0m\e[27;1f| Prima uma tecla para continuar ");
                    scanf ("%*[^\n]"); scanf ("%*c");
                  }
                  break;

        case 7 :  ReadPolyIndex (&Poly1, "polinomio origem");
                  if (NotActivePoly (PolyArray, Poly1)) break;
                  do
                  {
                      ReadPolyIndex (&Poly2, "polinomio destino");
                  } while (Poly2 == Poly1);
                  if (ActivePoly (PolyArray, Poly2)) break;
                  PolyArray[Poly2] = PolyCopy (PolyArray[Poly1]);
                  if (PolyError ()) WriteErrorMessage ("A copia");
                  break;

        case 8 :  ReadPolyIndex (&Poly1, "polinomio");
                  if (NotActivePoly (PolyArray, Poly1)) break;
                  ReadFileName (FileName);
                  PolyStoreFile (PolyArray[Poly1], FileName);
                  if (PolyError ()) WriteErrorMessage ("O armazenamento");
                  break;
        
        case 9 :  ReadPolyIndex (&Poly1, "polinomio");
                  if (NotActivePoly (PolyArray, Poly1)) break;
                  ChangePoly (PolyArray[Poly1]); 
                  break;

        case 10 : ReadPolyIndex (&Poly1, "polinomio");
                  if (NotActivePoly (PolyArray, Poly1)) break;
                  X = ReadX ();
                  Value = PolyEvaluation (PolyArray[Poly1], X);
                  if (PolyError ()) WriteErrorMessage ("A avaliacao");
                  else WriteMessageResult ("A avaliacao do polinomio", Value);
                  break;

        case 11 : ReadPolyIndex (&Poly1, "polinomio");
                  if (NotActivePoly (PolyArray, Poly1)) break;
                  PolyDestroy (&PolyArray[Poly1]);
                  if (PolyError ()) WriteErrorMessage ("A eliminacao");
                  break;
    }

  } while (Option != 0);

  for (Indice = 0; Indice < MAX_POLYS; Indice++) 
    if (PolyArray[Indice] != NULL) PolyDestroy (&PolyArray[Indice]);

  printf ("\e[28;1f");

  return EXIT_SUCCESS;
}

void Menu (void)
{
  system ("clear");

  printf("\e[2;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[3;1f|                                 Programa Grafico Para Simular Operacoes Sobre Polinomios                                 |\n");
  printf("\e[4;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[5;1f|  1 - Ler um polinomio (teclado)  | Poly  0 =                                                                             |\n");
  printf("\e[6;1f|  2 - Ler um polinomio (ficheiro) | Poly  1 =                                                                             |\n");
  printf("\e[7;1f|  3 - Somar polinomios            | Poly  2 =                                                                             |\n");
  printf("\e[8;1f|  4 - Subtrair polinomios         | Poly  3 =                                                                             |\n");
  printf("\e[9;1f|  5 - Multiplicar polinomios      | Poly  4 =                                                                             |\n");
  printf("\e[10;1f|  6 - Comparar polinomios         | Poly  5 =                                                                             |\n");
  printf("\e[11;1f|  7 - Copiar um polinomio         | Poly  6 =                                                                             |\n");
  printf("\e[12;1f|  8 - Armazenar um polinomio      | Poly  7 =                                                                             |\n");
  printf("\e[13;1f|  9 - Alterar um polinomio        | Poly  8 =                                                                             |\n");
  printf("\e[14;1f| 10 - Avaliar um polinomio        | Poly  9 =                                                                             |\n");
  printf("\e[15;1f| 11 - Apagar um polinomio         | Poly 10 =                                                                             |\n");
  printf("\e[16;1f|  0 - Terminar o programa         | Poly 11 =                                                                             |\n");
  printf("\e[17;1f|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| Poly 12 =                                                                             |\n");
  printf("\e[18;1f| Opcao ->                         | Poly 13 =                                                                             |\n");
  printf("\e[19;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[20;1f|                                               Janela de Aquisicao de Dados                                               |\n");
  printf("\e[21;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[22;1f|                                                                                                                          |\n");
  printf("\e[23;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[24;1f|                                        Janela de Mensagens de Erro e de Resultados                                       |\n");
  printf("\e[25;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[26;1f|                                                                                                                          |\n");
  printf("\e[27;1f|                                                                                                                          |\n");
  printf("\e[28;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void ReadOption (int *popc)
{
  do
  {  
    printf("\e[18;1f| Opcao ->                         |");
    printf("\e[18;12f"); scanf ("%d", popc);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*popc < 0 || *popc > MAX_OPTIONS);
}

void ReadPolyIndex (int *pnp, char *pmsg)
{
  unsigned int MsgLen = strlen (pmsg);

  do
  {
    *pnp = -1;
    printf("\e[22;1f| Indice do %s ->                               ", pmsg);
    printf("\e[22;%df", 17+MsgLen); scanf ("%d", pnp);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pnp < 0 || *pnp >= MAX_POLYS);
}

int ActivePoly (PtPoly ppolyarray[], int pnpoly)
{
  char Character;

  if (ppolyarray[pnpoly] != NULL)
  {
    do
    {
      printf("\e[1m\e[26;1f| O polinomio %d ja existe!                     ", pnpoly);
      printf("\e[0m\e[27;1f| Deseja apaga-lo (s/n)? ");
      scanf ("%c", &Character); Character = tolower (Character);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (Character != 'n' && Character != 's');

    if (Character == 's') { PolyDestroy (&ppolyarray[pnpoly]); return 0; }
    else  return 1;
  }
  else return 0;
}

int NotActivePoly (PtPoly ppolyarray[], int pnpoly)
{
  if (ppolyarray[pnpoly] == NULL)
  {
    printf("\e[1m\e[26;1f| O polinomio %d nao existe!                     ", pnpoly);
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
  printf("\e[26;1f| %s de polinomios nao foi efectuada devido a -> \e[1m%s", pmsg, PolyErrorMessage ());
  printf("\e[0m\e[27;1f| Prima uma tecla para continuar ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

PtPoly ReadPoly (void)
{
  PtPoly Poly; unsigned int I, Degree; double Coef;

  do
  {
    printf("\e[22;1f| Grau do polinomio ->                               ");
    printf("\e[22;24f"); scanf ("%d", &Degree);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Degree < 0 || Degree > 5);
    
  /* cria o polinomio nulo */
  if ((Poly = PolyCreate (Degree)) == NULL) return NULL;

  /* leitura das coeficientes do polinomio do teclado */
  for (I = 0; I <= Degree; I++)
  {
    printf("\e[22;1f| Coeficiente x^%1d ->                               ", I);
    printf("\e[22;22f"); scanf ("%lf", &Coef);
    scanf ("%*[^\n]"); scanf ("%*c");
    PolyModifyCoefficient (Poly, I, Coef);
  }

  return Poly;  /* devolve o polinomio criado */
}

void WritePoly (PtPoly ppol)
{
  int I, Degree = PolyDegree (ppol); double Coef;

  if (ppol != NULL)
  {
    /* escrita do coeficiente x^n */
    Coef = PolyObserveCoefficient (ppol, Degree);
    if (Degree > 1) printf ("%5.2f x^%d", Coef, Degree);
    else if (Degree == 1) printf ("%5.2f x", Coef);

    /* escrita dos coeficientes x^n-1 ... x^2 para polinómios com grau > 1 */
    if (Degree > 1)
      for (I = Degree-1; I > 1; I--)
      {
        Coef = PolyObserveCoefficient (ppol, I);
        if (Coef >= 0.0) printf (" + %5.2f x^%d", Coef, I);
        else printf (" - %5.2f x^%d", fabs(Coef), I);
      }

    /* escrita do coeficiente x para polinómios com grau > 1 */
    if (Degree > 1)
    {
      Coef = PolyObserveCoefficient (ppol, 1);
      if (Coef >= 0.0) printf (" + %5.2f x", Coef);
      else printf (" - %5.2f x", fabs(Coef));
    }

    /* escrita do coeficiente independente */
    if (Degree > 0)
    {
      Coef = PolyObserveCoefficient (ppol, 0);
      if (Coef >= 0.0) printf (" + %5.2f\n", Coef);
      else printf (" - %5.2f\n", fabs(Coef));  
    }
    else printf ("%5.2f", Coef);
  }
}

void ChangePoly (PtPoly ppol)
{
  unsigned int Degree = PolyDegree (ppol), Ind; double Coef; char Character;

  do
  {
    do
    {
      printf("\e[22;1f| Indice do coeficiente do polinomio ->                               ");
      printf("\e[22;41f"); scanf ("%d", &Ind);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (Ind < 0 || Ind > Degree);

    printf("\e[22;1f| Coeficiente x^%1d ->                               ", Ind);
    printf("\e[22;22f"); scanf ("%lf", &Coef);
    scanf ("%*[^\n]"); scanf ("%*c");
    PolyModifyCoefficient (ppol, Ind, Coef);

    do
    {
      printf("\e[22;1f| Deseja alterar mais algum coeficiente do polinomio (s/n)?           ");
      printf("\e[22;61f"); scanf ("%c", &Character); Character = tolower (Character);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (Character != 'n' && Character != 's');
  } while (Character == 's');
}

double ReadX (void)
{
  int Status; double X;
  
  do
  {
    printf("\e[22;1f| Valor do argumento do polinomio (X) ->                              ");
    printf("\e[22;42f"); Status = scanf ("%lf", &X);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Status == 0);

  return X;
}

void WriteMessageResult (char *pmsg, double pval)
{
  printf("\e[1m\e[26;1f| %s = \e[1m%f", pmsg, pval);
  printf("\e[0m\e[27;1f| Prima uma tecla para continuar ");
  scanf ("%*[^\n]"); scanf ("%*c");
}
