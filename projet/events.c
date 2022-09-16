/**
 * \file events.c
 * \brief Programme définissant les fonctions déclarées dans events.h
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 27 mai 2020
 */
 
#include "events.h"


void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    while( SDL_PollEvent( event ) ) {
        
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if (event->type == SDL_QUIT ) {
            //On indique la fin du jeu
            world->gameover = 1;
        }
       
         //si une touche est appuyée
         if(event->type == SDL_KEYDOWN){
            //si la touche appuyée est la flèche de droite
            if (event->key.keysym.sym == SDLK_RIGHT)
            {
                world->vaisseau->x += ECART_VAISSEAU + world->special->bonus_vitesse;
            }
            //si la touche appuyée est la flèche de gauche
            if (event->key.keysym.sym == SDLK_LEFT)
            {
                world->vaisseau->x -= ECART_VAISSEAU + world->special->bonus_vitesse;
            }
            //si la touche appuyée est espace
            if (event->key.keysym.sym == SDLK_SPACE && world->vaisseau->is_visible == 0)    //Si on appuie sur espace ET que le vaisseau est visible, on tire.
            {
                init_sprite(world->missile, world->vaisseau->x, world->vaisseau->y - (SHIP_SIZE / 2) - (MISSILE_SIZE / 2), world->missile->w, world->missile->h, MISSILE_SPEED);
            }
            //si le touche appuyée est echap
            if (event->key.keysym.sym == SDLK_ESCAPE)
            {
                world->gameover = 1;
            }
        }
    }
}