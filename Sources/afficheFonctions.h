#include <stdbool.h>
#include "creerFonctions.h"
#include "image.h"

void initialiseRepereCentre(Image* ptr_image);

int tracePoint(Image* ptr_image, int pixelOrdonnee, int pixelAbcisse, char* couleur, unsigned short int couleurMini);

void truncate(trace* function, unsigned short int plainPercentageKept);

//Cr�e un fichier (doit �tre bmp), et dessine le trac� � l'int�rieur
void traceFonction(trace fonction, char *fichier, bool center);

void donneesTrace(trace fonction);
