#include "analyse.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud)
{
	analyseGlobal(evt->code,statG);
	analyseFlux(evt->fid,listeFlux);
	analyseNoeud(evt,statNoeud);
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


void analyseFlux(unsigned int fid, struct listeFlux* listeFlux)
{
	insertion(fid,listeFlux);
	//TODO autre analyse
}



void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud)
{
	switch(evt->code)
	{
		case 0:
			break;
		case 1:
//			statNoeud->nbPaquetDansFile[evt->pos]++;
			statNoeud->nbPaquetTotalDansFile++;
			break;
		case 2:
//			statNoeud->nbPaquetDansFile[evt->pos]--;
			statNoeud->nbPaquetTotalDansFile--;
			break;
		case 3:
			break;
		case 4:
//			statG->tailleFile[evt->pos]=statG->nbPaquetDansFile[evt->pos];
			break;
		
	}
}
