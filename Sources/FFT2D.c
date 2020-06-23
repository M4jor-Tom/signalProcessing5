#include "FFT2D.h"

Complexe **FFT2D(Complexe **xN, int tailleL, int tailleH, int inverse)
{
	tailleL = biggestSmallerBits(tailleL);
	tailleH = biggestSmallerBits(tailleH);
	
	Complexe **XN = (Complexe **)safeMalloc(sizeof(Complexe *) * tailleH, "FFT2D");
	
	int i;
	for(i = 0; i < tailleH; i++)
	{
		XN[i] = (Complexe *)safeMalloc(sizeof(Complexe) * tailleL, "FFT2D");
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
	Complexe **ret = (Complexe **)safeMalloc(sizeof(Complexe * ) * taille1, "transposee/Init");
	
	int i, j;
	for(i = 0; i < taille1; i++)
		//Allocation cases
		ret = (Complexe *)safeMalloc(sizeof(Complexe) * taille2, "transposee/grid");
	
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
