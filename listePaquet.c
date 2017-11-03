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


/*
void setEmissionPaquet(struct evt* evt,struct listePaquet* liste)
{
	struct paquet* curseur = liste->suivant;

	//File non vide
	while(curseur!=NULL)
	{
		}
		else if(evt->pid == curseur->numPaquet)
		{
			printf("Erreur, paquet déjà emis\n");
			return;
		}
		else *if(numFluxPaquet < curseur->numFlux)
		{
			struct paquet* maillon = createPaquet(evt,trace,statNoeud);
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
			curseur = curseur->suivant;

	}

	//Insertion en fin de liste
	struct paquet* maillon = createPaquet(evt,trace,statNoeud);
	maillon->pos = convPosToNum(evt->src);



	maillon->suivant = NULL;
	precedant->suivant = maillon;
	liste->nbPaquet++;
	return;
}

*/


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

/*
int placementFile(unsigned int numPaquet,FILE* trace,struct statNoeud* statNoeud)
{
	long int backupPosition = ftell(trace);
	struct evt* evtTmp = NULL;

	do
	{
		if(evtTmp!=NULL)
		{
			free(evtTmp->src);
			free(evtTmp->dst);
			free(evtTmp->pos);
			free(evtTmp);
		}
		evtTmp = nextEvt(trace);
		
	} while (evtTmp->pid != numPaquet);

	int retour;

	switch(evtTmp->code)
	{
		case 1:
			//XXX pas de sens
			break;
		case 2:
			retour = convPosToNum(evtTmp->pos);
			break;
		case 3:
			retour = -1;
			//XXX arrive a dest
			break;
		case 4:
			retour = -1;
			//TODO quel file?
			break;
	}

	//TODO verifier si le lien entre les deux noeuds existe rellement
	free(evtTmp->src);
	free(evtTmp->dst);
	free(evtTmp->pos);
	free(evtTmp);

	fseek(trace,backupPosition,SEEK_SET);

	return retour;
}

*/




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
