#include "analyse.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux)
{
	analyseGlobal(evt->code,statG);
	analyseFlux(evt->fid,listeFlux);
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
