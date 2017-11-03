#ifndef __ANALYSE_H__
#define __ANALYSE_H__

#include "statGlobal.h"
#include "evt.h"
#include "trace.h"
#include "listeFlux.h"
#include "statNoeud.h"
#include "statEch.h"
#include "listePaquet.h"
#include "analyseurSimu.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct statEch* statEch, struct option* opt);
void analyseGlobal(int code, struct statGlobal* statG);
struct paquet* analyseFlux(struct evt* evt, struct listeFlux* listeFlux);
void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud, struct paquet* paquet);
void analyseEch(int code, struct statEch* statEch);
void analyseFinalFlux(struct listeFlux* listeFlux,struct option* opt, struct statGlobal* statG);
void analyseFinale(struct statGlobal* statG, struct listeFlux* listeFlux, struct option* opt);

#endif
