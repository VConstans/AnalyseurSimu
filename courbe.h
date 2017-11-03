#ifndef __COURBE_H__
#define __COURBE_H__

#include <stdio.h>
#include <stdlib.h>
#include "statNoeud.h"
#include "fd.h"
#include "analyseurSimu.h"

void writeDataOutput(struct fd* fds, double temps, struct statNoeud* statNoeud, struct statGlobal* statG, struct option* opt);
void courbeRemplissageFile(FILE* fd,double temps,struct statNoeud* statNoeud, struct option* opt);
void courbePaquetTransit(FILE* fd,double temps,struct statGlobal* statG);


#endif
