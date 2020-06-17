#include <stdlib.h>

#include "signal2D.h"

void traceFonction2D(trace fonction, char *fichier, int axe)
{
	//Création de l'image
	Image* ptr_image = alloueImage(fonction.nbValeurs, fonction.nbValeurs);
	
	int pixelAbcisse;
	for(pixelAbcisse = 0; pixelAbcisse < fonction.nbValeurs; pixelAbcisse++)
	{
		//Remplir toute l'image
		int pixelOrdonnee, _intensite;
		for(pixelOrdonnee = 0; pixelOrdonnee < fonction.nbValeurs; pixelOrdonnee++)
		{
			int 
				tempPixelAbcisse = axe == Oy
					? pixelAbcisse
					: pixelOrdonnee,
				tempPixelOrdonnee = axe == Oy
					? pixelOrdonnee
					: pixelAbcisse;
			
			unsigned short int intensite = (unsigned short int)((fonction.valeurs[pixelOrdonnee] - fonction.vMin) / (fonction.vMax - fonction.vMin) * 128.0);
				
			tracePoint(ptr_image, tempPixelAbcisse, tempPixelOrdonnee, "noir", intensite);
		}
	}
	
	sauveImage(ptr_image, fichier);

	libereImage(&ptr_image);
}

Complexe **imageVersComplexe(char *baseName, unsigned int *hauteur, unsigned int *largeur)
{
	Image *ptr_image = chargeImage(baseName);
	Complexe **ret = (Complexe **)safeMalloc(sizeof(Complexe *) * ptr_image -> hauteur);
	
	int i, j;
	for(i = 0; i < ptr_image -> hauteur; i++)
	{
		ret[i] = (Complexe *)safeMalloc(sizeof(Complexe) * ptr_image -> largeur);
		for(j = 0; j < ptr_image -> largeur; j++)
		{
			ret[i][j].reel = ptr_image -> gris[i][j];
			ret[i][j].imaginaire = 0.0;
		}
	}
	
	if(hauteur != NULL)
		*hauteur = ptr_image -> hauteur;
	if(largeur != NULL)
		*largeur = ptr_image -> largeur;
	
	libereImage(&ptr_image);
	return ret;
}
