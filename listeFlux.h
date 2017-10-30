#ifndef __LISTEFLUX_H__
#define __LISTEFLUX_H__

#include <stdio.h>
#include <stdlib.h>

struct flux
{
	unsigned int numFlux;
	unsigned int nbPaquet;
	struct flux* suivant;
};

struct listeFlux
{
	unsigned int nbFlux;
	struct flux* suivant;
};

void insertion(unsigned int numFluxPaquet, struct listeFlux* liste);

#endif
