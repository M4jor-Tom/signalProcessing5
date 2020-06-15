#pragma once

typedef struct Image
{
	int largeur, hauteur;
	short **rouge, **vert, **bleu, **gris;
}Image;

Image* alloueImage(int largeur, int hauteur);
void libereImage(Image** ptrImage);
Image* chargeImage(char* nom);
void sauveImage(Image* monImage, char* nom);
void sauveImageNG(Image* monImage, char* nom);
Image *dupliqueImage(Image* monImage);
Image* differenceImage(Image* image1, Image* image2);
void testAlloueImage(Image* ptr_image);
