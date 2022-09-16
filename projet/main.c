/**
 * \file main.c
 * \brief Programme principal du jeu
 * \author Mathieu Constant
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 18 mars 2020
 */
 
#include "database.h"
#include "graphique.h"
#include "events.h"
#include "one_use.h"
#include "update.h"


/**
* \brief fonction qui nettoie le jeu: nettoyage de la partie graphique (SDL), nettoyage des ressources, nettoyage des données
* \param window la fenêtre du jeu
* \param renderer le renderer
* \param resources les ressources
* \param world le monde
*/
void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *resources, world_t * world);


/**
 * \brief fonction qui initialise le jeu: initialisation de la partie graphique (SDL), chargement des ressources, initialisation des données
 * \param window la fenêtre du jeu
 * \param renderer le renderer
 * \param resources les ressources
 * \param wordl le monde
 */
void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *resources, world_t * world);


/**
 *  \brief programme principal qui implémente la boucle du jeu
 */
int main(int argc, char* args[]);


void clean(SDL_Window *window, SDL_Renderer * renderer, resources_t *resources, world_t * world){
    clean_data(world);
    clean_resources(resources);
    clean_sdl(renderer,window);
}


void init(SDL_Window **window, SDL_Renderer ** renderer, resources_t *resources, world_t * world){
    init_sdl(window,renderer,SCREEN_WIDTH, SCREEN_HEIGHT);
    init_ttf();
    init_data(world);
    init_resources(*renderer,resources);
}


int main(int argc, char* args[])
{
    SDL_Event event;
    world_t world;
    resources_t resources;
    SDL_Renderer *renderer;
    SDL_Window *window;

    //initialisation du jeu
    init(&window,&renderer,&resources,&world);
    printf("gameover = %d\n", world.gameover);
    while(!is_game_over(&world)){ //tant que le jeu n'est pas fini
        
        //gestion des évènements
        handle_events(&event,&world);
        //print_sprite(world.vaisseau);
        //mise à jour des données liée à la physique du monde
        update_data(&world);
        
        //rafraichissement de l'écran
        refresh_graphics(renderer,&world,&resources);
        
        // pause de 10 ms pour controler la vitesse de rafraichissement
        pause(10);

        //On incrémente le nombre de boucles faites si on est à la fin du jeu
        if (world.etat_jeu != 4)
        {
            world.boucles_faites += 1;
        }
    }

    //nettoyage final
    clean(window,renderer,&resources,&world);

    return 0;
}
