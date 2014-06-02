/*********** Interface do Dígrafo/Grafo Dinâmico - digraph.h ***********/

#ifndef _DIGRAPH_DYNAMIC
#define _DIGRAPH_DYNAMIC

/*********** Definição do Tipo Ponteiro para um Dígrafo/Grafo **********/

typedef struct digraph *PtDigraph;

/********************* Definição de Códigos de Erro ********************/

#define	OK	0	/* operação realizada com sucesso */
#define	NO_DIGRAPH	1	/* dígrafo/grafo inexistente */
#define	NO_MEM	2	/* memória esgotada */
#define	NULL_PTR	3	/* ponteiro nulo */
#define	DIGRAPH_EMPTY	4	/* dígrafo/grafo vazio */
#define	NO_VERTEX	5	/* vértice inexistente */
#define	REP_VERTEX	6	/* vértice repetido */
#define	NO_EDGE	7	/* aresta inexistente */
#define	REP_EDGE	8	/* aresta repetida */
#define	NO_FILE	9	/* ficheiro inexistente */
#define	NO_DAG	10	/* dígrafo cíclico */
#define	NEG_CYCLE	11	/* dígrafo/grafo com ciclo negativo */
#define	NO_CONNECTED	12	/* grafo não conexo */
#define	NO_PATH	13	/* não existe caminho/circuito */
#define	SINK          14  /* vértice sumidouro */
#define	SOURCE        15  /* vértice fonte */
#define	DISC          16  /* vértice desconexo */

/********************* Protótipos dos Subprogramas *********************/

PtDigraph Create (unsigned int ptype);
/* Cria um dígrafo ou um grafo, caso ptype seja igual a, respetivamente, 1 ou 0. Devolve a referência do dígrafo/grafo criado ou NULL, no caso de inexistência de memória. */

int Destroy (PtDigraph *pdig);
/* Destrói o dígrafo/grafo pdig e coloca a referência a NULL. Valores de retorno: OK ou NO_DIGRAPH. */

PtDigraph Copy (PtDigraph pdig);
/* Copia o dígrafo/grafo pdig, caso exista. Devolve a referência da cópia ou NULL, caso não consiga fazer a cópia. Valores de retorno: OK, NO_DIGRAPH ou NO_MEM. */

int InVertex (PtDigraph pdig, unsigned int pv);
/* Insere o vértice pv, no dígrafo/grafo pdig. Valores de retorno: OK, NO_DIGRAPH ou REP_VERTEX. */

int OutVertex (PtDigraph pdig, unsigned int pv);
/* Retira o vértice pv do dígrafo/grafo pdig. Retira também todas as suas arestas incidentes e emergentes. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY ou NO_VERTEX. */

int InEdge (PtDigraph pdig, unsigned int pv1, unsigned int pv2, \
            int pcost);
/* Insere a aresta pv1-pv2, com custo pc, no dígrafo/grafo pdig. Valores de retorno: OK, NO_DIGRAPH, NO_VERTEX ou REP_EDGE. */

int OutEdge (PtDigraph pdig, unsigned int pv1, unsigned int pv2);
/* Retira a aresta pv1-pv2 do dígrafo/grafo pdig. Valores de retorno: OK, NO_DIGRAPH, NO_VERTEX ou NO_EDGE. */

int Type (PtDigraph pdig, unsigned int *pty);
/* Determina e coloca em pty de que tipo é o dígrafo/grafo pdig (dígrafo = 1/ grafo = 0). Valores de retorno: OK, NO_DIGRAPH ou NULL_PTR. */

int VertexNumber (PtDigraph pdig, unsigned int *pnv);
/* Determina e coloca em pnv o número de vértices existentes no dígrafo/grafo pdig. Valores de retorno: OK, NO_DIGRAPH ou NULL_PTR. */

int EdgeNumber (PtDigraph pdig, unsigned int *pne);
/* Determina e coloca em pne o número de arestas existentes no dígrafo/grafo pdig. Valores de retorno: OK, NO_DIGRAPH ou NULL_PTR. */

int GetVertexList (PtDigraph pdig, unsigned int ppos, char *pvlist);
/* Cria uma sequência de carateres com a informação do ppos vértice (com 1 ? ppos ? V), incluindo a sua lista de adjacências, do dígrafo/grafo pdig. Esta operação é necessária para que uma aplicação gráfica possa fazer a escrita do dígrafo/grafo no monitor de forma controlada. Valores de retorno: OK, NO_DIGRAPH ou NULL_PTR. */

PtDigraph CreateFile (char *pfilename);
/* Cria um dígrafo/grafo com o conteudo do ficheiro pfilename. Devolve a referência do dígrafo/grafo criado ou NULL em caso de inexistência de memória ou de inexistência do ficheiro. */

int StoreFile (PtDigraph pdig, char *pfilename);
/* Armazena o dígrafo/grafo pdig no ficheiro pfilename. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY ou NO_FILE. */

int VertexType (PtDigraph pdig, unsigned int pv);
/* Determina de que tipo éo vertice pv. Valores de retorno: OK (vertice normal), NO_DIGRAPH, DIGRAPH_EMPTY, NO_VERT, SINK (vertice sumidouro), SOURCE (vertice fonte) ou DISC (vertice desconexo). */

int Dijkstra (PtDigraph pdig, unsigned int pv, unsigned int pvpred[], int pvcost[]);
/* Determina os caminhos mais curtos dos vertices alcançáveis a partir do vertice pv. Devolve a lista de vertices predecessores em pvpred e os respectivos custos dos caminhos em pvcost. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY, NULL_PTR ou NO_VERT. */

int Reach (PtDigraph pdig, unsigned int pv, unsigned int pvlist[]);
/* Determina os vertices alcançáveis a partir a partir do vertice pv. Devolve a lista de vertices em pvlist, sendo que a posição 0 da sequência indica o numero de vertices alcançáveis. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY, NULL_PTR, NO_VERT ou NO_MEM. */

int DigraphComplete (PtDigraph pdig, unsigned int *pcomp);
/* Determina se o digrafo  pdig é completo. Devolve 1 em caso afirmativo e 0 no caso contrário no parâmetro pcomp. Valores de retorno: OK, NO_DIGRAPH ou NULL_PTR. */

PtDigraph DigraphTranspose (PtDigraph pdig);
/* Cria o dígrafo transposto do digrafo pdig. Devolve a referência do dígrafo criado ou NULL, no caso de inexistência de memória. */

int DigraphStronglyConnected (PtDigraph pdig, unsigned int *pstrong);
/* Verifica se o digrafo pdig é fortemente conexo. Devolve 1 em caso afirmativo e 0 no caso contrário no parâmetro pstrong. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY, NULL_PTR ou NO_MEM. */

int DigraphTransitiveClosure (PtDigraph pdig);
/* Implementa o fecho transitivo do digrafo pdig. Valores de retorno: OK, NO_DIGRAPH, DIGRAPH_EMPTY ou NO_MEM. */


#endif