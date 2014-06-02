/*********** Interface do D�grafo/Grafo Din�mico - digraph.h ***********/

#ifndef _DIGRAPH_DYNAMIC
#define _DIGRAPH_DYNAMIC

/*********** Defini��o do Tipo Ponteiro para um D�grafo/Grafo **********/

typedef struct digraph *PtDigraph;

/********************* Defini��o de C�digos de Erro ********************/

#define	OK	0	/* opera��o realizada com sucesso */
#define	NO_DIGRAPH	1	/* d�grafo/grafo inexistente */
#define	NO_MEM	2	/* mem�ria esgotada */
#define	NULL_PTR	3	/* ponteiro nulo */
#define	DIGRAPH_EMPTY	4	/* d�grafo/grafo vazio */
#define	NO_VERTEX	5	/* v�rtice inexistente */
#define	REP_VERTEX	6	/* v�rtice repetido */
#define	NO_EDGE	7	/* aresta inexistente */
#define	REP_EDGE	8	/* aresta repetida */
#define	NO_FILE	9	/* ficheiro inexistente */
#define	NO_DAG	10	/* d�grafo c�clico */
#define	NEG_CYCLE	11	/* d�grafo/grafo com ciclo negativo */
#define	NO_CONNECTED	12	/* grafo n�o conexo */
#define	NO_PATH	13	/* n�o existe caminho/circuito */
#define	SINK          14  /* v�rtice sumidouro */
#define	SOURCE        15  /* v�rtice fonte */
#define	DISC          16  /* v�rtice desconexo */

/********************* Prot�tipos dos Subprogramas *********************/

PtDigraph Create (unsigned int ptype);
/* Cria um d�grafo ou um grafo, caso ptype seja igual a, respetivamente, 1 ou 0. Devolve a refer�ncia do d�grafo/grafo criado ou NULL, no caso de inexist�ncia de mem�ria. */

int Destroy (PtDigraph *pdig);
/* Destr�i o d�grafo/grafo pdig e coloca a refer�ncia a NULL. Valores de retorno: OK ou NO_DIGRAPH. */

PtDigraph Copy (PtDigraph pdig);
/* Copia o d�grafo/grafo pdig, caso exista. Devolve a refer�ncia da c�pia ou NULL, caso n�o consiga fazer a c�pia. Valores de retorno: OK, NO_DIGRAPH ou NO_MEM. */

int InVertex (PtDigraph pdig, unsigned int pv);
/* Insere o v�rtice pv, no d�grafo/grafo pdig. Valores de retorno: OK, NO_DIGRAPH ou REP_VERTEX. */

int OutVertex (PtDigraph pdig, unsigned int pv);
/* Retira o v�rtice pv do d�grafo/grafo pdig. Retira tamb�m todas as suas arestas incidentes e emergentes. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY ou NO_VERTEX. */

int InEdge (PtDigraph pdig, unsigned int pv1, unsigned int pv2, \
            int pcost);
/* Insere a aresta pv1-pv2, com custo pc, no d�grafo/grafo pdig. Valores de retorno: OK, NO_DIGRAPH, NO_VERTEX ou REP_EDGE. */

int OutEdge (PtDigraph pdig, unsigned int pv1, unsigned int pv2);
/* Retira a aresta pv1-pv2 do d�grafo/grafo pdig. Valores de retorno: OK, NO_DIGRAPH, NO_VERTEX ou NO_EDGE. */

int Type (PtDigraph pdig, unsigned int *pty);
/* Determina e coloca em pty de que tipo � o d�grafo/grafo pdig (d�grafo = 1/ grafo = 0). Valores de retorno: OK, NO_DIGRAPH ou NULL_PTR. */

int VertexNumber (PtDigraph pdig, unsigned int *pnv);
/* Determina e coloca em pnv o n�mero de v�rtices existentes no d�grafo/grafo pdig. Valores de retorno: OK, NO_DIGRAPH ou NULL_PTR. */

int EdgeNumber (PtDigraph pdig, unsigned int *pne);
/* Determina e coloca em pne o n�mero de arestas existentes no d�grafo/grafo pdig. Valores de retorno: OK, NO_DIGRAPH ou NULL_PTR. */

int GetVertexList (PtDigraph pdig, unsigned int ppos, char *pvlist);
/* Cria uma sequ�ncia de carateres com a informa��o do ppos v�rtice (com 1 ? ppos ? V), incluindo a sua lista de adjac�ncias, do d�grafo/grafo pdig. Esta opera��o � necess�ria para que uma aplica��o gr�fica possa fazer a escrita do d�grafo/grafo no monitor de forma controlada. Valores de retorno: OK, NO_DIGRAPH ou NULL_PTR. */

PtDigraph CreateFile (char *pfilename);
/* Cria um d�grafo/grafo com o conteudo do ficheiro pfilename. Devolve a refer�ncia do d�grafo/grafo criado ou NULL em caso de inexist�ncia de mem�ria ou de inexist�ncia do ficheiro. */

int StoreFile (PtDigraph pdig, char *pfilename);
/* Armazena o d�grafo/grafo pdig no ficheiro pfilename. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY ou NO_FILE. */

int VertexType (PtDigraph pdig, unsigned int pv);
/* Determina de que tipo �o vertice pv. Valores de retorno: OK (vertice normal), NO_DIGRAPH, DIGRAPH_EMPTY, NO_VERT, SINK (vertice sumidouro), SOURCE (vertice fonte) ou DISC (vertice desconexo). */

int Dijkstra (PtDigraph pdig, unsigned int pv, unsigned int pvpred[], int pvcost[]);
/* Determina os caminhos mais curtos dos vertices alcan��veis a partir do vertice pv. Devolve a lista de vertices predecessores em pvpred e os respectivos custos dos caminhos em pvcost. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY, NULL_PTR ou NO_VERT. */

int Reach (PtDigraph pdig, unsigned int pv, unsigned int pvlist[]);
/* Determina os vertices alcan��veis a partir a partir do vertice pv. Devolve a lista de vertices em pvlist, sendo que a posi��o 0 da sequ�ncia indica o numero de vertices alcan��veis. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY, NULL_PTR, NO_VERT ou NO_MEM. */

int DigraphComplete (PtDigraph pdig, unsigned int *pcomp);
/* Determina se o digrafo  pdig � completo. Devolve 1 em caso afirmativo e 0 no caso contr�rio no par�metro pcomp. Valores de retorno: OK, NO_DIGRAPH ou NULL_PTR. */

PtDigraph DigraphTranspose (PtDigraph pdig);
/* Cria o d�grafo transposto do digrafo pdig. Devolve a refer�ncia do d�grafo criado ou NULL, no caso de inexist�ncia de mem�ria. */

int DigraphStronglyConnected (PtDigraph pdig, unsigned int *pstrong);
/* Verifica se o digrafo pdig � fortemente conexo. Devolve 1 em caso afirmativo e 0 no caso contr�rio no par�metro pstrong. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY, NULL_PTR ou NO_MEM. */

int DigraphTransitiveClosure (PtDigraph pdig);
/* Implementa o fecho transitivo do digrafo pdig. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY ou NO_MEM. */


#endif