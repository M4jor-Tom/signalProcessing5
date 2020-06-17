#include "TCD2D.h"

float **TCD2D(float **xN, int tailleL, int tailleH, int inverse)
{
	tailleL = biggestSmallerBits(tailleL);
	tailleH = biggestSmallerBits(tailleH);
	
	float **XN = (float **)malloc(sizeof(float *) * tailleH);
	
	int i;
	for(i = 0; i < tailleH; i++)
	{
		XN[i] = (float *)malloc(sizeof(float) * tailleL);
		XN[i] = TCD(xN[i], tailleL, inverse);
	}
	
	XN = transposee(XN, tailleH, tailleL);
	
	for(i = 0; i < tailleH; i++)
		XN[i] = TCD(xN[i], tailleL, inverse);
	
	return XN;
}

float **transposeeTCD(float **mat, int taille1, int taille2)
{
	//Allocation lignes
	float **ret = (float **)malloc(sizeof(float * ) * taille1);
	
	int i, j;
	for(i = 0; i < taille1; i++)
		//Allocation cases
		ret = (float *)malloc(sizeof(float) * taille2);
	
	for(i = 0; i < taille1; i++)
		for(j = 0; j < taille2; j++)
			//Transposition
			ret[i][j] = mat[j][i];
	
	//Libération de lignes + cases entrée
	for(i = 0; i < taille1; i++)
		free(mat[i]);
		
	free(mat);
			
	return ret;
}
