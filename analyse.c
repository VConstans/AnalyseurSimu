#include "analyse.h"

double tempsEstimationTaille;
double estimationTaille;
int condEstimationTaille = 1;



void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct option* opt, struct fd* fds, struct matriceAdj* matAdj,struct listeLien* listeLien)
{
	struct paquet* paquet;

	analyseGlobal(evt->code,statG);
	paquet = analyseFlux(evt,listeFlux,opt,fds,statG,matAdj,listeLien);
	analyseNoeud(evt,statNoeud,paquet);
	//TODO autre analyse
}

void analyseFinale(struct statGlobal* statG, struct listeFlux* listeFlux, struct option* opt,struct fd* fds, struct listeLien* listeLien)
{
	analyseFinalFlux(listeFlux,opt,statG);
	if(opt->echLien == ACTIVE)
	{
		courbeUtilisationLien(fds->utilisationLien,listeLien);
	}
	//TODO autre analyse
}

void analyseFinalFlux(struct listeFlux* listeFlux,struct option* opt, struct statGlobal* statG)
{
	struct flux* curseur = listeFlux->suivant;
	double sommeDuree = 0;
	double sommeCarreDuree = 0;
	unsigned int sommePaquet = 0;

	while(curseur != NULL)
	{
		sommeDuree+=curseur->dureeMoyenne;
		sommeCarreDuree+=curseur->dureeCarreMoyenne;
		sommePaquet+=curseur->recu;

		//XXX compraison entre signed et unsigned
		if(curseur->numFlux == (unsigned)opt->traceFlux)
		{
			printf("Nombre de paquets émis: %d\n",curseur->emis);
			printf("Nombre de paquets recu: %d\n",curseur->recu);
			printf("Nombre de paquets perdus: %d (taux de perte: %f%%)\n",curseur->perdu,((double)curseur->perdu/(double)curseur->emis)*100);
			printf("Durée de vie: %f\n",curseur->tempsFin - curseur->tempsDebut);

			double ecartType = (sqrt(curseur->dureeCarreMoyenne*(double)(curseur->recu) - curseur->dureeMoyenne*curseur->dureeMoyenne))/(double)(curseur->recu);

			double dureeMoyenne = curseur->dureeMoyenne/(double)curseur->recu;

			printf("Durée moyenne de bout en bout du flux %d: %f\n",curseur->numFlux,dureeMoyenne);
			printf("Ecart type: %f\n",ecartType);
			printf("Variance: %f\n",ecartType*ecartType);
			printf("Intervalle de confiance à 68%%: [%f , %f]\n",dureeMoyenne-ecartType,dureeMoyenne+ecartType);
			printf("Intervalle de confiance à 95%%: [%f , %f]\n",dureeMoyenne-2*ecartType,dureeMoyenne+2*ecartType);
			printf("Intervalle de confiance à 99%%: [%f , %f]\n",dureeMoyenne-3*ecartType,dureeMoyenne+3*ecartType);

		}

		curseur = curseur->suivant;
	}

	statG->dureeMoyenne = sommeDuree/(double)sommePaquet;
	statG->ecartType = (sqrt(sommeCarreDuree*(double)(sommePaquet) - sommeDuree*sommeDuree))/(double)(sommePaquet);


	printf("\n\n----------------------------------------------\n\n");
}


void analyseGlobal(int code, struct statGlobal* statG)
{
	switch(code)
	{
		case 0:
			statG->paquetEmis++;
			statG->nbPaquetTransit++;
			break;
		case 1:
			statG->arriveInter++;
			break;
		case 2:
			statG->departFile++;
			break;
		case 3:
			statG->paquetRecus++;
			statG->nbPaquetTransit--;
			break;
		case 4:
			statG->paquetPerdus++;
			statG->nbPaquetTransit--;
			break;
		
	}
}


struct paquet* analyseFlux(struct evt* evt, struct listeFlux* listeFlux, struct option* opt,struct fd* fds,struct statGlobal* statG, struct matriceAdj* matAdj,struct listeLien* listeLien)
{
	struct flux* flux = traitementFlux(evt,listeFlux);
	struct paquet* paquet = searchPaquet(evt, flux->paquets);
	double duree;
	double delai;
	unsigned int noeudTmp, noeudTmp2;
	int debitTmp;
	struct localisationPaquet* localisation;

	switch(evt->code)
	{
		case 0:
			if(opt->tracePaquet == (int)evt->pid)
			{
				printf("---------------------TRACAGE DU PAQUET %d-----------------------\n",opt->tracePaquet);
				printf("Source: %s\n",evt->src);
				printf("Destination: %s\n\n",evt->dst);
			}
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				printf("Départ du noeud %s à temps \t\t%f\n",evt->pos,evt->temps);
			}
			setActualTemps(evt,paquet);
			updatePos(paquet);
	//		addAndSetEmissionPaquet(evt,flux->paquets,trace,statNoeud);
			//XXX optimisation mémoire: chargé les info sur le paquet une fois que le paquet à été émis, et pas tout charger des le debut
			break;
		case 1:
			if(opt->echLien == ACTIVE)
			{
				localisation = posOfNumPaquet(paquet);
				delPaquetInLien(listeLien,localisation->noeud,localisation->file,evt);
			}
			duree = updateTempsLien(evt,paquet);
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				if(condEstimationTaille)
				{
					sscanf(evt->pos,"N%d",&noeudTmp);
					sscanf(evt->src,"N%d",&noeudTmp2);
					debitTmp=debitLien(matAdj->mat,noeudTmp2,noeudTmp);
					delai=evt->temps - tempsEstimationTaille;
					estimationTaille=(double)debitTmp*delai;
					condEstimationTaille=0;
				}
				printf("Temps passé sur le lien: \t\t%f\nArrivé sur le noeud %s à temps   \t%f\n",duree,evt->pos,evt->temps);
			}
			updatePos(paquet);
			break;
		case 2:
			if(opt->echLien == ACTIVE)
			{
				localisation = posOfNumPaquet(paquet);
				addPaquetInLien(listeLien,localisation->noeud,localisation->file,evt);
			}
			duree = updateTempsFile(evt,paquet);
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				if(condEstimationTaille)
				{
					sscanf(evt->pos,"N%d",&noeudTmp);
					tempsEstimationTaille=evt->temps;
				}

				printf("Temps passé dans la liste: \t\t%f\n",duree);
			}
	//		updatePos(evt,flux->paquets);	//XXX utile?
			break;
		case 3:
			setRecepDatePaquet(evt->temps,paquet);	//XXX utile?
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				printf("Arrivé à destination (%s) à temps \t%f\n",evt->pos,evt->temps);
				delai = calculDuree(paquet,flux);
				printf("\nDelai d'acheminement: %f\n",delai);
				printf("Temps passé dans les files: %f\n",paquet->tempsFile);
				printf("Temps passé sur les liens: %f\n",paquet->tempsLien);
				printf("Taille du paquet: %f\n",estimationTaille);
				printf("\n\n----------------------------------------------\n\n");
			}
			addTemps(statG,paquet);
	//		updatePos(evt,flux->paquets);	//XXX utile?
			//XXX optimisation update revoie la position du pauqet et setRecep l'uilise

			//TODO
			delai = calculDuree(paquet,flux);
			if(opt->echDelai != NONE && opt->echDelai == (int)evt->fid)
			{
				courbeDelaiPaquet(fds->delaiPaquet,paquet->numPaquet,delai);
			}
			//XXX IF(paquet trace alors affiche)
			//XXX durée de transmission avant del paquet
			//delPaquet(evt,flux->paquets);
			break;
		case 4:
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				printf("Destruction du paquet au noeud %s à temps %f\n",evt->pos,evt->temps);
				printf("Temps passé dans les files: %f\n",paquet->tempsFile);
				printf("Temps passé sur les liens: %f\n",paquet->tempsLien);
				printf("\n\n----------------------------------------------\n\n");
			}
			addTemps(statG,paquet);
	//		updatePos(evt,flux->paquets);	//XXX utile?
			setRecepDatePaquet(-1,paquet);	//XXX mettre a jour
	}

	return paquet;
}



void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud, struct paquet* paquet)
{
	struct localisationPaquet* localisation;

	localisation = posOfNumPaquet(paquet);

	switch(evt->code)
	{
		case 0:
			incrNbPaquetDansFile(statNoeud,localisation);
			statNoeud->nbPaquetTotalDansFile++;
			break;
		case 1:
			incrNbPaquetDansFile(statNoeud,localisation);
			statNoeud->nbPaquetTotalDansFile++;
			break;
		case 2:
			decrNbPaquetDansFile(statNoeud,localisation);
			statNoeud->nbPaquetTotalDansFile--;
			break;
		case 3:
			decrNbPaquetDansFile(statNoeud,localisation);
			//delPaquet(evt,listePaquet);
			//XXX optimisation mémoire: supprimer les paquets au fur et à mesure
			statNoeud->nbPaquetTotalDansFile--;
			break;
		case 4:
			statNoeud->nbPaquetTotalDansFile--;
			
			setTailleFile(statNoeud,localisation);
			decrNbPaquetDansFile(statNoeud,localisation);

			incrNbPerte(statNoeud,convPosToNum(evt->pos));
			break;
		
	}


	free(localisation);
}
