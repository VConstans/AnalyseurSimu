#include "analyse.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG)
{
	analyseGlobal(evt,statG);
}

void analyseGlobal(struct evt* evt, struct statGlobal* statG)
{
	switch(evt->code)
	{
		case 0:
			statG->paquetEmis++;
			break;
		case 2:
			statG->paquetTraite++;
			break;
		case 3:
			statG->paquetRecus++;
			break;
		case 4:
			statG->paquetPerdus++;
			break;
		
	}
}
