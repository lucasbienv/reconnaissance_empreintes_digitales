#include <stdlib.h>
#include <stdio.h>
#include "libbmp.h"
#include "binarisation.h"
#include "kernels.h"

int main(){
  binarisation("test1.bmp", "1_1.bmp", 256,256);
  binarisation("test2.bmp", "1_2.bmp", 256,256);
  binarisation("test3.bmp", "1_3.bmp", 256,256);
  binarisation("test4.bmp", "1_4.bmp", 256,256);
  kernel conv_ker = sobel_x();
  bmp_img img;
  bmp_img_read(&img, "imaget.bmp");
  apply_kernel(&img, conv_ker);
  bmp_img_free(&img);

  return 0;
}
