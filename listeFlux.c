#include "listeFlux.h"

void insertion(unsigned int numFluxPaquet, struct evt* evt,struct listeFlux* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		struct flux* maillon = (struct flux*) malloc(sizeof(struct flux));

		maillon->numFlux = numFluxPaquet;
		maillon->nbPaquet = 1;
		maillon->emis=0;
		maillon->recus=0;
		maillon->perdu=0;

		switch(evt->code)
		{
			case 0:
				maillon->emis=1;
				break;
			case 3:
				maillon->recus=1;
				break;
			case 4:
				maillon->perdu=1;
				break;
		}

		maillon->tempsDebut = evt->temps;
		maillon->tempsFin = evt->temps;

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

			switch(evt->code)
			{
				case 0:
					curseur->emis++;
					break;
				case 3:
					curseur->recus++;
					break;
				case 4:
					curseur->perdu++;
					break;
			}

			
			curseur->tempsFin = evt->temps;

			return;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			struct flux* maillon = (struct flux*) malloc(sizeof(struct flux));

			maillon->numFlux = numFluxPaquet;
			maillon->nbPaquet = 1;

			maillon->emis=0;
			maillon->recus=0;
			maillon->perdu=0;

			switch(evt->code)
			{
				case 0:
					maillon->emis=1;
					break;
				case 3:
					maillon->recus=1;
					break;
				case 4:
					maillon->perdu=1;
					break;
			}

			maillon->tempsDebut = evt->temps;
			maillon->tempsFin = evt->temps;


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

	maillon->emis=0;
	maillon->recus=0;
	maillon->perdu=0;

	switch(evt->code)
	{
		case 0:
			maillon->emis=1;
			break;
		case 3:
			maillon->recus=1;
			break;
		case 4:
			maillon->perdu=1;
			break;
	}

	maillon->tempsDebut = evt->temps;
	maillon->tempsFin = evt->temps;

	maillon->suivant = NULL;
	precedant->suivant = maillon;
	liste->nbFlux++;
	return;
}
