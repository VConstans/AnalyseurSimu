#include "listePaquet.h"

struct paquet* createPaquet(struct evt* evt)
{
	struct paquet* maillon = (struct paquet*) malloc(sizeof(struct paquet));

	maillon->numPaquet = evt->pid;

	maillon->emission = evt->temps;

	int taille = strlen(evt->src)+1;
	maillon->pos = (char*)malloc(taille*sizeof(char));

	strcpy(maillon->pos,evt->src);

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
	strcpy(maillon->pos,evt->src);



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
			free(curseur->pos);
			int taille = strlen(evt->pos)+1;
			curseur->pos = (char*)malloc(taille*sizeof(char*));

			strcpy(curseur->pos,evt->pos);
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


char* posOfNumPaquet(unsigned int numPaquet, struct listePaquet* liste)
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
			return curseur->pos;
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

			free(curseur->pos);
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
