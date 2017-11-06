#ifndef __FD_H__
#define __FD_H__

#include <stdio.h>
#include <stdlib.h>

//Contient les différents descripteur de fichier
struct fd
{
	FILE* remplissageFile;
	FILE* paquetTransit;
	FILE* fluxActif;
	FILE* delaiPaquet;
	FILE* paquetPerdu;
	FILE* utilisationLien;
	FILE* emission;
};

#endif
