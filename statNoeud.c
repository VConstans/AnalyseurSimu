#include "statNoeud.h"

void initStatNoeud(struct statNoeud* statNoeud, unsigned int nbNoeud)
{
	statNoeud->nbNoeud = nbNoeud;
	statNoeud->nbPaquetTotalDansFile = 0;
	statNoeud->tabNoeud = (struct noeud*)malloc(nbNoeud*sizeof(struct noeud));

	statNoeud->remplissage=0;
}



void initNoeud(struct statNoeud* statNoeud,char* noeud)
{
	unsigned int index = statNoeud->remplissage;
	int taille = strlen(noeud)+1;
	statNoeud->tabNoeud[index].noeud = malloc(taille*sizeof(char));
	strcpy(statNoeud->tabNoeud[index].noeud,noeud);
	statNoeud->tabNoeud[index].nbPaquetDansFile=0;
	statNoeud->tabNoeud[index].tailleFile=0;
	statNoeud->tabNoeud[index].nbPerte=0;
}

void setTailleFile(struct statNoeud* statNoeud, char* noeud)
{
	unsigned int i;

	for(i=0;i<statNoeud->remplissage;i++)
	{
		if(strcmp(statNoeud->tabNoeud[i].noeud,noeud) == 0)
		{
			statNoeud->tabNoeud[i].tailleFile=statNoeud->tabNoeud[i].nbPaquetDansFile;
			return;
		}
	}

	if(statNoeud->nbNoeud == statNoeud->remplissage)
	{
		printf("Erreur trop de noeud\n");
	}
	else
	{
		printf("Erreur, noeud pas encore rencontré\n");
	}
}





void incrNbPaquetDansFile(struct statNoeud* statNoeud, char* noeud)
{
	unsigned int i;

	for(i=0;i<statNoeud->remplissage;i++)
	{
		if(strcmp(statNoeud->tabNoeud[i].noeud,noeud) == 0)
		{
			statNoeud->tabNoeud[i].nbPaquetDansFile++;
			return;
		}
	}

	if(statNoeud->nbNoeud == statNoeud->remplissage)
	{
		printf("Erreur trop de noeud\n");
	}
	else
	{
		initNoeud(statNoeud,noeud);

		statNoeud->tabNoeud[statNoeud->remplissage].nbPaquetDansFile++;
		statNoeud->nbPaquetTotalDansFile++;
		statNoeud->remplissage++;
	}
}



void decrNbPaquetDansFile(struct statNoeud* statNoeud, char* noeud)
{
	unsigned int i;

	for(i=0;i<statNoeud->remplissage;i++)
	{
		if(strcmp(statNoeud->tabNoeud[i].noeud,noeud) == 0)
		{
			statNoeud->tabNoeud[i].nbPaquetDansFile--;
			return;
		}
	}

	printf("Erreur decr sur noeud non sauvegarde\n");
}



void incrNbPerte(struct statNoeud* statNoeud, char* noeud)
{
	unsigned int i;

	for(i=0;i<statNoeud->remplissage;i++)
	{
		if(strcmp(statNoeud->tabNoeud[i].noeud,noeud) == 0)
		{
			statNoeud->tabNoeud[i].nbPerte++;
			return;
		}
	}

	if(statNoeud->nbNoeud == statNoeud->remplissage)
	{
		printf("Erreur trop de noeud\n");
	}
	else
	{
		initNoeud(statNoeud,noeud);

		statNoeud->tabNoeud[statNoeud->remplissage].nbPerte++;
		statNoeud->remplissage++;
	}
}
