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
	opt.echFluxActif = NONE;
	opt.echDelai = NONE;
	opt.echPerdu = NONE;
	opt.echLien = NONE;


	while((arg=getopt(argc,argv,"i:m:p:x:f:F:tad:Pl")) != -1)
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
			case 'a':
				opt.echFluxActif = ACTIVE;
				break;
			case 'd':
				opt.echDelai = atoi(optarg);
				break;
			case 'P':
				opt.echPerdu = ACTIVE;
				break;
			case 'l':
				opt.echLien = ACTIVE;
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

	struct listeLien listeLien;


	initAnalyse(&stat,&flux,&statNoeud,&dataOutput,matAdj,&listeLien,&opt);

	initTrace(&flux,fdTrace);


	struct evt* ancienEvt=NULL;

	while((newEvt=nextEvt(fdTrace))!=NULL)
	{
		analyseEvt(newEvt,&stat,&flux,&statNoeud,&opt,&dataOutput,matAdj,&listeLien);
		writeDataOutput(&dataOutput, newEvt->temps,&statNoeud,&stat,&flux,&opt);


		if(ancienEvt!=NULL)
		{
			free(ancienEvt->src);
			free(ancienEvt->dst);
			free(ancienEvt->pos);
			free(ancienEvt);
		}
	}

	analyseFinale(&stat,&flux,&opt,&dataOutput,&listeLien);


	printf("Paquet Emis %d\nArrivé noeud inter %d\nDepart fille %d\nPaquet Recus %d\nPaquet perdus %d (taux de perte %f%%)\nNb flux %d\n",stat.paquetEmis,stat.arriveInter,stat.departFile,stat.paquetRecus,stat.paquetPerdus,(double)stat.paquetPerdus/(double)stat.paquetEmis,flux.nbFlux);
	printf("Délai moyen de bout en bout: %f\n",stat.dureeMoyenne);
	printf("Ecart type: %f\n",stat.ecartType);
	printf("Variance: %f\n",stat.ecartType*stat.ecartType);
	printf("Intervalle de confiance à 68%%: [%f , %f]\n",stat.dureeMoyenne-stat.ecartType,stat.dureeMoyenne+stat.ecartType);
	printf("Intervalle de confiance à 95%%: [%f , %f]\n",stat.dureeMoyenne-2*stat.ecartType,stat.dureeMoyenne+2*stat.ecartType);
	printf("Intervalle de confiance à 99%%: [%f , %f]\n",stat.dureeMoyenne-3*stat.ecartType,stat.dureeMoyenne+3*stat.ecartType);
	printf("Temps d'attente cumulé dans les files: %f\n",stat.tempsFile);
	printf("Temps d'attente cumulé dans les liens: %f\n",stat.tempsLien);

	printNbPerte(&statNoeud);

	return 0;
}


void initAnalyse(struct statGlobal* statG, struct listeFlux* flux, struct statNoeud* statNoeud, struct fd* dataOutput, struct matriceAdj* matAdj, struct listeLien* listeLien,struct option* opt)
{
	statG->paquetEmis=0;
	statG->arriveInter=0;
	statG->departFile=0;
	statG->paquetRecus=0;
	statG->paquetPerdus=0;
	statG->nbFlux=0;
	statG->locPerte=NULL;
	statG->nbPaquetTransit = 0;
	statG->tempsFile = 0;
	statG->tempsLien = 0;
	statG->dureeMoyenne=0;
	statG->dureeCarreMoyenne=0;
	statG->ecartType = 0;

	flux->nbFlux=0;
	flux->suivant = NULL;
	flux->nbFluxActif = 0;
	
	initStatNoeud(statNoeud,matAdj->nbNoeud,matAdj->mat);

	if(opt->echFile != NONE)
	{
		dataOutput->remplissageFile = fopen("remplissageFile.out","w+");
	}
	if(opt->echTransit != NONE)
	{
		dataOutput->paquetTransit = fopen("paquetTransit.out","w+");
	}
	if(opt->echFluxActif != NONE)
	{
		dataOutput->fluxActif = fopen("fluxActif.out","w+");
	}
	if(opt->echDelai != NONE)
	{
		dataOutput->delaiPaquet = fopen("delaiPaquet.out","w+");
	}
	if(opt->echPerdu != NONE)
	{
		dataOutput->paquetPerdu = fopen("paquetPerdu.out","w+");
	}
	if(opt->echLien != NONE)
	{
		dataOutput->utilisationLien = fopen("utilisationLien.out","w+");
	}

	initListeLien(listeLien,matAdj);
}
