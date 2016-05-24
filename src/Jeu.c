#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Jeu.h"

void jeuInit(Jeu *JeuTron, int idNiveau)
{
	JeuTron->N = (Niveau*) malloc(sizeof(Niveau));
	assert(JeuTron->N != NULL);
	JeuTron->N->idNiveau=idNiveau;
	initTerrain(&(JeuTron->N->T),LARGEUR_JEU,HAUTEUR_JEU,idNiveau);
	JeuTron->nbJoueur = 2;
	int nb = JeuTron->nbJoueur;
	JeuTron->J = (Joueur*) malloc(nb*sizeof(Joueur));
	assert(JeuTron->J != NULL);
	initJoueur(&(JeuTron->J[0]),0,&(JeuTron->N->T));
	initJoueur(&(JeuTron->J[1]),1,&(JeuTron->N->T));
}

void jeuInitPartie(Jeu * JeuTron,int idNiveau)
{
	Niveau * Niv = JeuTron->N;
	initTerrain(&(Niv->T),LARGEUR_JEU,HAUTEUR_JEU,idNiveau);
	initPos(jeuGetJoueur(JeuTron,0),0,&(Niv->T));
	initPos(jeuGetJoueur(JeuTron,1),1,&(Niv->T));
	(jeuGetJoueur(JeuTron,0))->ecr = 0;
	(jeuGetJoueur(JeuTron,1))->ecr = 0;
	// Réinitialisation du turbo
	(jeuGetJoueur(JeuTron,0))->turbo = 3;
	(jeuGetJoueur(JeuTron,1))->turbo = 3;
}

void jeuLibere(Jeu *JeuTron)
{
	Niveau * Niv = JeuTron->N;
	libereTerrain(&(Niv->T));
	libereJoueur(&(JeuTron->J[0]));
	if (JeuTron->nbJoueur == 2)
	{
		libereJoueur(&(JeuTron->J[1]));
	}
	JeuTron->nbJoueur=0;
}

Terrain * jeuGetTerrain(Jeu *JeuTron)
{
	return &(JeuTron->N->T);
}

void jeuSetJoueur(Jeu *JeuTron, int nb)
{
    int i;
	free(JeuTron->J);
	JeuTron->J = (Joueur*) malloc(nb*sizeof(Joueur));
	for(i=0; i<nb; i++)
	{
		initJoueur(&(JeuTron->J[i]),i,&(JeuTron->N->T));
	}
}

Joueur * jeuGetJoueur(const Jeu *JeuTron, const int id)
{
	if (id == 0)
	{
		return &(JeuTron->J[0]);
	}
	else
		return &(JeuTron->J[1]);
}

const Terrain * jeuGetConstTerrain(const Jeu *JeuTron)
{
	return &(JeuTron->N->T);
}

const Joueur * jeuGetConstJoueur(const Jeu *JeuTron, const int id)
{
	if (id == 0)
	{
		return &(JeuTron->J[0]);
	}
	else
		return &(JeuTron->J[1]);
}

Joueur * jeuTrouverGagnant(Jeu *JeuTron)
{
	int nb = JeuTron->nbJoueur;
	int i;
	for (i=0; i<=nb; i++)
	{
		if((JeuTron->J[i].score) == 3)
		{
			return &(JeuTron->J[i]);
		}
	}
	return NULL;
}

void jeuSetNiveau(Jeu *JeuTron, int idNiveau)
{
	libereTerrain(&(JeuTron->N->T));

	JeuTron->N->idNiveau = idNiveau;
	JeuTron->N = (Niveau*) malloc(sizeof(Niveau));
	initTerrain(&(JeuTron->N->T),LARGEUR_JEU,HAUTEUR_JEU,idNiveau);
}

void jeuClavier(Jeu * JeuTron)
{
	int i;
	Niveau * Niv = JeuTron->N;
	for(i = 0; i < JeuTron->nbJoueur; i++)
	{
		switch(JeuTron->J[i].direction)
		{
			case 'g':
				if (deplacementPossible(&JeuTron->J[i],'g'))
				{
					tronGauche(&JeuTron->J[i],&Niv->T);
				}
				else
					tronDroite(&JeuTron->J[i],&Niv->T);
				break;
			case 'd':
				if (deplacementPossible(&JeuTron->J[i],'d'))
				{
					tronDroite(&JeuTron->J[i],&Niv->T);
				}
				else
					tronGauche(&JeuTron->J[i],&Niv->T);
				break;
			case 'h':
				if (deplacementPossible(&JeuTron->J[i],'h'))
				{
					tronHaut(&JeuTron->J[i],&Niv->T);
				}
				else
					tronBas(&JeuTron->J[i],&Niv->T);
				break;
			case 'b':
				if (deplacementPossible(&JeuTron->J[i],'b'))
				{
					tronBas(&JeuTron->J[i],&Niv->T);
				}
				else
					tronHaut(&JeuTron->J[i],&Niv->T);
				break;
			default:
				break;
		}
	}
}



