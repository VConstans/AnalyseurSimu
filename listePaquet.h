#ifndef __LISTEPAQUET_H__
#define __LISTEPAQUET_H__

#include <stdio.h>
#include <stdlib.h>
#include "evt.h"
#include "trace.h"
#include "localisationPaquet.h"
#include "statNoeud.h"

struct paquet
{
	unsigned int numPaquet;
	double emission;
	double reception;
	unsigned int pos;
	int file;
	struct paquet* suivant;
};

struct listePaquet
{
	unsigned int nbPaquet;
	struct paquet* suivant;
};

struct paquet* createPaquet(struct evt* evt,FILE* trace,struct statNoeud* statNoeud);
int placementFile(unsigned int numPaquet,FILE* trace,struct statNoeud* statNoeud);
void addAndSetEmissionPaquet(struct evt* evt,struct listePaquet* liste, FILE* trace, struct statNoeud* statNoeud);
struct paquet* setRecepPaquet(struct evt* evt, struct listePaquet* liste);
void updatePos(struct evt* evt, struct listePaquet* liste, FILE* trace, struct statNoeud* statNoeud);
struct localisationPaquet* posOfNumPaquet(unsigned int numPaquet, struct listePaquet* liste);
void delPaquet(struct evt* evt, struct listePaquet* liste);

#endif
