#pragma once

#include <stdbool.h>

typedef struct Complexe
{
	float reel, imaginaire;
}Complexe;

void* safeMalloc(int sizeof_, char* parent);

void _free(void *ptr);

bool random(double proba);

//Retrouve l'argument d'un complexe
double argument(Complexe v);

//Retrouve la raison d'un complexe
double raison(Complexe v);

//Returns the biggest 'multiple' of 2^n inferior to max
unsigned int biggestSmallerBits(unsigned int max);

Complexe somme2(Complexe a, Complexe b);

Complexe soustraction2(Complexe a, Complexe b);

Complexe produit2(Complexe a, Complexe b);

void printMat(Complexe** mat, unsigned int H, unsigned int L);

Complexe** produitMat(Complexe** a, unsigned int Ha, unsigned int La, Complexe** b, unsigned int Hb, unsigned int Lb, unsigned short int diagonnale);

Complexe W(float kn, int N, int inverse);

Complexe *DN(int N, int *nb);

Complexe **TN(int N, int inverse);

void printComplexe(Complexe valeur);

//Affiche le résultat de TN
void printTN(Complexe **Tn, int taille);

Complexe **xN_vers_xpxi(Complexe *xN, int N);

Complexe **XPXI_vers_XLXH(Complexe *XP, Complexe *XI, int N, int inverse);
