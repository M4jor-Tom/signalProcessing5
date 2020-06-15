#pragma once

#include "signal.h"

float tcdW(float kn, int N, int inverse);

float **tcdxN_vers_xpxi(float *xN, int N);

float **tcdTN(int N, int inverse);
