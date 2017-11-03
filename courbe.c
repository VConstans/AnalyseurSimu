#include "courbe.h"


void writeDataOutput(struct fd* fds, double temps, struct statNoeud* statNoeud, struct statEch* statEch, struct option* opt)
{
	courbeRemplissageFile(fds->remplissageFile,temps,statNoeud,opt);
	courbePaquetTransit(fds->paquetTransit,temps,statEch);
	//TODO autre output
}

void courbeRemplissageFile(FILE* fd,double temps,struct statNoeud* statNoeud, struct option* opt)
{
	if(opt->echFile == NONE)
	{
		return;
	}
	else if(opt->echFile == SUM)
	{
		fprintf(fd,"%f ",temps);

		fprintf(fd,"%d\n",statNoeud->nbPaquetTotalDansFile);

		return;
	}
	else if(opt->echFile == ALL)
	{
		fprintf(fd,"%f ",temps);

		unsigned int i;

		for(i=0;i<statNoeud->nbNoeud;i++)
		{
			fprintf(fd,"%d ",statNoeud->tabNoeud[i].nbPaquetDansFile);
		}
		fprintf(fd,"\n");

		return;
	}
	else
	{
		if(opt->echFileDetail == NONE)
		{
			fprintf(fd,"%f ",temps);
			fprintf(fd,"%d\n",statNoeud->tabNoeud[opt->echFile].nbPaquetDansFile);
			printf("%d\n",statNoeud->tabNoeud[opt->echFile].numNoeud);

			return;
		}
		else if(opt->echFileDetail == ALL)
		{
			fprintf(fd,"%f ",temps);

			unsigned int i;

			for(i=0;i<statNoeud->nbNoeud;i++)
			{
				if(statNoeud->tabNoeud[opt->echFile].files[i].debit != 0)
				{
					fprintf(fd,"%d ",statNoeud->tabNoeud[opt->echFile].files[i].remplissage);
				}
			}
			return;
		}
		else
		{
			fprintf(fd,"%f ",temps);

			if(statNoeud->tabNoeud[opt->echFile].files[opt->echFileDetail].debit != 0)
			{
				fprintf(fd,"%d ",statNoeud->tabNoeud[opt->echFile].files[opt->echFileDetail].remplissage);
			}
			return;
		}
	}
}

void courbePaquetTransit(FILE* fd,double temps, struct statEch* statEch)
{
	fprintf(fd,"%f ",temps);

	fprintf(fd,"%d\n",statEch->nbPaquetTransit);
}
