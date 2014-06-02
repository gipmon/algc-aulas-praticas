/*******************************************************************************

 Programa gráfico de simulação da funcionalidade do TDA Digraph


 Autor : António Manuel Adrego da Rocha    Data : Março de 2013

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "digraph.h"  /* Ficheiro de interface do TAD */

#define MAX_DIGRAPHS 22
#define MAX_OPTIONS 19

void Menu (void);
void ReadOption (int *);
void ReadDigraphIndex (int *, char *);
int ActiveDigraph (PtDigraph *, int);
int NotActiveDigraph (PtDigraph *, int);
void ReadFilename (char *);
void WriteErrorMessage (unsigned int, char *);
void ReadVertex (unsigned int *);
void ReadEdge (unsigned int *, unsigned int *);
void ReadCost (int *);
void ReadType (unsigned int *);
void WriteDigraph (PtDigraph);
void WritePath (unsigned int[], unsigned int);
void WriteAllPaths (unsigned int[], int[], unsigned int, unsigned int pnv);

int main (void)
{
  PtDigraph DigraphArray[MAX_DIGRAPHS];
  int Option, Index, Digraph1, Digraph2, Error, Cost;
  unsigned int NVertexes, NEdges, DigType, Vertex1, Vertex2, Strong, Equal, Regular, NAlc, Cont;
  char Filename[21]; unsigned int *VertAlc; int *VertCost;

  for (Index = 0; Index < MAX_DIGRAPHS; Index++) DigraphArray[Index] = NULL;
  
  do
  {
    /* apresentar menu */
    Menu ();

    /* apresentar os digrafos activos */
    for (Index = 0; Index < MAX_DIGRAPHS; Index++)
      if (DigraphArray[Index] != NULL)
      {
        Type (DigraphArray[Index], &DigType);
        VertexNumber (DigraphArray[Index], &NVertexes);
        EdgeNumber (DigraphArray[Index], &NEdges);
        if (DigType) printf ("\e[1m\e[%d;36fDigrafo", 5+Index); else printf ("\e[1m\e[%d;36f  Grafo", 5+Index);
        printf ("\e[1m\e[%d;49fV = %d / A = %d", 5+Index, NVertexes, NEdges);
        printf ("\e[0m");
      }

    /* ler opção do utilizador */
    ReadOption (&Option);

    switch (Option)
    {
        case 1 :  ReadDigraphIndex (&Digraph1, "digrafo/grafo");
                  if (ActiveDigraph (DigraphArray, Digraph1)) break;
                  ReadType (&DigType);
                  DigraphArray[Digraph1] = Create (DigType);
                  if (DigraphArray[Digraph1] == NULL) WriteErrorMessage (NO_MEM, "A criacao");
                  break;

        case 2 :  ReadDigraphIndex (&Digraph1, "digrafo/grafo");
                  if (ActiveDigraph (DigraphArray, Digraph1)) break;
                  ReadFilename (Filename);
                  DigraphArray[Digraph1] = CreateFile (Filename);
                  if (DigraphArray[Digraph1] == NULL) WriteErrorMessage (NO_MEM, "A leitura");
                  break;

        case 3 :  ReadDigraphIndex (&Digraph1, "digrafo/grafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
		          ReadVertex (&Vertex1);
                  Error = InVertex (DigraphArray[Digraph1], Vertex1);
                  if (Error) WriteErrorMessage (Error, "A insercao do vertice");
                  break;

        case 4 :  ReadDigraphIndex (&Digraph1, "digrafo/grafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
		          ReadVertex (&Vertex1);
                  Error = OutVertex (DigraphArray[Digraph1], Vertex1);
                  if (Error) WriteErrorMessage (Error, "A remocao do vertice");
                  break;

        case 5 :  ReadDigraphIndex (&Digraph1, "digrafo/grafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
		          ReadEdge (&Vertex1, &Vertex2);
		          ReadCost (&Cost);
                  Error = InEdge (DigraphArray[Digraph1], Vertex1, Vertex2, Cost);
                  if (Error) WriteErrorMessage (Error, "A insercao da aresta");
                  break;

        case 6 :  ReadDigraphIndex (&Digraph1, "digrafo/grafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
		          ReadEdge (&Vertex1, &Vertex2);
                  Error = OutEdge (DigraphArray[Digraph1], Vertex1, Vertex2);
                  if (Error) WriteErrorMessage (Error, "A remocao da aresta");
                  break;

        case 7 :  ReadDigraphIndex (&Digraph1, "digrafo/grafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  ReadFilename (Filename);
                  Error = StoreFile (DigraphArray[Digraph1], Filename);
                  if (Error) WriteErrorMessage (Error, "O armazenamento");
                  break;

        case 8 :  ReadDigraphIndex (&Digraph1, "digrafo/grafo origem");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  do
                  {
                     ReadDigraphIndex (&Digraph2, "digrafo/grafo destino"); 
                  } while (Digraph2 == Digraph1);
                  if (ActiveDigraph (DigraphArray, Digraph2)) break;
                  DigraphArray[Digraph2] = Copy (DigraphArray[Digraph1]);
                  if (DigraphArray[Digraph2] == NULL) WriteErrorMessage (NO_MEM, "A copia");
                  break;
		  
        case 9 :  ReadDigraphIndex (&Digraph1, "digrafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  WriteDigraph (DigraphArray[Digraph1]);
                  printf("\e[1m\e[34;1f| Digrafo %d                     ", Digraph1);
                  printf("\e[0m\e[35;1f| Prima uma tecla para continuar ");
                  scanf ("%*[^\n]"); scanf ("%*c");
                  break;

        case 10 : ReadDigraphIndex (&Digraph1, "digrafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  Error = Destroy (&DigraphArray[Digraph1]);
                  if (Error) WriteErrorMessage (Error, "A eliminacao");
                  break;

        case 11 : ReadDigraphIndex (&Digraph1, "digrafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
		          ReadVertex (&Vertex1);
                  Error = VertexType (DigraphArray[Digraph1], Vertex1);
                  switch (Error)
		          {
                     case OK     : printf("\e[1m\e[34;3fvertice normal ");  break;
                     case SINK   : printf("\e[1m\e[34;3fvertice sumidouro");  break;
		             case SOURCE : printf("\e[1m\e[34;3fvertice fonte");  break;
		             case DISC   : printf("\e[1m\e[34;3fvertice desconexo");  break;
		             default     : WriteErrorMessage (Error, "O teste do vertice");
                  }
	              printf("\e[0m\e[35;1f| Prima uma tecla para continuar ");
                  scanf ("%*[^\n]"); scanf ("%*c");
                  break;

        case 12 : ReadDigraphIndex (&Digraph1, "digrafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  ReadVertex (&Vertex1); 
		          Error = VertexNumber(DigraphArray[Digraph1], &NVertexes);
                  if (Error) WriteErrorMessage (Error, "A determinacao dos vertices alcancaveis");
		          if ((VertAlc = (unsigned int*) calloc (sizeof (unsigned int), NVertexes)) == NULL)
		          {
		             WriteErrorMessage (NO_MEM, "A determinacao dos vertices alcancaveis");
		             break;
                  }
                  Error = Reach (DigraphArray[Digraph1], Vertex1, VertAlc);
                  if (Error) { WriteErrorMessage (Error, "A determinacao dos vertices alcancaveis"); free(VertAlc); break; }
		          printf("\e[1m\e[34;1f| Vertices alcancaveis: ");
                  NAlc = VertAlc[0];
		          if (NAlc == 0) printf("nenhum");
		          else for (Cont = 1; Cont <= NAlc; Cont++) printf("%u ", VertAlc[Cont]);
                  printf("\e[0m\e[35;1f| Prima uma tecla para continuar ");
                  scanf ("%*[^\n]"); scanf ("%*c");
		          free (VertAlc);
                  break;
			
        case 13 : ReadDigraphIndex (&Digraph1, "digrafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
		          ReadVertex (&Vertex1); 
		          Error = VertexNumber (DigraphArray[Digraph1], &NVertexes);
                  if (Error) WriteErrorMessage (Error, "A determinacao dos caminhos mais curtos");
		          if ((VertAlc = (unsigned int*) calloc (sizeof (unsigned int), NVertexes)) == NULL)
		          {
		             WriteErrorMessage (NO_MEM, "A determinacao dos caminhos mais curtos");
		             break;
                  }
		          if ((VertCost = (int*) calloc (sizeof (int), NVertexes)) == NULL)
		          {
		             WriteErrorMessage (NO_MEM, "A determinacao dos caminhos mais curtos");
		             free (VertAlc);
		             break;
                  }
		          Error = Dijkstra (DigraphArray[Digraph1], Vertex1, VertAlc, VertCost);
                  if (Error) { WriteErrorMessage (Error, "A determinacao dos caminhos mais curtos");
                  free(VertAlc); free (VertCost); break; }
		          WriteAllPaths (VertAlc, VertCost, Vertex1, NVertexes);
                  printf("\e[0m\e[35;1f| Prima uma tecla para continuar ");
                  scanf ("%*[^\n]"); scanf ("%*c");
		          free (VertAlc);
		          free (VertCost);
                  break;

        case 14 : ReadDigraphIndex (&Digraph1, "digrafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  Error = DigraphStronglyConnected (DigraphArray[Digraph1], &Strong);
                  if (Error) WriteErrorMessage (Error, "A determinacao de fortemente conexo");
		          {			 
		             if (Strong) printf("\e[1m\e[34;3fDigrafo fortemente conexo");
		             else printf("\e[1m\e[34;3fDigrafo nao fortemente conexo");
                     printf("\e[0m\e[35;1f| Prima uma tecla para continuar ");
                     scanf ("%*[^\n]"); scanf ("%*c");
                  }
                  break;

        case 15:  ReadDigraphIndex (&Digraph1, "digrafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  Error = DigraphTransitiveClosure (DigraphArray[Digraph1]);
                  if (Error) WriteErrorMessage (Error, "O fecho transitivo");
                  break;

        case 16:  ReadDigraphIndex (&Digraph1, "digrafo origem");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  do
                  {
                     ReadDigraphIndex (&Digraph2, "digrafo destino"); 
                  } while (Digraph2 == Digraph1);
                  if (ActiveDigraph (DigraphArray, Digraph2)) break;
                  DigraphArray[Digraph2] = DigraphTranspose (DigraphArray[Digraph1]);
                  if (Error) WriteErrorMessage (Error, "O digrafo transposto");
                  break;
			  
        /*case 17 : ReadDigraphIndex (&Digraph1, "digrafo origem");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  do
                  {
                     ReadDigraphIndex (&Digraph2, "digrafo destino"); 
                  } while (Digraph2 == Digraph1);
                  if (ActiveDigraph (DigraphArray, Digraph2)) break;
                  DigraphArray[Digraph2] = DigraphComplement (DigraphArray[Digraph1]);
                  if (Error) WriteErrorMessage (Error, "O digrafo complementar");
                  break;
	
        case 18 : ReadDigraphIndex (&Digraph1, "digrafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  Error = DigraphRegular (DigraphArray[Digraph1], &Regular);
                  if (Error) WriteErrorMessage (Error, "A determinacao de digrafo regular");	
		          else
		          {			 
		             if (Regular) printf("\e[1m\e[34;3fDigrafo regular");
		             else printf("\e[1m\e[34;3fDigrafo nao regular");
                     printf("\e[0m\e[35;1f| Prima uma tecla para continuar ");
                     scanf ("%*[^\n]"); scanf ("%*c");
                  }
                  break;
			
        case 19 : ReadDigraphIndex (&Digraph1, "primeiro digrafo/grafo");
                  if (NotActiveDigraph (DigraphArray, Digraph1)) break;
                  do
                  {
                     ReadDigraphIndex (&Digraph2, "segundo digrafo/grafo"); 
                  } while (Digraph2 == Digraph1);
                  Error = Equals (DigraphArray[Digraph1], DigraphArray[Digraph2], &Equal);
                  if (Error) WriteErrorMessage (Error, "A determinacao de igualdade");	
		          else
		          {			 
		             if (Equal) printf("\e[1m\e[34;3fDigrafos/Grafos iguais");
		             else printf("\e[1m\e[34;3fDigrafos/Grafos nao iguais");
                     printf("\e[0m\e[35;1f| Prima uma tecla para continuar ");
                     scanf ("%*[^\n]"); scanf ("%*c");
                  }
                  break;*/
    }
  } while (Option != 0);

  for (Index = 0; Index < MAX_DIGRAPHS; Index++) 
    if (DigraphArray[Index] != NULL) Destroy (&DigraphArray[Index]);

  printf ("\e[37;1f");
  return 0;
}

void Menu (void)
{
  system ("clear");

  printf("\e[2;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[3;1f|                               Programa Grafico Para Simular Operacoes Sobre Digrafos/Grafos                              |\n");
  printf("\e[4;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[5;1f|  1 - Criar um digrafo nulo     | Digrafo  0 =                 |                                                          |\n");
  printf("\e[6;1f|  2 - Ler um digrafo (ficheiro) | Digrafo  1 =                 |                                                          |\n");
  printf("\e[7;1f|  3 - Inserir um vertice        | Digrafo  2 =                 |                                                          |\n");
  printf("\e[8;1f|  4 - Retirar um vertice        | Digrafo  3 =                 |                                                          |\n");
  printf("\e[9;1f|  5 - Inserir uma aresta        | Digrafo  4 =                 |                                                          |\n");
  printf("\e[10;1f|  6 - Retirar uma aresta        | Digrafo  5 =                 |                                                          |\n");
  printf("\e[11;1f|  7 - Armazenar um digrafo      | Digrafo  6 =                 |                                                          |\n");
  printf("\e[12;1f|  8 - Copiar um digrafo         | Digrafo  7 =                 |                                                          |\n");
  printf("\e[13;1f|  9 - Mostrar um digrafo        | Digrafo  8 =                 |                                                          |\n");
  printf("\e[14;1f| 10 - Apagar um digrafo         | Digrafo  9 =                 |                                                          |\n");
  printf("\e[15;1f| 11 - Tipo de vertice           | Digrafo 10 =                 |                                                          |\n");
  printf("\e[16;1f| 12 - Vertices alcancaveis      | Digrafo 11 =                 |                                                          |\n");
  printf("\e[17;1f| 13 - Caminhos mais curtos      | Digrafo 12 =                 |                                                          |\n");
  printf("\e[18;1f| 14 - Digrafo fortemente conexo | Digrafo 13 =                 |                                                          |\n");
  printf("\e[19;1f| 15 - Fecho transitivo          | Digrafo 14 =                 |                                                          |\n");
  printf("\e[20;1f| 16 - Digrafo transposto        | Digrafo 15 =                 |                                                          |\n");
  printf("\e[21;1f| 17 - Digrafo complementar      | Digrafo 16 =                 |                                                          |\n");
  printf("\e[22;1f| 18 - Digrafo regular           | Digrafo 17 =                 |                                                          |\n");
  printf("\e[23;1f| 19 - Comparar digrafos         | Digrafo 18 =                 |                                                          |\n");
  printf("\e[24;1f|  0 - Terminar o programa       | Digrafo 19 =                 |                                                          |\n");
  printf("\e[25;1f|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| Digrafo 20 =                 |                                                          |\n");
  printf("\e[26;1f| Opcao ->                       | Digrafo 21 =                 |                                                          |\n");
  printf("\e[27;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[28;1f|                                               Janela de Aquisicao de Dados                                               |\n");
  printf("\e[29;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[30;1f|                                                                                                                          |\n");
  printf("\e[31;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[32;1f|                                        Janela de Mensagens de Error e de Resultados                                      |\n");
  printf("\e[33;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\e[34;1f|                                                                                                                          |\n");
  printf("\e[35;1f|                                                                                                                          |\n");
  printf("\e[36;1f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

void ReadDigraphIndex (int *pndg, char *pmsg)
{
  int MsgLen = strlen (pmsg);

  do
  {
    *pndg = -1;
    printf("\e[30;1f| Indice do %s ->                               ", pmsg);
    printf("\e[30;%df", 17+MsgLen); scanf ("%d", pndg);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pndg < 0 || *pndg >= MAX_DIGRAPHS);
}

int ActiveDigraph (PtDigraph pgrupodig[], int pndg)
{
  char Car;

  if (pgrupodig[pndg] != NULL)
  {
    do
    {
      printf("\e[1m\e[34;1f| O digrafo %d ja existe!                     ", pndg);
      printf("\e[0m\e[35;1f| Deseja apaga-lo (s/n)? ");
      scanf ("%c", &Car); Car = tolower (Car);
      scanf ("%*[^\n]"); scanf ("%*c");
    } while (Car != 'n' && Car != 's');

    if (Car == 's') { Destroy (&pgrupodig[pndg]); return 0; }
    else  return 1;
  }
  else return 0;
}

int NotActiveDigraph (PtDigraph pgrupodig[], int pndg)
{
  if (pgrupodig[pndg] == NULL)
  {
    printf("\e[1m\e[34;1f| O digrafo %d nao existe!                     ", pndg);
    printf("\e[0m\e[35;1f| Prima uma tecla para continuar ");
    scanf ("%*[^\n]"); scanf ("%*c");
    return 1;
  }
  else return 0;
}

void ReadFilename (char *pnf)
{
  int Status;

  do
  {
    printf("\e[30;1f| Nome do ficheiro ->                               ");
    printf("\e[30;23f"); Status = scanf ("%20[^\n]", pnf);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Status == 0);
}

void ReadOption (int *popc)
{
  do
  {  
    *popc = 0;
    printf("\e[26;1f| Opcao ->                       |");
    printf("\e[26;12f"); scanf ("%d", popc);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*popc < 0 || *popc > MAX_OPTIONS);
}

void WriteErrorMessage (unsigned int perro, char *pmsg)
{
  printf("\e[34;1f| %s nao foi efectuada devido a -> \e[1m", pmsg);
  switch (perro)
  {
    case NO_DIGRAPH    : printf ("Digrafo inexistente"); break;
    case NO_MEM        : printf ("Memoria esgotada"); break;
    case NULL_PTR      : printf ("Ponteiro nulo"); break;
    case DIGRAPH_EMPTY : printf ("Digrafo vazio"); break;
    case NO_VERTEX     : printf ("Vertice inexistente"); break;
    case REP_VERTEX    : printf ("Vertice repetido"); break;
    case NO_EDGE       : printf ("Aresta inexistente"); break;
    case REP_EDGE      : printf ("Aresta repetida"); break;
    case NO_FILE       : printf ("Ficheiro inexistente"); break;
    case NO_DAG        : printf ("Digrafo aciclico"); break;
    case NEG_CYCLE     : printf ("Digrafo com ciclo negativo"); break;
    case NO_CONNECTED  : printf ("Grafo desconexo"); break;
    case NO_PATH       : printf ("Caminho ou circuito inexistente"); break;
	case SINK          : printf ("Vertice sumidouro"); break;
	case SOURCE        : printf ("Vertice fonte"); break;
	case DISC          : printf ("Vertice desconexo"); break;
    default            : printf ("Erro desconhecido");
  }
  printf("\e[0m\e[35;1f| Prima uma tecla para continuar ");
  scanf ("%*[^\n]"); scanf ("%*c");
}

void ReadVertex (unsigned int *pvertex)
{
  do
  {
    printf("\e[30;1f| Vertice No ->                               ");
    printf("\e[30;17f"); scanf ("%d", pvertex);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pvertex <= 0);
}

void ReadEdge (unsigned int *pvert1, unsigned int *pvert2)
{
  do
  {
    printf("\e[30;1f| Vertice Origem ->                               ");
    printf("\e[30;21f"); scanf ("%d", pvert1);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pvert1 <= 0);

  do
  {
    printf("\e[30;1f| Vertice Destino ->                               ");
    printf("\e[30;22f"); scanf ("%d", pvert2);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*pvert2 <= 0);
}

void ReadCost (int *pcost)
{
  int Status;

  do
  {
    printf("\e[30;1f| Custo da aresta ->                               ");
    printf("\e[30;22f"); Status = scanf ("%d", pcost);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (Status != 1);
}

void ReadType (unsigned int *ptype)
{
  do
  {
    printf("\e[30;1f| Tipo Digrafo (1) / Grafo (0) ->                              ");
    printf("\e[30;35f"); scanf ("%d", ptype);
    scanf ("%*[^\n]"); scanf ("%*c");
  } while (*ptype > 1);
}

void WriteDigraph (PtDigraph pdigraph)
{
  unsigned int NVertexes, Index; char VertexList[256];

  VertexNumber (pdigraph, &NVertexes);

  printf("\e[1m");
  for (Index = 1; Index <= NVertexes; Index++)
  {
    GetVertexList (pdigraph, Index, VertexList);
    printf("\e[%d;66f ", 6+Index);
    printf ("%s\n", VertexList);
  }
  printf("\e[0m");
}

void WriteAllPaths (unsigned int pvpred[], int pcost[], unsigned int pvertex, unsigned int pnv)
{
  unsigned int I;

  printf ("\e[1m\e[5;67fCaminhos mais curtos a partir do vertice %d\n", pvertex);

  for (I = 1; I <= pnv; I++)
    if (pvpred[I-1] != 0)  /* vértice alcançável */
    {
      printf ("\e[%d;67f", 5+I); 
      WritePath (pvpred, I);
      printf ("%d - Custo = %d\n", I, pcost[I-1]);
    }

  printf("\e[0m");
}

void WritePath (unsigned int pvpred[], unsigned int pv)
{
  if (pvpred[pv-1] == 0) return;
  WritePath (pvpred, pvpred[pv-1]);
  printf ("%d - ", pvpred[pv-1]);
}

