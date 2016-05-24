#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Terrain.h"

/*nvelle fct coordonneesValide
  dans terGetXY: modif T->tab[x][y] par T->tab[y][x]
  nvelle fct terSetXY*/

void initTerrain(Terrain * T,const int x,const int y,const int id)
{
	int i,j;

	assert(x>0); /* On vérifie qu'on initialise avec des valeurs positives */
	assert(y>0);
	assert(id>0);
	T->dimx = x;
	T->dimy = y;
	
	T->tab = (s_case**) malloc(T->dimy*sizeof(s_case*));
	for (i = 0; i < T->dimy; ++i)
	{
		T->tab[i] = (s_case*) malloc(T->dimx*sizeof(s_case));
	}
	assert(T->tab != NULL);
	if(id == 1) // Terrain Niveau 1
	{
		//Pour remplir l'intérieur du terrain
		for (i = 1; i < T->dimy-1; ++i)
		{
			for (j = 1; j < T->dimx-1; ++j)
			{
				T->tab[i][j].valeur = ' ';
				T->tab[i][j].direction = '\0';
				T->tab[i][j].idJoueur = -1;
			}
		}

		// Pour remplir la première et la dernière ligne
		for (j = 0; j < T->dimx; ++j)
		{
			T->tab[0][j].valeur = '#';
			T->tab[0][j].direction = '#';
			T->tab[0][j].idJoueur = -1;

			T->tab[y-1][j].valeur = '#';
			T->tab[y-1][j].direction = '#';
			T->tab[y-1][j].idJoueur = -1;
		}
		// Pour remplir les bordures des lignes 1 à dimy-1 
		for (i = 1; i < T->dimy-1; ++i)
		{
			T->tab[i][0].valeur = '#';
			T->tab[i][0].direction = '#';
			T->tab[i][0].idJoueur = -1;

			T->tab[i][x-1].valeur = '#';
			T->tab[i][x-1].direction = '#';
			T->tab[i][x-1].idJoueur = -1;
		}
	}
	else if (id == 2) // Terrain Niveau 2
	{
		// Pour remplir la première et la dernière ligne
		for (j = 0; j < T->dimx; ++j)
		{
			T->tab[0][j].valeur = '#';
			T->tab[0][j].direction = '#';
			T->tab[0][j].idJoueur = -1;

			T->tab[y-1][j].valeur = '#';
			T->tab[y-1][j].direction = '#';
			T->tab[y-1][j].idJoueur = -1;
		}
		// Pour remplir les bordures des lignes 1 à dimy-1 
		for (i = 1; i < T->dimy-1; ++i)
		{
			T->tab[i][0].valeur = '#';
			T->tab[i][0].direction = '#';
			T->tab[i][0].idJoueur = -1;

			T->tab[i][x-1].valeur = '#';
			T->tab[i][x-1].direction = '#';
			T->tab[i][x-1].idJoueur = -1;
		}

		//Pour remplir l'intérieur du terrain
		for (i = 1; i < T->dimy-1; ++i)
		{
			for (j = 1; j < T->dimx-1; ++j)
			{
				T->tab[i][j].valeur = ' ';
				T->tab[i][j].direction = '\0';
				T->tab[i][j].idJoueur = -1;
			}
		}

		//ajout des obstacles
		for(i = x/6; i <= (2*x)/6; i++)
		{
			T->tab[y/4][i].valeur = '#';
			T->tab[y/4][i].direction = '#';
			T->tab[y/4][i].idJoueur = -1;
		}
		for(i = (4*x)/6; i <= (5*x)/6; i++)
		{
			T->tab[y/4][i].valeur = '#';
			T->tab[y/4][i].direction = '#';
			T->tab[y/4][i].idJoueur = -1;
		}

		for(i = (y/4)+1; i < (3*y)/4; i++)
		{
			T->tab[i][x/6].valeur = '#';
			T->tab[i][x/6].direction = '#';
			T->tab[i][x/6].idJoueur = -1;

			T->tab[i][(5*x)/6].valeur = '#';
			T->tab[i][(5*x)/6].direction = '#';
			T->tab[i][(5*x)/6].idJoueur = -1;
		}

		for(i = x/6; i <= (2*x)/6; i++)
		{
			T->tab[(3*y)/4][i].valeur = '#';
			T->tab[(3*y)/4][i].direction = '#';
			T->tab[(3*y)/4][i].idJoueur = -1;
		}
		for(i = (4*x)/6; i <= (5*x)/6; i++)
		{
			T->tab[(3*y)/4][i].valeur = '#';
			T->tab[(3*y)/4][i].direction = '#';
			T->tab[(3*y)/4][i].idJoueur = -1;
		}
	}
	else if (id == 3) // Terrain Niveau 3
	{
		// Pour remplir la première et la dernière ligne
		for (j = 0; j < T->dimx; ++j)
		{
			T->tab[0][j].valeur = '#';
			T->tab[0][j].direction = '#';
			T->tab[0][j].idJoueur = -1;

			T->tab[y-1][j].valeur = '#';
			T->tab[y-1][j].direction = '#';
			T->tab[y-1][j].idJoueur = -1;
		}
		// Pour remplir les bordures des lignes 1 à dimy-1 
		for (i = 1; i < T->dimy-1; ++i)
		{
			T->tab[i][0].valeur = '#';
			T->tab[i][0].direction = '#';
			T->tab[i][0].idJoueur = -1;

			T->tab[i][x-1].valeur = '#';
			T->tab[i][x-1].direction = '#';
			T->tab[i][x-1].idJoueur = -1;
		}

		//Pour remplir l'intérieur du terrain
		for (i = 1; i < T->dimy-1; ++i)
		{
			for (j = 1; j < T->dimx-1; ++j)
			{
				T->tab[i][j].valeur = ' ';
				T->tab[i][j].direction = '\0';
				T->tab[i][j].idJoueur = -1;
			}
		}

		//ajout des obstacles
		for(i = (x/6)+3; i <= ((2*x)/6)+3; i++)
		{
			T->tab[y/4][i].valeur = '#';
			T->tab[y/4][i].direction = '#';
			T->tab[y/4][i].idJoueur = -1;
		}
		for(i = ((4*x)/6)-2; i <= ((5*x)/6)-2; i++)
		{
			T->tab[y/4][i].valeur = '#';
			T->tab[y/4][i].direction = '#';
			T->tab[y/4][i].idJoueur = -1;
		}

		for(i = (y/4)+1; i < (3*y)/4; i++)
		{
			T->tab[i][(x/3)+3].valeur = '#';
			T->tab[i][(x/3)+3].direction = '#';
			T->tab[i][(x/3)+3].idJoueur = -1;

			T->tab[i][((4*x)/6)-2].valeur = '#';
			T->tab[i][((4*x)/6)-2].direction = '#';
			T->tab[i][((4*x)/6)-2].idJoueur = -1;
		}

		for(i = (x/6)+3; i <= ((2*x)/6)+3; i++)
		{
			T->tab[(3*y)/4][i].valeur = '#';
			T->tab[(3*y)/4][i].direction = '#';
			T->tab[(3*y)/4][i].idJoueur = -1;
		}
		for(i = ((4*x)/6)-2; i <= ((5*x)/6)-2; i++)
		{
			T->tab[(3*y)/4][i].valeur = '#';
			T->tab[(3*y)/4][i].direction = '#';
			T->tab[(3*y)/4][i].idJoueur = -1;
		}
	}
}

void libereTerrain(Terrain * T)
{
	int i;
	for (i = 0; i < T->dimy; ++i)
	{
		
		free(T->tab[i]);
	}
	free(T->tab);
	T->dimx = 0;
	T->dimy = 0;
	T->tab = NULL;
	assert(T->tab == NULL);
}

int getdimx(const Terrain * T)
{
	return T->dimx;
}

int getdimy(const Terrain * T)
{
	return T->dimy;
}

void coordonneesValide(const Terrain * T,const int x,const int y)
{
	assert(x >= 0);
	assert(x < T->dimx);
	assert(y >= 0);
	assert(y < T->dimy);
}

char terGetXY(const Terrain * T,const int x,const int y)
{
	coordonneesValide(T,x,y);
	return T->tab[y][x].valeur;
}

void terSetXY(Terrain * T,const int x,const int y,const s_case * c)
{
	coordonneesValide(T,x,y);
	T->tab[y][x] = *c;
}

int terPositionValide(const Terrain * T,const int x,const int y)
{
	char val;
	val = terGetXY(T,x,y);
	if (val == ' ')
	{			
		return 1;
	}
	else
		return 0;
}
