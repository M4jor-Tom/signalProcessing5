#define PI 3.14156

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
		Complexe 
			*XN = (Complexe *)safeMalloc(sizeof(Complexe) * taille/* == 2*/),
			**Tn = TN(taille, inverse),
			**XLXH = NULL;
		
		//Calcul matriciel
		/*XLXH = xN_vers_XLXH(xN, taille, inverse);
		XN[0] = XLXH[0][0];
		XN[1] = XLXH[1][0];*/
		
		memset(XN, 0, sizeof(Complexe) * taille);
		
		int k, n;
		for(k = 0; k < taille; k++)
			for(n = 0; n < taille; n++)
				XN[k] = 
					somme2(
						XN[k],
						produit2(Tn[k][n], xN[k])
					);
					
		for(k = 0; k < taille; k++)
			_free(Tn[k]);
		_free(Tn);
		
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
		for(i = 0; i < taille; i++)
			if(i < taille / 2)
				X[i] = XP[i];
			else
				X[i] = XI[i - taille / 2];
		
		_free(XP);
		_free(XI);
		
		return X;
	}
	else
		//Erreur
		return (Complexe *)NULL;
}
