#ifndef __LISTEPAQUET_H__
#define __LISTEPAQUET_H__

#include <stdio.h>
#include <stdlib.h>
#include "evt.h"
#include "trace.h"
#include "localisationPaquet.h"
#include "statNoeud.h"
#include "listePosition.h"

struct paquet
{
	unsigned int numPaquet;
	double emission;
	double reception;
	double tempsTmp;
	double tempsFile;
	double tempsLien;
	struct listePosition* positions;
	struct paquet* suivant;
	struct paquet* precedant;
};

struct listePaquet
{
	unsigned int nbPaquet;
	struct paquet* suivant;
};

struct paquet* createPaquet(struct evt* evt);
//int placementFile(unsigned int numPaquet,FILE* trace,struct statNoeud* statNoeud);
//void addAndSetEmissionPaquet(struct evt* evt,struct listePaquet* liste, FILE* trace, struct statNoeud* statNoeud);
struct paquet* addPaquet(struct evt* evt,struct listePaquet* liste);
struct paquet* searchPaquet(struct evt* evt, struct listePaquet* liste);
void setRecepDatePaquet(double temps, struct paquet* paquet);
void updatePos(struct paquet* paquet);
struct localisationPaquet* posOfNumPaquet(struct paquet* paquet);
void delPaquet(struct evt* evt, struct listePaquet* liste, struct paquet* paquet);
void setActualTemps(struct evt* evt, struct paquet* paquet);
double updateTempsFile(struct evt* evt, struct paquet* paquet);
double updateTempsLien(struct evt* evt, struct paquet* paquet);

#endif
