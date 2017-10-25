#include "matrice.h"


FILE* ouveretureMatrice(char* matrice)
{
	FILE* fdMatrice = fopen(matrice,"r");
	return fdMatrice;
}


int** lectureMatrice(FILE* fdMatrice)
{
	int val;

	

	while((val=fgetc(fdMatrice)) != EOF)
	{
		
	}

	//return
}
