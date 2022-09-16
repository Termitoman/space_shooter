/**
 * \file database.h
 * \brief Programme déclarant les constantes, structures et fonctions nécessaires à tous les modules
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 23 mai 2020
 */
 
#ifndef SCREEN_WIDTH
#include "sdl2-light.h"
#include <time.h>

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 300


/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480


/**
 * \brief Taille d'un vaisseau
 */

#define SHIP_SIZE 32


/**
 * \brief Taille du missile
*/

#define MISSILE_SIZE 8


/**
 * \brief Vitesse de l'ennemi
*/

#define ENNEMY_SPEED 2


/**
 * \brief Vitesse du missile
*/

#define MISSILE_SPEED 10


/**
 * \brief Ecart entre chaque déplacement du vaisseau
*/

#define ECART_VAISSEAU 20


/**
 * \brief Nombre d'ennemis en jeu
*/

#define NB_ENEMIES 20


/**
 * \brief Nombre de boucles de jeu à faire avant de fermer la fenêtre de jeu (~2sec).
*/

#define NB_BOUCLES 200


/**
 * \brief Nombre de vaisseaux infectés.
*/

#define NB_INFECTED NB_ENEMIES/5


/**
 * \brief Points de vie initiaux du boss.
*/

#define PV_INITIAL_BOSS 20



/**
 * \brief Représentation d'un sprite du jeu
*/

struct sprite_s{
    int x;          /*!< Champ indiquant la position du centre du sprite (sur l'abscisse) */
    int y;          /*!< Champ indiquant la position du centre du sprite (sur l'ordonnée) */
    int h;          /*!< Champ indiquant la hauteur du sprite */
    int w;          /*!< Champ indiquant la largeur du sprite */
    int v;          /*!< Champ indiquant la vitesse verticale du sprite */
    int is_visible; /*!< Champ indiquant si le sprite est visible (0) ou invisible (1) */
};

/**
 * \brief Type qui correspond à un sprite du jeu
 */

typedef struct sprite_s sprite_t;



/**
 * \brief Données rajoutées après le niveau 3
*/

struct special_s{
    int bonus_vitesse;                      /*!< Champ représentant le bonus de vitesse (1 si non attrapé et 2 si attrapé) */
    sprite_t * sbv;                         /*!< Champ représentant le sprite du bonus de vitesse */
    sprite_t * nuke;                        /*!< Champ représentant le sprite du bonus nuke */
    sprite_t** infected;                    /*!< Champ représentant le sprite des vaisseaux contaminés */
    int compteur_malus;                     /*!< Champ représentant le nombre de vaisseaux infectés détruits par un missile */
    int PV;                                 /*!< Champ représentant le nombre de points de vie du joueur */
    int nb_boucles_explosion;               /*!< Champ représentant le nombre de boucles faites pendant une explosion */ 
    int nb_boucles_explosion_infected;      /*!< Champ représentant le nombre de boucles faites pendant une explosion de vaisseau infecté */ 
    sprite_t * boss;                        /*!< Champ représentant le sprite du boss */
    int combat_boss_en_cours;               /*!< Champ représentant le fait que le combat de boss soit en cours ou non (0 si oui et 1 si non) */
    int BOSS_PV;                            /*!< Champ représentant le nombre de points de vie du boss */
    int compteur_boss;                      /*!< Champ représentant un nombre qui permet de ne faire apparaître le boss qu'une seule fois */
    sprite_t * portal;                      /*!< Champ représentant le sprite du portail */
    int background;                         /*!< Champ représentant le fond utilisé (1 ou 2) */
    sprite_t * boss_missile;                /*!< Champ représentant le missile du boss  */
    int nb_boucles_boss_explosion;          /*!< Champ représentant le nombre de boucles faites pendant l'explosion du boss */ 
    int nb_boucles_boss_missile_explosion;  /*!< Champ représentant le nombre de boucles faites pendant une explosion d'un missile du boss */ 
};

/**
 * \brief Type qui correspond aux données rajoutées après le niveau 3
 */

typedef struct special_s special_t;




/**
 * \brief Représentation du monde du jeu
*/

struct world_s{
    sprite_t * vaisseau;    /*!< Champ représentant le vaisseau du joueur */
    //sprite_t * ennemi;    /*!< Champ représentant l'ennemi */
    sprite_t * missile;     /*!< Champ représentant le missile */
    int gameover;           /*!< Champ indiquant si l'on est à la fin du jeu */
    sprite_t** enemies;     /*!< Champ représentant les ennemis en jeu */
    int compteur_bas;       /*!< Champ représentant les ennemis qui ont réussi à passer en bas */
    int score;              /*!< Champ représentant le score du joueur */
    int etat_jeu;           /*!< Champ représentant l'état de la partie en cours (1 = J perdu / 2 = E tous détruits / 3 = E pas tous détruits / 4 = partie pas finie) */
    int boucles_faites;     /*!< Champ représentant le nombre de boucles du jeu faites alors que la partie est terminée */
    special_t * special;    /*!< Champ représentant les données nécessaires aux pouvoirs spéciaux */
};


/**
 * \brief Type qui correspond aux données du monde
 */

typedef struct world_s world_t;



/**
 * \brief La procédure initialise les données d'un sprite
 * \param sprite le sprite à initialiser
 * \param x la position du centre du sprite (sur l'abscisse)
 * \param y la position du centre du sprite (sur l'ordonnée)
 * \param h la hauteur du sprite
 * \param w la largueur du sprite
 * \param v la vitesse verticale du sprite
 */
void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v);


/**
 * \brief Fonction qui génère un nombre aléatoire.
 * \param a Borne inférieure.
 * \param b Borne supérieure.
 * \return Un nombre compris entre \a a (inclus) et \a b (non-inclus).
 */
int generate_number(int a, int b);


/**
 * \brief La procédure rends le sprite visible
 * \param sprite le sprite à modifier
 */
void set_visible(sprite_t *sprite);


/**
 * \brief La procédure rends le sprite invisible
 * \param sprite le sprite à modifier
 */
void set_invisible(sprite_t *sprite);


/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t *world);

#endif