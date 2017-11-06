#ifndef __ANALYSEUR_SIMU_H__
#define __ANALYSEUR_SIMU_H__

//Structure servant à stocker les choix d'oiption de l'utilisateur
struct option
{
	char* traceFile;	//nom du fichier trace
	char* matriceFile;	//nom du fichier matrice
	int tracePaquet;	//tracage du paquet
	int traceFlux;		//tracage du flux
	int echFile;		//echantillonnage du remplissage des files
	int echFileDetail;
	int echTransit;		//Echantillonnage du nombre de paquet en transit
	int echFluxActif;	//echantillonnage du nombre de flux actif
	int echDelai;		//echantillonnage du delai des paquet d'un flux
	int echPerdu;		//echantillonnage du nombre de paquet perdus
	int echLien;		//Echantillonnage de l'utilisation des liens
	int echEmission;	//echantillonnage du nombre de paquet emis
};


#define ALL -2
#define SUM -3
#define NONE -1
#define ACTIVE -4


#include <stdio.h>
#include <stdlib.h>
#include "statGlobal.h"
#include "trace.h"
#include "evt.h"
#include "matrice.h"
#include "listeFlux.h"
#include "statNoeud.h"
#include "fd.h"
#include <unistd.h>
#include "analyse.h"
#include "courbe.h"
#include <string.h>
#include "listeLien.h"
#include <math.h>


int main(int argc, char* argv[]);
void initAnalyse(struct statGlobal* statG, struct listeFlux* flux, struct statNoeud* statNoeud, struct fd* dataOutput,struct matriceAdj* matAdj,struct listeLien* listeLien, struct option* opt);
void closeFile(struct fd* fds, struct option* opt);


#endif
