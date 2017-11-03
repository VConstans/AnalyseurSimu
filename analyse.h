#ifndef __ANALYSE_H__
#define __ANALYSE_H__

#include "statGlobal.h"
#include "evt.h"
#include "trace.h"
#include "listeFlux.h"
#include "statNoeud.h"
#include "listePaquet.h"
#include "analyseurSimu.h"
#include "courbe.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct option* opt, struct fd* fds);
void analyseGlobal(int code, struct statGlobal* statG);
struct paquet* analyseFlux(struct evt* evt, struct listeFlux* listeFlux,struct option* opt,struct fd* fds,struct statGlobal* statG);
void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud, struct paquet* paquet);
void analyseFinalFlux(struct listeFlux* listeFlux,struct option* opt, struct statGlobal* statG);
void analyseFinale(struct statGlobal* statG, struct listeFlux* listeFlux, struct option* opt);

#endif
