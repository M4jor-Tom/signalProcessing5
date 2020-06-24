#include <stdlib.h>

#include "afficheFonctions.h"
#include "signal2D.h"

void traceFonctions2D(trace *fonction, char *fichier, int axe, bool temporal)
{
	//Pre-treatment
	if(!temporal)
	{
		unsigned int i, originalWidth = fonction[0].nbValeurs;
		for (i = 0; i < originalWidth; i++)
			truncate(&fonction[i], 50);
	}

	//Création de l'image
	Image* ptr_image = alloueImage(fonction[0].nbValeurs, fonction[0].nbValeurs);
	
	int pixelAbcisse;
	for(pixelAbcisse = 0; pixelAbcisse < fonction[0].nbValeurs; pixelAbcisse++)
	{
		//Remplir toute l'image
		int pixelOrdonnee, _intensite;
		for(pixelOrdonnee = 0; pixelOrdonnee < fonction[pixelAbcisse].nbValeurs; pixelOrdonnee++)
		{
			int 
				tempPixelAbcisse = axe == Oy
					? pixelAbcisse
					: pixelOrdonnee,
				tempPixelOrdonnee = axe == Oy
					? pixelOrdonnee
					: pixelAbcisse;
			
			unsigned short int intensite = (unsigned short int)((fonction[pixelAbcisse].valeurs[pixelOrdonnee] - fonction[pixelAbcisse].vMin) / (fonction[pixelAbcisse].vMax - fonction[pixelAbcisse].vMin) * 128.0);
				
			tracePoint(ptr_image, tempPixelAbcisse, tempPixelOrdonnee, "noir", intensite);
		}
	}
	
	sauveImage(ptr_image, fichier);

	libereImage(&ptr_image);
}

float **imageVersFloat(char *baseName, unsigned int *hauteur, unsigned int *largeur)
{
	Image *ptr_image = chargeImage(baseName);
	float **ret = (float **)safeMalloc(sizeof(float *) * ptr_image -> hauteur, "imageVersFloat");
	
	int i, j;
	for(i = 0; i < ptr_image -> hauteur; i++)
	{
		ret[i] = (float *)safeMalloc(sizeof(float) * ptr_image -> largeur, "imageVersFloat");
		for(j = 0; j < ptr_image -> largeur; j++)
		{
			ret[i][j] = ptr_image -> gris[i][j];
		}
	}
	
	if(hauteur != NULL)
		*hauteur = ptr_image -> hauteur;
	if(largeur != NULL)
		*largeur = ptr_image -> largeur;
	
	libereImage(&ptr_image);
	return ret;
}

Complexe **imageVersComplexe(char *baseName, unsigned int *hauteur, unsigned int *largeur)
{
	Image *ptr_image = chargeImage(baseName);
	Complexe **ret = (Complexe **)safeMalloc(sizeof(Complexe *) * ptr_image -> hauteur, "imageVersComplexe");
	
	int i, j;
	for(i = 0; i < ptr_image -> hauteur; i++)
	{
		ret[i] = (Complexe *)safeMalloc(sizeof(Complexe) * ptr_image -> largeur, "imageVersComplexe");
		for(j = 0; j < ptr_image -> largeur; j++)
		{
			ret[i][j].reel = ptr_image -> gris[i][j];
			ret[i][j].imaginaire = ptr_image->gris[i][j];
		}
	}
	
	if(hauteur != NULL)
		*hauteur = ptr_image -> hauteur;
	if(largeur != NULL)
		*largeur = ptr_image -> largeur;
	
	libereImage(&ptr_image);
	return ret;
}
