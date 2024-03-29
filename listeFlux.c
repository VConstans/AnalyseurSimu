#include "listeFlux.h"

//Création et initialisation d'un nouveau flux
struct flux* createFlux(struct evt* evt)
{
	struct flux* maillon = (struct flux*) malloc(sizeof(struct flux));

	maillon->numFlux = evt->fid;
	maillon->nbPaquet = 0;
	maillon->emis=0;
	maillon->recu=0;
	maillon->perdu=0;
	maillon->paquets = (struct listePaquet*)malloc(sizeof(struct listePaquet));
	maillon->paquets->suivant=NULL;
	maillon->paquets->nbPaquet=0;
	maillon->dureeMoyenne = 0;
	maillon->dureeCarreMoyenne = 0;

	maillon->tempsDebut = evt->temps;
	maillon->tempsFin = evt->temps;

	return maillon;
}


//Ajout d'un flux à la liste chainée triée de flux
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



//Traitement d'un flux pour mettre à jour les information statistique concernant les flux
struct flux* traitementFlux(struct evt* evt,struct listeFlux* liste)
{
	struct flux* curseur = liste->suivant;

	while(curseur != NULL)
	{
		if(evt->fid == curseur->numFlux)
		{
			switch(evt->code)
			{
				case 0:
					curseur->emis++;
					curseur->nbPaquet++;
					if(evt->temps == curseur->tempsDebut)
					{
						liste->nbFluxActif++;
					}
					break;
				case 3:
					if(evt->temps == curseur->tempsFin)
					{
						liste->nbFluxActif--;
					}
					curseur->recu++;
					break;
				case 4:
					if(evt->temps == curseur->tempsFin)
					{
						liste->nbFluxActif--;
					}
					curseur->perdu++;
					break;
			}
			

			return curseur;
		}
		curseur = curseur->suivant;
	}
	return NULL;
}






//Renvoie la liste chainée de paquet qui font partit du même flux que l'événement passé en paramètre
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


//Calcul du délai de bout à bout d'un paquet et ajout de ce délai à la variable stockant le cumul des délai pour en calculer la moyenne
double calculDuree(struct paquet* paquet, struct flux* flux)
{
	if(paquet->reception == -1)
	{
		return 0;
	}
	else
	{
		double duree = paquet->reception - paquet->emission;

		flux->dureeMoyenne+=duree;
		flux->dureeCarreMoyenne+=duree*duree;

		return duree;
	}
}



/*Mise en mémoire des flux et paquet de ces flux ainsi que du chemin emprunter par ces paquet pour 
determiner dans quelle file il faut placer un paquet lorsqu'il arrive à un noeud intermédiaire*/
void initTrace(struct listeFlux* listeFlux,FILE* fdTrace)
{
	struct flux* flux;
	struct paquet* paquet;
	struct evt* newEvt;

	while((newEvt=nextEvt(fdTrace))!=NULL)
	{
		if(newEvt->code != 2) 
		{
			flux = addFlux(newEvt,listeFlux);
			paquet = addPaquet(newEvt,flux->paquets);

			unsigned int pos = convPosToNum(newEvt->pos);
			addListePosition(paquet->positions,pos);
		}
		free(newEvt->src);
		free(newEvt->dst);
		free(newEvt->pos);
		free(newEvt);
	}

	fseek(fdTrace,0,SEEK_SET);
}
