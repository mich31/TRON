#include <stdio.h>
#include <ncurses.h>
#include <assert.h>
#include <time.h>
#include "Jeu.h"

void ncursAffTerrain( WINDOW* win, const Jeu *pJeu) {
	int x,y;

	const Terrain *pTer = jeuGetConstTerrain(pJeu);
	const Joueur *pTron = jeuGetConstJoueur(pJeu,0);
    const Joueur *pTron1;

    if (pJeu->nbJoueur == 2)
    {
        pTron1 = jeuGetConstJoueur(pJeu,1);
    }

	wclear(win);

	for(x=0;x<getdimx(pTer);++x)
		for(y=0;y<getdimy(pTer);++y)
			mvwprintw( win, y, x, "%c", terGetXY(pTer,x,y) );

	mvwprintw( win, getPosy(pTron), getPosx(pTron), "X");
    mvwprintw( win, getPosy(pTron1), getPosx(pTron1), "X");

	wmove( win, getPosy(pTron), getPosx(pTron));
    wmove( win, getPosy(pTron1), getPosx(pTron1));
    wrefresh(win);
}

void ncursAffScore( WINDOW* win, const Jeu *pJeu) 
{

	wclear(win);
	if(getEcr(jeuGetConstJoueur(pJeu,0))==1 || getEcr(jeuGetConstJoueur(pJeu,1))==1)
	{
		mvwprintw( win, 0, 0, "PERDU!!!!!!" );
	}
	else
	{
		mvwprintw( win, 0, 0, "");
	}

	mvwprintw( win, 1, 0,"SCORE :\n %d - %d",getScore(jeuGetConstJoueur(pJeu,0)), getScore(jeuGetConstJoueur(pJeu,1)) );

	mvwprintw(win, 4,0,"TURBO Joueur1 : %d\nTURBO Joueur2 : %d",getTurbo(jeuGetConstJoueur(pJeu,0)),getTurbo(jeuGetConstJoueur(pJeu,1))); 
    wrefresh(win);
}


void ncursAffGagnant(WINDOW* win, Jeu *pJeu)
{
	wclear(win);
	mvwprintw(win, 10,30, "Le Joueur %d a gagné",(jeuTrouverGagnant(pJeu)->id)+1);
	wrefresh(win);
}


void ncursBoucle(Jeu *pJeu) 
{
	WINDOW *winscore;
	WINDOW *win;

	noecho();  	/* Lorsqu'une touche est préssée au clavier, elle n'apparait pasa à l'écran */
    cbreak();		/* un caractère est directement affiché, il ne passe pas dans un buffer */

	 /* Horloges (en secondes) */
    float horloge_courante, horloge_precedente;

    /* Intervalle de temps (en secondes) entre deux évolutions du jeu */
    /* Changer la valeur pour ralentir ou accélérer le déplacement des fantomes */
    float intervalle_horloge = 0.1f;
	
	win = newwin(getdimy(jeuGetTerrain(pJeu)), getdimx(jeuGetTerrain(pJeu)), 0, 0);
	winscore = newwin(15, 15, 0,getdimx(jeuGetTerrain(pJeu))+1 );
	keypad(win, TRUE);
	nodelay(win,true); /* Pour que l'appel à wgetch soit non-bloquant */


	int continue_boucle;
	int c;
	

	  do{

            continue_boucle = 1;

            //touche = 'g';
            //touche = pJeu->J.direction;

                /* Récupère l'horloge actuelle et la convertit en secondes */

            /* clock() retourne le nombre de tops horloge depuis le lancement du programme */

            horloge_precedente = (float)clock()/(float)CLOCKS_PER_SEC;

            ncursAffTerrain( win, pJeu);

            ncursAffScore( winscore, pJeu);
            
			/*tant que le joueur n'appuie pas sur 
           	 	la suivante partie ne commence pas*/

           		c = wgetch(win);

            	do{

                	c = wgetch(win);

				}while(c != 'r');
        

            do {
				
				
				

                /* Récupère l'horloge actuelle et la convertit en secondes */

                /* clock() retourne le nombre de tops horloge depuis le lancement du programme */

                horloge_courante = (float)clock()/(float)CLOCKS_PER_SEC;

                if (horloge_courante-horloge_precedente>=intervalle_horloge) 
                {

                        jeuClavier(pJeu);
						ncursAffScore( winscore, pJeu);

                        /*Verification ecrasement joueur */

                        if(getEcr(jeuGetJoueur(pJeu,0)) && getEcr(jeuGetJoueur(pJeu,1))) //Si les deux joueurs s'écrasent en même temps
                        {
                            continue_boucle=0;
                        }
						else if(getEcr(jeuGetJoueur(pJeu,1)))
		                {
		                	incrScore(jeuGetJoueur(pJeu,0));
		                	continue_boucle=0;
		                }
						else if(getEcr(jeuGetJoueur(pJeu,0))) 
                        {
							incrScore(jeuGetJoueur(pJeu,1));
                           	continue_boucle=0;
                       	}
                       	
													


                       
						ncursAffTerrain( win, pJeu);


                        horloge_precedente = horloge_courante;

                }

                   c = wgetch(win);

                   switch(c) {

                               case 'q':

                                        if ((pJeu->nbJoueur > 1) && (pJeu->J[1].direction != 'd'))
                                        {
                                            pJeu->J[1].direction = 'g';
                                        }
                                        break;

                               case KEY_LEFT:

                                        if(pJeu->J[0].direction != 'd')
                                        {
                                            pJeu->J[0].direction = 'g';
                                        }
                                        break;

                                case 'd':

                                        if ((pJeu->nbJoueur > 1) && (pJeu->J[1].direction != 'g'))
                                        {
                                            pJeu->J[1].direction = 'd';
                                        }
                                        break;

                                case KEY_RIGHT:

                                        if(pJeu->J[0].direction != 'g')
                                        {
                                            pJeu->J[0].direction = 'd';
                                        }
                                        break;

                                case 'z':

                                        if ((pJeu->nbJoueur > 1) && (pJeu->J[1].direction != 'b'))
                                        {
                                            pJeu->J[1].direction = 'h';
                                        }
                                        break;

                                case KEY_UP:

                                        if(pJeu->J[0].direction != 'b')
                                        {
                                            pJeu->J[0].direction = 'h';
                                        }

                                        break;

                                case 's':

                                        if ((pJeu->nbJoueur > 1) && (pJeu->J[1].direction != 'h'))
                                        {
                                            pJeu->J[1].direction = 'b';
                                        }
                                        break;

                                case KEY_DOWN:

                                        if(pJeu->J[0].direction != 'h')
                                        {
                                            pJeu->J[0].direction = 'b';
                                        }

                                        break;

                                case 'h':

                                        if(pJeu->J[0].turbo > 0) // S'il reste du turbo au joueur
                                        {
                                            pJeu->J[0].turbo += 10;
                                        }
                                        break;

                                case 'e':
                                        if(pJeu->J[1].turbo > 0) // S'il reste du turbo au joueur
                                        {
                                            pJeu->J[1].turbo += 10;
                                        }
                                        break;


                                case 27: /* ECHAP */

                                        continue_boucle = 0;

                                        break;

                                default : 
                                		break;

                        }

                } while (continue_boucle==1);

           // ncursAffTerrain( win, pJeu);

            ncursAffScore( winscore, pJeu);

            jeuInitPartie(pJeu,pJeu->N->idNiveau);

            

        }while(((getScore(jeuGetConstJoueur(pJeu,0)))<3)   &&   ((getScore(jeuGetConstJoueur(pJeu,1)))<3)); 

	ncursAffGagnant(win,pJeu);
c = wgetch(win);

            	do{

                	c = wgetch(win);

				}while(c != 27);
	
wclear(win);
wclear(winscore);
wrefresh(win);
wrefresh(winscore);

    endwin();
}

void ncursMenu(Jeu *pJeu) /* Affiche Menu et Initialise Jeu*/
{
    WINDOW* win;
    int c;
    int nbjoueurs;
    int idNiveau;

	initscr();		/* passe l'écran texte en mode NCurses */
	clear();		/* efface l'écran */
	noecho();  	/* Lorsqu'une touche est préssée au clavier, elle n'apparait pasa à l'écran */
    cbreak();		/* un caractère est directement affiché, il ne passe pas dans un buffer */
	
	win = newwin(100, 100, 10, 40);	

		//Affichage titre TRON
	mvwprintw(win, 0, 0,"TTTTTTTTTTT  RRRRRRRR    OOOOOOOO   NNN     NN\nTTTTTTTTTTT  RRR   RR    OOOOOOOO   NNNN    NN\n    TTT      RRR   RR    OO    OO   NN  NN  NN\n    TTT      RRRRRRR     OO    OO   NN   NN NN\n    TTT      RRR   RR    OOOOOOOO   NN    NNNN\n    TTT      RRR   RRR   OOOOOOOO   NN     NNN");
	mvwprintw(win, 10, 0,"Appuyez sur: \n\n 1)Nouvelle Partie\n 2)Quitter\n");
	wrefresh(win);
	c = wgetch(win);
	while (c=='1')
	{
		wclear(win);
		//Affichage mini-terrains
		mvwprintw(win, 0,0,"Quel terrain voulez-vous ?\n1)                                                   2)\n##########################                          ##########################\n#                        #                          #                        #\n#                        #                          #    ####        ####    #\n#                        #                          #    #              #    #\n#                        #                          #    #              #    #\n#                        #                          #    ####        ####    #\n#                        #                          #                        #\n##########################                          ##########################\n\n3)\n##########################\n#                        #\n#    ####        ####    #\n#       #        #       #\n#       #        #       #\n#    ####        ####    #\n#                        #\n##########################\n");
		wrefresh(win);
		idNiveau = wgetch(win)- '0';
		jeuInit(pJeu, idNiveau);
		wclear(win);
		ncursBoucle(pJeu);
		jeuLibere(pJeu);
		mvwprintw(win, 0, 0,"TTTTTTTTTTT  RRRRRRRR    OOOOOOOO   NNN     NN\nTTTTTTTTTTT  RRR   RR    OOOOOOOO   NNNN    NN\n    TTT      RRR   RR    OO    OO   NN  NN  NN\n    TTT      RRRRRRR     OO    OO   NN   NN NN\n    TTT      RRR   RR    OOOOOOOO   NN    NNNN\n    TTT      RRR   RRR   OOOOOOOO   NN     NNN");
		mvwprintw(win, 10, 0,"Appuyez sur: \n\n 1)Nouvelle Partie\n 2)Quitter\n");
		wrefresh(win);
		c = wgetch(win);
	}


    endwin();
}

