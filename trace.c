#include <stdio.h>
#include <stdlib.h>
#include "trace.h"

#define TAILLE_LECTURE 200

FILE* ouvertureTrace(char nomtrace[])
{
	FILE* fdTrace = fopen(nomtrace,"r");
	//TODO Contorler retour
}

struct evt* lectureEvt(FILE* fdTrace)
{
	struct evt* newEvt = malloc(sizeof(struct evt));

	int tos,bif;
	
	fscanf(fdTrace,"%f %d %d %d %d %d %d %d %d\n",newEvt->temps,newEvt->code, newEvt->pid, newEvt->fid, tos, bif, newEvt->src, newEvt->dst, newEvt->pos);

	return newEvt;
}

struct evt* nextEvt(FILE* fdTrace)
{
	struct evt* lecture = lectureEvt(fdTrace);

	return lecture;
}
