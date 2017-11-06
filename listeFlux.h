#ifndef __LISTEFLUX_H__
#define __LISTEFLUX_H__

#include <stdio.h>
#include <stdlib.h>
#include "evt.h"
#include "listePaquet.h"
#include "listePosition.h"

struct flux
{
	unsigned int numFlux;	//Numéro du flux
	unsigned int nbPaquet;	//Nombre de paquet dans le flux
	unsigned int recu;	//Nombre de paquet du flux recu
	unsigned int perdu;	//Nombre de paquet du flux perdus
	unsigned int emis;	//Nombre de paquet du flux emis
	double dureeMoyenne;	//Somme des durée de bout en bout pour calculé la durée moyenne
	double dureeCarreMoyenne;	//Somme des carrée des durée de bout en bout
	double tempsDebut;	//Heure de naissance du flux
	double tempsFin;	//Heure de mort du flux
	struct listePaquet* paquets;	//Liste chainée des paquet composant le flux
	struct flux* suivant;	//Flux suivant
};

struct listeFlux
{
	unsigned int nbFlux;	//Nombre de flux total
	unsigned int nbFluxActif;	//Nombre de flux actif à un instant
	struct flux* suivant;	//Début de la liste chainée de flux
};

struct flux* createFlux(struct evt* evt);
struct flux* addFlux(struct evt* evt,struct listeFlux* liste);
struct flux* traitementFlux(struct evt* evt,struct listeFlux* liste);
struct listePaquet* listePaquetOfFlux(struct evt* evt, struct listeFlux* listeFlux);
double calculDuree(struct paquet* paquet, struct flux* flux);
void initTrace(struct listeFlux* listeFlux,FILE* fdTrace);

#endif
