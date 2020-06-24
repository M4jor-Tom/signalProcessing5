#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BmpLib.h"
#include "OutilsLib.h"
#include "signal.h"
#include "image.h"

double distance(double xDelta, double yDelta)
{
	return sqrt(xDelta * xDelta + yDelta * yDelta);
}

Image* circleTruncate(Image* input, unsigned int rInf, unsigned int rSup, bool exclude)
{
	if (rSup > rInf)
	{
		unsigned int
			x,
			y,
			centerAbcissa = input->largeur / 2,
			centerOrdinate = input->hauteur / 2;

		for(y = 0; y < input -> hauteur; y++)
			for (x = 0; x < input -> largeur; x++)
			{
				float distanceWithCenter = distance(x - centerAbcissa, y - centerOrdinate);
				if(
					distanceWithCenter < rSup && distanceWithCenter > rInf && !exclude ||	//In zone, AND must clear elsewhere OR
					distanceWithCenter > rSup && distanceWithCenter < rInf && exclude		//Out of zone, AND must clear In
				)
				{
					//Here, must reproduce image

				}
				else
				{
					//Here, must clear image
					input->rouge[y][x] = 0;
					input->vert[y][x] = 0;
					input->bleu[y][x] = 0;
					input->gris[y][x] = 0;
				}
			}
	}
	else
	{
		printf("<circleTruncate> Warning: Inferior ray must be inferior than superior. Input returned.\n");
	}
	return input;
}

Image* alloueImage(int largeur, int hauteur)
{
	//Mémoire qu'occupe une ligne / colonne
	int allocLargeur = sizeof(short) * largeur;
	int allocHauteur = sizeof(short*) * hauteur;	//Contiendra les en-têtes de chaque ligne

	//Allocation de mémoire
	Image* ptr_image = (Image *)safeMalloc(sizeof(Image), "alloueImage/couleur");
	ptr_image->rouge = (short **)safeMalloc(allocHauteur, "alloueImage/couleur");
	ptr_image->vert = (short **)safeMalloc(allocHauteur, "alloueImage/couleur");
	ptr_image->bleu = (short **)safeMalloc(allocHauteur, "alloueImage/couleur");
	ptr_image->gris = (short **)safeMalloc(allocHauteur, "alloueImage/couleur");

	int h;
	for (h = 0; h < hauteur; h++)
	{
		//Pour chaque ligne
		ptr_image->rouge[h] = (short *)safeMalloc(allocLargeur, "alloueImage/couleur[]");
		ptr_image->vert[h] = (short *)safeMalloc(allocLargeur, "alloueImage/couleur[]");
		ptr_image->bleu[h] = (short *)safeMalloc(allocLargeur, "alloueImage/couleur[]");
		ptr_image->gris[h] = (short *)safeMalloc(allocLargeur, "alloueImage/couleur[]");
	}

	//Set des paramètres
	ptr_image -> largeur = largeur;
	ptr_image -> hauteur = hauteur;

	return ptr_image;
}

void libereImage(Image** ptr_ptrImage)
{
	if(ptr_ptrImage != NULL)
	{
		if(*ptr_ptrImage != NULL)
		{
			int h;
			for (h = 0; h < (*ptr_ptrImage)->hauteur; h++)
			{
				if ((*ptr_ptrImage)->rouge != NULL)
					free((*ptr_ptrImage)->rouge[h]);

				if ((*ptr_ptrImage)->vert != NULL)
					free((*ptr_ptrImage)->vert[h]);

				if ((*ptr_ptrImage)->bleu != NULL)
					free((*ptr_ptrImage)->bleu[h]);

				if ((*ptr_ptrImage)->gris != NULL)
					free((*ptr_ptrImage)->gris[h]);
			}

			free((*ptr_ptrImage) -> rouge);
			free((*ptr_ptrImage) -> vert);
			free((*ptr_ptrImage) -> bleu);
			free((*ptr_ptrImage) -> gris);
			free(*ptr_ptrImage);
		}
		*ptr_ptrImage = NULL;
	}
}

Image* chargeImage(char* nom)
{
	DonneesImageRGB* ptr_donneesImage = lisBMPRGB(nom);
	Image* ptr_image = 
		alloueImage(
			ptr_donneesImage -> largeurImage,
			ptr_donneesImage -> hauteurImage
		);

	//Données d'image dans le fichier: Bleu, Vert, Rouge
	int h, pixel, totalPixel;
	for (h = 0, totalPixel = 0; h < ptr_donneesImage -> hauteurImage; h++)
		for (pixel = 0; pixel < ptr_donneesImage -> largeurImage; pixel++, totalPixel++)
		{
			//h est un en-tête de ligne, il y en a autant que de lignes, donc c'est une hauteur
			ptr_image -> bleu[h][pixel] = ptr_donneesImage -> donneesRGB[totalPixel * 3];
			ptr_image -> vert[h][pixel] = ptr_donneesImage -> donneesRGB[totalPixel * 3 + 1];
			ptr_image -> rouge[h][pixel] = ptr_donneesImage -> donneesRGB[totalPixel * 3 + 2];
			ptr_image -> gris[h][pixel] =
				0.2125 * (double)(ptr_image->rouge[h][pixel]) +
				0.7154 * (double)(ptr_image->vert[h][pixel]) +
				0.0721 * (double)(ptr_image->bleu[h][pixel]);
		}

	return ptr_image;
}

void sauveImage(Image* monImage, char* nom)
{
	DonneesImageRGB* ptr_donneesImage = (DonneesImageRGB *)safeMalloc(sizeof(DonneesImageRGB), "");
	int nIndex = 0;

	ptr_donneesImage -> donneesRGB = (unsigned char *)safeMalloc(sizeof(short) * monImage -> hauteur * monImage -> largeur * 3, "");

	int h, l;
	for(h = 0; h < monImage -> hauteur; h++)
		for (l = 0; l < monImage -> largeur; l++)
		{
			ptr_donneesImage -> donneesRGB[nIndex++] = monImage -> bleu[h][l];
			ptr_donneesImage -> donneesRGB[nIndex++] = monImage -> vert[h][l];
			ptr_donneesImage -> donneesRGB[nIndex++] = monImage -> rouge[h][l];
		}
	
	ptr_donneesImage -> hauteurImage = monImage -> hauteur;
	ptr_donneesImage -> largeurImage = monImage -> largeur;

	ecrisBMPRGB_Dans(ptr_donneesImage, nom);
	libereDonneesImageRGB(&ptr_donneesImage);
}

void sauveImageNG(Image* monImage, char* nom)
{
	DonneesImageRGB* ptr_donneesImage = (DonneesImageRGB *)safeMalloc(sizeof(DonneesImageRGB), "");
	int nIndex = 0;

	ptr_donneesImage->donneesRGB = (short *)safeMalloc(sizeof(short) * monImage->hauteur * monImage->largeur * 3, "");

	int h, l;
	for (h = 0; h < monImage->hauteur; h++)
		for (l = 0; l < monImage->largeur; l++)
		{
			ptr_donneesImage->donneesRGB[nIndex++] = monImage->gris[h][l];
			ptr_donneesImage->donneesRGB[nIndex++] = monImage->gris[h][l];
			ptr_donneesImage->donneesRGB[nIndex++] = monImage->gris[h][l];
		}

	ptr_donneesImage->hauteurImage = monImage->hauteur;
	ptr_donneesImage->largeurImage = monImage->largeur;

	ecrisBMPRGB_Dans(ptr_donneesImage, nom);
	libereDonneesImageRGB(&ptr_donneesImage);
}

Image* dupliqueImage(Image* monImage)
{
	Image* ptr_imageBis = alloueImage(monImage -> largeur, monImage -> hauteur);

	ptr_imageBis -> largeur = monImage -> largeur;
	ptr_imageBis -> hauteur = monImage -> hauteur;

	int h, l;
	for(h = 0; h < monImage -> hauteur; h++)
		for(l = 0; l < monImage -> largeur; l++)
		{
			ptr_imageBis -> rouge[h][l] = monImage -> rouge[h][l];
			ptr_imageBis -> vert[h][l] = monImage -> vert[h][l];
			ptr_imageBis -> bleu[h][l] = monImage -> bleu[h][l];
			ptr_imageBis -> gris[h][l] = monImage -> gris[h][l];
		}

	return ptr_imageBis;
}

Image* differenceImage(Image* image1, Image* image2)
{
	Image* ptr_imageDiff = alloueImage(image1->largeur, image1->hauteur);

	ptr_imageDiff->largeur = image1->largeur;
	ptr_imageDiff->hauteur = image1->hauteur;

	int h, l;
	for (h = 0; h < image1->hauteur; h++)
		for (l = 0; l < image1->largeur; l++)
		{
			ptr_imageDiff->rouge[h][l] = abs(image1->rouge[h][l] - image2->rouge[h][l]);
			ptr_imageDiff->vert[h][l] = abs(image1->vert[h][l] - image2->vert[h][l]);
			ptr_imageDiff->bleu[h][l] = abs(image1->bleu[h][l] - image2->bleu[h][l]);
			ptr_imageDiff->gris[h][l] = abs(image1->gris[h][l] - image2->gris[h][l]);
		}

	return ptr_imageDiff;
}

void testAlloueImage(Image* ptr_image)
{
	int h, l;
	for (h = 0; h < ptr_image->hauteur; h++)
		for (l = 0; l < ptr_image->largeur; l++)
		{
			ptr_image->rouge[h][l] = (h * l) * 255 / (ptr_image->hauteur * ptr_image->largeur);
			ptr_image->vert[h][l] = ((ptr_image->hauteur - h) * (ptr_image->largeur - l)) * 255 / (ptr_image->hauteur * ptr_image->largeur);
			ptr_image->bleu[h][l] = (h * (ptr_image->largeur - l)) * 255 / (ptr_image->hauteur * ptr_image->largeur) +
				((ptr_image->hauteur - h) * l) * 255 / (ptr_image->hauteur * ptr_image->largeur);
			ptr_image->gris[h][l] = (h * l) * 255 / (ptr_image->hauteur * ptr_image->largeur);
		}
}
