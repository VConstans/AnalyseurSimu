#include "listeFlux.h"

struct flux* createFlux(struct evt* evt)
{
	struct flux* maillon = (struct flux*) malloc(sizeof(struct flux));

	maillon->numFlux = evt->fid;
	maillon->nbPaquet = 1;
	maillon->emis=0;
	maillon->recu=0;
	maillon->perdu=0;
	maillon->paquets = (struct listePaquet*)malloc(sizeof(struct listePaquet));
	maillon->paquets->suivant=NULL;
	maillon->paquets->nbPaquet=0;

	switch(evt->code)
	{
		case 0:
			maillon->emis=1;
			break;
		case 3:
			maillon->recu=1;
			break;
		case 4:
			maillon->perdu=1;
			break;
	}

	maillon->tempsDebut = evt->temps;
	maillon->tempsFin = evt->temps;

	return maillon;
}

struct flux* addFlux(struct evt* evt,struct listeFlux* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		struct flux* maillon = createFlux(evt);

		maillon->suivant = NULL;

		liste->suivant=maillon;
		liste->nbFlux++;


		return maillon;
	}

	struct flux* curseur = liste->suivant;
	struct flux* precedant = NULL;

	//File non vide
	while(curseur!=NULL)
	{
		if(evt->fid > curseur->numFlux)
		{
			precedant = curseur;
			curseur = curseur->suivant;
		}
		else if(evt->fid == curseur->numFlux)
		{

			switch(evt->code)
			{
				case 0:
					curseur->emis++;
					curseur->nbPaquet++;
					break;
				case 3:
					curseur->recu++;
					break;
				case 4:
					curseur->perdu++;
					break;
			}

			
			curseur->tempsFin = evt->temps;


			return curseur;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			struct flux* maillon = createFlux(evt);

			maillon->suivant = curseur;

			liste->nbFlux++;


			//Insertion en debut de liste
			if(precedant == NULL)
			{
				liste->suivant = maillon;
				return maillon;
			}
			else
			{
				precedant->suivant = maillon;
				return maillon;
			}
		}

	}

	//Insertion en fin de liste

	struct flux* maillon = createFlux(evt);

	maillon->suivant = NULL;
	precedant->suivant = maillon;


	liste->nbFlux++;
	return maillon;
}


struct listePaquet* listePaquetOfFlux(struct evt* evt, struct listeFlux* listeFlux)
{
	//File vide
	if(listeFlux->suivant == NULL)
	{
		printf("Liste de flux vide\n");
		return NULL;
	}

	struct flux* curseur = listeFlux->suivant;

	//File non vide
	while(curseur!=NULL)
	{
		if(evt->fid > curseur->numFlux)
		{
			curseur = curseur->suivant;
		}
		else if(evt->fid == curseur->numFlux)
		{
			return curseur->paquets;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			printf("Liste de paquet introuvable\n");
			return NULL;
		}

	}


	printf("Liste de paquet introuvable\n");
	
	return NULL;
}
