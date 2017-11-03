#include "courbe.h"

int header =1;


void writeDataOutput(struct fd* fds, double temps, struct statNoeud* statNoeud, struct statGlobal* statG, struct option* opt)
{
	courbeRemplissageFile(fds->remplissageFile,temps,statNoeud,opt);
	if(opt->echTransit == ACTIVE)
	{
		courbePaquetTransit(fds->paquetTransit,temps,statG);
	}
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
		if(header)
		{
			fprintf(fd,"1\n");
			header = 0;
		}
		fprintf(fd,"%f ",temps);

		fprintf(fd,"%d\n",statNoeud->nbPaquetTotalDansFile);

		return;
	}
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
	else
	{
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

void courbePaquetTransit(FILE* fd,double temps, struct statGlobal* statG)
{
	fprintf(fd,"%f ",temps);

	fprintf(fd,"%d\n",statG->nbPaquetTransit);
}
