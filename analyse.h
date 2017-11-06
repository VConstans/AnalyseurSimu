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
#include "matrice.h"
#include "listeLien.h"
#include <math.h>

void analyseEvt(struct evt* evt, struct statGlobal* statG,struct listeFlux* listeFlux, struct statNoeud* statNoeud, struct option* opt, struct fd* fds, struct matriceAdj* matAdj,struct listeLien* listeLien);
void analyseGlobal(int code, struct statGlobal* statG);
void analyseFlux(struct evt* evt,struct option* opt,struct fd* fds,struct statGlobal* statG, struct matriceAdj* matAdj,struct listeLien* listeLien, struct paquet* paquet, struct localisationPaquet* localisation, struct flux* flux);
void analyseNoeud(struct evt* evt, struct statNoeud* statNoeud, struct localisationPaquet* localisation);
void analyseFinalFlux(struct listeFlux* listeFlux,struct option* opt, struct statGlobal* statG);
void analyseFinale(struct statGlobal* statG, struct listeFlux* listeFlux, struct option* opt, struct fd* fds,struct listeLien* listeLien);

#endif
