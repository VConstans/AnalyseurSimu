#include "statGlobal.h"

void addTemps(struct statGlobal* statG, struct paquet* paquet)
{
	statG->tempsFile += paquet->tempsFile;
	statG->tempsLien += paquet->tempsLien;
}
