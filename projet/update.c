/**
 * \file update.c
 * \brief Programme définissant les fonctions déclarées dans update.h
 * \author YVOZ Ludovic
 * \author IOPETI Hugo
 * \date 27 mai 2020
 */

#include "update.h"

void update_data(world_t *world){
    //world->ennemi->y += world->ennemi->v;   //Va vers le bas
    world->missile->y -= world->missile->v; //Va vers le haut
    //On rends le missile invisible si il sort de l'écran pour qu'il ne tue pas d'ennemis en dehors de celui-ci
    if (world->missile->y <= 0)
    {
        set_invisible(world->missile);
    }
    if (world->special->combat_boss_en_cours == 1)
    {
        world->special->sbv->y += world->special->sbv->v;
        world->special->nuke->y += world->special->nuke->v;
        update_enemies(world);
        update_infected(world);
    }
    else
    {
        //On gère la mort du boss et l'apparition du portail
        if (world->special->portal->is_visible == 0)
        {
            world->special->portal->y += world->special->portal->v;
        }

        //On gère la disparition du portail
        handle_portal_collision(world->special->portal, world->vaisseau);
        if (world->special->portal->v == 0) //Si le vaisseau est rentré dans le portail
        {
            world->special->combat_boss_en_cours = 1;
            world->special->background = 2;
            world->special->portal->v = 1;
        }

        //On gère les déplaçements et collisions du boss
        world->special->boss->x += world->special->boss->v;
        limite_boss(world);
        handle_boss_collision(world->special->boss, world->missile);
        if (world->special->boss->v == 0 && world->special->boss->is_visible == 0)
        {
            world->special->BOSS_PV -= 1;

            //On fait en sorte que le boss reparte dans une direction aléatoire quand il est touché
            int i = generate_number(0, 2); //On génère un nombre aléatoire : soit 0, soit 1.
            if (i == 0)
            {
                world->special->boss->v = ENNEMY_SPEED;
            }
            else
            {
                world->special->boss->v = - ENNEMY_SPEED;
            }
        }
        if (world->special->BOSS_PV == 0)
        {
            set_invisible(world->special->boss);
            world->special->boss->v = 0;
            if (world->special->background == 1)
            {
                set_visible(world->special->portal);
            }
        }
    }
    

    //On s'occupe du missile du boss
    if (world->special->boss->is_visible == 0)
    {
        if (world->special->boss_missile->is_visible == 1 && world->special->nb_boucles_boss_missile_explosion == 0)
        {
            world->special->boss_missile->x = world->special->boss->x;
            world->special->boss_missile->y = world->special->boss->y + (world->special->boss->h / 2) + (world->special->boss_missile->h / 2);
            set_visible(world->special->boss_missile);
            if (world->special->BOSS_PV <= 5)
            {
                world->special->boss_missile->v = ENNEMY_SPEED * 2;
            }
            else if (world->special->BOSS_PV <= 10)
            {
                world->special->boss_missile->v = ENNEMY_SPEED;
            }
            else
            {
                world->special->boss_missile->v = ENNEMY_SPEED / 2;
            }
        }
        world->special->boss_missile->y += world->special->boss_missile->v;
        handle_sprites_collision(world->special->boss_missile, world->missile);
        handle_sprites_collision(world->special->boss_missile, world->vaisseau);
        if (world->special->boss_missile->y - world->special->boss_missile->h / 2 > SCREEN_HEIGHT)
        {
            set_invisible(world->special->boss_missile);
        }
    }
    else
    {
        if (world->special->boss_missile->is_visible == 0) 
        {
            set_invisible(world->special->boss_missile);
        }
    }
    
    


    limite_gauche(world);
    limite_droite(world);
    limite_bas(world);

    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        handle_sprites_collision(world->vaisseau, world->enemies[i]);
        handle_sprites_collision(world->missile, world->enemies[i]);
    }

    if (world->vaisseau->v == 0)
    {
        world->special->PV -= 1;
        if (world->special->PV > 0)
        {
            set_visible(world->vaisseau);
        }
        world->vaisseau->v = 1; //On donne une valeur à la vitesse pour que les PV ne continuent pas à s'incrémenter après la mort du joueur et aussi pour que ça ne s'incrémente que quand le vaisseau percute un ennemi.
    }
    
    handle_bonus_collision(world->special->sbv, world->vaisseau);
    if (world->special->sbv->v == 0)    //On indique que le bonus à été rammassé
    {
        world->special->bonus_vitesse += ECART_VAISSEAU;
    }
    if (world->special->sbv->y + world->special->sbv->h/2 >= 0) //On ralenti le bonus quand il est dans l'écran
    {
        world->special->sbv->v = ENNEMY_SPEED / 2;
    }


    handle_bonus_collision(world->special->nuke, world->vaisseau);
    if (world->special->nuke->v == 0)
    {
        for (int i = 0; i < NB_ENEMIES; ++i)
        {
            if (world->enemies[i]->y > -(world->enemies[i]->h / 2) && world->enemies[i]->is_visible == 0)
            {
                set_invisible(world->enemies[i]);
                world->enemies[i]->v = 0;
            }
        }
    }
    if (world->special->nuke->y + world->special->nuke->h/2 >= 0) //On accélère le bonus quand il est dans l'écran
    {
        world->special->nuke->v = ENNEMY_SPEED * 2;
    }


    //Pour s'occuper des explosions, on utilise la vitesse des vaisseaux détruits comme variable normale (v = 0 si détruit par vaisseau, v = 2 si détruit par missile, v = 1 si les malus sont appliqués, v = 4 si l'explosion est finie)
    for (int i = 0; i < NB_INFECTED; ++i)
    {
        handle_infected_collision(world->special->infected[i], world->vaisseau);
        handle_infected_collision(world->special->infected[i], world->missile);
    }
    infected_destroyed(world);


    //On gère l'apparition du boss et les actions du boss (se déclenche quand le joueur à détruit la moitié des vaisseaux ennemis)
    if (world->special->combat_boss_en_cours == 1 && ennemis_detruits(world) >= NB_ENEMIES / 2 && world->special->compteur_boss == 0 && world->vaisseau->is_visible == 0)
    {
        //Tout d'abord on enlève tout ce qu'il y a sur le terrain

        //1 : les bonus
        if (world->special->sbv->is_visible == 0 && world->special->sbv->y - (world->special->sbv->h / 2) <= SCREEN_HEIGHT)
        {
            world->special->sbv->y -= SCREEN_HEIGHT + world->vaisseau->h;   //On ajoute world->vaisseau->h pour s'assurer que aucun vaisseau ne reste dans l'écran
        }
        if (world->special->nuke->is_visible == 0 && world->special->nuke->y - (world->special->nuke->h / 2) <= SCREEN_HEIGHT)
        {
            world->special->nuke->y -= SCREEN_HEIGHT + world->vaisseau->h;
        }

        //2 : les ennemis
        for (int i = 0; i < NB_ENEMIES; ++i)
        {
            if (world->enemies[i]->is_visible == 0 && world->enemies[i]->y - (world->enemies[i]->h / 2) <= SCREEN_HEIGHT)
            {
                world->enemies[i]->y -= SCREEN_HEIGHT + world->vaisseau->h;
            }
        }

        //3 : les infectés
        for (int i = 0; i < NB_INFECTED; ++i)
        {
            if (world->special->infected[i]->is_visible == 0 && world->special->infected[i]->y - (world->special->infected[i]->h / 2) <= SCREEN_HEIGHT)
            {
                world->special->infected[i]->y -= SCREEN_HEIGHT + world->vaisseau->h;
            }
        }

        //Ensuite on initialise le boss
        set_visible(world->special->boss);
        world->special->combat_boss_en_cours = 0;
        world->special->compteur_boss = 1;  //On dit que cette boucle ne se refera pas
    }


    compute_game(world);

    //printf("cpt : %d\n",world->compteur_bas);
    //handle_sprites_collision(world->vaisseau, world->ennemi);
    //handle_sprites_collision(world->ennemi, world->missile);
}


void limite_gauche(world_t *world)
{
    if (world->vaisseau->x - world->vaisseau->w/2 < 0)
    {
        world->vaisseau->x = world->vaisseau->w/2;
    }
}


void limite_droite(world_t *world)
{
    if (world->vaisseau->x + world->vaisseau->w/2 > SCREEN_WIDTH)
    {
        world->vaisseau->x = SCREEN_WIDTH - world->vaisseau->w/2;
    }
}


void limite_bas(world_t *world)
{
    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        if (world->enemies[i]->is_visible == 0 && world->enemies[i]->y - world->enemies[i]->h/2 > SCREEN_HEIGHT)    //Si le vaisseau sors de l'écran en bas et qu'il est visible, on rajoute 1 au compteur et on le rends invisible
        {
            world->compteur_bas += 1;
            set_invisible(world->enemies[i]);
        }
    }
}


int sprites_collide(sprite_t *sp2, sprite_t *sp1)
{
    if (sqrt(pow((sp1->x - sp2->x), 2) + pow((sp1->y - sp2->y), 2)) <= (sp1->h + sp2->h)/2)
    {
        return 1;
    }
    return 0;
}


void handle_sprites_collision(sprite_t *sp2, sprite_t *sp1)
{
    if (sprites_collide(sp1, sp2) == 1 && sp1->is_visible == 0 && sp2->is_visible == 0)
    {
        set_invisible(sp1);
        set_invisible(sp2);
        sp1->v = 0;
        sp2->v = 0;
    }
}


void handle_bonus_collision(sprite_t *bonus, sprite_t *sp)
{
    if (sprites_collide(sp, bonus) == 1 && sp->is_visible == 0 && bonus->is_visible == 0)
    {
        set_invisible(bonus);
        bonus->v = 0;
    }
}


void handle_infected_collision(sprite_t *infect, sprite_t *sp)
{
    if (sprites_collide(sp, infect) == 1 && sp->is_visible == 0 && infect->is_visible == 0)
    {
        if (sp->h == MISSILE_SIZE)  //Si la collision est contre un missile
        {
            set_invisible(sp);
            sp->v = 0;
            set_invisible(infect);
            infect->v = 2;
        }
        else                        //Si la collision est contre le vaisseau du joueur
        {
            set_invisible(infect);
            infect->v = 0;
        }
    }
}


void handle_boss_collision(sprite_t* boss, sprite_t* sp)
{
    if (sprites_collide(boss, sp) == 1 && sp->is_visible == 0 && boss->is_visible == 0)
    {
        set_invisible(sp);
        sp->v = 0;
        boss->v = 0;    //On annule la vitesse du boss pour pouvoir savoir si il à été touché plus tard
    }
}


void handle_portal_collision(sprite_t *portail, sprite_t *sp)
{
    if (sprites_collide(portail, sp) == 1 && sp->is_visible == 0 && portail->is_visible == 0)
    {
        set_invisible(portail);
        portail->v = 0;
    }
}


void infected_destroyed(world_t* world)
{
    for (int i = 0; i < NB_INFECTED; ++i)
    {
        if (world->special->infected[i]->is_visible == 1 && world->special->infected[i]->v == 0)    //à touché le vaisseau du joueur
        {
            world->special->bonus_vitesse -= 4;
            world->special->infected[i]->v = 1;
        }
        else if (world->special->infected[i]->is_visible == 1 && world->special->infected[i]->v == 2)
        {
            world->special->compteur_malus += 1;
            world->special->infected[i]->v = 1;
        }
    }
}


void limite_boss(world_t* world)
{
    if (world->special->boss->x + world->special->boss->w / 2 >= SCREEN_WIDTH  ||  world->special->boss->x - world->special->boss->w / 2 <= 0)
    {
        world->special->boss->v = -world->special->boss->v;
    }
}


void print_sprite(sprite_t * sprite)
{
    printf("x = %d\ny = %d\nh = %d\nw = %d\nv = %d\n",
        sprite->x,sprite->y,sprite->h,sprite->w,sprite->v);
}


void update_enemies(world_t* world)
{
    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        world->enemies[i]->y += world->enemies[i]->v;
    }
}


void update_infected(world_t* world)
{
    for (int i = 0; i < NB_INFECTED; ++i)
    {
        if (world->special->infected[i]->is_visible == 0)
        {
            world->special->infected[i]->y += world->special->infected[i]->v;
        }
    }
}


void compute_game(world_t *world)
{
    //Gestion de l'état du jeu
    if (world->vaisseau->is_visible == 1)   //cas vaisseau joueur détruit
    {
        world->etat_jeu = 1;
    }
    else if (world->vaisseau->is_visible == 0 && ennemis_invisibles(world) == 0 && world->compteur_bas == 0) //cas tous les ennemis détruits
    {
        world->etat_jeu = 2;
    }
    else if (world->vaisseau->is_visible == 0 && ennemis_invisibles(world) == 0 && world->compteur_bas > 0) //cas pas tous les ennemis détruits
    {
        world->etat_jeu = 3;
    }
    else if(world->special->portal->y - world->special->portal->h / 2 > SCREEN_HEIGHT && world->special->portal->is_visible == 0)
    {
        world->etat_jeu = 3;
    }
    else
    {
        world->etat_jeu = 4;
    }
    printf("état partie = %d\n",world->etat_jeu);
    
    //Gestion du score
    if (world->etat_jeu == 1)
    {
        world->score = 0;
    }
    else if (world->etat_jeu == 2)
    {
        world->score = (ennemis_detruits(world) - world->special->compteur_malus) * 2; //On mets à jour le score avant de le doubler pour ne pas oublier de points.
    }
    else
    {
        world->score = ennemis_detruits(world) - world->special->compteur_malus;
    }
    printf("Score = %d\n",world->score);

    //On gère quand on ferme la fenêtre
    if (world->boucles_faites >= NB_BOUCLES)
    {
        world->gameover = 1;
    }
}


int ennemis_invisibles(world_t* world)
{
    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        if (world->enemies[i]->is_visible == 0)
        {
            return 1;
        }
    }
    return 0;
}


int ennemis_detruits(world_t* world)
{
    int a = 0;
    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        if (world->enemies[i]->is_visible == 1)
        {
            a += 1;
        }
    }
    return a - world->compteur_bas;
}