#ifndef BINARISATION_H
#define BINARISATION_H

#include <stdlib.h>
#include <stdio.h>
#include "libbmp.h"

unsigned int niveau_gris(bmp_pixel);
int* histogramme(bmp_img*);
int seuil(int*);
void binarisation(char*, char*, int, int);
#endif
