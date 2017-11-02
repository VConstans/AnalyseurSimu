#ifndef __ANALYSE_H__
#define __ANALYSE_H__

#include "statGlobal.h"
#include "evt.h"
#include "trace.h"
#include "listeFlux.h"
#include "statNoeud.h"
#include "statEch.h"
#include "listePaquet.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct statEch* statEch, FILE* trace);
void analyseGlobal(int code, struct statGlobal* statG);
void analyseFlux(struct evt* evt, struct listeFlux* listeFlux,FILE* trace, struct statNoeud* statNoeud);
void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud, struct listeFlux* listeFlux);
void analyseEch(int code, struct statEch* statEch);
void analyseFinalFlux(struct listeFlux* listeFlux,unsigned int fluxTracer, struct statGlobal* statG);
void analyseFinale(struct statGlobal* statG, struct listeFlux* listeFlux, unsigned int fluxTracer);

#endif
