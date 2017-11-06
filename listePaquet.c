//CONSTANS Victor

#include "listePaquet.h"


//Créé et initialise un paquet
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


//Ajoute un paquet à la liste chainée triée des paquets
struct paquet* addPaquet(struct evt* evt,struct listePaquet* liste)
{
	//File vide
	if(liste->suivant == NULL)
	{
		struct paquet* maillon = createPaquet(evt);

		maillon->suivant = NULL;
		maillon->precedant = NULL;

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
			maillon->precedant = precedant;

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
	maillon->precedant = precedant;
	precedant->suivant = maillon;
	liste->nbPaquet++;
	return maillon;
}



//Renvoie le paquet recherché
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




//Inscrit la date de recpetion du paquet
void setRecepDatePaquet(double temps, struct paquet* paquet)
{
	paquet->reception = temps;
}




//Avance le pointeur de la position courante du paquet dans la liste des noeuds traversé par le paquet
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



//Indique la localisation du paquet (noeud et file)
struct localisationPaquet* posOfNumPaquet(struct paquet* paquet)
{
	struct localisationPaquet* localisation = (struct localisationPaquet*)malloc(sizeof(struct localisationPaquet));

	localisation->noeud = paquet->positions->actuelle->numNoeud;
	localisation->file = paquet->positions->actuelle->suivant->numNoeud;

	return localisation;
}



//Supprime un paquet de la liste chainée
void delPaquet(struct listePaquet* liste, struct paquet* paquet)
{
	if(paquet->precedant == NULL)
	{
		liste->suivant = paquet->suivant;
	}
	else
	{
		paquet->precedant->suivant = paquet->suivant;
	}
	if( paquet->suivant != NULL)
	{
		paquet->suivant->precedant = paquet->precedant;
	}

	liste->nbPaquet--;

	free(paquet);

	return;
}



//Inscrit le temps actuel dans une variable
void setActualTemps(struct evt* evt, struct paquet* paquet)
{
	paquet->tempsTmp = evt->temps;
}


//Ajoute le temps passé dans une file
double updateTempsFile(struct evt* evt, struct paquet* paquet)
{
	double duree = evt->temps - paquet->tempsTmp;
	paquet->tempsFile+=duree;
	setActualTemps(evt,paquet);

	return duree;
}


//Ajoute le temps passé sur un lien
double updateTempsLien(struct evt* evt, struct paquet* paquet)
{
	double duree = evt->temps - paquet->tempsTmp;
	paquet->tempsLien+=duree;
	setActualTemps(evt,paquet);

	return duree;
}
