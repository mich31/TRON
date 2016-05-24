#include <stdio.h>
#include <stdlib.h>
#include "Jeu.h"
#include "Terrain.h"
#include "Joueur.h"
#include "ncursJeu.h"
#include "sdlJeu.h"

int main(int argc, char const *argv[])
{

#ifdef JEU_NCURSES
	Jeu jeu;
	
	ncursMenu(&jeu);
	
	printf("OK\n");
#endif

#ifdef JEU_SDL
	sdlJeu sJeu;
	sdlMenu(&sJeu);
	
#endif
	return 0;
}
