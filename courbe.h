#ifndef __COURBE_H__
#define __COURBE_H__

#include <stdio.h>
#include <stdlib.h>
#include "statNoeud.h"
#include "fd.h"
#include "statEch.h"

void writeDataOutput(struct fd* fds, double temps, struct statNoeud* statNoeud, struct statEch* statEch);
void courbeRemplissageFile(FILE* fd,double temps,struct statNoeud* statNoeud);
void courbePaquetTransit(FILE* fd,double temps,struct statEch* statEch);


#endif
