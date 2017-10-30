#ifndef __STATNOEUD_H__
#define __STATNOEUD_H__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct assocNoeudEntier
{
	char* noeud;
	unsigned int entier;
};

struct tabAssoc
{
	struct assocNoeudEntier* tab;
	unsigned int remplissage;
};

struct statNoeud
{
	unsigned int nbNoeud;
	struct tabAssoc nbPaquetDansFile;
	unsigned int nbPaquetTotalDansFile;
	struct tabAssoc tailleFile;
	struct tabAssoc nbPerte;
};


void initStatNoeud(struct statNoeud* statNoeud, unsigned int nbNoeud);
void setValTabAssoc(struct tabAssoc* tabAssoc, char* noeud, unsigned int val, unsigned int nbNoeud);
void incrTabAssoc(struct tabAssoc* tabAssoc, char* noeud, unsigned int nbNoeud);
void decrTabAssoc(struct tabAssoc* tabAssoc, char* noeud);

#endif
