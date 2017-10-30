#include "listeFlux.h"

struct listeFlux* insertion(unsigned int numFluxPaquet, struct listeFlux* liste)
{
	//File vide
	if(liste == NULL)
	{
		struct listeFlux* maillon = (struct listeFlux*) malloc(sizeof(struct listeFlux));

		maillon->numFlux = numFluxPaquet;
		maillon->nbPaquet = 1;
		maillon->suivant = NULL;

		return maillon;
	}

	struct listeFlux* curseur = liste;
	struct listeFlux* precedant = NULL;

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

			return liste;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			struct listeFlux* maillon = (struct listeFlux*) malloc(sizeof(struct listeFlux));

			maillon->numFlux = numFluxPaquet;
			maillon->nbPaquet = 1;
			maillon->suivant = curseur;

			//Insertion en debut de liste
			if(precedant == NULL)
			{
				return maillon;
			}
			else
			{
				precedant->suivant = maillon;

				return liste;
			}
		}

	}

	//Insertion en fin de liste
	struct listeFlux* maillon = (struct listeFlux*) malloc(sizeof(struct listeFlux));

	maillon->numFlux = numFluxPaquet;
	maillon->nbPaquet = 1;
	maillon->suivant = NULL;
	precedant->suivant = maillon;
	return liste;
}
