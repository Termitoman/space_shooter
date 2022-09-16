/**
 * \file tests.c
 * \brief Programme de tests
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 8 avril 2020
 */
 
#include "database.h"
#include "one_use.h"
#include "events.h"
#include "update.h"


/**
 * \brief Procédure qui teste l'initialisation et l'affichage d'un sprite
 * \param sprite le sprite à initialiser et à afficher
 * \param x la position du centre du sprite (sur l'abscisse)
 * \param y la position du centre du sprite (sur l'ordonnée)
 * \param h la hauteur du sprite
 * \param w la largueur du sprite
 * \param v la vitesse verticale du sprite
 */
void sprite_test_param(sprite_t *sprite, int x, int y, int w, int h, int v)
{
    init_sprite(sprite, x, y, w, h, v);
    print_sprite(sprite);
}

/**
 * \brief Procédure qui créée des sprite à tester
 */
void sprite_test()
{
    sprite_t* sprite = malloc(sizeof(sprite_t));

    sprite_test_param(sprite, 10, 10, 22, 22, 69);
    sprite_test_param(sprite, 420, 420, 420, 420, 420);
}

/*Voici le résultat du test
x = 10
y = 10
h = 22
w = 22
v = 69
x = 420
y = 420
h = 420
w = 420
v = 420
*/

/**
 * \brief Procédure qui teste la fonction limite_gauche
 * \param world données du monde
 */
void limite_gauche_test_param(world_t *world)
{
    print_sprite(world->vaisseau);
    limite_gauche(world);
    print_sprite(world->vaisseau);
}

/**
 * \brief Procédure qui teste la fonction limite_gauche
 */
void limite_gauche_test()
{
    world_t* world = malloc(sizeof(world_t));
    world->vaisseau = malloc(sizeof(sprite_t));

    world->vaisseau->x = 0;
    world->vaisseau->y = 0;
    world->vaisseau->w = SHIP_SIZE;
    world->vaisseau->h = SHIP_SIZE;
    world->vaisseau->v = 0;
    limite_gauche_test_param(world);

    world->vaisseau->x = -69;
    limite_gauche_test_param(world);

    world->vaisseau->x = SCREEN_WIDTH + 10;
    limite_gauche_test_param(world);
}

/*Voici le résultat du test
x = 0
y = 0
h = 32
w = 32
v = 0
x = 16
y = 0
h = 32
w = 32
v = 0
x = -69
y = 0
h = 32
w = 32
v = 0
x = 16
y = 0
h = 32
w = 32
v = 0
x = 310
y = 0
h = 32
w = 32
v = 0
x = 310
y = 0
h = 32
w = 32
v = 0
*/


/**
 * \brief Procédure qui teste la fonction limite_droite
 * \param world données du monde
 */
void limite_droite_test_param(world_t *world)
{
    print_sprite(world->vaisseau);
    limite_droite(world);
    print_sprite(world->vaisseau);
}

/**
 * \brief Procédure qui teste la fonction limite_droite
 */
void limite_droite_test()
{
    world_t* world = malloc(sizeof(world_t));
    world->vaisseau = malloc(sizeof(sprite_t));

    world->vaisseau->x = 0;
    world->vaisseau->y = 0;
    world->vaisseau->w = SHIP_SIZE;
    world->vaisseau->h = SHIP_SIZE;
    world->vaisseau->v = 0;
    limite_droite_test_param(world);

    world->vaisseau->x = -69;
    limite_droite_test_param(world);

    world->vaisseau->x = SCREEN_WIDTH + 10;
    limite_droite_test_param(world);
}

/*Voici le résultat du test
x = 0
y = 0
h = 32
w = 32
v = 0
x = 0
y = 0
h = 32
w = 32
v = 0
x = -69
y = 0
h = 32
w = 32
v = 0
x = -69
y = 0
h = 32
w = 32
v = 0
x = 310
y = 0
h = 32
w = 32
v = 0
x = 284
y = 0
h = 32
w = 32
v = 0
*/


/**
 * \brief Procédure qui teste la fonction limite_bas
 * \param world données du monde
 */
void limite_bas_test_param(world_t *world)
{
    //print_sprite(world->ennemi);
    //limite_bas(world);
    //print_sprite(world->ennemi);
}

/**
 * \brief Procédure qui teste la fonction limite_bas
 */
void limite_bas_test()
{
    //world_t* world = malloc(sizeof(world_t));
    //world->ennemi = malloc(sizeof(sprite_t));

    //world->ennemi->x = 0;
    //world->ennemi->y = 0;
    //world->ennemi->w = SHIP_SIZE;
    //world->ennemi->h = SHIP_SIZE;
    //world->ennemi->v = 0;
    //limite_bas_test_param(world);

    //world->ennemi->y = 20;
    //limite_bas_test_param(world);

    //world->ennemi->y = SCREEN_HEIGHT + SHIP_SIZE;
    //limite_bas_test_param(world);
}

/*Voici le résultat du test
x = 0
y = 0
h = 32
w = 32
v = 0
x = 0
y = 0
h = 32
w = 32
v = 0
x = 0
y = 20
h = 32
w = 32
v = 0
x = 0
y = 20
h = 32
w = 32
v = 0
x = 0
y = 512
h = 32
w = 32
v = 0
x = 0
y = 16
h = 32
w = 32
v = 0
*/


/**
 * \brief Procédure qui teste la fonction sprites_collide
 * \param sp1 sprite n°1
 * \param sp2 sprite n°2
 */
int sprites_collide_test_param(sprite_t *sp2, sprite_t *sp1)
{
    int test = sprites_collide(sp1, sp2);
    if (test == 1)
    {
        printf("Les deux sprites sont en collision !\n");
    }
    else
    {
        printf("Les deux sprites ne sont pas en collision !\n");
    }
    
}

/**
 * \brief Procédure qui teste la fonction sprites_collide
 */
int sprites_collide_test()
{
    sprite_t* sp1 = malloc(sizeof(sprite_t));
    sprite_t* sp2 = malloc(sizeof(sprite_t));
    sp1->h = SHIP_SIZE;
    sp2->h = SHIP_SIZE;

    //Test alors qu'ils ne sont pas en collision
    sp1->x = 0;
    sp1->y = 0;
    sp2->x = SHIP_SIZE + 6;
    sp2->y = SHIP_SIZE + 9;
    sprites_collide_test_param(sp1, sp2);

    //Test alors qu'ils sont en collision
    sp2->x = 0;
    sp2->y = 0;
    sprites_collide_test_param(sp1, sp2);
}

/*Résultat du test :
Les deux sprites ne sont pas en collision !
Les deux sprites sont en collision !
*/


/**
 * \brief Procédure qui teste la fonction handle_sprites_collision.
 * \param sp1 sprite n°1
 * \param sp2 sprite n°2
 */
void handle_sprites_collision_test_param(sprite_t *sp2, sprite_t *sp1)
{
    handle_sprites_collision(sp1, sp2);
    printf("La vitesse du sprite 1 est : %d\nLa vitesse du sprite 2 est : %d\n",
        sp1->v, sp2->v);
}

/**
 * \brief Procédure qui teste la fonction handle_sprites_collision.
 */
void handle_sprites_collision_test()
{
    sprite_t* sp1 = malloc(sizeof(sprite_t));
    sprite_t* sp2 = malloc(sizeof(sprite_t));
    sp1->h = SHIP_SIZE;
    sp2->h = SHIP_SIZE;
    sp1->v = 5;
    sp2->v = 5;
    

    //Test alors qu'ils ne sont pas en collision
    sp1->x = 0;
    sp1->y = 0;
    sp2->x = SHIP_SIZE + 6;
    sp2->y = SHIP_SIZE + 9;
    handle_sprites_collision_test_param(sp1, sp2);

    //Test alors qu'ils sont en collision
    sp2->x = 0;
    sp2->y = 0;
    handle_sprites_collision_test_param(sp1, sp2);
}


/*Résultat du test
La vitesse du sprite 1 est : 5
La vitesse du sprite 2 est : 5
La vitesse du sprite 1 est : 0
La vitesse du sprite 2 est : 0
*/


/**
 * \brief Procédure qui teste la fonction init_enemies.
 * \param world Données du monde.
 */
void init_enemies_test()
{
    world_t* world = malloc(sizeof(world_t));
    init_enemies(world);
    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        print_sprite(world->enemies[i]);
    }
}


/*Résultat du test (dépends du nombre d'ennemis, ici 5)
x = 35
y = -16
h = 32
w = 32
v = 2
x = 250
y = -80
h = 32
w = 32
v = 2
x = 29
y = -144
h = 32
w = 32
v = 2
x = 267
y = -208
h = 32
w = 32
v = 2
x = 37
y = -272
h = 32
w = 32
v = 2
*/


/**
 * \brief Procédure qui teste la fonction update_enemies
 * \param world données du monde
 */
void update_enemies_test_param(world_t *world)
{
    update_enemies(world);
    for (int i = 0; i < NB_ENEMIES; ++i)
    {
        printf("Sprite n°%d :\n", i);
        print_sprite(world->enemies[i]);
    }
}

/**
 * \brief Procédure qui teste la fonction update_enemies
 */
void update_enemies_test()
{
    world_t* world = malloc(sizeof(world_t));

    init_enemies(world);
    world->enemies[2]->y = SHIP_SIZE *2;
    update_enemies_test_param(world);

    world->enemies[2]->y = 258;
    world->enemies[1]->v = 888;
    world->enemies[4]->h = SHIP_SIZE *2;
    update_enemies_test_param(world);
}

/*Voici le résultat du test (dépends du nombre d'ennemis, ici 5)
Sprite n°0 :
x = 247
y = -14
h = 32
w = 32
v = 2
Sprite n°1 :
x = 150
y = -78
h = 32
w = 32
v = 2
Sprite n°2 :
x = 212
y = 66
h = 32
w = 32
v = 2
Sprite n°3 :
x = 121
y = -206
h = 32
w = 32
v = 2
Sprite n°4 :
x = 157
y = -270
h = 32
w = 32
v = 2
Sprite n°0 :
x = 247
y = -12
h = 32
w = 32
v = 2
Sprite n°1 :
x = 150
y = 810
h = 32
w = 32
v = 888
Sprite n°2 :
x = 212
y = 260
h = 32
w = 32
v = 2
Sprite n°3 :
x = 121
y = -204
h = 32
w = 32
v = 2
Sprite n°4 :
x = 157
y = -268
h = 64
w = 32
v = 2
*/


/**
 *  \brief programme principal qui effectue les tests
 */
int main(int argc, char* args[])
{
    sprite_test();
    limite_gauche_test();
    limite_droite_test();
    //limite_bas_test();
    sprites_collide_test();
    handle_sprites_collision_test();
    init_enemies_test();
    update_enemies_test();
    return EXIT_SUCCESS;
}