#include "analyse.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct statEch* statEch)
{
	analyseGlobal(evt->code,statG);
	analyseFlux(evt,listeFlux);
	analyseNoeud(evt,statNoeud);
	analyseEch(evt->code,statEch);
	//TODO autre analyse
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


void analyseFlux(struct evt* evt, struct listeFlux* listeFlux)
{
	addFlux(evt,listeFlux);
	//TODO autre analyse
}



void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud)
{
	switch(evt->code)
	{
		case 0:
			incrTabAssoc(&(statNoeud->nbPaquetDansFile),evt->pos,statNoeud->nbNoeud);
			statNoeud->nbPaquetTotalDansFile++;
			break;
		case 1:
			incrTabAssoc(&(statNoeud->nbPaquetDansFile),evt->pos,statNoeud->nbNoeud);
			statNoeud->nbPaquetTotalDansFile++;
			break;
		case 2:
		//	decrTabAssoc(&(statNoeud->nbPaquetDansFile),evt->pos);
			//TODO decr
			statNoeud->nbPaquetTotalDansFile--;
			break;
		case 3:
		//	decrTabAssoc(&(statNoeud->nbPaquetDansFile),evt->pos);
			statNoeud->nbPaquetTotalDansFile--;
			break;
		case 4:
			statNoeud->nbPaquetTotalDansFile--;
//			setValTabAssoc(&(statG->tailleFile),evt->pos,statG->nbPaquetDansFile[evt->pos];
		//	decrTabAssoc(&(statNoeud->nbPaquetDansFile),evt->pos);

			incrTabAssoc(&(statNoeud->nbPerte),evt->pos,statNoeud->nbNoeud);
			break;
		
	}
}
