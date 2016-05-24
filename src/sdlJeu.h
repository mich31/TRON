#ifndef _SDLJEU_H
#define _SDLJEU_H

/**
 * \file sdlJeu.h
 * \brief Module sdlJeu
 *
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Jeu.h"
#include "Constantes.h"

typedef struct
{
	Jeu jeu;
	SDL_Surface * ecran, *background, *menu1, *menu2, *menu3, *menu4, *menu5, *menu6;
	SDL_Surface *Tron1Haut, *Tron1Bas, *Tron1Gauche, *Tron1Droite;
	SDL_Surface *Tron2Haut, *Tron2Bas, *Tron2Gauche, *Tron2Droite;
	SDL_Surface *Trace1Horizontale, *Trace1Verticale, *Trace2Horizontale, *Trace2Verticale;
	SDL_Surface *Coin1J1, *Coin2J1, *Coin3J1, *Coin4J1;
	SDL_Surface *Coin1J2, *Coin2J2, *Coin3J2, *Coin4J2;
	SDL_Surface *ecrassement, *mur;
} sdlJeu;

void sdlJeuInit(sdlJeu * J);
void sdlJeuAff(sdlJeu * J);
void sdlJeuBoucle(sdlJeu * J);
void sdlJeuLibere(sdlJeu * J);
void sdlMenu(sdlJeu *J);

#endif
