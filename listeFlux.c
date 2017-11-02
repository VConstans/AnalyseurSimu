#include "listeFlux.h"

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
		curseur = curseur->suivant;
	}
	return NULL;
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


double calculDuree(struct paquet* paquet, struct flux* flux)
{
	double duree = paquet->emission - paquet->reception;

	flux->dureeMoyenne+=duree;

	return duree;
}


void initTrace(struct listeFlux* listeFlux,FILE* fdTrace)
{
	struct flux* flux;
	struct paquet* paquet;
	struct evt* newEvt;

	while((newEvt=nextEvt(fdTrace))!=NULL)
	{
		flux = addFlux(newEvt,listeFlux);
		paquet = addPaquet(newEvt,flux->paquets);
		unsigned int pos = convPosToNum(newEvt->pos);
		addListePosition(paquet->positions,pos);

		free(newEvt->src);
		free(newEvt->dst);
		free(newEvt->pos);
		free(newEvt);
	}

	fseek(fdTrace,0,SEEK_SET);
}
