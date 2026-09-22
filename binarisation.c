#include <stdlib.h>
#include <stdio.h>
#include "libbmp.h"

unsigned int niveau_gris(bmp_pixel p)
{
  return (2 * p.red
         + 5 * p.green
	  + 1 * p.blue)/8;
}

int* histogramme(bmp_img* img){

  //Entree : une image de h*w pixels, avec chaque pixel contenu dans img->int** img_pixels
  //sortie : un int* histo qui correspond à l'histogramme de l'image
  // complexité en O(h*w) = O(dim(Img))
  int h = img->img_header.biHeight;
  int w = img->img_header.biWidth;
  int* tab_histo = malloc(sizeof(int)*256);
  //init de tab_histo :
  for (int i=0; i<256;i++){
    tab_histo[i]=0;
  }
  int n =0;
  for (int i=0; i<h; i++)
    {
      for (int j=0; j<w; j++)
	{
	  int gris = niveau_gris(img->img_pixels[i][j]); // on récupère le niveau de gris de chaque pixel
	  tab_histo[gris]++; 
	  n++;
	}
    }
  printf("nombre de pixels : %d ", n); // vérification temporaire du nombre de pixels analysés
  return tab_histo;
}

int seuil(int* histo){
  //Entree : histogramme
  //Sortie : la moyenne de niveau de gris qui correspond au seuil
  int s = 0;
  for(int i=0; i<256; i++){
    s = s+ i*histo[i];
  }
  return s/(256*256);
}

void binarisation(char* f_sortie, char* f_source, int h, int w){
  //Entre : nom du fichier de l'image source, de sortie
  //sortie : image binarisé avec comme nom f_sortie

  //initialisation
  printf("ok\n");
  bmp_img* img_source = malloc(sizeof(bmp_img));
  bmp_img* img_sortie = malloc(sizeof(bmp_img));
  bmp_img_init_df(img_sortie, w,h);
  bmp_img_read(img_source, f_source);

  int* histo = histogramme(img_source);
  printf("ok\n");
  int s = seuil(histo);
   for (int i=0; i<h; i++)
    {
      for (int j=0; j<w; j++)
	{
	  int gris = niveau_gris(img_source->img_pixels[i][j]); // on récupère le niveau de gris de chaque pixel
	  if (gris > s){
	    //alors le pixel devient noir
	    bmp_pixel_init (&img_sortie->img_pixels[i][j], 250, 250, 250);
	  }
	  else {
	    //pixel devient blanc
	    bmp_pixel_init (&img_sortie->img_pixels[i][j], 0, 0, 0);
	  }
	}
    }
   bmp_img_write (img_sortie, f_sortie);
   bmp_img_free (img_source);
   bmp_img_free(img_sortie);
   free(img_source);
   free(img_sortie);
   free(histo);
}



