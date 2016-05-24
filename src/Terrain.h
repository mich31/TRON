#ifndef _TERRAIN_H
#define _TERRAIN_H

/**
 * \file Terrain.h
 * \brief Module Terrain
 *
 */


 /**
 * \struct s_case
 * \brief Structure s_case.
 * 
 */
typedef struct
{
	char valeur;
	char direction;
	int idJoueur;
} s_case;


/**
 * \struct Terrain
 * \brief Structure Terrain.
 * Terrain est une structure contenant des informations sur les dimensions du jeu et
 * un tableau de s_case.
 */
typedef struct 
{
	int dimx,dimy;
	//char ** tab;
	s_case ** tab;
} Terrain;


/**
 * \fn void initTerrain(Terrain * T,const int x,const int y, const int id)
 * \brief Fonction d'initialisation du terrain
 * Initialise les champs dimx et dimy avec les dimensions du terrain puis alloue un tableau 2D de char.
 * \param Terrain * T un pointeur sur le terrain à initialiser,x et y les dimensions du terrain à initialiser, id un entier identifiant le terrain.
 */
void initTerrain(Terrain * T,const int x,const int y, const int id);

/**
 * \fn void libereTerrain(Terrain * T)
 * \brief Fonction qui libère la mémoire allouée sur le tableau 2D.
 *
 * \param Terrain * T un pointeur sur terrain.
 */
void libereTerrain(Terrain * T);


/**
 * \fn int getdimx(const Terrain * T)
 * \brief Accesseur. 
 * Renvoie la dimension en x du terrain T.
 * \param Terrain * T un pointeur sur terrain.
 * \return Un entier correspondant à la largeur du terrain.
 */
int getdimx(const Terrain * T);


/**
 * \fn int getdimy(const Terrain * T)
 * \brief Accesseur. 
 * Renvoie la dimension en y du terrain T.
 * \param Terrain * T un pointeur sur terrain.
 * \return Un entier correspondant à la hauteur du terrain.
 */
int getdimy(const Terrain * T);


/**
 * \fn void coordonneesValide(const Terrain * T,const int x,const int y)
 * \brief Fonction vérifiant que les coordonnées (x,y) sont valides dans le terrain T à travers des assert.
 *
 * \param Terrain * T un pointeur sur terrain, x et y les coordonnées dont on doit vérifier la validité.
 */
void coordonneesValide(const Terrain * T,const int x,const int y);


/**
 * \fn char terGetXY(const Terrain * T,const int x,const int y)
 * \brief Fonction vérifiant la validité des coordonnées x et y puis renvoie le caractère stocké dans le tableau
 * aux coordonnées (x,y). 
 *
 * \param Terrain * T un pointeur sur terrain, x et y les coordonnées du point dont on veut obtenir la valeur.
 * \return Un caractère 
 */
char terGetXY(const Terrain * T,const int x,const int y);


/**
 * \fn void terSetXY(Terrain * T,const int x,const int y,const s_case * c)
 * \brief Mutateur du terrain aux coordonnées (x,y).
 * Modifie le contenu du terrain au point de coordonnées (x,y) par un s_case c.
 * \param Terrain * T un pointeur sur terrain, x et y les coordonnées du point dont on veut modifier le contenu.
 */
void terSetXY(Terrain * T,const int x,const int y,const s_case * c);


/**
 * \fn int terPositionValide(const Terrain * T,const int x,const int y)
 * \brief Fonction vérifiant que le terrain aux coordonnées (x,y) est libre.
 *
 * \param Terrain * T un pointeur sur terrain, x et y les coordonnées du point dont on veut vérifier la validité.
 */
int terPositionValide(const Terrain * T,const int x,const int y);

#endif
