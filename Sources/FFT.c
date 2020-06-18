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
			*XN = (Complexe *)safeMalloc(sizeof(Complexe) * taille/* == 2*/);
			//**Tn = TN(taille, inverse),
			//*XLXH = (Complexe *)safeMalloc(sizeof(Complexe) * taille/* == 2*/);
		
		
		memset(XN, 0, sizeof(Complexe) * taille);
		
		/*int k, n;
		for(k = 0; k < taille; k++)
			for(n = 0; n < taille; n++)
				XN[k] = 
					somme2(
						XN[k],
						produit2(Tn[k][n], xN[k])
					);*/
		
		
		XN[0] = somme2(xN[0], xN[1]);
		XN[1] = soustraction2(xN[0], xN[1]);
		
					
		/*for(k = 0; k < taille; k++)
			_free(Tn[k]);
		_free(Tn);*/
		
		return XN;
	}
	else if(taille > 2)
	{
		Complexe 
			*X = (Complexe *)safeMalloc(sizeof(Complexe) * taille),
			
			//Division du travail
			**xpxi = xN_vers_xpxi(xN, taille),
			
			//calcul XP et XI
			*XP = FFT(xpxi[0], taille / 2, inverse), // *wn
			*XI = FFT(xpxi[1], taille / 2, inverse); // *wn
		
		int i;
		for(i = 0; i < taille / 2; i++)
		{
			XP[i] = produit2(XP[i], W(i, taille / 2, inverse));
			XI[i] = produit2(XI[i], W(i, taille / 2, inverse));
		}
		
		Complexe **XLXH = XPXI_vers_XLXH(XP, XI, taille, inverse);
		
		for(i = 0; i < taille; i++)
			if(i < taille / 2)
				X[i] = XLXH[0][i];
			else
				X[i] = XLXH[1][i - taille / 2];
		
		_free(XLXH[0]);
		_free(XLXH[1]);
		_free(XLXH);
		_free(XP);
		_free(XI);
		
		return X;
	}
	else
		//Erreur
		return (Complexe *)NULL;
}
