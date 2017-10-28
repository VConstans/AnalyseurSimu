#include "analyse.h"
#include "trace.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG)
{
	analyseGlobal(evt,statG);
	//TODO autre analyse
}

void analyseGlobal(struct evt* evt, struct statGlobal* statG)
{
	switch(evt->code)
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
