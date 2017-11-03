#ifndef __STATNOEUD_H__
#define __STATNOEUD_H__


#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "localisationPaquet.h"
#include "matrice.h"
#include "listeFile.h"

struct noeud
{
	unsigned int numNoeud;
	unsigned int nbPaquetDansFile;
	unsigned int nbLien;
	unsigned int tailleFile;
	unsigned int nbPerte;
	struct file* files;
};

struct statNoeud
{
	unsigned int nbNoeud;
	unsigned int nbPaquetTotalDansFile;
	unsigned int remplissage;
	struct noeud* tabNoeud;
};



void initStatNoeud(struct statNoeud* statNoeud, unsigned int nbNoeud, matrice matAdj);
void initNoeud(struct noeud* noeud,unsigned int numNoeud, unsigned int nbNoeud, matrice matAdj);
void setTailleFile(struct statNoeud* statNoeud, struct localisationPaquet* localisation);
void incrNbPaquetDansFile(struct statNoeud* statNoeud, struct localisationPaquet* localisation);
void decrNbPaquetDansFile(struct statNoeud* tabAssoc, struct localisationPaquet* localisation);
void incrNbPerte(struct statNoeud* statNoeud, unsigned int noeud);
void printNbPerte(struct statNoeud* statNoeud);

#endif

