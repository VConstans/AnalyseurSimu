#include "analyseurSimu.h"

int main(/*TODO arg*/)
{
	FILE* fdTrace = ouvertureTrace("trace2650.txt");

	struct evt* newEvt;

	struct statGlobal stat;
	stat.paquetTraite=0;
	stat.paquetEmis=0;
	stat.paquetRecus=0;
	stat.paquetPerdus=0;
	stat.nbFlux=0;
	stat.locPerte=NULL;


	int cmpt=0;
	struct evt* ancienEvt;

	while((newEvt=nextEvt(fdTrace))!=NULL)
	{
		looping:
		analyseGlobal(newEvt,&stat);

		cmpt++;

		ancienEvt = newEvt;
	}


	printf("Paquet traite %u\nPaquet Emis %u\nPaquet Recus %u\nPaquet perdus %u\n",stat.paquetTraite,stat.paquetEmis,stat.paquetRecus,stat.paquetPerdus);

	printf("cmpt %d\n",cmpt);

	printf("%f %d %u",ancienEvt->temps,ancienEvt->code,ancienEvt->pid);

	return 0;
}
