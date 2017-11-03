#ifndef __ANALYSEUR_SIMU_H__
#define __ANALYSEUR_SIMU_H__

struct option
{
	char* traceFile;
	char* matriceFile;
	int tracePaquet;
	int traceFlux;
	int echFile;
	int echFileDetail;
	int echTransit;
	int echFluxActif;
	int echDelai;
};


#define ALL -2
#define SUM -3
#define NONE -1
#define ACTIVE -4


#include <stdio.h>
#include <stdlib.h>
#include "statGlobal.h"
#include "trace.h"
#include "evt.h"
#include "matrice.h"
#include "listeFlux.h"
#include "statNoeud.h"
#include "fd.h"
#include <unistd.h>
#include "analyse.h"
#include "courbe.h"
#include <string.h>


int main(int argc, char* argv[]);
void initAnalyse(struct statGlobal* statG, struct listeFlux* flux, struct statNoeud* statNoeud, struct fd* dataOutput,struct matriceAdj* matAdj);


#endif
