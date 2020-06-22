#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#ifdef _MSC_VER
	#define getch() _getch()
	#define getche() _getche()
#endif

#define PI 3.1415

#define SINUS 0
#define COSINUS 1
#define RECTANGLE 2
#define RECTANGULAIRE 2
#define Oy 0
#define Ox 1

#include "signal.h"
#include "image.h"
#include "creerFonctions.h"
#include "afficheFonctions.h"
#include "signal2D.h"
#include "FFT.h"
#include "FFT2D.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	system("color F0");

	Complexe* xN = NULL;
	trace 
		temporalGraph,
		fftGraph,
		*temporalGraph2D,
		*fftGraph2D;
	float frequency;
	int periodsCount, i;
	short int 
		reverse = 0,
		dimensions = 1,
		signalForm = SINUS;
	bool 
		leave = false,
		getFft = true;

	memset(&temporalGraph, 0, sizeof(trace));
	memset(&fftGraph, 0, sizeof(trace));

	do
	{
		system("cls");

		//Grabbing process
		printf("Output mode:\n1.Temporal signal\n2.Fourier transform\n3.Leave\n\n");
		bool redo = false;
		do
		{
			if (redo)
				printf("\rPlease re-select: ");
			else printf("Please select: ");
			redo = false;

			//Processing query
			switch (getch())
			{

				case '1':
				case '&':
					//Wanted temporal
					getFft = false;

				case '2':
				case 'é':
					//Wanted FFT or temporal
					printf("Signal form:\n\t1.Sinus\n\t2.Cosinus\n\t3.Rectangle\n");

					do
					{
						if (redo)
							printf("\rPlease re-select: ");
						else printf("Please select: ");
						redo = false;

						switch(getch())
						{
							case '1':
							case '&':
								signalForm = SINUS;
								break;

							case '2':
							case 'é':
								signalForm = COSINUS;
								break;

							case '3':
							case '"':
								signalForm = RECTANGLE;
								break;

							default:
								redo = true;
						}
					}while(redo);

					printf("Signal dimensions:\n\t1.Graphic (1 dimension)\n\t2.Image (2 dimensions)\n");

					do
					{
						if (redo)
							printf("\rPlease re-select: ");
						else printf("Please select: ");
						redo = false;

						switch (getch())
						{
							case '1':
							case '&':
								dimensions = 1;
								break;

							case '2':
							case 'é':
								dimensions = 2;
								break;

							default:
								redo = true;
						}

					} while (redo);

					printf("\nFrequency: ");
					scanf("%f", &frequency);
					getchar();

					printf("Periods count: ");
					scanf("%d", &periodsCount);
					getchar();

					//Processing graph (bmp file)
					temporalGraph = valeursFonction(signalForm, frequency, periodsCount);


					if (getFft)
					{
						temporalGraph.nbValeurs = biggestSmallerBits(temporalGraph.nbValeurs);
					}

					xN = safeMalloc(sizeof(Complexe) * temporalGraph.nbValeurs);

					if(getFft)
					{
						fftGraph.valeurs = FFT(xN, temporalGraph.nbValeurs, reverse);
					}

					break;

				case '3':
				case '"':
					//Wanted to leave
					leave = true;
					break;

				default:
					redo = true;
			}
		}while(redo);

		
	} while (leave == false);

	

	printf("<main> Test des fonction des questions P1 et P2 partie 4\n\n");
	
	trace graph;
	memset(&graph, 0, sizeof(trace));
	
	bool resaisir = false;
	double frequence = 0.0;
	int nbPeriodes = 0,
		formeSignal = SINUS,
		inverse = 0,
		i;
	
	int dimSignal = 1;
	do
	{
		if(dimSignal != 1 && dimSignal != 2)
			printf("<main> Veuillez re-saisir:\n");
		
		printf("<main> Dimensions du signal: ");
		scanf("%d", &dimSignal);
		getchar();
	}while(dimSignal != 1 && dimSignal != 2);
	
	graph = valeursFonction(formeSignal - 1, frequence, nbPeriodes);
	
	if(dimSignal == 2)
	{
		int axe = Oy;
		do
		{
			if(axe != Oy && axe != Ox)
				printf("<main> Veuillez re-saisir:\n");
			
			printf("<main> Axe: \n\t1.Oy\n\t2.Ox\n");
			scanf("%d", &axe);
			getchar();
			axe--;
		}while(axe != Oy && axe != Ox);
		
		//traceFonction2D(graph, "graph2D.bmp", axe);
	}
	
	
	int choixGraph = 1;
	do
	{
		if(choixGraph != 1 && choixGraph != 2)
			printf("<main> Veuillez re-saisir:\n");
		
		printf("<main>\n1.Tracer la fonction\n2.Tracer la FFT\n");
		scanf("%d", &choixGraph);
		getchar();
	}while(choixGraph != 1 && choixGraph != 2);
	
	//Transmission des valeurs vers une valeur de type complexe
	//Rendre multiple de 2^n
	graph.nbValeurs = biggestSmallerBits(graph.nbValeurs);
	Complexe *graphComplexe = malloc(sizeof(Complexe) * graph.nbValeurs);
	for(i = 0; i < graph.nbValeurs; i++)
	{
		graphComplexe[i].reel = (float)graph.valeurs[i];
		graphComplexe[i].imaginaire = 0.0;
	}
	if(dimSignal == 1)
		traceFonction(graph, "graph.bmp");
	Complexe *fft = FFT(graphComplexe, graph.nbValeurs, inverse);
	
	if(choixGraph == 2)
	{
		//Tracer FFT
		for(i = 0; i < graph.nbValeurs; i++)
			graph.valeurs[i] = fft[i].reel;
			
		minMax(&graph);
		
		if(dimSignal == 1)
		{
			traceFonction(graph, "fft.bmp");
		}
		/*else if(dimSignal == 2)
		{
			int hauteurImage2D, largeurImage2D;
			Complexe 
				**xN2D = imageVersComplexe("graph2D.bmp", &hauteurImage2D, &largeurImage2D),
				**fft2d = FFT2D(xN2D, largeurImage2D, hauteurImage2D, inverse);
			
			trace fft2DGraph;
			memset(&fft2DGraph, 0, sizeof(trace));
			
			fft2DGraph.nbValeurs = largeurImage2D;
			fft2DGraph.valeurs = malloc(sizeof(double) * fft2DGraph.nbValeurs);
			
			for(i = 0; i < fft2DGraph.nbValeurs; i++)
				fft2DGraph.valeurs[i] = fft2d[0][i].reel;
			
			minMax(&fft2DGraph);
			printf("test post\n");
			traceFonction2D(fft2DGraph, "fft2d.bmp", Oy);
		}*/
	}
	
	printf("\n<main> Test de FFT() avec les valeurs du graphique dessine:\n");
	int 
		*picsNegatifs = NULL,
		sizeNegatif = 0,
		*picsPositifs = NULL,
		sizePositif = 0;
	for(i = 0; i < graph.nbValeurs; i++)
	{
		printf("<main> X[%d] = ", i);
		printComplexe(fft[i]);
		printf("\n");
		
		if(fft[i].reel < -10.0 || fft[i].imaginaire < -10.0)
		{
			picsNegatifs = realloc(picsNegatifs, ++sizeNegatif * sizeof(int));
			picsNegatifs[sizeNegatif - 1] = i;
		}
		else if(fft[i].reel > 10.0 || fft[i].imaginaire > 10.0)
		{
			picsPositifs = realloc(picsPositifs, ++sizePositif * sizeof(int));
			picsPositifs[sizePositif - 1] = i;
		}
	}
	for(i = 0; i < sizeNegatif; i++)
	{
		printf("<main> Pic negatif %d: %d\n", i + 1, picsNegatifs[i]);
	}
	for(i = 0; i < sizePositif; i++)
	{
		printf("<main> Pic positif %d: %d\n", i + 1, picsPositifs[i]);
	}
	free(picsNegatifs);
	free(picsPositifs);
	
	
	
	//Test des fonctions
	
	printf("\n\n<main> Test des fonction des questions P3 et P4 partie 4\n\n");
	
	printf("<main> Test de TN():\nSaisir une taille: ");
	
	int taille = 0;
	scanf("%d", &taille);
	getchar();
	
	printTN(TN(taille, inverse), taille);
	
	printf("<main> A cause d'un bug lors du produit matriciel, xN_vers_XLXH() ne fonctionne que lorsqu'on lui demande N = 2\n");
	getch();
	
	printf("<main> Test de xN_vers_XLXH():\nSaisir N (taille): ");
	scanf("%d", &taille);
	getchar();
	
	//Rendre pair
	if(taille % 2) taille++;
	printf("\n<main> Saisie de xN avec N = %d\n", taille);
	
	Complexe 
		*xN = malloc(sizeof(Complexe) * taille),
		**XLXH = NULL;
	for(i = 0; i < taille; i++)
	{
		printf("<main> Re(x[%d]) = ", i);
		scanf("%f", &xN[i].reel);
		getchar();
		
		printf("<main> Im(x[%d]) = ", i);
		scanf("%f", &xN[i].imaginaire);
		getchar();
	}
	
	/*printf("<main> Test de xN_vers_XLXH():\n");
	XLXH = xN_vers_XLXH(xN, taille, inverse);
	free(xN);
	
	Complexe 
		*XL = XLXH[0],
		*XH = XLXH[1];
	
	//Affichage des valeurs du test
	for(i = 0; i < taille / 2; i++)
	{
		printf("<main> XL[%d] = ", i); printComplexe(XL[i]); printf("\n");
		printf("<main> XH[%d] = ", i); printComplexe(XH[i]); printf("\n");
	}
	
	//Tracer le signal d'origine (test)/*
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
	
	libereTrace(&graphTCDBack);
	
	/*int hauteur, largeur;
	float 
		**Sinus = imageVersFloat("Sinus.bmp", &hauteur, &largeur),
		**tcdHeaders = safeMalloc(sizeof(float *) * hauteur);
	
	tcdHeaders = TCD2D(Sinus, largeur, hauteur, 0);
	
	trace *tcd2DGraph = safeMalloc(sizeof(trace) * hauteur);
	
	int i;
	for(i = 0; i < hauteur; i++)
	{
		tcd2DGraph[i].nbValeurs = largeur;
		tcd2DGraph[i].valeurs = tcdHeaders[i];
		minMax(&tcd2DGraph[i]);
	}
	
	traceFonctions2D(tcd2DGraph, "graphTCD2D.bmp", Oy);*/
	
	getch();
	return 0;
}
