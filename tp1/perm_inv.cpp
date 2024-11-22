
#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"
#include <time.h>

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille;
    int K; 

    if (argc != 4) 
    {
        printf("Usage: ImageEncrypted.pgm Key(0-255) ImageDecrypted.pgm\n"); 
        exit(1);
    }
    
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%d", &K);
    sscanf(argv[3], "%s", cNomImgEcrite);

    if (K < 0 || K > 255)
    {
        printf("Key K must be between 0 and 255.\n");
        exit(1);
    }

    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
   
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    int *indices;
    allocation_tableau(indices, int, nTaille);

    for (int i = 0; i < nTaille; i++)
        indices[i] = i;

    srand(K);

    for (int i = nTaille - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    for (int i = 0; i < nTaille; i++)
    {
        ImgOut[i] = ImgIn[indices[i]];
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);
    free(indices);

    return 0;
}
