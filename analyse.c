#include "analyse.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct option* opt, struct fd* fds)
{
	struct paquet* paquet;

	analyseGlobal(evt->code,statG);
	paquet = analyseFlux(evt,listeFlux,opt,fds,statG);
	analyseNoeud(evt,statNoeud,paquet);
	//TODO autre analyse
}

void analyseFinale(struct statGlobal* statG, struct listeFlux* listeFlux, struct option* opt)
{
	analyseFinalFlux(listeFlux,opt,statG);
	//TODO autre analyse
}

void analyseFinalFlux(struct listeFlux* listeFlux,struct option* opt, struct statGlobal* statG)
{
	struct flux* curseur = listeFlux->suivant;
	double sommeDuree = 0;
	unsigned int sommePaquet = 0;

	while(curseur != NULL)
	{
		sommeDuree+=curseur->dureeMoyenne;
		sommePaquet+=curseur->nbPaquet;

		//XXX compraison entre signed et unsigned
		if(curseur->numFlux == (unsigned)opt->traceFlux)
		{
			printf("Nombre de paquets émis: %d\n",curseur->emis);
			printf("Nombre de paquets recu: %d\n",curseur->recu);
			printf("Nombre de paquets perdus: %d (taux de perte: %f)\n",curseur->perdu,(double)curseur->perdu/(double)curseur->emis);
			printf("Durée de vie: %f\n",curseur->tempsFin - curseur->tempsDebut);
			printf("Durée moyenne de bout en bout du flux %d: %f\n",curseur->numFlux,curseur->dureeMoyenne/(double)curseur->recu);
		}

		curseur = curseur->suivant;
	}

	statG->dureeMoyenne = sommeDuree/(double)sommePaquet;


	printf("\n\n----------------------------------------------\n\n");
}


void analyseGlobal(int code, struct statGlobal* statG)
{
	switch(code)
	{
		case 0:
			statG->paquetEmis++;
			statG->nbPaquetTransit++;
			break;
		case 1:
			statG->arriveInter++;
			break;
		case 2:
			statG->departFile++;
			break;
		case 3:
			statG->paquetRecus++;
			statG->nbPaquetTransit--;
			break;
		case 4:
			statG->paquetPerdus++;
			statG->nbPaquetTransit--;
			break;
		
	}
}


struct paquet* analyseFlux(struct evt* evt, struct listeFlux* listeFlux, struct option* opt,struct fd* fds,struct statGlobal* statG)
{
	struct flux* flux = traitementFlux(evt,listeFlux);
	struct paquet* paquet = searchPaquet(evt, flux->paquets);
	double duree;
	double delai;

	switch(evt->code)
	{
		case 0:
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				printf("Départ du noeud %s à temps %f\n",evt->pos,evt->temps);
			}
			setActualTemps(evt,paquet);
			updatePos(paquet);
	//		addAndSetEmissionPaquet(evt,flux->paquets,trace,statNoeud);
			//XXX optimisation mémoire: chargé les info sur le paquet une fois que le paquet à été émis, et pas tout charger des le debut

			if(opt->tracePaquet == (int)evt->pid)
			{
				printf("Source: %s\n",evt->src);
				printf("Destination: %s\n",evt->dst);
			}

			break;
		case 1:
			duree = updateTempsLien(evt,paquet);
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				printf("Arrivé sur le noeud %s à temps %f\nTemps passé sur le lien: %f\n",evt->pos,evt->temps,duree);
			}
			updatePos(paquet);
			break;
		case 2:
			duree = updateTempsFile(evt,paquet);
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				printf("Temps passé sur le lien: %f\n",duree);
			}
	//		updatePos(evt,flux->paquets);	//XXX utile?
			break;
		case 3:
			setRecepDatePaquet(evt->temps,paquet);	//XXX utile?
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				printf("Arrivé à destination (%s) à temps %f\n",evt->pos,evt->temps);
				delai = calculDuree(paquet,flux);
				printf("Delai d'acheminement: %f\n",delai);
				printf("Temps passé dans les files: %f\n",paquet->tempsFile);
				printf("Temps passé sur les liens: %f\n",paquet->tempsLien);
				printf("\n\n----------------------------------------------\n\n");
			}
			addTemps(statG,paquet);
	//		updatePos(evt,flux->paquets);	//XXX utile?
			//XXX optimisation update revoie la position du pauqet et setRecep l'uilise

			//TODO
			if(opt->echDelai != NONE && opt->echDelai == (int)evt->fid)
			{
				delai = calculDuree(paquet,flux);
				courbeDelaiPaquet(fds->delaiPaquet,paquet->numPaquet,delai);
			}
			//XXX IF(paquet trace alors affiche)
			//XXX durée de transmission avant del paquet
			//delPaquet(evt,flux->paquets);
			break;
		case 4:
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				printf("Destruction du paquet au noeud %s à temps %f\n",evt->pos,evt->temps);
				printf("Temps passé dans les files: %f\n",paquet->tempsFile);
				printf("Temps passé sur les liens: %f\n",paquet->tempsLien);
				printf("\n\n----------------------------------------------\n\n");
			}
			addTemps(statG,paquet);
	//		updatePos(evt,flux->paquets);	//XXX utile?
			setRecepDatePaquet(-1,paquet);	//XXX mettre a jour
	}

	return paquet;
}



void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud, struct paquet* paquet)
{
	struct localisationPaquet* localisation;

	localisation = posOfNumPaquet(paquet);

	switch(evt->code)
	{
		case 0:
			incrNbPaquetDansFile(statNoeud,localisation);
			statNoeud->nbPaquetTotalDansFile++;
			break;
		case 1:
			incrNbPaquetDansFile(statNoeud,localisation);
			statNoeud->nbPaquetTotalDansFile++;
			break;
		case 2:
			decrNbPaquetDansFile(statNoeud,localisation);
			statNoeud->nbPaquetTotalDansFile--;
			break;
		case 3:
			decrNbPaquetDansFile(statNoeud,localisation);
			//delPaquet(evt,listePaquet);
			//XXX optimisation mémoire: supprimer les paquets au fur et à mesure
			statNoeud->nbPaquetTotalDansFile--;
			break;
		case 4:
			statNoeud->nbPaquetTotalDansFile--;
			
			setTailleFile(statNoeud,localisation);
			decrNbPaquetDansFile(statNoeud,localisation);

			incrNbPerte(statNoeud,convPosToNum(evt->pos));
			break;
		
	}


	free(localisation);
}
