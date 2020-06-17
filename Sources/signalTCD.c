#include <stdlib.h>
#include "signalTCD.h"

float tcdW(float kn, int N, int inverse)
{
	Complexe ret = W(kn, N, inverse);
	return ret.reel;
}

float **tcdxN_vers_xpxi(float *xN, int N)
{
	//Init
	Complexe 
		*xNCplx = (Complexe *)safeMalloc(sizeof(Complexe) * N),
		**retCplx = NULL;
		
	int i;
	for(i = 0; i < N; i++)
	{
		xNCplx[i].reel = xN[i];
		xNCplx[i].imaginaire = 0.0;
	}
	
	//Process
	retCplx = xN_vers_xpxi(xNCplx, N);
	_free(xNCplx);
	
	//Return
	float **xpxi = (float **)safeMalloc(sizeof(float *) * 2);
	
	xpxi[0] = (float *)safeMalloc(sizeof(float) * N / 2);
	xpxi[1] = (float *)safeMalloc(sizeof(float) * N / 2);
	
	for(i = 0; i < N; i++)
	{
		if(N < 2)
			xpxi[0][i] = retCplx[0][i].reel;
		else
			xpxi[1][i - N / 2] = retCplx[1][i - N / 2].reel;
	}
	
	_free(retCplx[0]);
	_free(retCplx[1]);
	_free(retCplx);
	
	return xpxi;
}

float **tcdTN(int N, int inverse)
{
	float **headers = (float **)safeMalloc(sizeof(Complexe *) * N);
	
	int k;
	for(k = 0; k < N; k++)
	{
		int n;
		headers[k] = (float *)safeMalloc(sizeof(Complexe) * N);
		for(n = 0; n < N; n++)
		{
			headers[k][n] = tcdW(k * n, N, inverse);
		}
	}
	
	return headers;
}
