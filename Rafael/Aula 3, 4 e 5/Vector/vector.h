/*******************************************************************************

 Ficheiro de interface do Tipo de Dados Abstracto Vector (vector.h). O vector �
 composto pela sua dimens�o e pelas suas componentes reais. A implementa��o
 providencia um construtor para criar um vector nulo com a dimens�o pretendida.
 � da responsabilidade da aplica��o, invocar o destrutor, para libertar a
 mem�ria atribu�da ao objecto. O m�dulo providencia um controlo centralizado de
 erro, disponibilizando uma fun��o para obter o �ltimo erro ocorrido, uma fun��o
 para obter uma mensagem de erro elucidativa e uma fun��o para limpar o erro.
 Providencia tamb�m opera��es para armazenar e recuperar vectores para ficheiros.

 Autor : Ant�nio Manuel Adrego da Rocha    Data : Mar�o de 2013

*******************************************************************************/

#ifndef _VECTOR
#define _VECTOR

/****************** Defini��o do Tipo Ponteiro para um VECTOR *****************/

typedef struct vector *PtVector;

/************************ Defini��o de C�digos de Erro ************************/

#define  OK         0  /* opera��o realizada com sucesso */
#define  NO_VECTOR  1  /* o(s) vector(es) n�o existe(m) */
#define  NO_MEM     2  /* mem�ria esgotada */
#define  NO_FILE    3  /* o ficheiro n�o existe */
#define  BAD_SIZE   4  /* dimens�o do vector errada */
#define  BAD_INDEX  5  /* elemento inexistente no vector */
#define  DIF_SIZE   6  /* vectores com dimens�es diferentes */

/*************************** Prot�tipos das Fun��es ***************************/

void VectorClearError (void);
/*******************************************************************************
 Inicializa��o do erro.
*******************************************************************************/

int VectorError (void);
/*******************************************************************************
 Devolve o c�digo do �ltimo erro ocorrido.
*******************************************************************************/

char *VectorErrorMessage (void);
/*******************************************************************************
 Devolve uma mensagem esclarecedora da causa do �ltimo erro ocorrido.
*******************************************************************************/

PtVector VectorCreate (unsigned int pdim);
/*******************************************************************************
 Cria um vector nulo, de componentes reais, com a dimens�o indicada por pdim.
 Devolve a refer�ncia do vector criado ou NULL, caso n�o consiga criar o vector,
 por falta de mem�ria. Valores de erro: OK, BAD_SIZE ou NO_MEM.
*******************************************************************************/

void VectorDestroy (PtVector *pvector);
/*******************************************************************************
 Destr�i o vector pvector, caso ele exista, e coloca a sua
 refer�ncia a NULL. Valores de erro: OK ou NO_VECTOR.
*******************************************************************************/

PtVector VectorCopy (PtVector pvector);
/*******************************************************************************
 Copia o vector pvector, caso ele exista. Devolve a refer�ncia do vector c�pia ou 
 NULL, caso n�o consiga fazer a c�pia. Valores de erro: OK, NO_VECTOR ou NO_MEM.
*******************************************************************************/

int VectorDimension (PtVector pvector);
/*******************************************************************************
 Devolve a dimens�o do vector pvector. Valores de erro: OK ou NO_VECTOR.
*******************************************************************************/

void VectorModifyComponent (PtVector pvector, unsigned int ppos, double pval);
/*******************************************************************************
 Armazena pval no �ndice ppos do vector pvector.
 Valores de erro: OK, NO_VECTOR ou BAD_INDEX.
*******************************************************************************/

double VectorObserveComponent (PtVector pvector, unsigned int ppos);
/*******************************************************************************
 Devolve o valor armazenado no �ndice ppos do vector pvector.
 Valores de erro: OK, NO_VECTOR ou BAD_INDEX.
*******************************************************************************/

int VectorIsNull (PtVector pvector);
/*******************************************************************************
 Verifica se o vector pvector � um vector nulo. Devolve 1 em caso afirmativo e 0
 em caso contr�rio. Valores de erro: OK ou NO_VECTOR.
*******************************************************************************/

PtVector VectorAddition (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Soma os dois vectores pvector1 e pvector2. Devolve a refer�ncia do vector soma ou NULL,
 caso n�o consiga fazer a adi��o. Valores de erro: OK, NO_VECTOR, DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtVector VectorSubtraction (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Subtrai os dois vectores pvector1 e pvector2. Devolve a refer�ncia do vector 
 diferen�a ou NULL, caso n�o consiga fazer a subtrac��o. Valores de erro: OK, 
 NO_VECTOR, DIF_SIZE ou NO_MEM.
*******************************************************************************/

PtVector VectorMultiplication (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Faz o produto vectorial dos dois vectores pvector1 e pvector2. Devolve a refer�ncia 
 do vector produto ou NULL, caso n�o consiga fazer a multiplica��o. Valores de 
 erro: OK, NO_VECTOR ou DIF_SIZE.
*******************************************************************************/

double VectorScalarMultiplication (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Devolve o produto escalar dos dois vectores pvector1 e pvector2, ou 0, caso n�o 
 possa realizar o produto. Valores de erro: OK, NO_VECTOR ou DIF_SIZE.
*******************************************************************************/

int VectorEquals (PtVector pvector1, PtVector pvector2);
/*******************************************************************************
 Compara se os dois vectores pvector1 e pvector2 s�o id�nticos. Devolve 1 em caso 
 afirmativo e 0 em caso contr�rio. Valores de erro: OK, NO_VECTOR ou DIF_SIZE.
*******************************************************************************/

void VectorStoreFile (PtVector pvector, char *pfname);
/*******************************************************************************
 Armazena o vector pvector, caso ele exista, no ficheiro pfname. O ficheiro tem na 
 primeira linha o n�mero de componentes do vector, seguido das componentes, uma 
 por linha. Valores de erro: OK, NO_VECTOR ou NO_FILE.
*******************************************************************************/

PtVector VectorCreateFile (char *pfname);
/*******************************************************************************
 Cria um vector a partir de informa��o lida do ficheiro pfname. Devolve a
 refer�ncia do vector criado ou NULL, caso n�o consiga criar o vector.
 Valores de erro: OK, NO_FILE, BAD_SIZE ou NO_MEM.
*******************************************************************************/

#endif
