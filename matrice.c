#include "matrice.h"

FILE* ouvertureMatrice(char* matrice)
{
	FILE* fdMatrice = fopen(matrice,"r");
	return fdMatrice;
}


//Mise de la matrice en mémoire
struct matriceAdj* lectureMatrice(FILE* fdMatrice)
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
		lg = fscanf(fdMatrice,"%d",&val);
		if(lg == 0 || lg == EOF)
		{
			perror("Fichier mal formaté");
			exit(-1);
		}
		taille++;
	} while(fgetc(fdMatrice) == '\t');


	fseek(fdMatrice,0,SEEK_SET);


	struct matriceAdj* matAdj= (struct matriceAdj*) malloc (sizeof(struct matriceAdj));

	matAdj->nbNoeud = taille;

	matAdj->mat = (int**) malloc (taille*sizeof(int*));

	int i,j;

	for(i=0;i<taille;i++)
	{
		matAdj->mat[i] = (int*) malloc(taille*sizeof(int));
	}

	for(i=0;i<taille;i++)
	{
		for(j=0;j<taille;j++)
		{
			fscanf(fdMatrice,"%d",&(matAdj->mat[i][j]));
			fseek(fdMatrice,1,SEEK_CUR);
		}
	}

	return matAdj;
}


struct matriceAdj* loadMatriceAdjacence(char* fileMatrice)
{
	FILE* fdMatrice = ouvertureMatrice(fileMatrice);
	struct matriceAdj* mat = lectureMatrice(fdMatrice);
	fclose(fdMatrice);

	return mat;
}


//Renvoie le débit d'un lien
int debitLien(matrice mat,int i, int j)
{
	return (mat[i-1][j-1]<mat[j-1][i-1])? mat[j-1][i-1] : mat[i-1][j-1];
}
