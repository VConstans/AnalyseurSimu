#include <stdio.h>
#include <stdlib.h>
#include "trace.h"

#define TAILLE_NOM_NOEUD 10


FILE* ouvertureTrace(char nomtrace[])
{
	FILE* fdTrace = fopen(nomtrace,"r");

	return fdTrace;
}


//Lecture de l'événement suivant dans le fichier trace
struct evt* nextEvt(FILE* fdTrace)
{
	struct evt* newEvt = (struct evt*) malloc(sizeof(struct evt));
	newEvt->src = (char*) malloc (TAILLE_NOM_NOEUD*sizeof(char));
	newEvt->dst = (char*) malloc (TAILLE_NOM_NOEUD*sizeof(char));
	newEvt->pos = (char*) malloc (TAILLE_NOM_NOEUD*sizeof(char));

	int tos,bif;
	
	int cmpt = fscanf(fdTrace,"%lf %d %d %d %d ",&(newEvt->temps),&(newEvt->code),&(newEvt->pid), &(newEvt->fid), &(tos));

	if(cmpt==-1)
	{
		free(newEvt->src);
		free(newEvt->dst);
		free(newEvt->pos);
		free(newEvt);
		return NULL;
	}
	else
	{
		if(newEvt->code == 4)
		{
			fscanf(fdTrace,"%s %s %s\n",(newEvt->src),(newEvt->dst),(newEvt->pos));
		}
		else
		{
			fscanf(fdTrace,"%d %s %s %s\n",&bif,(newEvt->src),(newEvt->dst),(newEvt->pos));
		}
		return newEvt;
	}
}



//Convertit la position (chaine de caractère) en numéro
unsigned int convPosToNum(char* pos)
{
	unsigned int num;
	sscanf(pos,"N%d",&num);
	return num;
}
