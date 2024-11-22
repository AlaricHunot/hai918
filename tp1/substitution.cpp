#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"
#include <ctime>

int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, k;

    if (argc != 4) {
        printf("Usage: ImageIn.pgm key ImageOut.pgm\n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%d", &k);  
    sscanf(argv[3], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;
    srand(k);
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);
    k = rand() % 256; 
    ImgOut[0] = (ImgIn[0] + k) % 256; 
    for (int i = 0; i < nTaille; i++) {
        k = rand() % 256; 
        ImgOut[i] = (ImgOut[i-1]+ImgIn[i] + k) % 256; 
    }

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    free(ImgOut);

    return 0;
}
