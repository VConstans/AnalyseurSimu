#ifndef __MATRICE_H__
#define __MATRICE_H__

#include <stdio.h>
#include <stdlib.h>

typedef int** matrice;


FILE* ouvertureMatrice(char* matrice);
matrice lectureMatrice(FILE* fdMatrice);
matrice loadMatriceAdjacence(char* fileMatrice);
int debitLien(matrice mat,int i, int j);

#endif
