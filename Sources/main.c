#define _CRT_SECURE_NO_WARNINGS

#include <conio.h>
#ifdef _MSC_VER
	#define getch() _getch()
	#define getche() _getche()
#endif

#define PIXELS_PAR_UNITES 100

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

	FILE* testFilePtr;
	trace 
		temporalGraph,
		fftGraph,
		*temporalGraph2D = NULL,
		*fftGraph2D = NULL;
	Complexe
		*xN = NULL,
		*XN = NULL,
		**xN2D = NULL,
		**XN2D = NULL;
	float frequency;
	unsigned int
		imageHeight = 0,
		imageWidth = 0,
		outPutHeight = 0,
		outPutWidth = 0;
	int periodsCount, i, j;
	char fileName[1000] = "\0";
	short int 
		reverse = 0,
		dimensions = 1,
		signalForm = SINUS,
		axis = horizontal;
	bool 
		leave = false,
		getFft = true,
		grabParameters = true;

	memset(&temporalGraph, 0, sizeof(trace));
	memset(&fftGraph, 0, sizeof(trace));

	do
	{
		system("cls");

		//Grabbing process

		bool redo = false;
		printf("Work mode:\n1.Temporal signals\n2.Fourier transform/reversing\n3.Leave\n\n");
		do
		{
			if (redo)
				printf("\rPlease re-select: ");
			else printf("Please select: ");
			redo = false;
			getFft = true;

			//Processing query
			switch (getche())
			{

				case '1':
				case '&':
					//Wanted temporal
					getFft = false;

				case '2':
				case 'é':
					if (getFft)
					{
						printf("\n\nWork from:\n1.Parameters set\n2.Existing file\n");
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
									grabParameters = true;
									break;

								case '2':
								case 'é':
									grabParameters = false;
									printf("\n\nFile name:\n");
									//Get file name
									do
									{
										if (redo)
											printf("\rPlease re-select: ");
										else printf("Please select: ");
										redo = false;

										scanf("%s", fileName);
										testFilePtr = fopen(fileName, "r");

										if(testFilePtr == NULL)
											redo = true;
										else
											fclose(testFilePtr);
									}while(redo);

									printf("\n\nWich process ?\n1.FFT-ize\n2.Reverse FFT\n");
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
												reverse = 0;
												break;

											case '2':
											case 'é':
												reverse = 1;
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
					}

					if (grabParameters)
					{
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

						printf("\n\nOutput image dimensions:\n\t1.Graphic (1 dimension)\n\t2.Image (2 dimensions)\n");

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
						outPutWidth = temporalGraph.nbValeurs;
						outPutHeight = (temporalGraph.vMax - temporalGraph.vMin) * PIXELS_PAR_UNITES;
					}
					else
					{
						//Get graph from file
						xN2D = imageVersComplexe(fileName, &imageHeight, &imageWidth);
						dimensions = 2;
						outPutWidth = imageWidth;
						outPutHeight = imageWidth;
					}

					if(getFft)
						outPutWidth = biggestSmallerBits(outPutWidth);


					if (dimensions == 1)
					{
						//1D
						xN = safeMalloc(sizeof(Complexe) * temporalGraph.nbValeurs, "main/xN 1D");

						if(getFft)
						{
							//FFT
							//Initialize FFT values
							fftGraph.nbValeurs = biggestSmallerBits(temporalGraph.nbValeurs);
							XN = safeMalloc(sizeof(Complexe) * fftGraph.nbValeurs, "main/FFT xN");
							fftGraph.valeurs = safeMalloc(sizeof(double) * fftGraph.nbValeurs, "main/FFT graph");

							//Prepare FFT input values
							for(i = 0; i < fftGraph.nbValeurs; i++)
							{
								xN[i].reel = (float)temporalGraph.valeurs[i];
								xN[i].imaginaire = (float)temporalGraph.valeurs[i];//0.0;
							}

							//Proceed FFT
							XN = FFT(xN, fftGraph.nbValeurs, reverse, fftGraph.nbValeurs);
							printf("\n");

							for(i = 0; i < fftGraph.nbValeurs; i++)
								fftGraph.valeurs[i] = (float)raison(XN[i]);

							//Prepare and trace
							minMax(&fftGraph);
							traceFonction(fftGraph, "graph.bmp", !getFft);

							//Free memory
							free(XN);
						}
						else
							//TEMP
							traceFonction(temporalGraph, "graph.bmp", !getFft);

						free(xN);
					}
					else
					{
						//2D
						if (grabParameters)
						{
							xN2D = safeMalloc(sizeof(Complexe *) * outPutHeight, "main/FFT2D xN");
							temporalGraph2D = valeursMat(signalForm, frequency, periodsCount);

							if(xN2D != NULL)
								for (i = 0; i < outPutWidth; i++)
								{
									xN2D[i] = safeMalloc(sizeof(Complexe) * outPutWidth, "main/FFT2D xN[]");
									for (j = 0; j < outPutWidth; j++)
									{
										xN2D[i][j].reel = temporalGraph2D[i].valeurs[j];
										xN2D[i][j].imaginaire = temporalGraph2D[i].valeurs[j];
									}
								}

						}

						if (getFft)
						{
							//FFT
							XN2D = FFT2D(xN2D, outPutWidth, outPutWidth, reverse, outPutWidth);

							fftGraph2D = safeMalloc(sizeof(trace) * outPutWidth, "main/FFT 2D graph");
							for(i = 0; i < outPutWidth; i++)
							{
								fftGraph2D[i].nbValeurs = outPutWidth;
								fftGraph2D[i].valeurs = safeMalloc(sizeof(double) * outPutWidth, "main/FFT 2D graph values");

								for(j = 0; j < fftGraph2D[i].nbValeurs; j++)
									fftGraph2D[i].valeurs[j] = raison(XN2D[i][j]);
								minMax(&fftGraph2D[i]);

							}
							traceFonctions2D(fftGraph2D, "graph.bmp", axis, false);
						}
						else
						{
							if (!grabParameters)
							{
								printf("<main> Something is going to happen, but I don't know what.\n\t- Eminem -\n\n");
								getch();
							}

							//TEMP
							temporalGraph2D = safeMalloc(sizeof(trace) * outPutWidth, "main/temp2D graph");
							for (i = 0; i < outPutWidth; i++)
								temporalGraph2D[i] = temporalGraph;

							traceFonctions2D(temporalGraph2D, "graph.bmp", axis, !getFft);
						}

						if(xN2D != NULL)
						{
							for (i = 0; i < outPutWidth; i++)
								free(xN2D[i]);
							free(xN2D);
						}
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
