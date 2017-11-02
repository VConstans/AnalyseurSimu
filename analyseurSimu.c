#include "analyseurSimu.h"

int main(int argc, char* argv[])
{
	FILE* fdTrace = ouvertureTrace(argv[1]);

	struct matriceAdj* matAdj = loadMatriceAdjacence(argv[2]);

	struct evt* newEvt;

	struct statGlobal stat;
	stat.paquetEmis=0;
	stat.arriveInter=0;
	stat.departFile=0;
	stat.paquetRecus=0;
	stat.paquetPerdus=0;
	stat.nbFlux=0;
	stat.locPerte=NULL;

	struct listeFlux flux;
	flux.nbFlux=0;
	flux.suivant = NULL;

	struct statNoeud statNoeud;
	initStatNoeud(&statNoeud,matAdj->nbNoeud,matAdj->mat);

	struct statEch statEch;
	statEch.nbPaquetTransit = 0;

	struct fd dataOutput;
	dataOutput.remplissageFile = fopen("remplissageFile.out","w+");
	dataOutput.paquetTransit = fopen("paquetTransit.out","w+");



	initTrace(&flux,fdTrace);


	struct evt* ancienEvt=NULL;

	while((newEvt=nextEvt(fdTrace))!=NULL)
	{
		analyseEvt(newEvt,&stat,&flux,&statNoeud,&statEch);
		writeDataOutput(&dataOutput, newEvt->temps,&statNoeud,&statEch);


		if(ancienEvt!=NULL)
		{
			free(ancienEvt->src);
			free(ancienEvt->dst);
			free(ancienEvt->pos);
			free(ancienEvt);
		}
	}


	printf("Paquet Emis %u\nArrivé noeud inter %u\nDepart fille %u\nPaquet Recus %u\nPaquet perdus %u\nNb flux %u",stat.paquetEmis,stat.arriveInter,stat.departFile,stat.paquetRecus,stat.paquetPerdus,flux.nbFlux);


	return 0;
}
