#include "analyse.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct statEch* statEch)
{
	struct paquet* paquet;

	analyseGlobal(evt->code,statG);
	paquet = analyseFlux(evt,listeFlux);
	analyseNoeud(evt,statNoeud,paquet);
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


struct paquet* analyseFlux(struct evt* evt, struct listeFlux* listeFlux)
{
	struct flux* flux = traitementFlux(evt,listeFlux);
	struct paquet* paquet = searchPaquet(evt, flux->paquets);
	double duree;

	switch(evt->code)
	{
		case 0:
			updatePos(paquet);
	//		addAndSetEmissionPaquet(evt,flux->paquets,trace,statNoeud);
			//XXX optimisation mémoire: chargé les info sur le paquet une fois que le paquet à été émis, et pas tout charger des le debut
			break;
		case 1:
			updatePos(paquet);
			break;
		case 2:
	//		updatePos(evt,flux->paquets);	//XXX utile?
			break;
		case 3:
	//		updatePos(evt,flux->paquets);	//XXX utile?
			//XXX optimisation update revoie la position du pauqet et setRecep l'uilise
			setRecepPaquet(evt,paquet);	//XXX utile?
			duree = calculDuree(paquet,flux);
			//XXX IF(paquet trace alors affiche)
			//XXX durée de transmission avant del paquet
			//delPaquet(evt,flux->paquets);
			break;
		case 4:
	//		updatePos(evt,flux->paquets);	//XXX utile?
			setRecepPaquet(evt,paquet);	//XXX mettre a jour
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
