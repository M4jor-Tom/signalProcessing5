#define PI 3.14156

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FFT.h"

Complexe *FFT(Complexe *xN, int taille, int inverse)
{
	taille = biggestSmallerBits(taille);
	if(taille == 2)
	{
		//retour simple (calcul)
		Complexe *XN = (Complexe *)safeMalloc(sizeof(Complexe) * taille/* == 2*/);
		
		
		memset(XN, 0, sizeof(Complexe) * taille);
		
		
		XN[0] = somme2(xN[0], xN[1]);
		XN[1] = soustraction2(xN[0], xN[1]);
		
		return XN;
	}
	else if(taille > 2)
	{
		Complexe 
			*X = (Complexe *)safeMalloc(sizeof(Complexe) * taille),
			
			//Division du travail
			**xpxi = xN_vers_xpxi(xN, taille),
			
			//calcul XP et XI
			*XP = FFT(xpxi[0], taille / 2, inverse),
			*XI = FFT(xpxi[1], taille / 2, inverse);

		int i;
		for(i = 0; i < taille / 2; i++)
		{
			//printf("<FFT> "); printComplexe(XP[i]); printComplexe(XI[i]); printf(" [%d]\n", taille);
			XP[i] = produit2(XP[i], W(i, taille / 2, inverse));
			XI[i] = produit2(XI[i], W(i, taille / 2, inverse));
		}
		//printf("_________________________\n");
		
		Complexe **XLXH = XPXI_vers_XLXH(XP, XI, taille, inverse);
		
		for(i = 0; i < taille; i++)
			if(i < taille / 2)
				X[i] = XLXH[0][i];
			else
				X[i] = XLXH[1][i - taille / 2];
		
		free(XLXH[0]);
		free(XLXH[1]);
		free(XLXH);
		free(XP);
		free(XI);
		
		return X;
	}
	else
		//Erreur
		return (Complexe *)NULL;
}
