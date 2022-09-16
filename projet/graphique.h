/**
 * \file graphique.h
 * \brief Programme déclarant les fonctions graphiques
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 30 avril 2020
 */
 
#ifndef apply_sprite
#include "database.h"
#include "sdl2-ttf-light.h"

/**
 * \brief Représentation pour stocker les ressources nécessaires à l'affichage graphique
*/

struct resources_s{
    SDL_Texture* background;            /*!< Texture liée à l'image du fond de l'écran. */
    SDL_Texture* vaisseau;              /*!< Texture liée à l'image du vaisseau. */
    SDL_Texture* ennemi;                /*!< Texture liée à l'image de l'ennemi. */
    SDL_Texture* missile;               /*!< Texture liée à l'image du missile. */
    TTF_Font* font;                     /*!< Police d'écriture. */
    SDL_Texture* sbv;                   /*!< Texture liée à l'image du bonus de vitesse. */
    SDL_Texture* nuke;                  /*!< Texture liée à l'image du bonus nuke */
    SDL_Texture* infected;              /*!< Texture liée à l'image des vaisseaux corrompus */
    SDL_Texture* explosion;             /*!< Texture liée à l'image de l'explosion des ennemis détruits */
    SDL_Texture* infected_explosion;    /*!< Texture liée à l'image de l'explosion des vaisseaux infectés detruits */
    SDL_Texture* boss;                  /*!< Texture liée à l'image du boss */
    SDL_Texture* boss_missile;          /*!< Texture liée à l'image du missile du boss */
    SDL_Texture* portal;                /*!< Texture liée à l'image du portail */
    SDL_Texture* infected_background;   /*!< Texture liée à l'image du fond de l'écran après être passé dans le portail */
    SDL_Texture* boss_explosion;        /*!< Texture liée à l'image de l'explosion du boss */
    SDL_Texture* boss_missile_explosion;/*!< Texture liée à l'image de l'explosion des missiles du boss */
    SDL_Texture* boss_rage_milieu;      /*!< Texture liée à l'image du boss enragé pour la première fois */
    SDL_Texture* boss_rage_fin;         /*!< Texture liée à l'image du boss enragé pour la deuxième fois */
};

/**
 * \brief Type qui correspond aux ressources du jeu
*/

typedef struct resources_s resources_t;



/**
 * \brief La procédure applique une texture sur le renderer à sa position
 * \param renderer Le renderer actuel
 * \param texture La texture à appliquer
 * \param sprite Le sprite dont on doit appliquer la texture
*/
void apply_sprite(SDL_Renderer * renderer, SDL_Texture * texture, sprite_t * sprite);


/**
 * \brief La fonction nettoie les ressources
 * \param resources les ressources
*/
void clean_resources(resources_t *resources);


/**
 * \brief La fonction initialise les texures
 * \param screen la surface correspondant à l'écran de jeu
 * \param resources les ressources du jeu
*/
void  init_resources(SDL_Renderer *renderer, resources_t *resources);


/**
 * \brief La fonction applique la texture du fond sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param resources les ressources du jeu
*/
void apply_background(SDL_Renderer *renderer, resources_t *resources);


/**
 * \brief La fonction applique la texture du fond (2) sur le renderer lié à l'écran de jeu
 * \param renderer le renderer
 * \param resources les ressources du jeu
*/
void apply_background_2(SDL_Renderer *renderer, resources_t *resources);


/**
 * \brief La fonction rafraichit l'écran en fonction de l'état des données du monde
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
 */
void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *resources);


/**
 * \brief Procédure qui applique les sprites des ennemis.
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
 */
void apply_enemies(SDL_Renderer *renderer, world_t *world,resources_t *resources);


/**
 * \brief Procédure qui applique les sprites des vaisseaux infectés.
 * \param renderer la surface de l'écran de jeu
 * \param world les données du monde
 * \param resources les ressources
 */
void apply_infected(SDL_Renderer *renderer, world_t *world,resources_t *resources);

#endif