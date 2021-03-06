#define PI 3.14156
#include <conio.h>
#ifdef _MSC_VER
#define getch() _getch()
#define getche() _getche()
#endif

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "signal.h"


void *safeMalloc(int sizeof_, char *parent)
{
	void *ptr = malloc(sizeof_);
	if(ptr == NULL)
	{
		printf("<safeMalloc> Error in %s: NULL return", parent);
		exit(1);
	}
	return ptr;
}

void _free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

bool random(double proba)
{
	unsigned int maxVal = 1000;
	//maxVal--; //Overflow value

	unsigned int treshold = ((double)maxVal) * proba;
	int rando = rand() % maxVal;
	return rando < treshold
		? true
		: false;
}

double argument(Complexe v)
{
	return atan(-v.imaginaire / v.reel);
}

double raison(Complexe v)
{
	return sqrt(((double)v.reel * (double)v.reel) + ((double)v.imaginaire * (double)v.imaginaire));
}

unsigned int biggestSmallerBits(unsigned int max)
{
	unsigned int ret = 1, i = 1;
	
	while(pow(2, i) < (double)max + 0.5)
	{
		ret = pow(2, i++);
	}
	
	return ret;
}

Complexe somme2(Complexe a, Complexe b)
{
	Complexe ret;
	
	ret.reel = a.reel + b.reel;
	ret.imaginaire = a.imaginaire + b.imaginaire;
	
	return ret;
}

Complexe sommeT(Complexe *valeurs, int taille)
{
	Complexe ret;
	memset(&ret, 0.0, sizeof(Complexe));
	
	int i;
	for(i = 0; i < taille; i++)
	{
		ret.reel += valeurs[i].reel;
		ret.imaginaire += valeurs[i].imaginaire;
	}
	
	return ret;
}

Complexe soustraction2(Complexe a, Complexe b)
{
	Complexe ret;
	
	ret.reel = a.reel - b.reel;
	ret.imaginaire = a.imaginaire - b.imaginaire;
	
	return ret;
}

Complexe produit2(Complexe a, Complexe b)
{
	Complexe ret;
	
	ret.reel = a.reel * b.reel;
	ret.imaginaire = a.imaginaire * b.imaginaire;
	
	return ret;
}

Complexe produitT(Complexe *valeurs, int taille)
{
	Complexe ret;
	memset(&ret, 1.0, sizeof(Complexe));
	
	int i;
	for(i = 0; i < taille; i++)
	{
		ret.reel *= valeurs[i].reel;
		ret.imaginaire *= valeurs[i].imaginaire;
	}
	
	return ret;
}

void printMat(Complexe **mat, unsigned int H, unsigned int L)
{
	unsigned int i;
	for (i = 0; i < H; i++)
	{
		unsigned int j;
		for (j = 0; j < L; j++)
		{
			printf("\t%.3lf|", raison(mat[i][j]));
		}
		printf("\n");
	}
}

Complexe **produitMat(Complexe **a, unsigned int Ha, unsigned int La, Complexe **b, unsigned int Hb, unsigned int Lb, unsigned short int diagonnale)
{
	int H, L, prodLH;
	Complexe **ret = NULL;
	if(Hb == La)
	{
		//Operer si les matrices ont des dimensions propices au produit
		//printf("<produitMat> execute\n");
		//Allocation de la m�moire � la valeur de return
		ret = (Complexe **)safeMalloc(sizeof(Complexe *) * Ha, "");
		//printf("<produitMat> safeMalloc inter okay\n");
		for(H = 0; H < Ha; H++)
			//Pour chaque ligne de la matrice a, allouer la m�moire
			ret[H] = (Complexe *)safeMalloc(sizeof(Complexe) * Lb, "");
		//printf("<produitMat> safeMalloc okay\n");
		
		for(L = 0; L < Lb; L++)
		{
			//Pour chaque colonne de la matrice b
			for(H = 0; H < Ha; H++)
			{
				//printf("<produitMat> loop %d;%d\n", L, H);
				//Pour chaque ligne de la matrice a
				//Calculer les produits avant la somme
				
				Complexe somme =
				{
					.reel = 0.0,
					.imaginaire = 0.0
				};
				if(diagonnale == 0)
					for(prodLH = 0; prodLH < Hb && prodLH < La; prodLH++)
					{
						somme =
							somme2(
								somme,
								produit2(
									a[H][prodLH],
									b[prodLH][L]
								)
							);
					}
				else if ((diagonnale == 1 || diagonnale == 2) && H == L)
				{
					somme =
						produit2(
							a[H][L],
							b[H][L]
						);
				}
				ret[H][L] = somme;
			}
		}
	}
	else
		printf("<produitMat> Erreur: Matrices de mauvaises dimensions (%u(Hb) != %u(La))\n", Hb, La);
		
	return ret;
}

Complexe W(float kn, int N, int inverse)
{
	float exposant = -2.0 * kn * (float)PI / (float)N;
	
	if(inverse)
		exposant = - exposant;
	
	Complexe w;
	w.reel = cos(exposant);
	w.imaginaire = sin(exposant);
	
	return w;
}

Complexe *DN(int N, int *nb)
{
	*nb = (N / 2);
	Complexe *wN = (Complexe *)safeMalloc(sizeof(Complexe) * *nb, "");
	
	int i;
	for(i = 0; i < *nb; i++)
	{
		wN[i] = W((float)i, N, 0);
	}
	
	return wN;
}

Complexe **TN(int N, int inverse)
{
	Complexe **headers = (Complexe **)safeMalloc(sizeof(Complexe *) * N, "");
	
	int k;
	for(k = 0; k < N; k++)
	{
		int n;
		headers[k] = (Complexe *)safeMalloc(sizeof(Complexe) * N, "");
		for(n = 0; n < N; n++)
		{
			headers[k][n] = W(k * n, N, inverse);
		}
	}
	
	return headers;
}

void printComplexe(Complexe valeur)
{
	printf(
		"%.2f %s%.2f * i",
		valeur.reel,
		valeur.imaginaire >= 0.0 ? "+" : "",
		valeur.imaginaire
	);
}

void printTN(Complexe **Tn, int taille)
{
	int i, j;
	for(i = 0; i < taille; i++)
		for(j = 0; j < taille; j++)
		{
			printf("TN[k = %d;n = %d] = ", i, j);
			printComplexe(Tn[i][j]);
			printf("\n");
		}
}

Complexe **xN_vers_xpxi(Complexe *xN, int N)
{
	int
		n = 0,
		nxp = 0,
		nxi = 0;
		
	Complexe
		*xp = (Complexe *)safeMalloc(sizeof(Complexe) * N / 2, ""),
		*xi = (Complexe *)safeMalloc(sizeof(Complexe) * N / 2, ""),
		**xpxi = (Complexe **)safeMalloc(sizeof(Complexe *) * 2, "");
		
	xpxi[0] = xp;
	xpxi[1] = xi;
	
	//les xp (paires de xn => nxp valeurs) et ni (impaires de xn => nxi valeurs) nxp = nxi = N / 2
	for(n = 0; n < N; n++)
		if(n % 2)
			xp[nxp++] = xN[n];
		else
			xi[nxi++] = xN[n];
			
	return xpxi;
}

Complexe **XPXI_vers_XLXH(Complexe *XP, Complexe *XI, int N, int inverse)
{
	//Allocation de la RAM
	int
		n = 0,
		k = 0,
		i = 0,
		j = 0,
		tailleDN = 0;
	Complexe
		*Dn = DN(N, &tailleDN),
		**DnMat = (Complexe **)safeMalloc(sizeof(Complexe *) * tailleDN, ""),
		**TnDemi = TN(N, inverse),
		**TnDemiParxp = NULL,
		*XL = (Complexe *)safeMalloc(sizeof(Complexe) * tailleDN, ""),
		*XH = (Complexe *)safeMalloc(sizeof(Complexe) * tailleDN, ""),
		**XLXH = (Complexe **)safeMalloc(sizeof(Complexe *) * 2, ""),
		*xp = NULL,
		*xi = NULL,
		**xpxi = NULL;
	for(i = 0; i < tailleDN; i++)
	{
		//On met Dn sous forme Complexe ** pour pouvoir faire un produi matriciel
		DnMat[i] = (Complexe *)safeMalloc(sizeof(Complexe) * tailleDN, "");
		
		//On met toutes les valeurs de la matrice � 0
		//memset(&DnMat[i], 0, sizeof(Complexe) * tailleDN);
		for(j = 0; j < tailleDN; j++)
		{
			DnMat[i][j].imaginaire = 0.0;
			DnMat[i][j].reel = 0.0;
		}
		
		//On place les valeurs de DN
		//printf("D%d = ", i); printComplexe(Dn[i]); printf("\n");
		DnMat[i][i] = Dn[i];
	}
	
	XLXH[0] = XL;
	XLXH[1] = XH;
	
	Complexe 
		**xiMat = (Complexe **)safeMalloc(sizeof(Complexe *) * tailleDN, ""),
		**xpMat = (Complexe **)safeMalloc(sizeof(Complexe *) * tailleDN, "");
	
	for(i = 0; i < tailleDN; i++)
	{
		xiMat[i] = (Complexe *)safeMalloc(sizeof(Complexe), "");
		xiMat[i][0].reel = XI[i].reel;
		xiMat[i][0].imaginaire = XI[i].imaginaire;
		
		xpMat[i] = (Complexe *)safeMalloc(sizeof(Complexe), "");
		xpMat[i][0].reel = XP[i].reel;
		xpMat[i][0].imaginaire = XP[i].imaginaire;
	}

	
	//Calcul pr�liminaire des matrices
	//printf("\n<XPXI_vers_XLXH> PRODUITMAT1 (%d)\n", tailleDN);
	TnDemiParxp = produitMat(TnDemi, tailleDN, tailleDN, xpMat, tailleDN, 1, 0);

	//printf("<XPXI_vers_XLXH> PRODUITMAT2 (%d)\n", tailleDN);
	Complexe **DnParTnDemi = produitMat(DnMat, tailleDN, tailleDN, TnDemi, tailleDN, tailleDN, 0);

	//printf("<XPXI_vers_XLXH> PRODUITMAT3 (%d)\n", tailleDN);
	Complexe **DnParTnDemiParxi = produitMat(DnParTnDemi, tailleDN, tailleDN, xiMat, tailleDN, 1, 0);

	//Calcul de XL et XH
	for(k = 0; k < tailleDN; k++)
	{
		XL[k] =
			somme2(
				TnDemiParxp[k][0],
				DnParTnDemiParxi[k][0]
			);
		
		XH[k] =
			soustraction2(
				TnDemiParxp[k][0],
				DnParTnDemiParxi[k][0]
			);
	}
	
	//Lib�ration de la RAM
	free(Dn);
	
	for(i = 0; i < N; i++)
		free(TnDemi[i]);
	free(TnDemi);
	
	for(i = 0; i < tailleDN; i++)
	{
		free(DnMat[i]);
		free(DnParTnDemi[i]);
		
		free(xiMat[i]);
		free(xpMat[i]);
		
		free(TnDemiParxp[i]);
	}
	free(DnMat);
	free(DnParTnDemi);
	
	free(xiMat);
	free(xpMat);
	
	free(xp);
	free(xi);
	free(xpxi);
	
	free(TnDemiParxp);
	
	return XLXH;
}
