#ifndef __LISTEPAQUET_H__
#define __LISTEPAQUET_H__

#include <stdio.h>
#include <stdlib.h>
#include "evt.h"
#include <string.h>

struct paquet
{
	unsigned int numPaquet;
	double emission;
	double reception;
	char* pos;
	struct paquet* suivant;
};

struct listePaquet
{
	unsigned int nbPaquet;
	struct paquet* suivant;
};

void addAndSetEmissionPaquet(struct evt* evt, struct listePaquet* liste);
struct paquet* setRecepPaquet(struct evt* evt, struct listePaquet* liste);
void updatePos(struct evt* evt, struct listePaquet* liste);
char* posOfNumPaquet(unsigned int numPaquet, struct listePaquet* liste);
void delPaquet(struct evt* evt, struct listePaquet* liste);

#endif
