#pragma once

typedef struct trace
{
	double *valeurs, vMin, vMax;
	int nbValeurs;
}trace;

//Retourne le r�sultat d'un signal carr� � la phase d'un sinus et � 2*PI sa p�riode
int signalCarre(double x, int max);

//Retrouve la valeur min et la valeur max d'un trace et place les valeurs
void minMax(trace *ptr_graph);

//Remplit une variable trace des valeurs d'une fonction, ainsi que les informations n�cessaires � toutes actions avec cette variable
trace valeursFonction(int fonction, double frequence, int nbPeriodes);

//Pareil qu'au dessus, mais dans une matrice carr�e. Chaque ligne est un r�sultat.
trace *valeursMat(int fonction, double frequence, int nbPeriodes);

void libereTrace(trace *cible);
