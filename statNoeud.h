#ifndef __STATNOEUD_H__
#define __STATNOEUD_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct noeud
{
	char* noeud;
	unsigned int nbPaquetDansFile;
	unsigned int tailleFile;
	unsigned int nbPerte;
};

struct statNoeud
{
	unsigned int nbNoeud;
	unsigned int nbPaquetTotalDansFile;
	unsigned int remplissage;
	struct noeud* tabNoeud;
};



void initStatNoeud(struct statNoeud* statNoeud, unsigned int nbNoeud);
void initNoeud(struct statNoeud* statNoeud,char* noeud);
void setTailleFile(struct statNoeud* statNoeud, char* noeud);
void incrNbPaquetDansFile(struct statNoeud* statNoeud, char* noeud);
void decrNbPaquetDansFile(struct statNoeud* tabAssoc, char* noeud);
void incrNbPerte(struct statNoeud* statNoeud, char* noeud);

#endif

