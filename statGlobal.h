#ifndef __STATGLOBAL_H__
#define __STATGLOBAL_H__

#include "listePaquet.h"


struct statGlobal
{
	unsigned int paquetEmis;	//Nombre total de paquet émis
	unsigned int arriveInter;	//Nombre total de paquet arrivé à un noeud intermédiaire
	unsigned int departFile;	//Nombre total de départ de file
	unsigned int paquetRecus;	//Nombre total de paquet arrivé à destination
	unsigned int paquetPerdus;	//Nombre total de paquet perdus
	unsigned int nbFlux;		//Nombre de flux totale
	double dureeMoyenne;		//Durée de bout en bout moyenne
	double dureeCarreMoyenne;	//Carré des durée de bout en bout
	double ecartType;		//Ecrat type de la durée moyenne
	double tempsFile;		//Temps total passé dans les files
	double tempsLien;		//Temps total passé sur des liens
	unsigned int nbPaquetTransit;	//Nombre de paquet en transit à un instant t
};


void addTemps(struct statGlobal* statG, struct paquet* paquet);

#endif
