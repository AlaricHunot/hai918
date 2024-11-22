

#include <stdio.h>
#include "image_ppm.h"
#include <math.h>
int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    int nH, nW, nTaille;
    float controle = 0;
    double transi[255];
    double entropie=0.;
    double histo[255];
    FILE *file;

    if (argc != 2)
    {
        printf("Usage: ImageIn.pgm\n");
        exit (1) ;
    }

   sscanf (argv[1],"%s",cNomImgLue) ;


   OCTET *ImgIn;
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   printf("nb de pixels = %d \n ",nTaille);
   allocation_tableau(ImgIn, OCTET, nTaille);
   lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    for (int i = 0; i < 255; i++) {
        histo[i] = 0;
    }
    for (int i=0; i < nH; i++){
        for (int j=0; j < nW; j++)
        {   
            histo[ImgIn[i*nW+j]]++;
        }
        }

    for (int j=0; j < 255; j++)
    {   
        histo[j]= histo[j]/nTaille;
        controle += histo[j];
        transi[j] = histo[j]*log2f(histo[j]);
        if (transi[j]!=transi[j]) transi[j]=0;
        entropie += transi[j];
        printf ( "value entropie = %f \n",transi[j]);
    }
    printf ( "value entropie = %f \n",entropie);
    entropie = entropie * -1 ; 
    printf("%f controle value at 1 \n",controle);
    printf ( "value entropie = %f \n",entropie);
    free(ImgIn);

   return 1;
}
