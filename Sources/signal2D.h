#pragma once

#define Oy 0
#define Ox 1

#include "afficheFonctions.h"
#include "signal.h"

void traceFonction2D(trace fonction, char *fichier, int axe);

Complexe **imageVersComplexe(char *baseName, unsigned int *hauteur, unsigned int *largeur);
