#ifndef __MATRICE_H__
#define __MATRICE_H__

#include <stdio.h>
#include <stdlib.h>

typedef matrice int**


FILE* ouvertureMatrice(char* matrice);
matrice lectureMatrice(FILE* fdMatrice);
matrice loadMatriceAdjacence(char* fileMatrice);

#endif
