#include "statNoeud.h"

void initStatNoeud(struct statNoeud* statNoeud, unsigned int nbNoeud)
{
	statNoeud->nbNoeud = nbNoeud;
	statNoeud->nbPaquetTotalDansFile = 0;
	statNoeud->nbPaquetDansFile.tab = (struct assocNoeudEntier*)malloc(nbNoeud*sizeof(struct assocNoeudEntier));
	statNoeud->tailleFile.tab = (struct assocNoeudEntier*)malloc(nbNoeud*sizeof(struct assocNoeudEntier));
	statNoeud->nbPerte.tab = (struct assocNoeudEntier*)malloc(nbNoeud*sizeof(struct assocNoeudEntier));

	statNoeud->nbPaquetDansFile.remplissage=0;
	statNoeud->tailleFile.remplissage=0;
	statNoeud->nbPerte.remplissage=0;
}



void setValTabAssoc(struct tabAssoc* tabAssoc, char* noeud, unsigned int val, unsigned int nbNoeud)
{
	unsigned int i;

	for(i=0;i<tabAssoc->remplissage;i++)
	{
		if(strcmp(tabAssoc->tab[i].noeud,noeud) == 0)
		{
			printf("Reecriture\n");
			tabAssoc->tab[i].entier=val;
			return;
		}
	}

	if(nbNoeud == tabAssoc->remplissage)
	{
		printf("Erreur trop de noeud\n");
	}
	else
	{
		int taille = strlen(noeud)+1;
		tabAssoc->tab[tabAssoc->remplissage].noeud = (char*) malloc(taille*sizeof(char));
		strcpy(tabAssoc->tab[tabAssoc->remplissage].noeud,noeud);
		tabAssoc->tab[tabAssoc->remplissage].entier=val;
		tabAssoc->remplissage++;
	}
}





void incrTabAssoc(struct tabAssoc* tabAssoc, char* noeud, unsigned int nbNoeud)
{
	unsigned int i;

	for(i=0;i<tabAssoc->remplissage;i++)
	{
		if(strcmp(tabAssoc->tab[i].noeud,noeud) == 0)
		{
//			printf("Match %s %d\n",noeud,i);
			tabAssoc->tab[i].entier++;
			return;
		}
	}

	if(nbNoeud == tabAssoc->remplissage)
	{
		printf("Erreur trop de noeud\n");
	}
	else
	{
//		printf("Crée %s %d\n",noeud,tabAssoc->remplissage);
		int taille = strlen(noeud)+1;
		tabAssoc->tab[tabAssoc->remplissage].noeud = (char*) malloc(taille*sizeof(char));
		strcpy(tabAssoc->tab[tabAssoc->remplissage].noeud,noeud);
		tabAssoc->tab[tabAssoc->remplissage].entier=1;
		tabAssoc->remplissage++;
	}
}


void decrTabAssoc(struct tabAssoc* tabAssoc, char* noeud)
{
	unsigned int i;

	for(i=0;i<tabAssoc->remplissage;i++)
	{
		if(strcmp(tabAssoc->tab[i].noeud,noeud) == 0)
		{
			tabAssoc->tab[i].entier--;
			return;
		}
	}

	printf("Erreur decr sur noeud non sauvegarde\n");
}
