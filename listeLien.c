#include "listeLien.h"

void initListeLien(struct listeLien* listeLien, struct matriceAdj* matAdj)
{
	unsigned int i,j;
	int nbLien=0;
	listeLien->liens=NULL;

	for(i=0;i<matAdj->nbNoeud;i++)
	{
		for(j=0;j<matAdj->nbNoeud;j++)
		{
			if(matAdj->mat[i][j] != 0)
			{
				struct lien* newLien = (struct lien*)malloc(sizeof(struct lien));
				newLien->ext1 = i+1;
				newLien->ext2 = j+1;
				newLien->tempsOccupe=0;
				newLien->tempsTmp=0;
				newLien->paquetInLien=NULL;

				newLien->suivant = listeLien->liens;
				listeLien->liens = newLien;

				nbLien++;
			}
		}
	}

	listeLien->nbLien=nbLien;
}


void addPaquetInLien(struct listeLien* listeLien, unsigned int ext1, unsigned int ext2, struct evt* evt)
{
	struct lien* curseur = listeLien->liens;

	while(curseur != NULL)
	{
		if((curseur->ext1 == ext1 && curseur->ext2 == ext2 )|| (curseur->ext1 == ext2 && curseur->ext2 == ext1))
		{
			struct paquetInLien* newPaquetInLien = (struct paquetInLien*)malloc(sizeof(struct paquetInLien));
			newPaquetInLien->numPaquet=evt->pid;

			if(curseur->paquetInLien == NULL)
			{
				curseur->tempsTmp=evt->temps;
			}
			newPaquetInLien->suivant = curseur->paquetInLien;
			curseur->paquetInLien = newPaquetInLien;

			return;
		}
		curseur = curseur->suivant;
	}
}



void delPaquetInLien(struct listeLien* listeLien, unsigned int ext1, unsigned int ext2, struct evt* evt)
{
	struct lien* curseur = listeLien->liens;

	while(curseur != NULL)
	{
		if((curseur->ext1 == ext1 && curseur->ext2 == ext2 )|| (curseur->ext1 == ext2 && curseur->ext2 == ext1))
		{
			struct paquetInLien* curseurPaquet = curseur->paquetInLien;
			struct paquetInLien* precedant = NULL;

			while(curseurPaquet !=NULL)
			{
				if(curseurPaquet->numPaquet == evt->pid)
				{
					struct paquetInLien* tmp = curseurPaquet->suivant;

					if(precedant==NULL && curseurPaquet->suivant == NULL)
					{
						curseur->tempsOccupe += (evt->temps - curseur->tempsTmp);
					}

					free(curseur);

					if(precedant ==NULL)
					{
						curseur->paquetInLien=tmp;
					}
					else
					{
						precedant->suivant = tmp;
					}

					return;
				}

				precedant=curseurPaquet;
				curseurPaquet=curseurPaquet->suivant;
			}

		}
		curseur = curseur->suivant;
	}
}
