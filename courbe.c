#include "courbe.h"


void writeDataOutput(struct fd* fds, double temps, struct statNoeud* statNoeud)
{
	courbeRemplissageFile(fds->remplissageFile,temps,statNoeud);
	//TODO autre output
}

void courbeRemplissageFile(FILE* fd,double temps,struct statNoeud* statNoeud)
{
	fprintf(fd,"%f ",temps);

	unsigned int i;

	for(i=0;i<statNoeud->nbNoeud;i++)
	{
		//fprintf(fd,"%u ",statNoeud->nbPaquetDansFile[i]);
	}
	
	fprintf(fd,"%d\n",statNoeud->nbPaquetTotalDansFile);
}
