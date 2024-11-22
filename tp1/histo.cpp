

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250];
    int nH, nW, nTaille;
    int histo[255];
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

    file= fopen("histTemp.dat","w");
    for (int i=0; i < nH; i++){
        for (int j=0; j < nW; j++)
        {   
            histo[ImgIn[i*nW+j]]++;
        }
        }

    for (int j=0; j < 256; j++)
    {   
        fprintf(file,"%d %d \n",j,histo[j]);
    }

    fclose(file);
    free(ImgIn);

   return 1;
}
