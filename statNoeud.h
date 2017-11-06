#ifndef __STATNOEUD_H__
#define __STATNOEUD_H__


#include <stdio.h>
#include <stdlib.h>
#include "localisationPaquet.h"
#include "matrice.h"
#include "listeFile.h"

//Représentation des noeuds
struct noeud
{
	unsigned int numNoeud;	//Numéro du noeud
	unsigned int nbPaquetDansFile;	//Dans de paquet dans les files du noeud
	unsigned int nbLien;	//nombre de lien qui parte du noeud
	unsigned int tailleFile;	
	unsigned int nbPerte;	//nombre de perte de ce noeud
	struct file* files;	//liste des files de ce noeud
};

struct statNoeud
{
	unsigned int nbNoeud;	//nombre de noeud dans le système
	unsigned int nbPaquetTotalDansFile;	//Nombre de paquet total dans les files
	unsigned int remplissage;	
	struct noeud* tabNoeud;		//Liste chainée des noeuds
};



void initStatNoeud(struct statNoeud* statNoeud, unsigned int nbNoeud, matrice matAdj);
void initNoeud(struct noeud* noeud,unsigned int numNoeud, unsigned int nbNoeud, matrice matAdj);
void incrNbPaquetDansFile(struct statNoeud* statNoeud, struct localisationPaquet* localisation);
void decrNbPaquetDansFile(struct statNoeud* tabAssoc, struct localisationPaquet* localisation);
void incrNbPerte(struct statNoeud* statNoeud, unsigned int noeud);
void printNbPerte(struct statNoeud* statNoeud);

#endif

