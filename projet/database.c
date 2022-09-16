/**
 * \file database.c
 * \brief Programme definissant les fonctions déclarées dans database.h
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 23 mai 2020
 */
 
#include "database.h"


void init_sprite(sprite_t *sprite, int x, int y, int w, int h, int v)
{
    sprite->x = x;
    sprite->y = y;
    sprite->h = h;
    sprite->w = w;
    sprite->v = v;
    sprite->is_visible = 0;
}


int generate_number(int a, int b)
{
    return rand()%(b-a)+a;
}


void set_visible(sprite_t *sprite)
{
    sprite->is_visible = 0;
}


void set_invisible(sprite_t *sprite)
{
    sprite->is_visible = 1;
}


int is_game_over(world_t *world){
    return world->gameover;
}