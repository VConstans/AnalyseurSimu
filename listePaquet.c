#include "listePaquet.h"

void addAndSetEmissionPaquet(unsigned int numPaquet, struct evt* evt,struct listePaquet* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		struct paquet* maillon = (struct paquet*) malloc(sizeof(struct paquet));

		maillon->numPaquet = numPaquet;

		maillon->emission = evt->temps;

		maillon->suivant = NULL;

		liste->suivant=maillon;
		liste->nbPaquet++;
		return;
	}

	struct paquet* curseur = liste->suivant;
	struct paquet* precedant = NULL;

	//File non vide
	while(curseur!=NULL)
	{
		if(numPaquet > curseur->numPaquet)
		{
			precedant = curseur;
			curseur = curseur->suivant;
		}
		else if(numPaquet == curseur->numPaquet)
		{
			printf("Erreur, paquet déjà emis\n");
			return;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			struct paquet* maillon = (struct paquet*) malloc(sizeof(struct paquet));

			maillon->numPaquet = numPaquet;
			maillon->emission = evt->temps;

			maillon->suivant = curseur;

			liste->nbPaquet++;

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
	struct paquet* maillon = (struct paquet*) malloc(sizeof(struct paquet));

	maillon->numPaquet = numPaquet;
	maillon->emission = evt->temps;

	maillon->suivant = NULL;
	precedant->suivant = maillon;
	liste->nbPaquet++;
	return;
}




void SetRecepPaquet(unsigned int numPaquet,struct evt* evt, struct listePaquet* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		printf("Erreur: message pas encore émis\n");
		return;
	}

	struct paquet* curseur = liste->suivant;

	//File non vide
	while(curseur!=NULL)
	{
		if(numPaquet > curseur->numPaquet)
		{
			curseur = curseur->suivant;
		}
		else if(numPaquet == curseur->numPaquet)
		{
			curseur->reception = evt->temps;
			return;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			printf("Erreur: message pas encore émis\n");
			return;
		}

	}

	//Insertion en fin de liste
	printf("Erreur: message pas encore émis\n");
	return;

}
