/**
 * \file one_use.h
 * \brief Programme déclarant les fonctions utilisées une seule fois pour initialiser ou nettoyer les données
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 27 mai 2020
 */
 
#ifndef init_data
#include "database.h"


/**
 * \brief Hauteur du bonus nuke
*/

#define NUKE_HEIGHT 31


/**
 * \brief Largeur du bonus nuke
*/

#define NUKE_WIDTH 16


/**
 * \brief Hauteur du bonus de vitesse
*/

#define BV_HEIGHT 22


/**
 * \brief Largeur du bonus de vitesse
*/

#define BV_WIDTH 10


/**
 * \brief Hauteur du boss
*/

#define BOSS_HEIGHT 48


/**
 * \brief Largeur du boss
*/

#define BOSS_WIDTH 40


/**
 * \brief Hauteur du portail
*/

#define PORTAL_HEIGHT 32


/**
 * \brief Largeur du portail
*/

#define PORTAL_WIDTH 20


/**
 * \brief Hauteur du missile du boss
*/

#define BOSS_MISSILE_HEIGHT 21


/**
 * \brief Largeur du missile du boss
*/

#define BOSS_MISSILE_WIDTH 11


/**
 * \brief Points de vie initiaux du vaisseau du joueur.
*/

#define PV_INITIAL 3


/**
 * \brief Distance verticale entre deux ennemis.
*/

#define VERTICAL_DIST 4*SHIP_SIZE


/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t * world);


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t *world);


/**
 * \brief Procédure qui initialise les ennemis.
 * \param world Données du monde.
 */
void init_enemies(world_t* world);


/**
 * \brief Procédure qui initialise les vaisseaux infectés.
 * \param world Données du monde.
 */
void init_infected(world_t* world);


#endif