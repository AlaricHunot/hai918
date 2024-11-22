#include <stdio.h>
#include <stdlib.h>
#include "image_ppm.h"
#include <ctime>

void generate_permutation(int* permutation, int size, int key) {
    srand(key);  

    for (int i = 0; i < size; i++) {
        permutation[i] = i;
    }

    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);  
        int temp = permutation[i];
        permutation[i] = permutation[j];
        permutation[j] = temp;
    }
}

int main(int argc, char* argv[]) {
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, key;

    if (argc != 4) {
        printf("Usage: ImageIn.pgm key ImageOut.pgm\n");
        exit(1);
    }
    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%d", &key); 
    sscanf(argv[3], "%s", cNomImgEcrite);

    OCTET *ImgIn, *ImgOut;
    
    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;
    
    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nTaille);
    allocation_tableau(ImgOut, OCTET, nTaille);

    int *permutation = (int*)malloc(nTaille * sizeof(int));
    generate_permutation(permutation, nTaille, key);

    for (int i = 0; i < nTaille; i++) {
        ImgOut[permutation[i]] = ImgIn[i];
    }


    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);

    free(ImgIn);
    free(ImgOut);
    free(permutation);

    return 0;
}