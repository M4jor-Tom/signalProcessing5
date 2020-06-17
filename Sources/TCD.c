#define PI 3.14156

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "TCD.h"

float *TCD(float *xN, int taille, int inverse)
{
	//FUK HERE
	printf("%d\n", taille);
	taille = biggestSmallerBits(taille);
	if(taille == 2)
	{
		printf("<TCD> proc init\n");
		//retour simple (calcul)
		float 
			*XN = (float *)malloc(sizeof(float) * taille/* == 2*/),
			**Tn = tcdTN(taille, inverse);
		
		printf("<TCD> proc inter\n");
		memset(XN, 0, sizeof(float) * taille);
		
		int k, n;
		for(k = 0; k < taille; k++)
			for(n = 0; n < taille; n++)
				XN[k] = XN[k] + Tn[k][n] * xN[k];
		
		for(k = 0; k < taille; k++)
			free(Tn[k]);
		free(Tn);
		
		printf("<TCD> proc end\n");
		return XN;
	}
	else if(taille > 2)
	{
		printf("<TCD> rec init\n");
		float
			*X = (float *)malloc(sizeof(float) * taille),
		
		//Division du travail
			**xpxi = tcdxN_vers_xpxi(xN, taille),
		
		//calcul XP et XI
			*XP = TCD(xpxi[0], taille / 2, inverse),
			*XI = TCD(xpxi[1], taille / 2, inverse);
		printf("<TCD> rec post proc\n");
		
		if(XP == NULL || XI == NULL) 
			printf("<TCD> Error: biggestSmallerBits bugged\n");
		
		int i;
		for(i = 0; i < taille; i++)
			if(i < taille / 2)
				X[i] = XP[i];
			else
				X[i] = XI[i - taille / 2];
		printf("<TCD> rec post ordening\n");
		
		/*free(xpxi[0]);
		free(xpxi[1]);
		free(xpxi);
		
		free(XP);
		free(XI);*/
		printf("<TCD> rec end\n");
		
		return X;
	}
	else
		//Erreur
		return (float *)NULL;
}
