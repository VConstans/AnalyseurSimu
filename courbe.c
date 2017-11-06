//CONSTANS Victor

#include "courbe.h"

int header =1;

//Appelle des différentes fonction qui vont inscrire les données utiles pour les différentes représentation graphique
void writeDataOutput(struct fd* fds, double temps, struct statNoeud* statNoeud, struct statGlobal* statG, struct listeFlux* listeFlux,struct option* opt)
{
	courbeRemplissageFile(fds->remplissageFile,temps,statNoeud,opt);
	if(opt->echTransit == ACTIVE)
	{
		courbePaquetTransit(fds->paquetTransit,temps,statG);
	}
	if(opt->echFluxActif == ACTIVE)
	{
		courbeFluxActif(fds->fluxActif,temps,listeFlux);
	}
	if(opt->echPerdu == ACTIVE)
	{
		courbePaquetPerdu(fds->paquetPerdu,temps,statG);
	}
	if(opt->echEmission == ACTIVE)
	{
		courbeEmission(fds->emission,temps,statG);
	}
}


//Inscrit l'heure à laquelle s'est produit l'événement et le nombre de paquet dans la file selectionnée
void courbeRemplissageFile(FILE* fd,double temps,struct statNoeud* statNoeud, struct option* opt)
{
	if(opt->echFile == NONE)
	{
		return;
	}
	//On cumul la somme de toute les files de tout les noeuds
	else if(opt->echFile == SUM)
	{
		if(header)
		{
			fprintf(fd,"1\n");
			header = 0;
		}
		fprintf(fd,"%f ",temps);

		fprintf(fd,"%d\n",statNoeud->nbPaquetTotalDansFile);

		return;
	}
	//On inscrit la somme des files noeud par noeud
	else if(opt->echFile == ALL)
	{
		if(header)
		{
			fprintf(fd,"%d\n",statNoeud->nbNoeud);
			header=0;
		}
		fprintf(fd,"%f ",temps);

		unsigned int i;

		for(i=0;i<statNoeud->nbNoeud;i++)
		{
			fprintf(fd,"%d ",statNoeud->tabNoeud[i].nbPaquetDansFile);
		}
		fprintf(fd,"\n");

		return;
	}
	//On a selectionner un noeud précis à echantillonner
	else
	{
		//On affiche la somme de toute les files d'un noeud
		if(opt->echFileDetail == NONE)
		{
			if(header)
			{
				fprintf(fd,"1\n");
				header = 0;
			}
			fprintf(fd,"%f ",temps);
			fprintf(fd,"%d\n",statNoeud->tabNoeud[opt->echFile].nbPaquetDansFile);

			return;
		}
		//On inscrit le détail de remplissage de chacune des files d'un noeud précis
		else if(opt->echFileDetail == ALL)
		{
			if(header)
			{
				fprintf(fd,"%d\n",statNoeud->tabNoeud[opt->echFile].nbLien);
				header = 0;
			}
			fprintf(fd,"%f ",temps);

			unsigned int i;

			for(i=0;i<statNoeud->nbNoeud;i++)
			{
				if(statNoeud->tabNoeud[opt->echFile].files[i].debit != 0)
				{
					fprintf(fd,"%d ",statNoeud->tabNoeud[opt->echFile].files[i].remplissage);
				}
			}
			fprintf(fd,"\n");
			return;
		}
		//On affiche le remplissage d'une file précise d'un noeud précis
		else
		{
			if(header)
			{
				fprintf(fd,"1\n");
				header = 0;
			}

			if(statNoeud->tabNoeud[opt->echFile].files[opt->echFileDetail].debit != 0)
			{
				fprintf(fd,"%f ",temps);
				fprintf(fd,"%d\n",statNoeud->tabNoeud[opt->echFile].files[opt->echFileDetail].remplissage);
			}
			return;
		}
	}
}


//On inscrit le nombre de paquet en transit dans le reseau
void courbePaquetTransit(FILE* fd,double temps, struct statGlobal* statG)
{
	fprintf(fd,"%f ",temps);

	fprintf(fd,"%d\n",statG->nbPaquetTransit);
}



//On inscrit le nombre de flux actif
void courbeFluxActif(FILE* fd,double temps,struct listeFlux* listeFlux)
{
	fprintf(fd,"%f ",temps);
	fprintf(fd,"%d\n",listeFlux->nbFluxActif);
}


//On inscrit le délai des différents paquet d'un flux
void courbeDelaiPaquet(FILE* fd,double temps,double delai)
{
	fprintf(fd,"%f %f\n",temps,delai);
}


//On inscrit le nombre de paquet perdus à un instant
void courbePaquetPerdu(FILE* fd,double temps,struct statGlobal* statG)
{
	fprintf(fd,"%f %d\n",temps,statG->paquetPerdus);
}


//On inscrit le temps d'utilisation des différents liens
void courbeUtilisationLien(FILE* fd, struct listeLien* listeLien)
{
	struct lien* curseur = listeLien->liens;

	while(curseur !=NULL)
	{
		fprintf(fd,"%d-%d %f\n",curseur->ext1,curseur->ext2,curseur->tempsOccupe);

		curseur = curseur->suivant;
	}
}


//On inscrit le nombre de paquet émis à un instant
void courbeEmission(FILE* fd, double temps,struct statGlobal* statG)
{
	fprintf(fd,"%f %d\n",temps,statG->paquetEmis);
}
