#ifndef __LISTEFLUX_H__
#define __LISTEFLUX_H__

#include <stdio.h>
#include <stdlib.h>

struct listeFlux
{
	unsigned int numFlux;
	unsigned int nbPaquet;
	struct listeFlux* suivant;
};

struct listeFlux* insetion(unsigned int numFluxPaquet, struct listeFlux* liste);

#endif
