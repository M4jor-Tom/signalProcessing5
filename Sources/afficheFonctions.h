#include <stdbool.h>
#include "creerFonctions.h"
#include "image.h"

void initialiseRepereCentre(Image* ptr_image);

int tracePoint(Image* ptr_image, int pixelOrdonnee, int pixelAbcisse, char* couleur, unsigned short int couleurMini);

void truncate(trace* function, unsigned short int plainPercentageKept);

//Crée un fichier (doit être bmp), et dessine le tracé à l'intérieur
void traceFonction(trace fonction, char *fichier, bool center);

void donneesTrace(trace fonction);
