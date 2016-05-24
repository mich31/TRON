#ifndef _JOUEUR_H
#define _JOUEUR_H

/**
 * \file Joueur.h
 * \brief Module Joueur
 *
 */

#include <stdbool.h>
#include "Terrain.h"

/**
 * \struct Joueur
 * \brief Structure Joueur.
 * Joueur est une structure contenant des informations sur les coordonnées du joueur,
 * son identifiant, son niveau de turbo, la direction dans laquelle il se déplace et son score.
 */

typedef struct 
{
	int posx,posy;
	int id,turbo;
	int score;
	char direction;
	int ecr; /* 0 si le joueur se trouve dans position valide, 1 sinon; elle sert à savoir quand il s'ecrase */
} Joueur;

void setDirection(Joueur * J, const char direction);
void initPos(Joueur * J,int id,const Terrain * T);
int getPosx(const Joueur * J);
void setPosx(Joueur * J,int x);
int getPosy(const Joueur * J);
void setPosy(Joueur * J,int y);
int getScore(const Joueur * J);
void setScore(Joueur * J,int score);
void incrScore(Joueur * J);
int getEcr(const Joueur *J);
void setEcr(Joueur * J, int ecr);
int getTurbo(const Joueur *J);
void initJoueur(Joueur * J,int id,const Terrain * T);
void libereJoueur(Joueur * J);
void tronGauche(Joueur * J,Terrain * T);
void tronDroite(Joueur * J,Terrain * T);
void tronHaut(Joueur * J,Terrain * T);
void tronBas(Joueur * J,Terrain * T);
bool deplacementPossible(const Joueur * J, const char touche);

#endif
