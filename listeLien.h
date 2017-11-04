#ifndef __LISTELIEN_H__
#define __LISTELIEN_H__


#include "matrice.h"
#include "evt.h"
#include <stdio.h>
#include <stdlib.h>

struct paquetInLien
{
	unsigned int numPaquet;
	struct paquetInLien* suivant;
};

struct lien
{
	unsigned int ext1;
	unsigned int ext2;
	double tempsOccupe;
	double tempsTmp;
	struct paquetInLien* paquetInLien;
	struct lien* suivant;
};


struct listeLien
{
	unsigned int nbLien;
	struct lien* liens;
};



void initListeLien(struct listeLien* listeLien, struct matriceAdj* matAdj);
void addPaquetInLien(struct listeLien* listeLien, unsigned int ext1, unsigned int ext2, struct evt* evt);
void delPaquetInLien(struct listeLien* listeLien, unsigned int ext1, unsigned int ext2, struct evt* evt);

#endif
