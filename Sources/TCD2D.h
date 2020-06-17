#pragma once
#include <stdlib.h>
#include "signalTCD.h"

float **TCD2D(float **xN, int tailleL, int tailleH, int inverse);

float **transposeeTCD(float **mat, int taille1, int taille2);
