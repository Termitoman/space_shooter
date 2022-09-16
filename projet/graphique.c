/**
 * \file graphique.c
 * \brief Programme définissant les fonctions déclarées dans graphique.h
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 30 avril 2020
 */
 
#include "graphique.h"


void apply_sprite(SDL_Renderer * renderer, SDL_Texture * texture, sprite_t * sprite)
{
    if (sprite->is_visible == 0)
    {
        apply_texture(texture, renderer, sprite->x - (sprite->h/2), sprite->y - (sprite->w/2)); //On donne les coordonnées du coin en haut à gauche du sprite à partir du centre du sprite
    }
}


void clean_resources(resources_t *resources){
    clean_texture(resources->background);
    clean_texture(resources->vaisseau);
    clean_texture(resources->ennemi);
    clean_texture(resources->missile);
    clean_font(resources->font);
    clean_texture(resources->sbv);
    clean_texture(resources->nuke);
    clean_texture(resources->infected);
    clean_texture(resources->explosion);
    clean_texture(resources->infected_explosion);
    clean_texture(resources->boss);
    clean_texture(resources->boss_missile);
    clean_texture(resources->portal);
    clean_texture(resources->infected_background);
    clean_texture(resources->boss_explosion);
    clean_texture(resources->boss_missile_explosion);
    clean_texture(resources->boss_rage_milieu);
    clean_texture(resources->boss_rage_fin);
}


void  init_resources(SDL_Renderer *renderer, resources_t *resources){
    resources->background = load_image( "ressources/space-background.bmp",renderer);
    resources->vaisseau = load_image("ressources/spaceship2.bmp", renderer);
    resources->ennemi = load_image("ressources/ennemy2.bmp", renderer);
    resources->missile = load_image("ressources/missile2.bmp", renderer);
    resources->font = load_font("ressources/arial.ttf",14);
    resources->sbv = load_image("ressources/bv.bmp", renderer);
    resources->nuke = load_image("ressources/nuke.bmp", renderer);
    resources->infected = load_image("ressources/infected.bmp", renderer);
    resources->explosion = load_image("ressources/explosion.bmp", renderer);
    resources->infected_explosion = load_image("ressources/infected_explosion.bmp", renderer);
    resources->boss = load_image("ressources/boss.bmp", renderer);
    resources->boss_rage_milieu = load_image("ressources/boss_rage_milieu.bmp", renderer);
    resources->boss_rage_fin = load_image("ressources/boss_rage_fin.bmp", renderer);
    resources->boss_missile = load_image("ressources/boss_missile.bmp", renderer);
    resources->portal = load_image("ressources/portal.bmp", renderer);
    resources->infected_background = load_image("ressources/infected_background.bmp", renderer);
    resources->boss_explosion = load_image("ressources/boss_explosion.bmp", renderer);
    resources->boss_missile_explosion = load_image("ressources/boss_missile_explosion.bmp", renderer);
}


void apply_background(SDL_Renderer *renderer, resources_t *resources){
    if(resources->background != NULL){
      apply_texture(resources->background, renderer, 0, 0);
    }
}


void apply_background_2(SDL_Renderer *renderer, resources_t *resources){
    if(resources->background != NULL){
      apply_texture(resources->infected_background, renderer, 0, 0);
    }
}


void refresh_graphics(SDL_Renderer *renderer, world_t *world,resources_t *resources){
    
    //on vide le renderer
    clear_renderer(renderer);
    
    //application des ressources dans le renderer
    if (world->special->background == 1)
    {
        apply_background(renderer, resources);
    }
    else if (world->special->background == 2)
    {
        apply_background_2(renderer, resources);
    }
    
    apply_sprite(renderer, resources->vaisseau, world->vaisseau);
    //apply_sprite(renderer, resources->ennemi, world->ennemi);
    apply_sprite(renderer, resources->missile, world->missile);
    apply_enemies(renderer, world, resources);
    apply_sprite(renderer, resources->sbv, world->special->sbv);
    apply_sprite(renderer, resources->nuke, world->special->nuke);
    apply_infected(renderer, world, resources);
    apply_sprite(renderer, resources->portal, world->special->portal);
    apply_sprite(renderer, resources->boss_missile, world->special->boss_missile);

    //On s'occupe du boss
    if (world->special->BOSS_PV <= PV_INITIAL_BOSS / 4 && world->special->BOSS_PV > 0)
    {
        apply_sprite(renderer, resources->boss_rage_fin, world->special->boss);
        apply_text(renderer,SCREEN_WIDTH/2 - 100,(SCREEN_HEIGHT / 4) + 15,200,100,"YOU'RE DEAD !!!",resources->font);
    }
    else if (world->special->BOSS_PV <= PV_INITIAL_BOSS / 2 && world->special->BOSS_PV > 0)
    {
        apply_sprite(renderer, resources->boss_rage_milieu, world->special->boss);
        apply_text(renderer,SCREEN_WIDTH/2 - 75,(SCREEN_HEIGHT / 4) + 15,150,100,"I'M ANGRY !",resources->font);
    }
    else
    {
        apply_sprite(renderer, resources->boss, world->special->boss);
    }
    


    //On applique l'explosion
    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        if (world->enemies[i]->v == 0)
        {
            set_visible(world->enemies[i]);
            apply_sprite(renderer, resources->explosion, world->enemies[i]);
            set_invisible(world->enemies[i]);
            world->special->nb_boucles_explosion += 1;
        }
        if (world->special->nb_boucles_explosion >= NB_BOUCLES / 8) //Temps d'une explosion approximatif (après des tests)
        {
            world->enemies[i]->v = 1;
            world->special->nb_boucles_explosion = 0;
        }
    }


    //On applique l'explosion des infectés
    for (int i = 0; i < NB_INFECTED; ++i)
    {
        if (world->special->infected[i]->is_visible == 1 && world->special->infected[i]->v == 1)
        {
            set_visible(world->special->infected[i]);
            apply_sprite(renderer, resources->infected_explosion, world->special->infected[i]);
            set_invisible(world->special->infected[i]);
            world->special->nb_boucles_explosion_infected += 1;
        }
        if (world->special->nb_boucles_explosion_infected >= NB_BOUCLES / 8) //Temps d'une explosion approximatif (après des tests)
        {
           world->special->nb_boucles_explosion_infected = 0;
           world->special->infected[i]->v = 4;
        }
    }


    //On applique l'explosion du boss
    if (world->special->boss->v == 0 && world->special->nb_boucles_boss_explosion >= 0)
    {
        set_visible(world->special->boss);
        apply_sprite(renderer, resources->boss_explosion, world->special->boss);
        set_invisible(world->special->boss);
        world->special->nb_boucles_boss_explosion += 1;
    }
    if (world->special->nb_boucles_boss_explosion >= NB_BOUCLES / 8) //Temps d'une explosion approximatif (après des tests)
    {
        world->special->boss->v = 1;
        world->special->nb_boucles_boss_explosion = -1;
    }

    //On applique l'explosion des missiles du boss
    if (world->special->boss_missile->v == 0)
    {
        set_visible(world->special->boss_missile);
        apply_sprite(renderer, resources->boss_missile_explosion, world->special->boss_missile);
        set_invisible(world->special->boss_missile);
        world->special->nb_boucles_boss_missile_explosion += 1;
    }
    if (world->special->nb_boucles_boss_missile_explosion >= NB_BOUCLES / 8) //Temps d'une explosion approximatif (après des tests)
    {
        world->special->boss_missile->v = 1;
        world->special->nb_boucles_boss_missile_explosion = 0;
    }


    //On affiche le score
    char* str = malloc(sizeof(char) * 20);          //On met 20 pour prévenir un bug sur certaines machines (buffer overflow)
    sprintf(str,"Score : %d",world->score);         //On utilise juste sprintf pour convertir notre score en chaine de caractères
    apply_text(renderer,0,30,100,30,str,resources->font);
    free(str);

    //On affiche les points de vie
    char* str2 = malloc(sizeof(char) * 20);         //On met 20 pour prévenir un bug sur certaines machines (buffer overflow)
    sprintf(str2,"PV : %d",world->special->PV);     //On utilise juste sprintf pour convertir notre score en chaine de caractères
    apply_text(renderer,0,0,100,30,str2,resources->font);
    free(str2);

    //On affiche le message de fin de jeu selon l'état de la partie
    switch (world->etat_jeu)
    {
        case (1) :
        {
            apply_sprite(renderer, resources->explosion, world->vaisseau);
            apply_text(renderer,SCREEN_WIDTH/2 - 100,SCREEN_HEIGHT/2 - 50,200,100,"GAME OVER",resources->font);
            break;
        }
        case (2) :
        {
            apply_text(renderer,SCREEN_WIDTH/2 - 100,SCREEN_HEIGHT/2 - 50,200,100,"HIGH SCORE",resources->font);
            break;
        }
        case (3) :
        {
            apply_text(renderer,SCREEN_WIDTH/2 - 100,SCREEN_HEIGHT/2 - 50,200,100,"YOU WIN",resources->font);
            break;
        }
    }

    //On affiche un message quand on à le bonus de vitesse
    if (world->special->bonus_vitesse > 0)
    {
        apply_text(renderer, SCREEN_WIDTH - 150, 0, 150, 30 , "SPEED BONUS ON !", resources->font);
    }

    //On affiche un message quand on a le malus de vitesse
    if (world->special->bonus_vitesse < 0)
    {
        apply_text(renderer, SCREEN_WIDTH - 150, 0, 150, 30 , "YOU'RE INFECTED !", resources->font);
    }


    //On affiche les points de vie du boss
    if (world->special->combat_boss_en_cours == 0 && world->special->portal->is_visible == 1)
    {
        char* str3 = malloc(sizeof(char) * 20);                       //On met 20 pour prévenir un bug sur certaines machines (buffer overflow)
        sprintf(str3,"PV : %d",world->special->BOSS_PV);              //On utilise juste sprintf pour convertir notre score en chaine de caractères
        apply_text(renderer,(SCREEN_WIDTH / 2) - 50,(SCREEN_HEIGHT / 4) - 15,100,30,str3,resources->font);
        free(str3);
    }

    
    // on met à jour l'écran
    update_screen(renderer);
}


void apply_enemies(SDL_Renderer *renderer, world_t *world,resources_t *resources)
{
    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        apply_sprite(renderer, resources->ennemi, world->enemies[i]);
    }
}


void apply_infected(SDL_Renderer *renderer, world_t *world,resources_t *resources)
{
    for (int i = 0; i < NB_INFECTED; ++i)
    {
        apply_sprite(renderer, resources->infected, world->special->infected[i]);
    }
}