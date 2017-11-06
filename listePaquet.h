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
	unsigned int numPaquet;	//Numéro du paquet
	double emission;	//Date d'émission
	double reception;	//date de reception
	double tempsTmp;	//Variable de stockage de temps temporaire
	double tempsFile;	//Somme du temps passé dans les files
	double tempsLien;	//Somme du temps passé sur un lien
	struct listePosition* positions;	//Liste chainée des noeud traversé par le paquet
	struct paquet* suivant;		//Paquet suivant dans la liste
	struct paquet* precedant;	//Paquet précédant dans la liste
};

struct listePaquet
{
	unsigned int nbPaquet;	//Nombre de paquet
	struct paquet* suivant;	//Liste doublement chainée triée des paquets
};

struct paquet* createPaquet(struct evt* evt);
//int placementFile(unsigned int numPaquet,FILE* trace,struct statNoeud* statNoeud);
//void addAndSetEmissionPaquet(struct evt* evt,struct listePaquet* liste, FILE* trace, struct statNoeud* statNoeud);
struct paquet* addPaquet(struct evt* evt,struct listePaquet* liste);
struct paquet* searchPaquet(struct evt* evt, struct listePaquet* liste);
void setRecepDatePaquet(double temps, struct paquet* paquet);
void updatePos(struct paquet* paquet);
struct localisationPaquet* posOfNumPaquet(struct paquet* paquet);
void delPaquet(struct listePaquet* liste, struct paquet* paquet);
void setActualTemps(struct evt* evt, struct paquet* paquet);
double updateTempsFile(struct evt* evt, struct paquet* paquet);
double updateTempsLien(struct evt* evt, struct paquet* paquet);

#endif
