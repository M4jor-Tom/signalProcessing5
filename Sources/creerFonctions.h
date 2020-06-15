#pragma once

typedef struct trace
{
	double *valeurs, vMin, vMax;
	int nbValeurs;
}trace;

//Retourne le résultat d'un signal carré à la phase d'un sinus et à 2*PI sa période
int signalCarre(double x, int max);

//Retrouve la valeur min et la valeur max d'un trace et place les valeurs
void minMax(trace *ptr_graph);

//Remplit une variable trace des valeurs d'une fonction, ainsi que les informations nécessaires à toutes actions avec cette variable
trace valeursFonction(int fonction, double frequence, int nbPeriodes);

//Pareil qu'au dessus, mais dans une matrice carrée. Chaque ligne est un résultat.
trace *valeursMat(int fonction, double frequence, int nbPeriodes);

void libereTrace(trace *cible);
