/**
 * \file one_use.c
 * \brief Programme définissant les fonctions déclarées dans one_use.h
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 27 mai 2020
 */

#include "one_use.h"

 
void init_data(world_t * world){
    srand(time(NULL));
    world->vaisseau = malloc(sizeof(sprite_t));
    //world->ennemi = malloc(sizeof(sprite_t));
    world->missile = malloc(sizeof(sprite_t));
    world->special = malloc(sizeof(special_t));
    world->special->sbv = malloc(sizeof(sprite_t));
    world->special->nuke = malloc(sizeof(sprite_t));
    world->special->boss = malloc(sizeof(sprite_t));
    world->special->portal = malloc(sizeof(sprite_t));
    world->special->boss_missile = malloc(sizeof(sprite_t));

    init_sprite(world->vaisseau, SCREEN_WIDTH / 2, SCREEN_HEIGHT - SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, 1);
    //init_sprite(world->ennemi, SCREEN_WIDTH / 2, SHIP_SIZE, SHIP_SIZE, SHIP_SIZE, ENNEMY_SPEED);
    init_sprite(world->missile, SCREEN_WIDTH / 2, SCREEN_HEIGHT - (1.5 * SHIP_SIZE) - (MISSILE_SIZE / 2), MISSILE_SIZE, MISSILE_SIZE, MISSILE_SPEED);   //La position y du missile équivaut à la positio y du vaisseau - 1/2vaisseau-1/2missile (il est juste au-dessus).
    set_invisible(world->missile);
    init_enemies(world);
    init_sprite(world->special->sbv, generate_number(BV_WIDTH / 2, SCREEN_WIDTH - (BV_WIDTH / 2)), generate_number(world->enemies[NB_ENEMIES - 1]->y, -(BV_HEIGHT / 2)), BV_WIDTH, BV_HEIGHT, ENNEMY_SPEED);
    init_sprite(world->special->nuke, generate_number(NUKE_WIDTH / 2, SCREEN_WIDTH - (NUKE_WIDTH / 2)), generate_number(world->enemies[NB_ENEMIES - 1]->y, -(NUKE_HEIGHT / 2)), NUKE_WIDTH, NUKE_HEIGHT, ENNEMY_SPEED);
    init_infected(world);
    init_sprite(world->special->boss, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, BOSS_WIDTH, BOSS_HEIGHT, ENNEMY_SPEED);
    set_invisible(world->special->boss);
    init_sprite(world->special->portal, SCREEN_WIDTH / 2, PORTAL_HEIGHT, PORTAL_WIDTH, PORTAL_HEIGHT, ENNEMY_SPEED);
    set_invisible(world->special->portal);
    init_sprite(world->special->boss_missile, world->special->boss->x, world->special->boss->y + (world->special->boss->h / 2) + (BOSS_MISSILE_HEIGHT / 2), BOSS_MISSILE_WIDTH, BOSS_MISSILE_HEIGHT, ENNEMY_SPEED / 2);
    set_invisible(world->special->boss_missile);

    
    //test
    //print_sprite(world->vaisseau);
    //print_sprite(world->ennemi);
    //print_sprite(world->missile);
    //on n'est pas à la fin du jeu

    world->gameover = 0;
    world->score = 0;
    world->boucles_faites = 0;
    world->compteur_bas = 0;
    world->special->bonus_vitesse = 0;
    world->special->compteur_malus = 0;
    world->special->PV = PV_INITIAL;
    world->special->nb_boucles_explosion = 0;
    world->special->nb_boucles_explosion_infected = 0;
    world->special->combat_boss_en_cours = 1;
    world->special->BOSS_PV = PV_INITIAL_BOSS;
    world->special->compteur_boss = 0;
    world->special->background = 1;
    world->special->nb_boucles_boss_explosion = 0;
    world->special->nb_boucles_boss_missile_explosion = 0;
}


void clean_data(world_t *world){
    /* utile uniquement si vous avez fait de l'allocation dynamique (malloc); la fonction ici doit permettre de libérer la mémoire (free) */
    free(world->vaisseau);
    free(world->missile);
    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        free(world->enemies[i]);
    }
    free(world->enemies);
    free(world->special->sbv);
    free(world->special->nuke);
    for (int i = 0; i < NB_INFECTED; ++i)
    {
        free(world->special->infected[i]);
    }
    free(world->special->infected);
    free(world->special->boss);
    free(world->special->portal);
    free(world->special->boss_missile);
    free(world->special);
}


void init_enemies(world_t* world)
{  
    world->enemies = malloc(sizeof(sprite_t*)*NB_ENEMIES);
    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        world->enemies[i] = malloc(sizeof(sprite_t));
        init_sprite(world->enemies[i], generate_number(SHIP_SIZE/2,SCREEN_WIDTH-SHIP_SIZE/2), -(SHIP_SIZE/2) -(VERTICAL_DIST * i), SHIP_SIZE, SHIP_SIZE, ENNEMY_SPEED);
    }
}


void init_infected(world_t* world)
{  
    world->special->infected = malloc(sizeof(sprite_t*)*NB_INFECTED);
    for (int i = 0; i < NB_INFECTED; ++i)
    {
        world->special->infected[i] = malloc(sizeof(sprite_t));
        init_sprite(world->special->infected[i], generate_number(SHIP_SIZE / 2, SCREEN_WIDTH - (SHIP_SIZE / 2)), generate_number(world->enemies[NB_ENEMIES - 1]->y, -(SHIP_SIZE / 2)), SHIP_SIZE, SHIP_SIZE, ENNEMY_SPEED);
    }
}