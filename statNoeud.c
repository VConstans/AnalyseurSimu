#include "statNoeud.h"

//Initialise le tableau de noeud
void initStatNoeud(struct statNoeud* statNoeud, unsigned int nbNoeud, matrice matAdj)
{
	statNoeud->nbNoeud = nbNoeud;
	statNoeud->nbPaquetTotalDansFile = 0;
	statNoeud->tabNoeud = (struct noeud*)malloc(nbNoeud*sizeof(struct noeud));
	statNoeud->remplissage=0;

	unsigned int i;
	for(i=0;i<nbNoeud;i++)
	{
		initNoeud(&(statNoeud->tabNoeud[i]),i+1,nbNoeud,matAdj);
	}
}


//Initialise un noeud
void initNoeud(struct noeud* noeud,unsigned int numNoeud,unsigned int nbNoeud, matrice matAdj)
{
	noeud->numNoeud = numNoeud;
	noeud->nbPaquetDansFile = 0;
	noeud->tailleFile=0;
	noeud->nbPerte=0;
	noeud->nbLien = 0;

	noeud->files = (struct file*)malloc(nbNoeud*sizeof(struct file));

	unsigned int i;
	for(i=0;i<nbNoeud;i++)
	{
		noeud->files[i].dest = i+1;
		noeud->files[i].taille = 0;
		noeud->files[i].remplissage = 0;
		noeud->files[i].debit = debitLien(matAdj,numNoeud,i+1);
		if(noeud->files[i].debit != 0)
		{
			noeud->nbLien++;
		}
	}
}



//Incrémente le nombre de paquet contenu dans une file
void incrNbPaquetDansFile(struct statNoeud* statNoeud, struct localisationPaquet* localisation)
{
	if(localisation->file != -1)
	{
		statNoeud->tabNoeud[localisation->noeud-1].files[localisation->file-1].remplissage++;
		statNoeud->tabNoeud[localisation->noeud-1].nbPaquetDansFile++;
	}
}


//Décrémente le nombre de paquet contenu dans une file
void decrNbPaquetDansFile(struct statNoeud* statNoeud, struct localisationPaquet* localisation)
{
	if(localisation->file != -1)
	{
		statNoeud->tabNoeud[localisation->noeud-1].files[localisation->file-1].remplissage--;
		statNoeud->tabNoeud[localisation->noeud-1].nbPaquetDansFile--;
	}
}


//Incrémente le compteur de nombre de perte
void incrNbPerte(struct statNoeud* statNoeud, unsigned int noeud)
{
	statNoeud->tabNoeud[noeud-1].nbPerte++;
}


//Affiche les perte d'un noeuds
void printNbPerte(struct statNoeud* statNoeud)
{
	printf("Nombre de perte par noeud:\n");
	unsigned int i;
	for(i=0;i<statNoeud->nbNoeud;i++)
	{
		printf("\tnoeud N%d: %d\n",statNoeud->tabNoeud[i].numNoeud, statNoeud->tabNoeud[i].nbPerte);
	}
}
