#include "analyse.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct statEch* statEch, FILE* trace)
{
	analyseGlobal(evt->code,statG);
	analyseFlux(evt,listeFlux,trace,statNoeud);
	analyseNoeud(evt,statNoeud,listeFlux);
	analyseEch(evt->code,statEch);
	//TODO autre analyse
}

void analyseFinale(struct statGlobal* statG, struct listeFlux* listeFlux, unsigned int fluxTracer)
{
	analyseFinalFlux(listeFlux,fluxTracer,statG);
	//TODO autre analyse
}

void analyseFinalFlux(struct listeFlux* listeFlux,unsigned int fluxTracer, struct statGlobal* statG)
{
	struct flux* curseur = listeFlux->suivant;
	double sommeDuree = 0;
	unsigned int sommePaquet = 0;

	while(curseur != NULL)
	{
		sommeDuree+=curseur->dureeMoyenne;
		sommePaquet+=curseur->nbPaquet;

		if(curseur->numFlux == fluxTracer)
		{
			printf("Nombre de paquets émis: %d\n",curseur->emis);
			printf("Nombre de paquets recu: %d\n",curseur->recu);
			printf("Nombre de paquets perdus: %d (taux de perte: %f)\n",curseur->perdu,(double)curseur->perdu/(double)curseur->emis);
			printf("Durée de vie: %f\n",curseur->tempsFin - curseur->tempsDebut);
			printf("Durée moyenne de bout en bout du flux %d: %f\n",curseur->numFlux,curseur->dureeMoyenne/(double)curseur->nbPaquet);
		}
	}

	statG->dureeMoyenne = sommeDuree/(double)sommePaquet;
}


void analyseGlobal(int code, struct statGlobal* statG)
{
	switch(code)
	{
		case 0:
			statG->paquetEmis++;
			break;
		case 1:
			statG->arriveInter++;
			break;
		case 2:
			statG->departFile++;
			break;
		case 3:
			statG->paquetRecus++;
			break;
		case 4:
			statG->paquetPerdus++;
			break;
		
	}
}


void analyseEch(int code, struct statEch* statEch)
{
	switch(code)
	{
		case 0:
			statEch->nbPaquetTransit++;
			break;
		case 3:
			statEch->nbPaquetTransit--;
			break;
		case 4:
			statEch->nbPaquetTransit--;
			break;
	}
}


void analyseFlux(struct evt* evt, struct listeFlux* listeFlux,FILE* trace, struct statNoeud* statNoeud)
{
	struct flux* flux = addFlux(evt,listeFlux);
	struct paquet* paquet;
	double duree;

	switch(evt->code)
	{
		case 0:
			addAndSetEmissionPaquet(evt,flux->paquets,trace,statNoeud);
			break;
		case 1:
			updatePos(evt,flux->paquets,trace,statNoeud);
			break;
		case 2:
	//		updatePos(evt,flux->paquets);	//XXX utile?
			break;
		case 3:
	//		updatePos(evt,flux->paquets);	//XXX utile?
			//XXX optimisation update revoie la position du pauqet et setRecep l'uilise
			paquet = setRecepPaquet(evt,flux->paquets);	//XXX utile?
			duree = calculDuree(paquet,flux);
			//XXX IF(paquet trace alors affiche)
			//XXX durée de transmission avant del paquet
			//delPaquet(evt,flux->paquets);
			break;
		case 4:
	//		updatePos(evt,flux->paquets);	//XXX utile?
			setRecepPaquet(evt,flux->paquets);	//XXX utile?
	}
}



void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud, struct listeFlux* listeFlux)
{
	struct localisationPaquet* localisation;
	struct listePaquet* listePaquet;

	listePaquet = listePaquetOfFlux(evt,listeFlux);
	//TODO verifier retour listePaquet
	localisation = posOfNumPaquet(evt->pid, listePaquet);
	/*XXX Utilisé des poiteur vers les paquets dans les noeuds, amélioration de la complexite*/
	/*XXX pas performant*/

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
			delPaquet(evt,listePaquet);
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
