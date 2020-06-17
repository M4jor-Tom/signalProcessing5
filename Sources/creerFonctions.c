#define SINUS 0
#define COSINUS 1
#define RECTANGULAIRE 2

#define PI 3.14159
#define PIXELS_PAR_UNITES 100

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "creerFonctions.h"
#include "image.h"


int signalCarre(double x, int max)
{
	return sin(x) > 0
		? max
		: -max;
}

void minMax(trace *ptr_graph)
{
	int i;
	for(i = 0; i < ptr_graph -> nbValeurs; i++)
	{
		ptr_graph -> vMin = ptr_graph -> valeurs[i] < ptr_graph -> vMin
			? ptr_graph -> valeurs[i]
			: ptr_graph -> vMin;
				
		ptr_graph -> vMax = ptr_graph -> valeurs[i] > ptr_graph -> vMax
			? ptr_graph -> valeurs[i]
			: ptr_graph -> vMax;
	}
}

trace valeursFonction(int fonction, double frequence, int nbPeriodes)
{
	int i, curseur;
	trace fonctionGraph;
	
	fonctionGraph.nbValeurs = nbPeriodes * (double)PIXELS_PAR_UNITES / frequence;
	fonctionGraph.valeurs = (double *)safeMalloc(sizeof(double) * fonctionGraph.nbValeurs);
	
	fonctionGraph.vMin = 0.0;
	fonctionGraph.vMax = fonctionGraph.vMin;
	
	for(i = 1, curseur = 0; curseur < fonctionGraph.nbValeurs; i++, curseur++)
	{
		double argumentFonction = 2.0 * PI * frequence * ((double)i - (double)fonctionGraph.nbValeurs / 2.0) / (double)PIXELS_PAR_UNITES;
		switch(fonction)
		{
			case SINUS:
				fonctionGraph.valeurs[curseur] = sin(argumentFonction);
				break;
				
			case COSINUS:
				fonctionGraph.valeurs[curseur] = cos(argumentFonction);
				break;
				
			case RECTANGULAIRE:
				fonctionGraph.valeurs[curseur] = (double)signalCarre(argumentFonction, 1);
				break;
				
			default:
				printf("<valeursFonction> Erreur: %d n'est pas une fonction\n", fonction);
				_free(fonctionGraph.valeurs);
				memset(&fonctionGraph, 0, sizeof(trace));
				return fonctionGraph;
		}
	}
	
	minMax(&fonctionGraph);
	
	printf("<valeursFonction>\n\tnbValeurs: %d\n\tvMin: %.2lf\n\tvMax: %.2lf\n", fonctionGraph.nbValeurs, fonctionGraph.vMin, fonctionGraph.vMax);
	
	return fonctionGraph;
}

trace *valeursMat(int fonction, double frequence, int nbPeriodes)
{
	trace
		first = valeursFonction(fonction, frequence, nbPeriodes),
		*ret = (trace *)safeMalloc(sizeof(trace) * first.nbValeurs);
	
	int i;
	for(i = 0; i < first.nbValeurs; i++)
		ret[i] = valeursFonction(fonction, frequence, nbPeriodes);
		
	return ret;
}

void libereTrace(trace *cible)
{
	if(cible != NULL)
	{
		_free(cible -> valeurs);
		_free(cible);
	}
}
