// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"
#include <math.h>
int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgLue2[250];
  int nH, nW, nTaille,nTaille2 ,R,G,B,nH2,nW2;
  R = 0;
  G = 0;
  B = 0;
    if (argc != 3) 
     {
       printf("Usage: ImageIn.ppm ImageIn2.ppm \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   sscanf (argv[2],"%s",cNomImgLue2);

   OCTET *ImgIn, *ImgIn2;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue2, &nH2, &nW2);
   nTaille = nH * nW;
   nTaille2 = nH2 * nW2 ;
   printf("nTaille = %d \nnTaille2 = %d \n",nTaille,nTaille2);
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   printf("Tab1 \n");
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   printf("lecture img1  \n");
   allocation_tableau(ImgIn2, OCTET, nTaille3);
   printf("Tab2  \n");
   lire_image_ppm(cNomImgLue2, ImgIn2, nH * nW);
   printf("Images lues \n");
   for (int i=0; i < nTaille3; i+=3)
     {R += (ImgIn[i]-ImgIn2[i])*(ImgIn[i]-ImgIn2[i]);
      G += (ImgIn[i+1]-ImgIn2[i+1])*(ImgIn[i+1]-ImgIn2[i+1]);
      B += (ImgIn[i+2]-ImgIn2[i+2])*(ImgIn[i]-ImgIn2[i+2]);
     }
     printf("EQM part 1 done \n");
     R = R / nTaille;
     G = G / nTaille;
     B = B / nTaille;
     float EQM = (R + G +B )/3;
     printf("EQM part 2 done \n");
     double transition = (255.0*255.0)/EQM;
     printf("Transition done \n");
     double log = log10(transition);
     printf("Fini?  \n");
     double PSNR = 10 * log ;
     printf("PSNR = %f \n",PSNR);
   free(ImgIn);
   free(ImgIn2);
   return 1;
}
