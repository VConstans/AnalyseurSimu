#ifndef __ANALYSE_H__
#define __ANALYSE_H__

#include "statGlobal.h"
#include "evt.h"
#include "trace.h"
#include "listeFlux.h"

void analyseEvt(struct evt* evt, struct statGlobal* statG, struct listeFlux* listeFlux);
void analyseGlobal(int code, struct statGlobal* statG);
void analyseFlux(unsigned int fid, struct listeFlux* listeFlux);


#endif
