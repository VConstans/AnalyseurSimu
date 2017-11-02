#ifndef __LISTEPOSITION_H__
#define __LISTEPOSITION_H__

#include <stdio.h>
#include <stdlib.h>

struct position
{
	unsigned int numNoeud;
	struct position* suivant;
};


struct listePosition
{
	struct position* debut;
	struct position* fin;
	struct position* actuelle;
};


struct listePosition* initListePosition();
void addListePosition(struct listePosition* listePosition, unsigned int numNoeud);

#endif
