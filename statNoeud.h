#ifndef __STATNOEUD_H__
#define __STATNOEUD_H__


#include <stdio.h>
#include <stdlib.h>

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

#endif
