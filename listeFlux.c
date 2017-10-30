#include "listeFlux.h"

void insertion(unsigned int numFluxPaquet, struct listeFlux* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		struct flux* maillon = (struct flux*) malloc(sizeof(struct flux));

		maillon->numFlux = numFluxPaquet;
		maillon->nbPaquet = 1;
		maillon->suivant = NULL;

		liste->suivant=maillon;
		liste->nbFlux++;
		return;
	}

	struct flux* curseur = liste->suivant;
	struct flux* precedant = NULL;

	//File non vide
	while(curseur!=NULL)
	{
		if(numFluxPaquet > curseur->numFlux)
		{
			precedant = curseur;
			curseur = curseur->suivant;
		}
		else if(numFluxPaquet == curseur->numFlux)
		{
			curseur->nbPaquet++;

			return;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			struct flux* maillon = (struct flux*) malloc(sizeof(struct flux));

			maillon->numFlux = numFluxPaquet;
			maillon->nbPaquet = 1;
			maillon->suivant = curseur;

			liste->nbFlux++;

			//Insertion en debut de liste
			if(precedant == NULL)
			{
				liste->suivant = maillon;
				return;
			}
			else
			{
				precedant->suivant = maillon;
				return;
			}
		}

	}

	//Insertion en fin de liste
	struct flux* maillon = (struct flux*) malloc(sizeof(struct flux));

	maillon->numFlux = numFluxPaquet;
	maillon->nbPaquet = 1;
	maillon->suivant = NULL;
	precedant->suivant = maillon;
	liste->nbFlux++;
	return;
}
