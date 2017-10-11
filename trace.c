#include <stdio.h>
#include <stdlib.h>

#define TAILLE_LECTURE 200

FILE* ouvertureTrace(char nomtrace[])
{
	FILE* fdTrace = fopen(nomtrace,"r");
}

char* lectureEvt(FILE* fdTrace)
{
	char* lecture = malloc(TAILLE_LECTURE*sizeof(char));
	fgets(lecture, TAILLE_LECTURE, fdTrace);

	return lecture;
}

struct evt* parseEvt(char* evt)
{
	struct evt* newEvt = malloc(sizeof(struct evt));
	

	char* token = strtok(evt,"\t");
	//test si tocken = null
	evt->temps = atof(token);
	token = strtok(NULL,"\t");
	evt->code = atoi(token);
	token = strtok(NULL,"\t");
	evt->pid = atoi(token);
	token = strtok(NULL,"\t");
	evt->fid = atoi(token);
	token = strtok(NULL,"\t");
	token = strtok(NULL,"\t");
	token = strtok(NULL,"\t");
	evt->src = token;
	token = strtok(NULL,"\t");
	evt->dst = token;
}

struct evt* nextEvt(FILE* fdTrace)
{
	char* lecture = lectureEvt(fdTrace);
	struct evt* evt = parseEvt(lecture);

	return evt;
}
