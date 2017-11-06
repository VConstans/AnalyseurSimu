//CONSTANS Victor

#include "analyse.h"

double tempsEstimationTaille;
double estimationTaille;
int condEstimationTaille = 1;


//Lancement des différentes analyse de l'évenement et recherche du flux et du paquet concerné par l'événement
void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct option* opt, struct fd* fds, struct matriceAdj* matAdj,struct listeLien* listeLien)
{
	struct flux* flux = traitementFlux(evt,listeFlux);
	struct paquet* paquet = searchPaquet(evt, flux->paquets);

	if(evt->code == 0)
	{
		updatePos(paquet);
	}
	struct localisationPaquet* localisation = posOfNumPaquet(paquet);

	if(evt->code ==1)
	{
		if(opt->echLien == ACTIVE)
		{
			delPaquetInLien(listeLien,localisation->noeud,localisation->file,evt);
		}
		updatePos(paquet);

	}


	analyseGlobal(evt->code,statG);
	analyseFlux(evt,opt,fds,statG,matAdj,listeLien,paquet,localisation,flux);
	analyseNoeud(evt,statNoeud,localisation);

	free(localisation);
}



void analyseFinale(struct statGlobal* statG, struct listeFlux* listeFlux, struct option* opt,struct fd* fds, struct listeLien* listeLien)
{
	analyseFinalFlux(listeFlux,opt,statG);
	if(opt->echLien == ACTIVE)
	{
		courbeUtilisationLien(fds->utilisationLien,listeLien);
	}
}



void analyseFinalFlux(struct listeFlux* listeFlux,struct option* opt, struct statGlobal* statG)
{
	struct flux* curseur = listeFlux->suivant;
	double sommeDuree = 0;
	double sommeCarreDuree = 0;
	unsigned int sommePaquet = 0;

	//Calcul du temps moyen de bout en bout global
	while(curseur != NULL)
	{
		sommeDuree+=curseur->dureeMoyenne;
		sommeCarreDuree+=curseur->dureeCarreMoyenne;
		sommePaquet+=curseur->recu;

		//Si on trace un flux, on affiche les informations le concernant
		if(curseur->numFlux == (unsigned)opt->traceFlux)
		{
			printf("\n\n----------------TRACAGE DU FLUX %d-----------------\n\n",curseur->numFlux);
			printf("Nombre de paquets émis: %d\n",curseur->emis);
			printf("Nombre de paquets recu: %d\n",curseur->recu);
			printf("Nombre de paquets perdus: %d (taux de perte: %f%%)\n",curseur->perdu,((double)curseur->perdu/(double)curseur->emis)*100);
			printf("Naissance du flux à temps %f\n",curseur->tempsDebut);
			printf("Mort du flux à temps %f\n",curseur->tempsFin);
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


//Mise a jour des informations statistique globale
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



//Mise a jour des informations statistique du flux et du paquet de l'événement
void analyseFlux(struct evt* evt, struct option* opt,struct fd* fds,struct statGlobal* statG, struct matriceAdj* matAdj,struct listeLien* listeLien, struct paquet* paquet,struct localisationPaquet* localisation, struct flux* flux)
{
	double duree;
	double delai;
	unsigned int noeudTmp, noeudTmp2;
	int debitTmp;

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
			break;
		case 1:
			
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
			break;
		case 2:
			if(opt->echLien == ACTIVE)
			{
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
			break;
		case 3:
			setRecepDatePaquet(evt->temps,paquet);
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				printf("Arrivé à destination (%s) à temps \t%f\n",evt->pos,evt->temps);
				delai = calculDuree(paquet,flux);
				printf("\nDelai d'acheminement: %f\n",delai);
				printf("Temps passé dans les files: %f\n",paquet->tempsFile);
				printf("Temps passé sur les liens: %f\n",paquet->tempsLien);
				printf("Taille du paquet: %f\n",estimationTaille);
			}
			addTemps(statG,paquet);
			delai = calculDuree(paquet,flux);
			if(opt->echDelai != NONE && opt->echDelai == (int)evt->fid)
			{
				courbeDelaiPaquet(fds->delaiPaquet,evt->temps,delai);
			}

			delPaquet(flux->paquets,paquet);
			break;
		case 4:
			if(opt->tracePaquet != NONE && opt->tracePaquet == (int)evt->pid)
			{
				printf("Destruction du paquet au noeud %s à temps %f\n",evt->pos,evt->temps);
				printf("Temps passé dans les files: %f\n",paquet->tempsFile);
				printf("Temps passé sur les liens: %f\n",paquet->tempsLien);
			}
			addTemps(statG,paquet);
			setRecepDatePaquet(-1,paquet);
			delPaquet(flux->paquets,paquet);
	}

}


//Mise a jour des informations statisitique du noeuds concerné par l'événement
void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud, struct localisationPaquet* localisation)
{
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
			statNoeud->nbPaquetTotalDansFile--;
			break;
		case 4:
			statNoeud->nbPaquetTotalDansFile--;
			
			decrNbPaquetDansFile(statNoeud,localisation);

			incrNbPerte(statNoeud,convPosToNum(evt->pos));
			break;
		
	}


}
