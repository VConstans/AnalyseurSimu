#include "analyseurSimu.h"

int main(int argc, char* argv[])
{
	FILE* fdTrace = ouvertureTrace(argv[1]);

	struct evt* newEvt;

	struct statGlobal stat;
	stat.paquetEmis=0;
	stat.arriveInter=0;
	stat.departFile=0;
	stat.paquetRecus=0;
	stat.paquetPerdus=0;
	stat.nbFlux=0;
	stat.locPerte=NULL;


	int cmpt=0;
	struct evt* ancienEvt=NULL;

	while((newEvt=nextEvt(fdTrace))!=NULL)
	{
		looping:
		analyseGlobal(newEvt,&stat);

		cmpt++;

		if(ancienEvt!=NULL)
		{
			free(ancienEvt->src);
			free(ancienEvt->dst);
			free(ancienEvt->pos);
			free(ancienEvt);
		}
		ancienEvt = newEvt;
	}


	printf("Paquet Emis %u\nArrivé noeud inter %u\nDepart fille %u\nPaquet Recus %u\nPaquet perdus %u\n",stat.paquetEmis,stat.arriveInter,stat.departFile,stat.paquetRecus,stat.paquetPerdus);

	printf("cmpt %d\n",cmpt);

	printf("%f %d %u",ancienEvt->temps,ancienEvt->code,ancienEvt->pid);

	return 0;
}
