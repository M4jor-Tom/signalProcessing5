#include "FFT2D.h"

Complexe **FFT2D(Complexe **xN, int tailleL, int tailleH, int inverse)
{
	tailleL = biggestSmallerBits(tailleL);
	tailleH = biggestSmallerBits(tailleH);
	
	Complexe **XN = (Complexe **)malloc(sizeof(Complexe *) * tailleH);
	
	int i;
	for(i = 0; i < tailleH; i++)
	{
		XN[i] = (Complexe *)malloc(sizeof(Complexe) * tailleL);
		XN[i] = FFT(xN[i], tailleL, inverse);
	}
	
	XN = transposee(XN, tailleH, tailleL);
	
	for(i = 0; i < tailleH; i++)
		XN[i] = FFT(xN[i], tailleL, inverse);
	
	return XN;
}

Complexe **transposee(Complexe **mat, int taille1, int taille2)
{
	//Allocation lignes
	Complexe **ret = (Complexe **)malloc(sizeof(Complexe * ) * taille1);
	
	int i, j;
	for(i = 0; i < taille1; i++)
		//Allocation cases
		ret = (Complexe *)malloc(sizeof(Complexe) * taille2);
	
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
