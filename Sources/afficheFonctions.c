#define PI 3.1415
#define PIXELS_PAR_UNITES 100
#define flatTreshold (long long)15

#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include "image.h"
#include "afficheFonctions.h"

void initialiseRepereCentre(Image* ptr_image)
{
	short colonneRepere = 0, ligneRepere = 0;
	int h, l;
	printf("<initialiseRepereCentre>\n\tHauteur: [%d-%d]\n\tLargeur: [%d-%d]\n", 0, ptr_image->hauteur, 0, ptr_image->largeur);
	for (h = 0; h < ptr_image->hauteur; h++)
		for (l = 0; l < ptr_image->largeur; l++)
		{
			if(l == ptr_image->largeur / 2)
				colonneRepere = l;
			if(h == ptr_image->hauteur / 2)
				ligneRepere = h;
			short repere = (h == ptr_image->hauteur / 2 || l == ptr_image->largeur / 2)
				? 0
				: 255;
			ptr_image->rouge[h][l] = repere;
			ptr_image->vert[h][l] = repere;
			ptr_image->bleu[h][l] = repere;
			ptr_image->gris[h][l] = repere;
		}
	/*printf(
		"<initialiseRepereCentre> Repere: Colonne %d sur %d / Ligne %d sur %d\n",
		colonneRepere,
		ptr_image->largeur,
		ligneRepere,
		ptr_image->hauteur
	);*/
}

int tracePoint(Image *ptr_image, int pixelOrdonnee, int pixelAbcisse, char *couleur, unsigned short int couleurMini)
{
	if(!strcmp(couleur, "noir"))
	{
		ptr_image->rouge[pixelOrdonnee][pixelAbcisse] = couleurMini;
		ptr_image->bleu[pixelOrdonnee][pixelAbcisse] = couleurMini;
		ptr_image->vert[pixelOrdonnee][pixelAbcisse] = couleurMini;
		ptr_image->gris[pixelOrdonnee][pixelAbcisse] = couleurMini;
	}
	else if(!strcmp(couleur, "rouge"))
	{
		ptr_image->rouge[pixelOrdonnee][pixelAbcisse] = 255;
		ptr_image->bleu[pixelOrdonnee][pixelAbcisse] = couleurMini;
		ptr_image->vert[pixelOrdonnee][pixelAbcisse] = couleurMini;
		ptr_image->gris[pixelOrdonnee][pixelAbcisse] = couleurMini;
	}
	else if(!strcmp(couleur, "vert"))
	{
		ptr_image->rouge[pixelOrdonnee][pixelAbcisse] = couleurMini;
		ptr_image->bleu[pixelOrdonnee][pixelAbcisse] = couleurMini;
		ptr_image->vert[pixelOrdonnee][pixelAbcisse] = 255;
		ptr_image->gris[pixelOrdonnee][pixelAbcisse] = couleurMini;
	}
	else if(!strcmp(couleur, "bleu"))
	{
		ptr_image->rouge[pixelOrdonnee][pixelAbcisse] = couleurMini;
		ptr_image->bleu[pixelOrdonnee][pixelAbcisse] = 255;
		ptr_image->vert[pixelOrdonnee][pixelAbcisse] = couleurMini;
		ptr_image->gris[pixelOrdonnee][pixelAbcisse] = couleurMini;
	}
	else 
	{
		printf("<tracePoint> Error: Couleur inconnue: %s", couleur);
		return 0;
	}
	return 1;
}

void printTrace(trace graph)
{
	int i;
	for(i = 0; i < graph.nbValeurs; i++)
	{
		printf("<printTrace> %d: %.2f [%.2f;%.2f]\n", i, graph.valeurs[i], graph.vMin, graph.vMax);
	}
}

void flatTrace(trace *ptr_graph)
{
	int i;
	if(ptr_graph -> vMin < flatTreshold * -1)
		for(i = 0; i < ptr_graph -> nbValeurs; i++)
			if(ptr_graph -> valeurs[i] <  flatTreshold * -1)
			{
				ptr_graph -> valeurs[i] = flatTreshold * -1;
				ptr_graph -> vMin = flatTreshold * -1;
			}
		
	if(ptr_graph -> vMax > flatTreshold)
		for(i = 0; i < ptr_graph -> nbValeurs; i++)
			if(ptr_graph -> valeurs[i] > flatTreshold)
			{
				ptr_graph -> valeurs[i] = flatTreshold;
				ptr_graph -> vMax = flatTreshold;
			}
}

void traceFonction(trace fonction, char *fichier)
{
	flatTrace(&fonction);
	printTrace(fonction);
	//Création de l'image
	int 
		largeurImagePixels = fonction.nbValeurs, 
		hauteurImagePixels = (int)(((fonction.vMax - fonction.vMin) * 1.01) * (double)PIXELS_PAR_UNITES),
		axeAbcisse = hauteurImagePixels / 2;
		
	Image* ptr_image = alloueImage(largeurImagePixels, hauteurImagePixels);
	//Insertion du repère
	initialiseRepereCentre(ptr_image);
	
	int pixelAbcisse, pixelOrdonneePrecedentTrace = (int)(fonction.valeurs[0] * PIXELS_PAR_UNITES) + axeAbcisse;
	printf("%d\n\n", pixelOrdonneePrecedentTrace);
	for(pixelAbcisse = 0; pixelAbcisse < fonction.nbValeurs; pixelAbcisse++)
	{
		int 
			pixelOrdonnee = (int)(fonction.valeurs[pixelAbcisse] * PIXELS_PAR_UNITES),
			pixelOrdonneeTrace = pixelOrdonnee + axeAbcisse;
			
		printf("[%d;%d]\n", pixelAbcisse, pixelOrdonneeTrace);
		
		tracePoint(ptr_image, pixelOrdonneeTrace, pixelAbcisse, "noir", 0);
		
		//Relier les points
		while(pixelOrdonneePrecedentTrace != pixelOrdonneeTrace)
		{
			if(pixelOrdonneePrecedentTrace < pixelOrdonneeTrace)
				pixelOrdonneePrecedentTrace++;
			else
				pixelOrdonneePrecedentTrace--;
			
			tracePoint(ptr_image, pixelOrdonneePrecedentTrace, pixelAbcisse, "noir", 0);
		}
		
		pixelOrdonneePrecedentTrace = pixelOrdonneeTrace;
	}
	
	sauveImage(ptr_image, fichier);

	libereImage(&ptr_image);
}

void donneesTrace(trace fonction)
{
	printf("<donneesTrace> Info:\n\t%d valeurs\n\tvMax = %.2f\n\tvMin = %.2f\n", fonction.nbValeurs, fonction.vMax, fonction.vMin);
}
