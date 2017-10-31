#ifndef __LISTEFLUX_H__
#define __LISTEFLUX_H__

#include <stdio.h>
#include <stdlib.h>
#include "evt.h"
#include "listePaquet.h"

struct flux
{
	unsigned int numFlux;
	unsigned int nbPaquet;
	unsigned int recu;
	unsigned int perdu;
	unsigned int emis;
	double tempsDebut;
	double tempsFin;
	struct listePaquet* paquets;
	struct flux* suivant;
};

struct listeFlux
{
	unsigned int nbFlux;
	struct flux* suivant;
};

struct flux* addFlux(struct evt* evt,struct listeFlux* liste);

#endif
