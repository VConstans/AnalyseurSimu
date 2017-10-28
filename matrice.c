#include "matrice.h"

FILE* ouvertureMatrice(char* matrice)
{
	FILE* fdMatrice = fopen(matrice,"r");
	return fdMatrice;
}


matrice lectureMatrice(FILE* fdMatrice)
{
	int taille = 0;
	int val,lg;

	if(fgetc(fdMatrice) == EOF)
	{
		perror("Fichier matrice vide");
		exit(-1);
	}

	fseek(fdMatrice,0,SEEK_SET);

	do
	{
		lg = fscanf(fdMatrice,"%d",&val);	//TODO test si fichier mal formaté
		if(lg == 0 || lg == EOF)
		{
			perror("Fichier mal formaté");
			exit(-1);
		}
		taille++;
	} while(fgetc(fdMatrice) == '\t');


	fseek(fdMatrice,0,SEEK_SET);


	matrice mat = (int**) malloc (taille*sizeof(int*));

	int i,j;

	for(i=0;i<taille;i++)
	{
		mat[i] = (int*) malloc(taille*sizeof(int));
	}

	for(i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
		{
			fscanf(fdMatrice,"%d",&mat[i][j]);
			fseek(fdMatrice,1,SEEK_CUR);
		}
	}

	return mat;
}

matrice loadMatriceAdjacence(char* fileMatrice)
{
	FILE* fdMatrice = ouvertureMatrice(fileMatrice);
	matrice mat = lectureMatrice(fdMatrice);
	fclose(fdMatrice);

	return mat;
}


int debitLien(matrice mat,int i, int j)
{
	return (mat[i][j]<mat[j][i])? mat[j][i] : mat[i][j];
}
