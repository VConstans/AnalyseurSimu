#ifndef __ANALYSEUR_SIMU_H__
#define __ANALYSEUR_SIMU_H__

#include <stdio.h>
#include <stdlib.h>
#include "statGlobal.h"
#include "trace.h"
#include "evt.h"
#include "analyse.h"
#include "matrice.h"
#include "listeFlux.h"
#include "statNoeud.h"
#include "fd.h"
#include "courbe.h"



int main(int argc, char* argv[]);
void initAnalyse(struct statGlobal* statG, struct listeFlux* flux, struct statNoeud* statNoeud, struct statEch* statEch, struct fd* dataOutput,struct matriceAdj* matAdj);

#endif
