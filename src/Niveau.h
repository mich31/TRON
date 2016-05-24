#ifndef _NIVEAU_H
#define _NIVEAU_H

/**
 * \file Niveau.h
 * \brief Module Niveau
 *
 */

#include "Terrain.h"


/**
 * \struct Niveau
 * \brief Structure Niveau.
 * Niveau est une structure contenant des informations sur l'identifiant du niveau de jeu et
 * un pointeur sur le terrain correspondant à cet identifiant.
 */
typedef struct
{
	int idNiveau;
	Terrain T;
} Niveau;

void initNiveau(Niveau * N, const int id);
void libereNiveau(Niveau * N);
int getNiveau(Niveau * N); // Retourne l'id du niveau
Terrain getTerrain(const Niveau * N);

#endif