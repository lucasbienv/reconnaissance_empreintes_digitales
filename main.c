#include <stdlib.h>
#include <stdio.h>
#include "libbmp.h"
#include "binarisation.h"

int main(){
  binarisation("test1.bmp", "1_1.bmp", 256,256);
  binarisation("test2.bmp", "1_2.bmp", 256,256);
  binarisation("test3.bmp", "1_3.bmp", 256,256);
  binarisation("test4.bmp", "1_4.bmp", 256,256);
  return 0;
}
