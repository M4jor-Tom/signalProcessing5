#define PI 3.1415

#define SINUS 0
#define COSINUS 1
#define RECTANGULAIRE 2
#define Oy 0
#define Ox 1

#include "signal.h"
#include "signalTCD.h"
#include "image.h"
#include "creerFonctions.h"
#include "afficheFonctions.h"
#include "signal2D.h"
#include "FFT.h"
#include "FFT2D.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
	/*//Tracer le signal d'origine (test)
	trace graph = valeursFonction(SINUS, 0.3, 2);
	minMax(&graph);
	
	//Tracer la TCD
	trace graphTCD =
	{
		.valeurs = TCD(graph.valeurs, graph.nbValeurs, 0),
		.nbValeurs = biggestSmallerBits(graph.nbValeurs)
	};
	
	
	printf("OUT\n");
	minMax(&graphTCD);
	
	printf("minMax\n");
	graphTCD.nbValeurs = biggestSmallerBits(graphTCD.nbValeurs);
	
	printf("preTrace\n");
	traceFonction(graph, "graph.bmp");
	traceFonction(graphTCD, "graphTCD.bmp");

	libereTrace(&graph);
	
	//Tracer le signal retransformé
	trace graphTCDBack =
	{
		.valeurs = TCD(graphTCD.valeurs, graphTCD.nbValeurs, 1),
		.nbValeurs = biggestSmallerBits(graphTCD.nbValeurs)
	};
	
	libereTrace(&graphTCD);
	
	minMax(&graphTCDBack);
	
	traceFonction(graphTCDBack, "graphTCDBack.bmp");
	
	libereTrace(&graphTCDBack);*/
	
	Image *ptr_sinus = chargeImage("Sinus.bmp");
	
	float **tcdHeaders = safeMalloc(sizeof(float *) * ptr_sinus -> hauteur);
	tcdHeaders = TCD2D(ptr_sinus -> gris, ptr_sinus -> largeur, ptr_sinus -> hauteur, 0);
	
	trace *tcd2DGraph = safeMalloc(sizeof(trace) * ptr_sinus -> hauteur);
	
	int i;
	for(i = 0; i < ptr_sinus -> hauteur; i++)
	{
		tcd2DGraph[i].valeurs = tcdHeaders[i];
		minMax(&tcd2DGraph[i]);
	}
	
	
	
	_getch();
	return 0;
}
