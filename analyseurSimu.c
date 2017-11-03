#include "analyseurSimu.h"

int main(int argc, char* argv[])
{
	if(argc < 5)
	{
		printf("Usage: %s -i <trace_file> -m <matrice_file> [-p trace_packet] [-f trace_flux]\n",argv[0]);
		exit(-1);
	}

	int arg;

	struct option opt;
	opt.tracePaquet = NONE;
	opt.traceFlux = NONE;
	opt.echFile = NONE;
	opt.echFileDetail = NONE;
	opt.echTransit = NONE;

	while((arg=getopt(argc,argv,"i:m:p:x:f:F:t")) != -1)
	{
		switch(arg)
		{
			case 'i':
				//opt.traceFile = (char*)malloc(strlen(optarg)*sizeof(char*));
				opt.traceFile = optarg;
				break;
			case 'm':
				//opt.matriceFile = (char*)malloc(strlen(optarg)*sizeof(char*));
				opt.matriceFile = optarg;
				break;
			case 'p':
				opt.tracePaquet = atoi(optarg);
				break;
			case 'x':
				opt.traceFlux = atoi(optarg);
				break;
			case 'f':
				if(strcmp(optarg,"sum") == 0)
				{
					opt.echFile = SUM;
				}
				else if(strcmp(optarg,"all") == 0)
				{
					opt.echFile = ALL;
				}
				else
				{
					opt.echFile = atoi(optarg)-1;
				}

				break;
			case 'F':
				if(strcmp(optarg,"all") == 0)
				{
					opt.echFileDetail = ALL;
				}
				else
				{
					opt.echFileDetail = atoi(optarg)-1;
				}

				break;
			case 't':
				opt.echTransit = ACTIVE;
				break;
			default:
				printf("Erreur, option non valide\n");
				exit(-1);
				break;
		}
	}

	FILE* fdTrace = ouvertureTrace(opt.traceFile);

	struct matriceAdj* matAdj = loadMatriceAdjacence(opt.matriceFile);

	struct evt* newEvt;

	struct statGlobal stat;

	struct listeFlux flux;

	struct statNoeud statNoeud;

	struct fd dataOutput;


	initAnalyse(&stat,&flux,&statNoeud,&dataOutput,matAdj);

	initTrace(&flux,fdTrace);


	struct evt* ancienEvt=NULL;

	while((newEvt=nextEvt(fdTrace))!=NULL)
	{
		analyseEvt(newEvt,&stat,&flux,&statNoeud,&opt);
		writeDataOutput(&dataOutput, newEvt->temps,&statNoeud,&stat,&opt);


		if(ancienEvt!=NULL)
		{
			free(ancienEvt->src);
			free(ancienEvt->dst);
			free(ancienEvt->pos);
			free(ancienEvt);
		}
	}

	analyseFinale(&stat,&flux,&opt);


	printf("Paquet Emis %u\nArrivé noeud inter %u\nDepart fille %u\nPaquet Recus %u\nPaquet perdus %u\nNb flux %u",stat.paquetEmis,stat.arriveInter,stat.departFile,stat.paquetRecus,stat.paquetPerdus,flux.nbFlux);


	return 0;
}


void initAnalyse(struct statGlobal* statG, struct listeFlux* flux, struct statNoeud* statNoeud, struct fd* dataOutput, struct matriceAdj* matAdj)
{
	statG->paquetEmis=0;
	statG->arriveInter=0;
	statG->departFile=0;
	statG->paquetRecus=0;
	statG->paquetPerdus=0;
	statG->nbFlux=0;
	statG->locPerte=NULL;
	statG->nbPaquetTransit = 0;

	flux->nbFlux=0;
	flux->suivant = NULL;
	flux->nbFluxActif = 0;
	
	initStatNoeud(statNoeud,matAdj->nbNoeud,matAdj->mat);

	dataOutput->remplissageFile = fopen("remplissageFile.out","w+");
	dataOutput->paquetTransit = fopen("paquetTransit.out","w+");
}
