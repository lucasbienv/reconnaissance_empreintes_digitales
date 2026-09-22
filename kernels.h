#ifndef KERNELS_Hx
#define KERNELS_H


#include <stdlib.h>
#include <stdio.h>
#include "libbmp.h"


struct kernel {
  int h;
  int w;
  float* valeurs;
};

typedef struct kernel kernel;


kernel gauss();
kernel convolution();
kernel sobel_x();
void apply_kernel(bmp_img*, kernel);


#endif
