#include <stdio.h>
#include <stdlib.h>
#include "trace.h"

#define TAILLE_LECTURE 200

FILE* ouvertureTrace(char nomtrace[])
{
	FILE* fdTrace = fopen(nomtrace,"r");
	//TODO Contorler retour
}

struct evt* nextEvt(FILE* fdTrace)
{
	struct evt* newEvt = malloc(sizeof(struct evt));

	int tos,bif;
	
	int cmpt = fscanf(fdTrace,"%f %d %d %d %d %d %d %d %d\n",newEvt->temps,newEvt->code, newEvt->pid, newEvt->fid, tos, bif, newEvt->src, newEvt->dst, newEvt->pos);

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
