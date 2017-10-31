#include "courbe.h"


void writeDataOutput(struct fd* fds, double temps, struct statNoeud* statNoeud, struct statEch* statEch)
{
	courbeRemplissageFile(fds->remplissageFile,temps,statNoeud);
	courbePaquetTransit(fds->paquetTransit,temps,statEch);
	//TODO autre output
}

void courbeRemplissageFile(FILE* fd,double temps,struct statNoeud* statNoeud)
{
	fprintf(fd,"%f ",temps);

	unsigned int i;

	for(i=0;i<statNoeud->nbNoeud;i++)
	{
		if(i<statNoeud->nbPaquetDansFile.remplissage)
		{
			fprintf(fd,"%d ",statNoeud->nbPaquetDansFile.tab[i].entier);
		}
		else
		{
			fprintf(fd,"0 ");
		}
	}
	
	fprintf(fd,"%d\n",statNoeud->nbPaquetTotalDansFile);
}

void courbePaquetTransit(FILE* fd,double temps, struct statEch* statEch)
{
	fprintf(fd,"%f ",temps);

	fprintf(fd,"%d\n",statEch->nbPaquetTransit);
}
