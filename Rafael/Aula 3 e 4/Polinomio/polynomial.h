/*******************************************************************************

 Ficheiro de interface do Tipo Abstracto de Dados Polin�mio (polynomial.h).
 O polin�mio � composto pelo seu grau e pelos seus coeficientes reais, sendo
 que um polin�mio com grau n tem n+1 coeficientes. A implementa��o providencia
 um construtor para criar um polin�mio nulo com o grau pretendido. � da
 responsabilidade da aplica��o, invocar o destrutor, para libertar a mem�ria
 atribu�da ao objecto. O m�dulo providencia um controlo centralizado de erro,
 disponibilizando uma fun��o para obter o �ltimo erro ocorrido, uma fun��o para
 obter uma mensagem de erro elucidativa e uma fun��o para limpar o erro.
 Providencia tamb�m opera��es para armazenar e recuperar polin�mios para ficheiros.
 
 Autor : Ant�nio Manuel Adrego da Rocha    Data : Mar�o de 2013


*******************************************************************************/

#ifndef _POLY
#define _POLY

/**************** Defini��o do Tipo Ponteiro para um Polin�mio ****************/

typedef struct poly *PtPoly;  /* tipo de dados que � um ponteiro, o acesso � por */

/************************ Defini��o de C�digos de Erro ************************/


#define  OK         0  /* opera��o realizada com sucesso */
#define  NO_POLY    1  /* o(s) polin�mio(s) n�o existe(m) */
#define  NO_MEM     2  /* mem�ria esgotada */
#define  NO_FILE    3  /* o ficheiro n�o existe */
#define  BAD_SIZE   4  /* grau do polin�mio errada */
#define  BAD_INDEX  5  /* coeficiente inexistente no polin�mio */

/*************************** Prot�tipos das Fun��es ***************************/

void PolyClearError (void);
/*******************************************************************************
 Inicializa��o do erro.
*******************************************************************************/

int PolyError (void);
/*******************************************************************************
 Fun��o que devolve o c�digo do �ltimo erro ocorrido.
*******************************************************************************/

char *PolyErrorMessage (void);
/*******************************************************************************
 Fun��o que devolve uma mensagem esclarecedora da causa do �ltimo erro ocorrido.
*******************************************************************************/

PtPoly PolyCreate (unsigned int pdegree);
/*******************************************************************************
 Cria um polin�mio nulo, de coeficientes reais, com o grau indicado por pdegree.
 Devolve a refer�ncia do polin�mio criado ou NULL, caso n�o consiga criar o
 polin�mio, por falta de mem�ria. Valores de erro: OK ou NO_MEM.
*******************************************************************************/

void PolyDestroy (PtPoly *ppoly);
/*******************************************************************************
 Destr�i o polin�mio ppoly, caso ele exista, e coloca a sua refer�ncia a NULL.
 Valores de erro: OK ou NO_POLY.
*******************************************************************************/

PtPoly PolyCopy (PtPoly ppoly);
/*******************************************************************************
 Copia do polin�mio ppoly, caso ele exista. Devolve a refer�ncia do polin�mio c�pia
 ou NULL, caso n�o consiga fazer a c�pia. Valores de erro: OK, NO_POLY ou NO_MEM.
*******************************************************************************/

int PolyDegree (PtPoly ppoly);
/*******************************************************************************
 Devolve o grau do polin�mio ppoly. Valores de erro: OK ou NO_POLY.
*******************************************************************************/

void PolyModifyCoefficient (PtPoly ppoly, unsigned int ppos, double pval);
/*******************************************************************************
 Armazena pval no �ndice ppos, do polin�mio ppoly. Valores de erro: OK, NO_POLY
 ou BAD_INDEX.
*******************************************************************************/

double PolyObserveCoefficient (PtPoly ppoly, unsigned int ppos);
/*******************************************************************************
 Devolve o valor armazenado no �ndice ppos do polin�mio ppoly. Valores de erro: 
 OK, NO_POLY ou BAD_INDEX.
*******************************************************************************/

int PolyIsNull (PtPoly ppoly);
/*******************************************************************************
 Verifica se o polin�mio ppoly � um polin�mio nulo. Devolve 1 em caso afirmativo 
 e 0 em caso contr�rio. Valores de erro: OK ou NO_POLY.
*******************************************************************************/

PtPoly PolyAddition (PtPoly ppoly1, PtPoly ppoly2);
/*******************************************************************************
 Soma os dois polin�mios ppoly1 e ppoly2. Devolve a refer�ncia do polin�mio soma 
 ou NULL, caso n�o consiga fazer a adi��o. Valores de erro: OK, NO_POLY ou NO_MEM.
*******************************************************************************/

PtPoly PolySubtraction (PtPoly ppoly1, PtPoly ppoly2);
/*******************************************************************************
 Subtrai os dois polin�mios ppoly1 e ppoly2. Devolve a refer�ncia do polin�mio 
 diferen�a ou NULL, caso n�o consiga fazer a subtrac��o. Valores de erro: OK, 
 NO_POLY ou NO_MEM.
*******************************************************************************/

PtPoly PolyMultiplication (PtPoly ppoly1, PtPoly ppoly2);
/*******************************************************************************
 Multiplica os dois polin�mios ppoly1 e ppoly2. Devolve a refer�ncia do polin�mio 
 produto ou NULL, caso n�o consiga fazer a multiplica��o. Valores de erro: OK, 
 NO_POLY ou NO_MEM.
*******************************************************************************/

int PolyEquals (PtPoly ppoly1, PtPoly ppoly2);
/*******************************************************************************
 Compara se os dois polin�mios ppoly1 e ppoly2 s�o id�nticos. Devolve 1 em caso 
 afirmativo e 0 em caso contr�rio. Valores de erro: OK ou NO_POLY.
*******************************************************************************/

void PolyStoreFile (PtPoly ppoly, char *pfname);
/*******************************************************************************
 Armazena o polin�mio ppoly, caso ele exista, no ficheiro pfname. O ficheiro tem 
 na primeira linha o grau do polin�mio, seguido dos coeficientes, um por linha.
 Valores de erro: OK, NO_POLY ou NO_FILE.
*******************************************************************************/

PtPoly PolyCreateFile (char *pfname);
/*******************************************************************************
 Cria um polin�mio a partir de informacao lida do ficheiro pfname. Devolve a
 refer�ncia do polin�mio criado ou NULL, caso n�o consiga criar o polin�mio.
 Valores de erro: OK, NO_FILE ou NO_MEM.
*******************************************************************************/

#endif
