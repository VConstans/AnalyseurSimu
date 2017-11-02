#include "analyseurSimu.h"

int main(int argc, char* argv[])
{
	FILE* fdTrace = ouvertureTrace(argv[1]);

	struct matriceAdj* matAdj = loadMatriceAdjacence(argv[2]);

	struct evt* newEvt;

	struct statGlobal stat;

	struct listeFlux flux;

	struct statNoeud statNoeud;

	struct statEch statEch;

	struct fd dataOutput;


	initAnalyse(&stat,&flux,&statNoeud,&statEch,&dataOutput,matAdj);

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


void initAnalyse(struct statGlobal* statG, struct listeFlux* flux, struct statNoeud* statNoeud, struct statEch* statEch, struct fd* dataOutput, struct matriceAdj* matAdj)
{
	statG->paquetEmis=0;
	statG->arriveInter=0;
	statG->departFile=0;
	statG->paquetRecus=0;
	statG->paquetPerdus=0;
	statG->nbFlux=0;
	statG->locPerte=NULL;

	flux->nbFlux=0;
	flux->suivant = NULL;

	initStatNoeud(statNoeud,matAdj->nbNoeud,matAdj->mat);

	statEch->nbPaquetTransit = 0;

	dataOutput->remplissageFile = fopen("remplissageFile.out","w+");
	dataOutput->paquetTransit = fopen("paquetTransit.out","w+");
}
