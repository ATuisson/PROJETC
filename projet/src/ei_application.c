#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ei_draw.h"
#include "ei_application.h"
#include "hw_interface.h"
#include "ei_widgetclass.h"
#include "ei_types.h"
#include "ei_geometrymanager.h"

extern ei_widgetclass_t* CLASSES;
extern ei_geometrymanager_t* MANAGERS;
ei_widget_t* ROOT;
void explore(ei_widget_t* widget, ei_rect_t* clipper);
ei_surface_t surface_fenetre_syst;
ei_surface_t surface_offscreen;
ei_linked_rect_t* UPDATES;
ei_bool_t EXIT = EI_FALSE;

/**
 * @brief Le parametre clipper servira à la mise à jour de rectangles particuliers
 *        cad widget supprimé, mis à jour, ... cf 3.8.2
 *
 **/
void explore(ei_widget_t* widget, ei_rect_t* clipper)
{
        // suis teubé faut acceder a surface_offscreen et surface_fenetre_syst avec des pointeurs...
        if (widget->parent != NULL) {
                if (clipper == NULL){
                        widget->wclass->drawfunc(widget,surface_fenetre_syst, surface_offscreen,
                                                          widget->parent->content_rect);
                }
                else {
                        widget->wclass->drawfunc(widget,surface_fenetre_syst, surface_offscreen,
                                                          clipper);
                }
        }
        else {
                if (clipper == NULL){
                        widget->wclass->drawfunc(widget,surface_fenetre_syst, surface_offscreen,
                                                    NULL);
                }
                else {
                        widget->wclass->drawfunc(widget,surface_fenetre_syst, surface_offscreen,
                                                    clipper);
                }
        }
        if (widget->children_head != NULL){
                explore(widget->children_head, clipper);
                ei_widget_t* current = widget->children_head->next_sibling;
                while (current != NULL){
                      explore(current, clipper);
                      current = current->next_sibling;
                }
        }

}

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
        hw_init(); //
        ei_bool_t faux = EI_FALSE;
        surface_fenetre_syst = hw_create_window(main_window_size, fullscreen); //
        surface_offscreen = hw_surface_create(surface_fenetre_syst, main_window_size, faux); //
        ei_frame_register_class(); //
        ei_register_placer_manager();
        ROOT = ei_widget_create("frame", NULL);
        const ei_color_t root_color = {20,20,20,255};
        ei_point_t root_top_left_point = {0, 0};
        ei_rect_t root_screen_location = {root_top_left_point, *main_window_size};
        uint32_t pick_id = ei_map_rgba(surface_offscreen, &root_color);
        ROOT->wclass = CLASSES;
        ROOT->pick_id = pick_id;
        ROOT->pick_color = &root_color;
        ROOT->children_head = NULL;
        ROOT->children_tail = NULL;
        ROOT->next_sibling = NULL;
        ROOT->geom_params = NULL;
        ROOT->screen_location = root_screen_location;
        ROOT->content_rect = &(ROOT->screen_location);
}


void ei_app_free(void)
{
        hw_quit();
}

/**
 * CF enonce 3.8.2 et 3.7
 *
 **/
void ei_app_run(void)
{
        while (EXIT == EI_FALSE){
                // attente d'un evenement
                // il rajoutera des elements à updates
                while (UPDATES != NULL){
                        // d'apres l'enonce c'est ici que se fait le lock et l'unlock.
                        // TODO : optimisation, pousser plus loin le 3.7
                        hw_surface_unlock(surface_fenetre_syst);
                        uint8_t* buffer = hw_surface_get_buffer(surface_fenetre_syst);
                        explore(ROOT, &(UPDATES -> rect));
                        UPDATES = UPDATES -> next;
                        hw_surface_unlock(surface_fenetre_syst);
                        hw_surface_update_rects(surface_fenetre_syst, UPDATES);
                }
                UPDATES = NULL;
                int sortie = getchar();
                if (sortie != 0){
                        EXIT = EI_TRUE;
                }
        }

}

/**
 * Rajoute le rectangle à la liste des rectangles à mettre à jour
 * Problème : portée des variables ? # pas sur de moi
 * TODO : PAS SUR DU CODE
 **/
void ei_app_invalidate_rect(ei_rect_t* rect)
{
      ei_linked_rect_t* temp = malloc(sizeof(ei_linked_rect_t));
      temp -> next = NULL;
      temp -> rect = *rect;
      if (UPDATES == NULL) {
                      UPDATES = temp;
      }
      else {
                      ei_linked_rect_t* current = UPDATES;
                      while(current -> next != NULL) {
                                      current = current -> next;
                      }
                      current -> next = temp;
      }
}

void ei_app_quit_request(void)
{

}

ei_widget_t* ei_app_root_widget(void)
{
      return ROOT;
}

ei_surface_t ei_app_root_surface(void)
{
        return surface_fenetre_syst;
}
