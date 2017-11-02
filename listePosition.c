#include "listePosition.h"

struct listePosition* initListePosition()
{
	struct listePosition* listePosition = (struct listePosition*)malloc(sizeof(struct listePosition));

	listePosition->debut = NULL;
	listePosition->fin = NULL;
	listePosition->actuelle = NULL;

	return listePosition;
}

void addListePosition(struct listePosition* listePosition, unsigned int numNoeud)
{
	struct position* maillon = (struct position*)malloc(sizeof(struct position));
	maillon->numNoeud = numNoeud;
	maillon->suivant = NULL;


	if(listePosition->debut == NULL)
	{
		listePosition->debut = maillon;
	}
	else
	{
		listePosition->fin->suivant = maillon;
	}
	listePosition->fin = maillon;
}
