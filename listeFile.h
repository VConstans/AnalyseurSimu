#ifndef __LISTEFILE_H__
#define __LISTEFILE_H__


//Représentation d'une file
struct file
{
	unsigned int remplissage;	//Nombre de paquet dans la file
	unsigned int taille;		//taille de la file
	unsigned int dest;		//Destination du lien attaché à la file
	unsigned int debit;		//débit du lien attaché à la file
};


#endif
