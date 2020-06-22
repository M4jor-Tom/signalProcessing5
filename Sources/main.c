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
#define horizontal 0
#define vertical 1

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
#include <math.h>

int main()
{
	system("color F0");

	Complexe
		*xN = NULL,
		*XN = NULL,
		**xN2D = NULL,
		**XN2D = NULL;
	trace 
		temporalGraph,
		fftGraph,
		*temporalGraph2D = NULL,
		*fftGraph2D = NULL;
	float frequency;
	int periodsCount, i;
	short int 
		reverse = 0,
		dimensions = 1,
		signalForm = SINUS,
		axis = horizontal;
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
			switch (getche())
			{

				case '1':
				case '&':
					//Wanted temporal
					getFft = false;

				case '2':
				case 'é':
					//Wanted FFT or temporal
					printf("\n\nSignal form:\n\t1.Sinus\n\t2.Cosinus\n\t3.Rectangle\n");

					do
					{
						if (redo)
							printf("\rPlease re-select: ");
						else printf("Please select: ");
						redo = false;

						switch(getche())
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

					printf("\n\nSignal dimensions:\n\t1.Graphic (1 dimension)\n\t2.Image (2 dimensions)\n");

					do
					{
						if (redo)
							printf("\rPlease re-select: ");
						else printf("Please select: ");
						redo = false;

						switch (getche())
						{
							case '1':
							case '&':
								dimensions = 1;
								break;

							case '2':
							case 'é':
								dimensions = 2;

								printf("\n\nPlease select an axis:\n1.Horizontal\n2.Vertical\n");
								do
								{
									if (redo)
										printf("\rPlease re-select: ");
									else printf("Please select: ");
									redo = false;

									switch (getche())
									{
										case '1':
										case '&':
											axis = horizontal;
											break;

										case '2':
										case 'é':
											axis = vertical;
											break;

										default:
											redo = true;
									}

								} while (redo);
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

					if (dimensions == 1)
					{
						//1D
						xN = safeMalloc(sizeof(Complexe) * temporalGraph.nbValeurs);

						if(getFft)
						{
							//FFT
							//Initialize FFT values
							fftGraph.nbValeurs = biggestSmallerBits(temporalGraph.nbValeurs);
							XN = safeMalloc(sizeof(Complexe) * fftGraph.nbValeurs);
							fftGraph.valeurs = safeMalloc(sizeof(double) * fftGraph.nbValeurs);

							//Prepare FFT input values
							for (i = 0; i < fftGraph.nbValeurs; i++)
							{
								xN[i].reel = (float)temporalGraph.valeurs[i];
								xN[i].imaginaire = 0.0;
							}

							//Proceed FFT
							XN = FFT(xN, fftGraph.nbValeurs, reverse);
							for (i = 0; i < fftGraph.nbValeurs; i++)
								fftGraph.valeurs[i] = (float)raison(XN[i]);

							//Prepare and trace
							minMax(&fftGraph);
							traceFonction(fftGraph, "graph.bmp");

							//Free memory
							free(XN);
						}
						else
							//TEMP
							traceFonction(temporalGraph, "graph.bmp");

						free(xN);
					}
					else
					{
						//2D
						xN2D = safeMalloc(sizeof(Complexe *) * temporalGraph.nbValeurs);
						if(getFft)
							XN2D = safeMalloc(sizeof(Complexe*) * temporalGraph.nbValeurs);

						for (i = 0; i < temporalGraph.nbValeurs; i++)
						{
							xN2D[i] = safeMalloc(sizeof(Complexe) * temporalGraph.nbValeurs);
							if (getFft)
								XN2D[i] = safeMalloc(sizeof(Complexe) * temporalGraph.nbValeurs);
						}

						if (getFft)
						{
							//FFT
							XN2D = FFT2D(xN2D, temporalGraph.nbValeurs, temporalGraph.nbValeurs, reverse);
						}
						else
						{
							//TEMP
							temporalGraph2D = safeMalloc(sizeof(trace) * temporalGraph.nbValeurs);
							for (i = 0; i < temporalGraph.nbValeurs; i++)
								temporalGraph2D[i] = temporalGraph;

							traceFonctions2D(temporalGraph2D, "graph.bmp", axis);
						}

						for (i = 0; i < temporalGraph.nbValeurs; i++)
							free(xN2D[i]);
						free(xN2D);
					}

					//libereTrace(&temporalGraph);
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
	
	getch();
	return 0;
}
