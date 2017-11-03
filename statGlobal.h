#ifndef __STATGLOBAL_H__
#define __STATGLOBAL_H__

#include "listePaquet.h"


struct statGlobal
{
	unsigned int paquetEmis;
	unsigned int arriveInter;
	unsigned int departFile;
	unsigned int paquetRecus;
	unsigned int paquetPerdus;
	unsigned int nbFlux;
	unsigned int* locPerte;	//XXX utile?
	double dureeMoyenne;
	double tempsFile;
	double tempsLien;
	unsigned int nbPaquetTransit;
	//XXX....
};


void addTemps(struct statGlobal* statG, struct paquet* paquet);

#endif
