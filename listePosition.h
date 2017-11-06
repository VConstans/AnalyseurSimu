#ifndef __LISTEPOSITION_H__
#define __LISTEPOSITION_H__

#include <stdio.h>
#include <stdlib.h>

//Position d'un paquet
struct position
{
	unsigned int numNoeud;	//numero du noeud
	struct position* suivant;	//noeud suivant que le paquet va traverser
};


struct listePosition
{
	struct position* debut;	//Debut de la liste chainée
	struct position* fin;	//Fin de la liste chainée
	struct position* actuelle;	//Position courante du paquet 
};


struct listePosition* initListePosition();
void addListePosition(struct listePosition* listePosition, unsigned int numNoeud);

#endif
