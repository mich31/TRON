#ifndef _JEU_H
#define _JEU_H

/**
 * \file Jeu.h
 * \brief Module Jeu
 *
 */

#include "Niveau.h"
#include "Joueur.h"
#include "Constantes.h"

/**
 * \struct Jeu
 * \brief Structure Jeu.
 * Jeu est une structure contenant des informations sur le nombre de joueur du jeu,
 * un tableau de pointeur sur les joueurs et un pointeur sur Niveau.
 */
typedef struct
{
	
	int nbJoueur;
	Joueur * J;	
	Niveau * N;
} Jeu;

/**
 * \fn void jeuInit(Jeu * JeuTron, int idNiveau)
 * \brief procédure d'initialisation du jeu.
 *
 * \param JeuTron un pointeur sur Jeu, idNiveau un entier identifiant le niveau de jeu auquel sera initialisé le jeu.
 */
void jeuInit(Jeu * JeuTron, int idNiveau);
							/*parties*/

/**
 * \fn void jeuInitPartie(Jeu * JeuTron, int idNiveau)
 * \brief procédure initialisant une partie, elle initialise le terrain,les positions initiales des joueurs
 * tout en conservant le score.
 *
 * \param JeuTron un pointeur sur Jeu, idNiveau un entier identifiant le niveau de jeu auquel sera initialisé le jeu.
 */
void jeuInitPartie(Jeu * JeuTron, int idNiveau);


/**
 * \fn void jeuLibere(Jeu *JeuTron)
 * \brief procédure qui libère l'espace mémoire alloué pour le niveau et les joueurs.
 *
 * \param JeuTron un pointeur sur Jeu.
 */
void jeuLibere(Jeu *JeuTron);

/**
 * \fn Terrain * jeuGetTerrain(Jeu *JeuTron)
 * \brief Accesseur au terrain du jeu.
 *
 * \param JeuTron un pointeur sur Jeu.
 * \return Pointeur sur le terrain du jeu.
 */
Terrain * jeuGetTerrain(Jeu *JeuTron);

/**
 * \fn void jeuSetJoueur(Jeu *JeuTron, int nb)
 * \brief Mutateur du joueur.
 * Procédure qui fait les allocations dynamiques et initialise un nombre nb de joueurs.
 * \param JeuTron un pointeur sur Jeu, nb un entier désignant le nombre de joueurs à initialiser (à créer)
 */
void jeuSetJoueur(Jeu *JeuTron, int nb);

/**
 * \fn Joueur * jeuGetJoueur(const Jeu *JeuTron, const int id)
 * \brief Accesseur du joueur.
 *
 * \param JeuTron un pointeur sur Jeu, id un entier identifiant le joueur auquel on veut accéder.
 * \return Pointeur sur un joueur.
 */
Joueur * jeuGetJoueur(const Jeu *JeuTron, const int id);

/**
 * \fn const Terrain * jeuGetConstTerrain(const Jeu *JeuTron)
 * \brief Accesseur du terrain.
 *
 * \param JeuTron un pointeur sur Jeu.
 * \return Pointeur sur le terrain.
 */
const Terrain * jeuGetConstTerrain(const Jeu *JeuTron);

/**
 * \fn Joueur * jeuGetConstJoueur(const Jeu *JeuTron, const int id)
 * \brief Accesseur du joueur.
 *
 * \param JeuTron un pointeur sur Jeu, id un entier identifiant le joueur auquel on veut accéder.
 * \return Pointeur sur un joueur.
 */
const Joueur * jeuGetConstJoueur(const Jeu *JeuTron, const int id);

/**
 * \fn Joueur * jeuTrouverGagnant(Jeu *JeuTron)
 * \brief Fonction qui détermine le gagnant d'une partie.
 *
 * \param JeuTron un pointeur sur Jeu.
 * \return Pointeur sur le joueur qui gagne la partie.
 */
Joueur * jeuTrouverGagnant(Jeu *JeuTron);

/**
 * \fn void jeuSetNiveau(Jeu *JeuTron, int idNiveau)
 * \brief Mutateur du niveau.
 * Cette fonction initialise le niveau en fonction de l'identifiant idNiveau et en initialisant le terrain.
 * \param JeuTron un pointeur sur Jeu, idNiveau un entier identifiant le niveau.
 */
void jeuSetNiveau(Jeu *JeuTron, int idNiveau);

/**
 * \fn void jeuClavier(Jeu * JeuTron)
 * \brief Fonction de gestion des déplacements des joueurs.
 *
 * \param JeuTron un pointeur sur Jeu
 */
void jeuClavier(Jeu * JeuTron);

#endif
