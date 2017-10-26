#include <stdio.h>
#include <stdlib.h>
#include "trace.h"

#define TAILLE_NOM_NOEUD 10	//TODO changer


FILE* ouvertureTrace(char nomtrace[])
{
	FILE* fdTrace = fopen(nomtrace,"r");
	//TODO Contorler retour

	return fdTrace;
}

struct evt* nextEvt(FILE* fdTrace)
{
	struct evt* newEvt = (struct evt*) malloc(sizeof(struct evt));
	newEvt->src = (char*) malloc (TAILLE_NOM_NOEUD*sizeof(char));
	newEvt->dst = (char*) malloc (TAILLE_NOM_NOEUD*sizeof(char));
	newEvt->pos = (char*) malloc (TAILLE_NOM_NOEUD*sizeof(char));

	int tos,bif;
	
	int cmpt = fscanf(fdTrace,"%lf %d %d %d %d %d %s %s %s\n",&(newEvt->temps),&(newEvt->code),&(newEvt->pid), &(newEvt->fid), &(tos), &(bif), newEvt->src, newEvt->dst, newEvt->pos);

	if(cmpt==0)
	{
		free(newEvt);
		return NULL;
	}
	else
	{
		return newEvt;
	}
}
