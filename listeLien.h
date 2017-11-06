#ifndef __LISTELIEN_H__
#define __LISTELIEN_H__


#include "matrice.h"
#include "evt.h"
#include <stdio.h>
#include <stdlib.h>

//Paquet sur un lien
struct paquetInLien
{
	unsigned int numPaquet;		//Numéro du paquet sur le lien
	struct paquetInLien* suivant;	//paquet suivant
};



struct lien
{
	unsigned int ext1;	//extrémité du lien
	unsigned int ext2;	//extrémité du lien
	double tempsOccupe;	//Temps ou le lien est occupe
	double tempsTmp;
	struct paquetInLien* paquetInLien;	//liste chainée des pauqet sur le lien à un instant t
	struct lien* suivant;	//Lien suivant
};


struct listeLien
{
	unsigned int nbLien;	//nombre de lien
	struct lien* liens;	//liste chainée de lien
};



void initListeLien(struct listeLien* listeLien, struct matriceAdj* matAdj);
void addPaquetInLien(struct listeLien* listeLien, unsigned int ext1, unsigned int ext2, struct evt* evt);
void delPaquetInLien(struct listeLien* listeLien, unsigned int ext1, unsigned int ext2, struct evt* evt);

#endif
