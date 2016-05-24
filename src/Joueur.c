#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Joueur.h"

void setDirection(Joueur * J, const char direction)
{
	J->direction = direction;
}

void initPos(Joueur * J,int id,const Terrain * T)
{
	assert(id >= 0);
	if (id == 1)
	{
		J->posx = ((T->dimx * 2)/3)+1;
		J->posy = (T->dimy / 2);
		setDirection(J,'g');
		assert((J->posx > 0) && (J->posy > 0));
	}
	else
	{	
		J->posx = (T->dimx / 3);
		J->posy = (T->dimy / 2);
		setDirection(J,'d');
		assert((J->posx > 0) && (J->posy > 0));	
	}
}

int getPosx(const Joueur * J)
{
	return J->posx;
}

void setPosx(Joueur * J,int x)
{
	J->posx = x;
}

int getPosy(const Joueur * J)
{
	return J->posy;
}

void setPosy(Joueur * J,int y)
{
	J->posy = y;
}

int getScore(const Joueur * J)
{
	return J->score;
}

void setScore(Joueur * J,int score)
{
	J->score = score;
}

void incrScore(Joueur * J)
{
	J->score++;
}

int getEcr(const Joueur * J)
{
	return J->ecr;
}

void setEcr(Joueur * J,int ecr)
{
	J->ecr = ecr;
}

int getTurbo(const Joueur *J)
{
	return J->turbo;
}

void initJoueur(Joueur * J,int id,const Terrain * T)
{
	assert(T != NULL);
	initPos(J, id,T);
	assert(id >= 0);
	J->id = id;
	J->score = 0;
	J->ecr = 0;
	J->turbo = 3;
}

void libereJoueur(Joueur * J)
{
	J->posx = -1;
	J->posy = -1;
	J->id = -1;
	J->score = -1;
	J->direction = '\0';
	J->ecr = -1;
	J->turbo = -1;
}

void tronGauche(Joueur * J,Terrain * T)
{
	int i = 0;
	int x,y;
	s_case c;
	if (terPositionValide(T,J->posx-1,J->posy))
	{
		if (J->turbo > 3)
		{
			while(i < 5)
			{
				c.valeur = 'x';
				c.direction = 'G';
				c.idJoueur = J->id;
				terSetXY(T,J->posx-i,J->posy,&c); /* Trace */
				i++;
			}
			c.valeur = 'X';
			terSetXY(T,J->posx-i,J->posy,&c); // Tron
			setDirection(J,'g');
			J->posx = (J->posx)-i;
			J->turbo -= 11;
		}
		else
		{
			c.valeur = 'x';
			x = getPosx(J);
			y = getPosy(J);
			c.direction = T->tab[y][x].direction;
			c.idJoueur = J->id;
			terSetXY(T,J->posx,J->posy,&c); /* Trace */
			c.valeur = 'X';
			c.direction = 'G';
			terSetXY(T,J->posx-1,J->posy,&c); // Tron
			setDirection(J,'g');
			J->posx = (J->posx)-1;
		}
	}
	else
	{
		J->ecr=1;
	}
}

void tronDroite(Joueur * J,Terrain * T)
{
	int i = 0;
	int x,y;
	s_case c;
	if (terPositionValide(T,J->posx+1,J->posy))
	{
		if (J->turbo > 3)
		{
			while(i < 5)
			{
				c.valeur = 'x';
				c.direction = 'D';
				c.idJoueur = J->id;
				terSetXY(T,J->posx+i,J->posy,&c); // Trace
				i++;
			}
			c.valeur = 'X';
			terSetXY(T,J->posx+i,J->posy,&c); // Tron
			setDirection(J,'d');
			J->posx = (J->posx)+i;
			J->turbo -= 11;
		}
		else
		{
			c.valeur = 'x';
			x = getPosx(J);
			y = getPosy(J);
			c.direction = T->tab[y][x].direction;
			c.idJoueur = J->id;
			terSetXY(T,J->posx,J->posy,&c); // Trace
			c.valeur = 'X';
			c.direction = 'D';
			terSetXY(T,J->posx+1,J->posy,&c); // Tron
			setDirection(J,'d');
			J->posx = (J->posx)+1;
		}
	}
	else
	{
		J->ecr=1;
	}
}
void tronHaut(Joueur * J,Terrain * T)
{
	int i = 0;
	int x,y;
	s_case c;
	if (terPositionValide(T,J->posx,J->posy-1))
	{
		if (J->turbo > 3)
		{
			while(i < 5)
			{
				c.valeur = 'x';
				c.direction = 'H';
				c.idJoueur = J->id;
				terSetXY(T,J->posx,J->posy-i,&c); // Trace
				i++;
			}
			c.valeur = 'X';
			terSetXY(T,J->posx,J->posy-i,&c); // Tron
			setDirection(J,'h');
			J->posy = (J->posy)-i;
			J->turbo -= 11;
		}
		else
		{
			c.valeur = 'x';
			x = getPosx(J);
			y = getPosy(J);
			c.direction = T->tab[y][x].direction;
			c.idJoueur = J->id;
			terSetXY(T,J->posx,J->posy,&c); // Trace
			c.valeur = 'X';
			c.direction = 'H';
			terSetXY(T,J->posx,J->posy-1,&c); // Tron
			setDirection(J,'h');
			J->posy = (J->posy)-1;
		}
	}
	else
	{
		J->ecr=1;
	}
}
void tronBas(Joueur * J,Terrain * T)
{
	int i = 0;
	int x,y;
	s_case c;
	if (terPositionValide(T,J->posx,J->posy+1))
	{
		if (J->turbo > 3)
		{
			while(i < 5)
			{
				c.valeur = 'x';
				c.direction = 'B';
				c.idJoueur = J->id;
				terSetXY(T,J->posx,J->posy+i,&c); // Trace
				i++;
			}
			c.valeur = 'X';
			terSetXY(T,J->posx,J->posy+i,&c); // Tron
			setDirection(J,'b');
			J->posy = (J->posy)+i;
			J->turbo -= 11;
		}
		else
		{
			c.valeur = 'x';
			x = getPosx(J);
			y = getPosy(J);
			c.direction = T->tab[y][x].direction;
			c.idJoueur = J->id;
			terSetXY(T,J->posx,J->posy,&c); // Trace
			c.valeur = 'X';
			c.direction = 'H';
			terSetXY(T,J->posx,J->posy+1,&c); // Tron
			setDirection(J,'b');
			J->posy = (J->posy)+1;
		}
	}
	else
	{
		J->ecr=1;
	}
}

bool deplacementPossible(const Joueur * J, const char touche)
{
	switch(touche)
	{
		case 'g':
			if (J->direction == 'd')
			{
				return false;
			}
			break;
			
		case 'd':
			if (J->direction == 'g')
			{
				return false;
			}
			break;
			
		case 'h':
			if (J->direction == 'b')
			{
				return false;
			}
			break;

		case 'b':
			if (J->direction == 'h')
			{
				return false;
				
			}
			break;
		default:
			break;
	}
	return true;
}
