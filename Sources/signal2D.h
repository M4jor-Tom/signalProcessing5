#pragma once

#define Oy 0
#define Ox 1

#include "afficheFonctions.h"
#include "signal.h"

void traceFonctions2D(trace *fonction, char *fichier, int axe);

//void traceFonction2D(trace fonction, char *fichier, int axe);

float **imageVersFloat(char *baseName, unsigned int *hauteur, unsigned int *largeur);

//Complexe **imageVersComplexe(char *baseName, unsigned int *hauteur, unsigned int *largeur);
