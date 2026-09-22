#include <stdlib.h>
#include <stdio.h>
#include "libbmp.h"
#include "binarisation.h"
#include "kernels.h"

kernel gauss()
{
    kernel gaus;

    gaus.h = 3;
    gaus.w = 3;

    gaus.valeurs = malloc(9 * sizeof(float));

    float valeurs[9] = {
        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
        2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
        1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
    };

    for (int i = 0; i < 9; i++)
        gaus.valeurs[i] = valeurs[i];

    return gaus;
}


kernel convolution()
{
    kernel conv;

    conv.h = 3;
    conv.w = 3;

    conv.valeurs = malloc(9 * sizeof(float));

    float valeurs[9] = {
        1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f,
        1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f,
        1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f
    };

    for (int i = 0; i < 9; i++)
        conv.valeurs[i] = valeurs[i];

    return conv;
}

kernel sobel_x()
{
    kernel sobel;

    sobel.h = 3;
    sobel.w = 3;

    sobel.valeurs = malloc(9 * sizeof(float));

    float valeurs[9] = {
        -1.0f,  0.0f,  1.0f,
        -2.0f,  0.0f,  2.0f,
        -1.0f,  0.0f,  1.0f
    };

    for (int i = 0; i < 9; i++)
        sobel.valeurs[i] = valeurs[i];

    return sobel;
}


void apply_kernel(bmp_img* img, kernel ker){
  int h = img->img_header.biHeight;
  int w = img->img_header.biWidth;
  bmp_img* result = malloc(sizeof(bmp_img));
  printf("h : %d, w  %d", h,w);
  bmp_img_init_df(result, w, h);
  
  int ker_h = ker.h;
  int ker_w = ker.w;

  //on commence avec des lignes et colonnes de décalalge pour ne
  //pas avoir de problemes pour l'application du kernel
  for (int i = ker_h/2; i<h - ker_h/2; i++){
    for (int j = ker_w/2; j< w  - ker_w/2; j++){
      //on applique le kernel sur le pixel:
      float pixel_out = 0.0f;
      
      for (int kx=0; kx<ker_h ; kx++){
	for (int ky=0 ; ky<ker_w; ky++){
	  //indices des pixels à utiliser
	  int ix = i + kx - ker_h/2;
	  int jy = j + ky - ker_w/2;
	  pixel_out += niveau_gris(img->img_pixels[ix][jy]) * ker.valeurs[ker_w*kx + ky];
	}
      }
      int value = (int)pixel_out;
      if (value<0) value = -value;
      if (value > 255) value = 255;
      bmp_pixel_init(&result->img_pixels[i][j], value, value, value);   
    }
  }

  //enfin on oublie pas les pixels qu'on a pas touché:
  for (int i=0; i<h; i++){
    for (int j=0; j<w; j++){
      if (i<ker_h/2 || i>=h - ker_h/2 || j<ker_w/2 || j>= w - ker_w/2){
	int pixel = niveau_gris(img->img_pixels[i][j]);
	bmp_pixel_init(&result->img_pixels[i][j], pixel, pixel, pixel);   
      }   
    }
  }

  
  bmp_img_write(result, "test_conv.bmp");
  free(ker.valeurs);
  bmp_img_free(result);
  free(result);
  
}
