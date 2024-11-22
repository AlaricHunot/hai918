#include <stdio.h>
#include "image_ppm.h"
#include <math.h>

int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgLue2[250];
  int nH, nW, nTaille;
  float sommeErreur = 0.0;

  if (argc != 3) 
  {
    printf("Usage: ImageIn.pgm ImageIn2.pgm \n"); 
    exit (1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgLue2);

  OCTET *ImgIn, *ImgIn2;

  lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nTaille);

  allocation_tableau(ImgIn2, OCTET, nTaille);
  lire_image_pgm(cNomImgLue2, ImgIn2, nTaille);

  for (int i = 0; i < nTaille; i++) 
  {
    sommeErreur += (ImgIn[i] - ImgIn2[i]) * (ImgIn[i] - ImgIn2[i]);
  }

  float EQM = sommeErreur / nTaille;


  float PSNR = 10.0 * log10((255.0 * 255.0) / EQM);
  printf("PSNR = %f dB\n", PSNR);

  free(ImgIn);
  free(ImgIn2);
  
  return 0;
}
