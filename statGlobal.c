//CONSTANS Victor

#include "statGlobal.h"


//Ajout des temps passés par un paquet dans les files et sur les liens
void addTemps(struct statGlobal* statG, struct paquet* paquet)
{
	statG->tempsFile += paquet->tempsFile;
	statG->tempsLien += paquet->tempsLien;
}
