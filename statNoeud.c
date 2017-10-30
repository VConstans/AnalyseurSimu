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



