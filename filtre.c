#include <stdlib.h>
#include <stdio.h>
#include "libbmp.h"
#include "binarisation.h"


int mean_9_case(bmp_img* img, int i, int j){
  //d'abord les bords
  int h = img->img_header.biHeight;
  int w = img->img_header.biWidth;
  int sum=0;


  //PASSER PAR UN KERNEL


	      
  if (i!=0 && i!=h-1 && j!=0 && j!=w-1){
    //on somme les niveaux de gris des cases du dessus
    for (int k=i-1; k<i+2; k++){
      for (int l=j-1; l<j+2; l++){
	sum = sum + niveau_gris(img->img_pixels[k][l]);
	  }
    }
    //puis on fait la moyenne : 
    return sum/9;
  }
  //on est en haut
  else if (i==0 && j!=0 && j!=w-1){
    for (int k=0; k<2; k++){
      for (int l=j-1; l<j+2; l++){
	sum = sum + niveau_gris(img->img_pixels[k][l]);
	  }
    }
    return sum/6;
  }
  //on est en bas
  else if (i==h-1 && j!=0 && j!=w-1){
    for (int k=h-2; k<h; k++){
      for (int l=j-1; l<j+2; l++){
	sum = sum + niveau_gris(img->img_pixels[k][l]);
	  }
    }
    return sum/6;
  }
  
  //on est a gauche
   else if (i!=0 && i!=w-1 && j==0){
    for (int k=i-1; k<i+2; k++){
      for (int l=0; l<2; l++){
	sum = sum + niveau_gris(img->img_pixels[k][l]);
	  }
    }
    return sum/6;
  }
  //on est a droite
  else if (i!=0 && i!=w-1 && j==w-1){
    for (int k=i-1; k<i+2; k++){
      for (int l=j-1; l<w; l++){
	sum = sum + niveau_gris(img->img_pixels[k][l]);
	  }
    }
    return sum/6;
  }

  //enfin les coins
  else if (i==0 j==0){
    for (int k=0; k<2; k++){
      for (int l=0; l<2; l++){
	sum = sum + niveau_gris(img->img_pixels[k][l]);
	  }
    }
    return sum/4;
  }
  else if (i==0 && j==w-1){
    for (int k=0; k<2; k++){
      for (int l=j-1; l<w; l++){
	sum = sum + niveau_gris(img->img_pixels[k][l]);
	  }
    }
    return sum/4;
  }
  else if (i==h-1 && j==0){
    for (int k=i-1; k<h; k++){
      for (int l=0; l<2; l++){
	sum = sum + niveau_gris(img->img_pixels[k][l]);
	  }
    }
    return sum/4;
  }
  else if (i==h-1 && j==w-1){
    for (int k=i-1; k<h; k++){
      for (int l=j-1; l<w; l++){
	sum = sum + niveau_gris(img->img_pixels[k][l]);
	  }
    }
    return sum/4;
  }
}


void filtrage(char* f_sortie, char* f_source, int h, int w){
  bmp_img* img_source = malloc(sizeof(bmp_img));
  bmp_img* img_sortie = malloc(sizeof(bmp_img));
  bmp_img_init_df(img_sortie, h,w);
  bmp_img_read(img_source, f_source);
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
