#include "listePaquet.h"

struct paquet* createPaquet(struct evt* evt,FILE* trace,struct statNoeud* statNoeud)
{
	struct paquet* maillon = (struct paquet*) malloc(sizeof(struct paquet));

	maillon->numPaquet = evt->pid;

	maillon->emission = evt->temps;

	maillon->pos = convPosToNum(evt->pos);

	maillon->file = placementFile(maillon->numPaquet,trace,statNoeud);


	return maillon;
}

void addAndSetEmissionPaquet(struct evt* evt,struct listePaquet* liste, FILE* trace, struct statNoeud* statNoeud)
{
	//File vide
	if(liste->suivant == NULL)
	{
		struct paquet* maillon = createPaquet(evt,trace, statNoeud);

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
		if(evt->pid > curseur->numPaquet)
		{
			precedant = curseur;
			curseur = curseur->suivant;
		}
		else if(evt->pid == curseur->numPaquet)
		{
			printf("Erreur, paquet déjà emis\n");
			return;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
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

	}

	//Insertion en fin de liste
	struct paquet* maillon = createPaquet(evt,trace,statNoeud);
	maillon->pos = convPosToNum(evt->src);



	maillon->suivant = NULL;
	precedant->suivant = maillon;
	liste->nbPaquet++;
	return;
}




struct paquet* setRecepPaquet(struct evt* evt, struct listePaquet* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		printf("Erreur: message pas encore émis\n");
		return NULL;
	}

	struct paquet* curseur = liste->suivant;

	//File non vide
	while(curseur!=NULL)
	{
		if(evt->pid > curseur->numPaquet)
		{
			curseur = curseur->suivant;
		}
		else if(evt->pid == curseur->numPaquet)
		{
			curseur->reception = evt->temps;
			return curseur;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			printf("Erreur: message pas encore émis\n");
			return NULL;
		}

	}

	//Insertion en fin de liste
	printf("Erreur: message pas encore émis\n");
	return NULL;

}


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

void updatePos(struct evt* evt, struct listePaquet* liste, FILE* trace, struct statNoeud* statNoeud)
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
		if(evt->pid > curseur->numPaquet)
		{
			curseur = curseur->suivant;
		}
		else if(evt->pid == curseur->numPaquet)
		{
			curseur->pos = convPosToNum(evt->pos);

			curseur->file = placementFile(curseur->numPaquet,trace,statNoeud);

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


struct localisationPaquet* posOfNumPaquet(unsigned int numPaquet, struct listePaquet* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		printf("Erreur: message pas encore émis\n");
		return NULL;
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
			struct localisationPaquet* localisation = (struct localisationPaquet*)malloc(sizeof(struct localisationPaquet));
			localisation->noeud = curseur->pos;
			localisation->file = curseur->file;
			//TODO verifier si le lien entre les deux noeuds existe rellement
			return localisation;
		}
		else /*if(numFluxPaquet < curseur->numFlux)*/
		{
			printf("Erreur: message pas encore émis\n");
			return NULL;
		}

	}

	//Insertion en fin de liste
	printf("Erreur: message pas encore émis\n");
	return NULL;
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
