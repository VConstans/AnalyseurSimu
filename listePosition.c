//CONSTANS Victor

#include "listePosition.h"


//Initialisation de la liste chainée des noeuds traversé par un paquet
struct listePosition* initListePosition()
{
	struct listePosition* listePosition = (struct listePosition*)malloc(sizeof(struct listePosition));

	listePosition->debut = NULL;
	listePosition->fin = NULL;
	listePosition->actuelle = NULL;

	return listePosition;
}


//Ajout d'un noeud traversé par un paquet à la liste de ce paquet
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
