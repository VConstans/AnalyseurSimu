#ifndef __LISTEPAQUET_H__
#define __LISTEPAQUET_H__

#include <stdio.h>
#include <stdlib.h>
#include "evt.h"

struct paquet
{
	unsigned int numPaquet;
	double emission;
	double reception;
	struct paquet* suivant;
};

struct listePaquet
{
	unsigned int nbPaquet;
	struct paquet* suivant;
};

void addAndSetEmissionPaquet(unsigned int numPaquet,struct evt* evt, struct listePaquet* liste);
void SetRecepPaquet(unsigned int numPaquet,struct evt* evt, struct listePaquet* liste);

#endif
