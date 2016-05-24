#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "sdlJeu.h"

void sdlJeuInit(sdlJeu * J)
{
	
	if(SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL: %s\n", SDL_GetError()); // Ecriture de l'erreur
		exit(EXIT_FAILURE); // On quitte le programme
	}

	J->ecran = NULL;
	J->background = NULL;

	J->ecran = SDL_SetVideoMode(LARGEUR_FENETRE_SDL,HAUTEUR_FENETRE_SDL,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_RESIZABLE);
	assert(J->ecran != NULL);

	SDL_WM_SetCaption("TRON",NULL); // Affichage du titre de la fenêtre

	J->background = IMG_Load("./data/sprite/background.png");
	J->Tron1Haut = IMG_Load("./data/sprite/T1H.png");
	J->Tron1Bas = IMG_Load("./data/sprite/T1B.png");
	J->Tron1Gauche = IMG_Load("./data/sprite/T1G.png");
	J->Tron1Droite = IMG_Load("./data/sprite/T1D.png");
	J->Tron2Haut = IMG_Load("./data/sprite/T2H.png");
	J->Tron2Bas = IMG_Load("./data/sprite/T2B.png");
	J->Tron2Gauche = IMG_Load("./data/sprite/T2G.png");
	J->Tron2Droite = IMG_Load("./data/sprite/T2D.png");
	J->Trace1Horizontale = IMG_Load("./data/sprite/Trace1H.png");
	J->Trace1Verticale = IMG_Load("./data/sprite/Trace1V.png");
	J->Trace2Horizontale = IMG_Load("./data/sprite/Trace2H.png");
	J->Trace2Verticale = IMG_Load("./data/sprite/Trace2V.png");
	J->Coin1J1 = IMG_Load("./data/sprite/Coin1J1.png");
	J->Coin2J1 = IMG_Load("./data/sprite/Coin2J1.png");
	J->Coin3J1 = IMG_Load("./data/sprite/Coin3J1.png");
	J->Coin4J1 = IMG_Load("./data/sprite/Coin4J1.png");
	J->Coin1J2 = IMG_Load("./data/sprite/Coin1J2.png");
	J->Coin2J2 = IMG_Load("./data/sprite/Coin2J2.png");
	J->Coin3J2 = IMG_Load("./data/sprite/Coin3J2.png");
	J->Coin4J2 = IMG_Load("./data/sprite/Coin4J2.png");
	J->ecrassement = IMG_Load("./data/sprite/ecrassement.png");
	J->menu1 = IMG_Load("./data/sprite/Menu1.png");
	J->menu2 = IMG_Load("./data/sprite/Menu2.png");
	J->menu3 = IMG_Load("./data/sprite/Menu3.png");
	J->menu4 = IMG_Load("./data/sprite/Menu4.png");
	J->menu5 = IMG_Load("./data/sprite/Menu5.png");
	J->menu6 = IMG_Load("./data/sprite/Menu6.png");
	J->mur = IMG_Load("./data/sprite/mur.png");

	TTF_Init(); // Démarrage SDL_ttf
}

void sdlJeuAff(sdlJeu * J)
{
	int x,y;
	const Jeu * pJeu = &(J->jeu);
	const Niveau * N = J->jeu.N;
	SDL_Surface * ScoreJoueur1 = NULL;
 	SDL_Surface * ScoreJoueur2 = NULL;
 	SDL_Surface * turbo1 = SDL_CreateRGBSurface(SDL_HWSURFACE,10,10,32,0,0,0,0);
 	SDL_Surface * turbo2 = SDL_CreateRGBSurface(SDL_HWSURFACE,10,10,32,0,0,0,0);
 	SDL_Color blanc = {255,255,255};

 	char chScore1[32];
 	char chScore2[32];
	
	SDL_Rect pos_trace,posJoueur1,posJoueur2,pos_background;
	SDL_Rect position_score_joueur1,position_score_joueur2,pos_turbo1,pos_turbo2;

	TTF_Font * police1 = NULL;
 	police1 = TTF_OpenFont("./data/police/UKNumberPlate.ttf",30);

 	position_score_joueur1.x = (16 * TAILLE_SPRITE) + 5;
 	position_score_joueur1.y = (2 * TAILLE_SPRITE) + 8;

 	position_score_joueur2.x = (25 * TAILLE_SPRITE) + 5;
 	position_score_joueur2.y = (2 * TAILLE_SPRITE) + 8;

 	pos_turbo1.x = (9 * TAILLE_SPRITE) + 20;
 	pos_turbo1.y = 3 * TAILLE_SPRITE;
 	pos_turbo2.x = (31 * TAILLE_SPRITE) + 18;
 	pos_turbo2.y = 3 * TAILLE_SPRITE;


	pos_background.x = 0;
	pos_background.y = 0;

	posJoueur1.x = (pJeu->J[0].posx * TAILLE_SPRITE);
	posJoueur1.y = (pJeu->J[0].posy * TAILLE_SPRITE) + 90;
	posJoueur2.x = (pJeu->J[1].posx * TAILLE_SPRITE);
	posJoueur2.y = (pJeu->J[1].posy * TAILLE_SPRITE) + 90;

	// Affichage de l'arrière plan
	SDL_BlitSurface(J->background,NULL,J->ecran,&pos_background);

	for (y = 0; y < N->T.dimy ; y++)
	{
		for (x = 0; x < N->T.dimx ; x++)
		{
			// Calcul des coordonnées du sprite
			pos_trace.x = x * TAILLE_SPRITE;
			pos_trace.y = (y * TAILLE_SPRITE) + 90;
			
			// Affichage des sprites
			switch(N->T.tab[y][x].direction)
			{
				case '\0':
					
					break;
				case '#':
					SDL_BlitSurface(J->mur,NULL,J->ecran,&pos_trace);
					break;

				case 'H':
				case 'B':
					if(N->T.tab[y][x].idJoueur == 0)
					{
						SDL_BlitSurface(J->Trace1Verticale,NULL,J->ecran,&pos_trace);
					}
					else
					{
						SDL_BlitSurface(J->Trace2Verticale,NULL,J->ecran,&pos_trace);
					}
					break;

				case 'G':
				case 'D':
					if(N->T.tab[y][x].idJoueur == 0)
					{
						SDL_BlitSurface(J->Trace1Horizontale,NULL,J->ecran,&pos_trace);
					}
					else
					{
						SDL_BlitSurface(J->Trace2Horizontale,NULL,J->ecran,&pos_trace);
					}
					break;

				case '1':
					if(N->T.tab[y][x].idJoueur == 0)
					{
						SDL_BlitSurface(J->Coin1J1,NULL,J->ecran,&pos_trace);
					}
					else
					{
						SDL_BlitSurface(J->Coin1J2,NULL,J->ecran,&pos_trace); // pos_trace 1 à modifier !!!!
					}
					break;

				case '2':
					if(N->T.tab[y][x].idJoueur == 0)
					{
						SDL_BlitSurface(J->Coin2J1,NULL,J->ecran,&pos_trace);
					}
					else
					{
						SDL_BlitSurface(J->Coin2J2,NULL,J->ecran,&pos_trace);
					}
						break;

				case '3':
					if(N->T.tab[y][x].idJoueur == 0)
					{
						SDL_BlitSurface(J->Coin3J1,NULL,J->ecran,&pos_trace);
					}
					else
					{
						SDL_BlitSurface(J->Coin3J2,NULL,J->ecran,&pos_trace);
					}
						break;

				case '4':
					if(N->T.tab[y][x].idJoueur == 0)
					{
						SDL_BlitSurface(J->Coin4J1,NULL,J->ecran,&pos_trace);
					}
					else
					{
						SDL_BlitSurface(J->Coin4J2,NULL,J->ecran,&pos_trace);
					}
						break;

				default:
					break;
			}
		}
	}

	if(getEcr(jeuGetJoueur(pJeu,0)))
	{
		SDL_BlitSurface(J->ecrassement,NULL,J->ecran,&posJoueur1);
	}
	else
	{
		switch(pJeu->J[0].direction)
		{
			case 'g':
				SDL_BlitSurface(J->Tron1Gauche,NULL,J->ecran,&posJoueur1);
				break;
			case 'd':
				SDL_BlitSurface(J->Tron1Droite,NULL,J->ecran,&posJoueur1);
				break;
			case 'h':
				SDL_BlitSurface(J->Tron1Haut,NULL,J->ecran,&posJoueur1);
				break;
			case 'b':
				SDL_BlitSurface(J->Tron1Bas,NULL,J->ecran,&posJoueur1);
				break;
			default:
				break;
		}
	}
	

	if(pJeu->nbJoueur == 2)
	{
		if(getEcr(jeuGetJoueur(pJeu,1)))
		{
			SDL_BlitSurface(J->ecrassement,NULL,J->ecran,&posJoueur2);
		}
		else
		{
			switch(pJeu->J[1].direction)
			{
				case 'g':
					SDL_BlitSurface(J->Tron2Gauche,NULL,J->ecran,&posJoueur2);
					break;
				case 'd':
					SDL_BlitSurface(J->Tron2Droite,NULL,J->ecran,&posJoueur2);
					break;
				case 'h':
					SDL_BlitSurface(J->Tron2Haut,NULL,J->ecran,&posJoueur2);
					break;
				case 'b':
					SDL_BlitSurface(J->Tron2Bas,NULL,J->ecran,&posJoueur2);
					break;
				default:
					break;
			}
		}
	}


	sprintf(chScore1,"%d",pJeu->J[0].score);
	sprintf(chScore2,"%d",pJeu->J[1].score);

	ScoreJoueur1 = TTF_RenderText_Solid(police1,chScore1,blanc);
	ScoreJoueur2 = TTF_RenderText_Solid(police1,chScore2,blanc);


	SDL_BlitSurface(ScoreJoueur1,NULL,J->ecran,&position_score_joueur1); 
	SDL_BlitSurface(ScoreJoueur2,NULL,J->ecran,&position_score_joueur2);

	//Affichage du turbo
	if(pJeu->J[0].turbo > 0)
	{
		SDL_FillRect(turbo1,NULL,SDL_MapRGB(J->ecran->format,138,221,251));
		SDL_BlitSurface(turbo1,NULL,J->ecran,&pos_turbo1);
		if(pJeu->J[0].turbo > 1)
		{
			pos_turbo1.x = (10 * TAILLE_SPRITE) + 9;
			SDL_BlitSurface(turbo1,NULL,J->ecran,&pos_turbo1);
			if(pJeu->J[0].turbo > 2)
			{
				pos_turbo1.x = (10 * TAILLE_SPRITE) + 21;
				SDL_BlitSurface(turbo1,NULL,J->ecran,&pos_turbo1);
			}
		}
	}

	if (pJeu->J[1].turbo > 0)
	{
		SDL_FillRect(turbo2,NULL,SDL_MapRGB(J->ecran->format,247,255,149));
		SDL_BlitSurface(turbo2,NULL,J->ecran,&pos_turbo2);
		if (pJeu->J[1].turbo > 1)
		{
			pos_turbo2.x -= 13;
			SDL_BlitSurface(turbo2,NULL,J->ecran,&pos_turbo2);
			if(pJeu->J[1].turbo > 2)
			{
				pos_turbo2.x -= 13;
				SDL_BlitSurface(turbo2,NULL,J->ecran,&pos_turbo2);
			}
		}
	}


	SDL_Flip(J->ecran);

	TTF_CloseFont(police1);	
	SDL_FreeSurface(turbo1);
	SDL_FreeSurface(turbo2);
	SDL_FreeSurface(ScoreJoueur1);
	SDL_FreeSurface(ScoreJoueur2);


}

 void sdlJeuBoucle(sdlJeu * J)
 {
 	Jeu * pJeu = &(J->jeu);
 	int continuer, continuer2 = 1;
 	int x0,x1,y0,y1;
 	Terrain * pTer = &(J->jeu.N->T);
 	float horloge_courante, horloge_precedente; /* Horloges (en secondes) */
 	float intervalle_horloge = 0.1f; /* Intervalle de temps (en secondes) entre deux évolutions du jeu */
 	SDL_Event event;
 	int rafraichissement;

 	

     do
     {

     	continuer = 1;
    	sdlJeuAff(J);
 	 	/* Récupère l'horloge actuelle et la convertit en secondes */
     	/* clock() retourne le nombre de tops horloge depuis le lancement du programme */
     	horloge_precedente = (float)clock()/(float)CLOCKS_PER_SEC;
     	//c = wgetch(win);


        while(continuer)
        {
        	SDL_WaitEvent(&event);
        	switch(event.type)
        	{
        		case SDL_KEYDOWN :
        			continuer=0;
        			break;
        		default :
        			break;
        	}
        }
        jeuInitPartie(pJeu,pJeu->N->idNiveau);
        continuer=1;
    	while(continuer && continuer2)
    	{
     		rafraichissement = 0;
     		horloge_courante = (float)clock()/(float)CLOCKS_PER_SEC; /* Récupère l'horloge actuelle et la convertit en secondes */

     		/* Si suffisamment de temps s'est écoulé depuis la dernière prise d'horloge */
         	if (horloge_courante-horloge_precedente>=intervalle_horloge) 
         	{
                jeuClavier(&(J->jeu));
                rafraichissement = 1;
                /*Verification ecrasement joueur */

                if(getEcr(jeuGetJoueur(pJeu,0)) && getEcr(jeuGetJoueur(pJeu,1))) //Si les deux joueurs s'écrasent en même temps
                {
                    continuer=0;
                }
				else if(getEcr(jeuGetJoueur(pJeu,1)))
		        {
		            incrScore(jeuGetJoueur(pJeu,0));
		            continuer=0;
		        }
				else if(getEcr(jeuGetJoueur(pJeu,0))) 
                {
				incrScore(jeuGetJoueur(pJeu,1));
                continuer=0;
                }
                 horloge_precedente = horloge_courante;
         	}

         	/* tant qu'il y a des evenements à traiter : cette boucle n'est pas bloquante */
 			while ( SDL_PollEvent( &event )) 
 			{
 				switch(event.type)
 				{
 					case SDL_QUIT:	/* Si l'utilisateur a cliqué sur la croix de fermeture */
 						continuer = 0;
 						continuer2 = 0;
 						break;

 					case SDL_KEYDOWN:	/* Si l'utilisateur a appuyé sur une touche */
 						x0 = getPosx(&pJeu->J[0]);
						y0 = getPosy(&pJeu->J[0]);
						if(pJeu->nbJoueur > 1)
						{
							x1 = getPosx(&pJeu->J[1]);
							y1 = getPosy(&pJeu->J[1]);
						}
 						switch(event.key.keysym.sym)
 						{
 							case SDLK_ESCAPE:
 								continuer = 0;
 								continuer2 = 0;
 								break;

 							case SDLK_UP:
 								if(pJeu->J[0].direction != 'b')
 								{
 									if(pJeu->J[0].direction == 'g')
									{
										pTer->tab[y0][x0].direction = '4';
									}
									else if(pJeu->J[0].direction == 'd')
									{
										pTer->tab[y0][x0].direction = '3';
									}
	 								pJeu->J[0].direction = 'h';
	 								rafraichissement = 1;
 								}
 								break;

 							case 'z':
 								if(pJeu->J[1].direction != 'b')
 								{
 									if(pJeu->J[1].direction == 'g')
									{
										pTer->tab[y1][x1].direction = '4';
									}
									else if(pJeu->J[1].direction == 'd')
									{
										pTer->tab[y1][x1].direction = '3';
									}
	 								pJeu->J[1].direction = 'h';
	 								rafraichissement = 1;
 								}
 								break;


 							case SDLK_DOWN:
 								if(pJeu->J[0].direction != 'h')
 								{
 									if (pJeu->J[0].direction == 'g')
									{
										pTer->tab[y0][x0].direction = '1';
									}
									else if(pJeu->J[0].direction == 'd')
									{
										pTer->tab[y0][x0].direction = '2';
									}
	 								pJeu->J[0].direction = 'b';
	 								rafraichissement = 1;
	 							}
 								break;

 							case 's':
 								if(pJeu->J[1].direction != 'h')
 								{
									if (pJeu->J[1].direction == 'g')
									{
										pTer->tab[y1][x1].direction = '1';
									}
									else if(pJeu->J[1].direction == 'd')
									{
										pTer->tab[y1][x1].direction = '2';
									}
	 								pJeu->J[1].direction = 'b';
	 								rafraichissement = 1;
 								}
 								break;


	 						case SDLK_LEFT:
	 							if(pJeu->J[0].direction != 'd')
	 							{
	 								if (pJeu->J[0].direction == 'h')
									{
										pTer->tab[y0][x0].direction = '2';
									}
									else if(pJeu->J[0].direction == 'b')
									{
										pTer->tab[y0][x0].direction = '3';
									}
		 							pJeu->J[0].direction = 'g';
		 							rafraichissement = 1;
	 							}
	 							break;

	 						case 'q':
	 							if(pJeu->J[1].direction != 'd')
	 							{
	 								if (pJeu->J[1].direction == 'h')
									{
										pTer->tab[y1][x1].direction = '2';
									}
									else if(pJeu->J[1].direction == 'b')
									{
										pTer->tab[y1][x1].direction = '3';
									}
		 							pJeu->J[1].direction = 'g';
		 							rafraichissement = 1;
	 							}
	 							break;


	 						case SDLK_RIGHT:
	 							if(pJeu->J[0].direction != 'g')
	 							{
	 								if (pJeu->J[0].direction == 'h')
									{
										pTer->tab[y0][x0].direction = '1';
									}
									else if(pJeu->J[0].direction == 'b')
									{
										pTer->tab[y0][x0].direction = '4';
									}
		 							pJeu->J[0].direction = 'd';
		 							rafraichissement = 1;
	 							}
	 							break;

	 						case 'd':
	 							if(pJeu->J[1].direction != 'g')
	 							{
	 								if (pJeu->J[1].direction == 'h')
									{
										pTer->tab[y1][x1].direction = '1';
									}
									else if(pJeu->J[1].direction == 'b')
									{
										pTer->tab[y1][x1].direction = '4';
									}
		 							pJeu->J[1].direction = 'd';
		 							rafraichissement = 1;
	 							}
	 							break;


	 						case 'h': // turbo joueur 1
	 							if(pJeu->J[0].turbo > 0) // S'il reste du turbo au joueur
	                         	{
	                             	pJeu->J[0].turbo += 10;
	                         	}
	                         	break;

	                         case 'e': // turbo joueur 2
	                         	if (pJeu->J[1].turbo > 0) // S'il reste du turbo au joueur
	                         	{
	                         		pJeu->J[1].turbo += 10;
	                         	}
	                         	break;

 							default:
 								break;
 					}
 				}
     		}


     	if (rafraichissement == 1)
     	{
     		/* on affiche le jeu sur le buffer caché */
     		sdlJeuAff(J);

     		/* on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans a boucle) */
             SDL_Flip(J->ecran);
     	}

     	}
     	if(( ((getScore(jeuGetConstJoueur(pJeu,0)))>2)   ||   ((getScore(jeuGetConstJoueur(pJeu,1)))>2) ))
     	{
     		continuer2=0;
     	}
     
    } while(continuer2); 

    continuer=1;
    while(continuer)
    {
    	SDL_WaitEvent(&event);
       	switch(event.type)
       	{
       		case SDL_KEYDOWN :
       			continuer=0;
       			break;
       		default :
       			break;
       	}
    }

 }


void sdlJeuLibere(sdlJeu * J)
{
	SDL_FreeSurface(J->background);
	SDL_FreeSurface(J->Tron1Haut);
	SDL_FreeSurface(J->Tron1Bas);
	SDL_FreeSurface(J->Tron1Gauche);
	SDL_FreeSurface(J->Tron1Droite);
	SDL_FreeSurface(J->Tron2Haut);
	SDL_FreeSurface(J->Tron2Bas);
	SDL_FreeSurface(J->Tron2Gauche);
	SDL_FreeSurface(J->Tron2Droite);
	SDL_FreeSurface(J->Trace1Horizontale);
	SDL_FreeSurface(J->Trace1Verticale);
	SDL_FreeSurface(J->Trace2Horizontale);
	SDL_FreeSurface(J->Trace2Verticale);
	SDL_FreeSurface(J->Coin1J1);
	SDL_FreeSurface(J->Coin2J1);
	SDL_FreeSurface(J->Coin3J1);
	SDL_FreeSurface(J->Coin4J1);
	SDL_FreeSurface(J->Coin1J2);
	SDL_FreeSurface(J->Coin2J2);
	SDL_FreeSurface(J->Coin3J2);
	SDL_FreeSurface(J->Coin4J2);
	SDL_FreeSurface(J->ecrassement);
	SDL_FreeSurface(J->menu1);
	SDL_FreeSurface(J->menu2);
	SDL_FreeSurface(J->menu3);
	SDL_FreeSurface(J->menu4);
	SDL_FreeSurface(J->menu5);
	SDL_FreeSurface(J->menu6);
	SDL_FreeSurface(J->mur);
	
	TTF_Quit();
	SDL_Quit();
}

void sdlMenu(sdlJeu *J)
{
	SDL_Event event;
	int continuer;
	int continuer_jeu = 1;
	int menu;
	SDL_Rect posmenu;

	posmenu.x = 0;
	posmenu.y = 0;
	sdlJeuInit(J);
	
	while(continuer_jeu)
	{
	continuer = 1;
	continuer_jeu = 1;
	menu = 1;
    
    
	
		SDL_BlitSurface(J->menu1,NULL,J->ecran,&posmenu);
		SDL_Flip(J->ecran);
	
		
		while(continuer)
	     	{
	        	SDL_WaitEvent(&event);
	        	switch(event.type)
	        	{
	        		case SDL_KEYDOWN :
	        			switch(event.key.keysym.sym)
	        			{
	        				case SDLK_UP :
	        				case SDLK_DOWN :	
	        					if (menu==1)
	        					{
	        						menu=2;
	        						SDL_BlitSurface(J->menu2,NULL,J->ecran,&posmenu);
									SDL_Flip(J->ecran);
								}
	        					else
	        					{
	        						menu=1;
	        						SDL_BlitSurface(J->menu1,NULL,J->ecran,&posmenu);
									SDL_Flip(J->ecran);
								}
	        					break;

	        				case SDLK_RETURN :
	        					if (menu==1)
	        						continuer=0;
	        					else
	        					{
	        						continuer=0;
	        						continuer_jeu=0;
	        					}
	        					break;

	        				default :
	        					break;
	        			}
	        			break;

	        		case SDL_QUIT :
	        			continuer=0;
	        			continuer_jeu=0;
	        			break;

	        		default :
	        			break;
	        	}
	        }
	    if(continuer_jeu)
	    {
		    continuer=1;
		    menu=1;
		    SDL_BlitSurface(J->menu3,NULL,J->ecran,&posmenu);
			SDL_Flip(J->ecran);
		    while(continuer)
		     	{
		        	SDL_WaitEvent(&event);
		        	switch(event.type)
		        	{
		        		case SDL_KEYDOWN :
		        			switch(event.key.keysym.sym)
		        			{
		        				case SDLK_UP :
		        				case SDLK_DOWN :	
		        					if ((menu==1)||(menu==2))
		        					{
		        						menu=3;
		        						SDL_BlitSurface(J->menu5,NULL,J->ecran,&posmenu);
										SDL_Flip(J->ecran);
									}
		        					else
		        					{
		        						menu=1;
		        						SDL_BlitSurface(J->menu3,NULL,J->ecran,&posmenu);
										SDL_Flip(J->ecran);
									}
		        					break;
		        				case SDLK_LEFT :
		        				case SDLK_RIGHT :	
		        					if (menu==1)
		        					{
		        						menu=2;
		        						SDL_BlitSurface(J->menu4,NULL,J->ecran,&posmenu);
										SDL_Flip(J->ecran);
									}
		        					else if (menu==2)
		        					{
		        						menu=1;
		        						SDL_BlitSurface(J->menu3,NULL,J->ecran,&posmenu);
										SDL_Flip(J->ecran);
									}
		        					break;
		        				case SDLK_RETURN :
		        					continuer=0;
		        					break;
		        				default :
		        					break;
		        			}
		        			break;
		        		case SDL_QUIT :
		        			continuer=0;
		        			continuer_jeu=0;
		        			break;
		        		default :
		        			break;
		        	}
		        }
		    continuer=1;
		    SDL_BlitSurface(J->menu6,NULL,J->ecran,&posmenu);
			SDL_Flip(J->ecran);
		    while(continuer)
		    {
		    	SDL_WaitEvent(&event);
		        	switch(event.type)
		        	{
		        		case SDL_KEYDOWN :
		        			continuer = 0;
		        			break;
		        		case SDL_QUIT :
		        			continuer = 0;
		        			continuer_jeu = 0;
		        			break;
		        		default :
		        			break;
		    		}
		    }
		    if(menu==1)
		    	jeuInit(&(J->jeu),1);
		    else if(menu ==2)
		    	jeuInit(&(J->jeu), 2);
		    else if(menu==3)
		    	jeuInit(&(J->jeu), 3);

		}
	    if(continuer_jeu)
	    {

		sdlJeuBoucle(J);
		jeuLibere(&(J->jeu));
		
		}
	
	}
	
	sdlJeuLibere(J);
}
