#include "listePaquet.h"

struct paquet* createPaquet(struct evt* evt)
{
	struct paquet* maillon = (struct paquet*) malloc(sizeof(struct paquet));

	maillon->numPaquet = evt->pid;

	maillon->emission = evt->temps;

	maillon->pos = convPosToNum(evt->pos);


	return maillon;
}

void addAndSetEmissionPaquet(struct evt* evt,struct listePaquet* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		struct paquet* maillon = createPaquet(evt);

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
			struct paquet* maillon = createPaquet(evt);
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
	struct paquet* maillon = createPaquet(evt);
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


void updatePos(struct evt* evt, struct listePaquet* liste)
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
			//TODO update file

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
