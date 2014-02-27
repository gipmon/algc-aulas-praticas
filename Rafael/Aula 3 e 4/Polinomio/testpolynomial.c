#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polynomial.h"

void WritePoly (PtPoly);

int main (void)
{
	PtPoly poly1 = NULL, poly2 = NULL, poly3 = NULL;
	char filename[21]; int st, degree, i; double coef;

	system ("clear");
	printf ("\nler polinomio do ficheiro\n");
	do
	{
  		printf ("Nome do ficheiro -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);
	poly1 = PolyCreateFile (filename);
	printf ("\npolinomio lido do ficheiro %s\n", filename);

	WritePoly (poly1);

	printf ("\nler polinomio do teclado\n");
	do
	{
		printf ("grau do polinomio? "); scanf ("%d", &degree);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (degree < 0);

	poly2 = PolyCreate (degree);
    	for (i = 0; i <= degree; i++)
	{
		do
		{
			printf ("Coeficiente do polinomio? "); st = scanf ("%lf", &coef);
			scanf ("%*[^\n]"); scanf ("%*c");
		} while (st == 0);
		PolyModifyCoefficient (poly2, i, coef);
	}

	printf ("\npolinomio lido do teclado\n");
	WritePoly (poly2);

	printf ("\nescrever polinomio no ficheiro\n");
	do
	{
  		printf ("Nome do ficheiro -> ");
		st = scanf ("%20[^\n]", filename);
		scanf ("%*[^\n]"); scanf ("%*c");
	} while (st == 0);
	PolyStoreFile (poly2, filename);

	poly3 = PolyAddition (poly1, poly2);
	printf ("\npolinomio soma\n");
	WritePoly (poly3);

	PolyDestroy (&poly3);
	poly3 = PolySubtraction (poly1, poly2);
	printf ("\npolinomio diferenca\n");
	WritePoly (poly3);

	PolyDestroy (&poly3);
	poly3 = PolyMultiplication (poly1, poly2);
	printf ("\npolinomio produto\n");
	WritePoly (poly3);

	printf ("\ndestruir os polinomios e terminar o programa\n");
	PolyDestroy (&poly1);
	PolyDestroy (&poly2);
	PolyDestroy (&poly3);

	WritePoly (poly3);

	return 0;
}

void WritePoly (PtPoly ppol)
{
  int i, degree = PolyDegree (ppol); double coef;

  if (ppol != NULL)
  {
    /* escrita do coeficiente x^n */
    coef = PolyObserveCoefficient (ppol, degree);
    if (degree > 1) printf ("%5.2f x^%d", coef, degree);
    else if (degree == 1) printf ("%5.2f x", coef);

    /* escrita dos coeficientes x^n-1 ... x^2 para polinomios com grau > 1 */
    if (degree > 1)
      for (i = degree-1; i > 1; i--)
      {
        coef = PolyObserveCoefficient (ppol, i);
        if (coef >= 0.0) printf (" + %5.2f x^%d", coef, i);
        else printf (" - %5.2f x^%d", fabs(coef), i);
      }

    /* escrita do coeficiente x para polinómios com grau > 1 */
    if (degree > 1)
    {
      coef = PolyObserveCoefficient (ppol, 1);
      if (coef >= 0.0) printf (" + %5.2f x", coef);
      else printf (" - %5.2f x", fabs(coef));
    }

    /* escrita do coeficiente independente */
    if (degree > 0)
    {
      coef = PolyObserveCoefficient (ppol, 0);
      if (coef >= 0.0) printf (" + %5.2f\n", coef);
      else printf (" - %5.2f\n", fabs(coef));  
    }
    else printf ("%5.2f", coef);
  }
}

