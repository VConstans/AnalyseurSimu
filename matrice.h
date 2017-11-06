#ifndef __MATRICE_H__
#define __MATRICE_H__

#include <stdio.h>
#include <stdlib.h>

typedef int** matrice;

struct matriceAdj
{
	matrice mat;	//stockage de la matrice
	unsigned int nbNoeud;	//Nombre de noeud dans le systeme
};


FILE* ouvertureMatrice(char* matrice);
struct matriceAdj* lectureMatrice(FILE* fdMatrice);
struct matriceAdj* loadMatriceAdjacence(char* fileMatrice);
int debitLien(matrice mat,int i, int j);

#endif
