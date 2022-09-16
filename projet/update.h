/**
 * \file update.h
 * \brief Programme déclarant les fonctions utilisées pour mettre à jour les données à chaque boucle de jeu
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 27 mai 2020
 */
  
#ifndef update_data
#include "database.h"


/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world données du monde
 */
void update_data(world_t *world);


/**
 * \brief Procédure qui vérifie si le vaisseau dépasse la limite gauche de l'écran
 * \param world données du monde
 */
void limite_gauche(world_t *world);


/**
 * \brief Procédure qui vérifie si le vaisseau dépasse la limite droite de l'écran
 * \param world données du monde
 */
void limite_droite(world_t *world);


/**
 * \brief Procédure qui vérifie si le vaisseau ennemi dépasse la limite basse de l'écran et ajoute +1 au compteur
 * \param world données du monde
 */
void limite_bas(world_t *world);


/**
 * \brief Fonction qui vérifie si deux sprites sont en collision.
 * \param sp1 sprite n°1
 * \param sp2 sprite n°2
 * \return 1 en cas de collision et 0 en cas de non-collision
 */
int sprites_collide(sprite_t *sp2, sprite_t *sp1);


/**
 * \brief Procédure qui annule la vitesse de deux sprites en collision et qui les rends invisible.
 * \param sp1 sprite n°1
 * \param sp2 sprite n°2
 */
void handle_sprites_collision(sprite_t *sp2, sprite_t *sp1);


/**
 * \brief Procédure qui gère la collision entre un bonus et le vaisseau du joueur.
 * \param sp1 sprite n°1 (bonus)
 * \param sp2 sprite n°2
 */
void handle_bonus_collision(sprite_t *bonus, sprite_t *sp);


/**
 * \brief Procédure qui gère la collision entre un vaisseau infecté et un missile ou le joueur.
 * \param sp1 sprite n°1 (vaisseau infecté)
 * \param sp2 sprite n°2
 */
void handle_infected_collision(sprite_t *infect, sprite_t *sp);


/**
 * \brief Procédure qui gère la collision entre le boss et un missile du joueur.
 * \param sp1 sprite n°1 (boss)
 * \param sp2 sprite n°2
 */
void handle_boss_collision(sprite_t *boss, sprite_t *sp);


/**
 * \brief Procédure qui gère la collision entre le portail et le vaisseau du joueur.
 * \param sp1 sprite n°1 (portail)
 * \param sp2 sprite n°2
 */
void handle_portal_collision(sprite_t *portail, sprite_t *sp);


/**
 * \brief Procédure qui éxecute des changements si un vaisseau infecté est détruit.
 * \param world Données du monde.
 */
void infected_destroyed(world_t* world);


/**
 * \brief Procédure qui gère le fait que le boss touche un mur.
 * \param world Données du monde.
 */
void limite_boss(world_t* world);


/**
 * \brief Procédure qui print les données d'un sprite
 * \param sprite Le sprite dont on veut afficher les données
 */
void print_sprite(sprite_t * sprite);


/**
 * \brief Procédure qui mets à jour les données des ennemis.
 * \param world Données du monde.
 */
void update_enemies(world_t* world);


/**
 * \brief Procédure qui mets à jour les données des vaisseaux infectés.
 * \param world Données du monde.
 */
void update_infected(world_t* world);


/**
 * \brief Procédure qui implémente les règles du jeu.
 * \param world Données du monde.
 */
void compute_game(world_t *world);


/**
 * \brief Fonction qui indique si tous les ennemis sont invisible (donc tous morts ou passés).
 * \param world Données du monde.
 * \return 0 si ils sont tous invisibles, 1 si il y en a au moins un de visible.
 */
int ennemis_invisibles(world_t* world);


/**
 * \brief Fonction qui regarde le nombre de vaisseaux détruits.
 * \param world Données du monde.
 * \return Nombre d'ennemis détruits par le joueur.
 */
int ennemis_detruits(world_t* world);


#endif