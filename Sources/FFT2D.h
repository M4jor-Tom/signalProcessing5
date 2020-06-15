#pragma once
#include <stdlib.h>
#include "signal.h"

//génère une FFT en 2D
Complexe **FFT2D(Complexe **xN, int tailleL, int tailleH, int inverse);

//Transpose une matrice Complexe **
Complexe **transposee(Complexe **mat, int taille1, int taille2);
