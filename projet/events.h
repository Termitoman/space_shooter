/**
 * \file events.h
 * \brief Programme déclarant les fonctions utilisées pour gérer les événements
 * \author IOPETI Hugo
 * \author YVOZ Ludovic
 * \date 27 mai 2020
 */
 
#ifndef handle_events
#include "database.h"


/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event *event,world_t *world);


#endif