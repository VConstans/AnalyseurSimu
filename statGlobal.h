#ifndef __STATGLOBAL_H__
#define __STATGLOBAL_H__


struct statGlobal
{
	unsigned int paquetEmis;
	unsigned int arriveInter;
	unsigned int departFile;
	unsigned int paquetRecus;
	unsigned int paquetPerdus;
	unsigned int nbFlux;
	unsigned int* locPerte;
	//XXX....
};

#endif
