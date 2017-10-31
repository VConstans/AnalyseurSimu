#ifndef __ANALYSE_H__
#define __ANALYSE_H__

#include "statGlobal.h"
#include "evt.h"
#include "trace.h"
#include "listeFlux.h"
#include "statNoeud.h"
#include "statEch.h"
#include "listePaquet.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG, struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct statEch* statEch, struct listePaquet* listePaquet);
void analyseGlobal(int code, struct statGlobal* statG);
void analyseFlux(struct evt* evt, struct listeFlux* listeFlux);
void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud, struct listePaquet* listePaquet);
void analyseEch(int code, struct statEch* statEch);
void analysePaquet(struct evt* evt, struct listePaquet* listePaquet);

#endif
