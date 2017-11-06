#include "listePaquet.h"

struct paquet* createPaquet(struct evt* evt)
{
	struct paquet* maillon = (struct paquet*) malloc(sizeof(struct paquet));

	maillon->numPaquet = evt->pid;

	maillon->emission = evt->temps;

	maillon->tempsFile = 0;
	maillon->tempsLien = 0;

	maillon->positions = initListePosition();


	return maillon;
}


struct paquet* addPaquet(struct evt* evt,struct listePaquet* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		struct paquet* maillon = createPaquet(evt);

		maillon->suivant = NULL;

		liste->suivant=maillon;
		liste->nbPaquet++;
		return maillon;
	}

	struct paquet* curseur = liste->suivant;
	struct paquet* precedant = NULL;

	//File non vide
	while(curseur!=NULL)
	{
		if(evt->pid > curseur->numPaquet)
		{
			precedant = curseur;
			curseur = curseur->suivant;
		}
		else if(evt->pid == curseur->numPaquet)
		{
			return curseur;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			struct paquet* maillon = createPaquet(evt);
			maillon->suivant = curseur;

			liste->nbPaquet++;

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
	struct paquet* maillon = createPaquet(evt);



	maillon->suivant = NULL;
	precedant->suivant = maillon;
	liste->nbPaquet++;
	return maillon;
}



struct paquet* searchPaquet(struct evt* evt, struct listePaquet* liste)
{
	struct paquet* curseur = liste->suivant;

	//File non vide
	while(curseur!=NULL)
	{
		if(evt->pid == curseur->numPaquet)
		{
			return curseur;
		}
		curseur = curseur->suivant;
	}

	return NULL;
}




void setRecepDatePaquet(double temps, struct paquet* paquet)
{
	paquet->reception = temps;
}



void updatePos(struct paquet* paquet)
{
	if(paquet->positions->actuelle == NULL)
	{
		paquet->positions->actuelle = paquet->positions->debut;
	}
	else
	{
		paquet->positions->actuelle = paquet->positions->actuelle->suivant;
	}
}



struct localisationPaquet* posOfNumPaquet(struct paquet* paquet)
{
	struct localisationPaquet* localisation = (struct localisationPaquet*)malloc(sizeof(struct localisationPaquet));

	localisation->noeud = paquet->positions->actuelle->numNoeud;
	localisation->file = paquet->positions->actuelle->suivant->numNoeud;

	return localisation;
}


void delPaquet(struct evt* evt, struct listePaquet* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		printf("Liste vide\n");
		return;
	}

	struct paquet* curseur = liste->suivant;
	struct paquet* precedant = NULL;

	//File non vide
	while(curseur!=NULL)
	{
		if(evt->pid > curseur->numPaquet)
		{
			precedant = curseur;
			curseur = curseur->suivant;
		}
		else if(evt->pid == curseur->numPaquet)
		{
			//TODO
			if(precedant == NULL)
			{
				liste->suivant = curseur->suivant;
			}
			else
			{
				precedant->suivant = curseur->suivant;
			}

			liste->nbPaquet--;

			free(curseur);

			return;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			printf("Paquet pas dans le liste\n");
		}

	}

	//Insertion en fin de liste
	printf("Paquet par trouvé\n");
	return;

}


void setActualTemps(struct evt* evt, struct paquet* paquet)
{
	paquet->tempsTmp = evt->temps;
}

double updateTempsFile(struct evt* evt, struct paquet* paquet)
{
	double duree = evt->temps - paquet->tempsTmp;
	paquet->tempsFile+=duree;
	setActualTemps(evt,paquet);

	return duree;
}

double updateTempsLien(struct evt* evt, struct paquet* paquet)
{
	double duree = evt->temps - paquet->tempsTmp;
	paquet->tempsLien+=duree;
	setActualTemps(evt,paquet);

	return duree;
}
