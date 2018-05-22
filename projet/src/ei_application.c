#include "ei_application.h"
#include "hw_interface.h"
#include <stdio.h>

void explore(ei_widget_t* widget);
void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{

        hw_init();
        ei_frame_register_class();
        // il va falloir appeler ei_widgetclass_register ici.

      //  surface_fenetre_syst = malloc(main_window_size->width*main_window_size->height*4)
        ei_surface_t surface_fenetre_syst = NULL;
        surface_fenetre_syst = hw_create_window(main_window_size, fullscreen);
}


void ei_app_free(void)
{

        hw_quit();
}

void ei_app_run(void)
{       ei_widget_t*  racine=;
        ei_widget_t*  courant=;
        explore(racine);
        // partir de la racine et "recursivement" passer les desendants et appeler leur drawfunc
        // racine : faire une variable globale qui memorise la racine ?
        // tant que children != null continuer
        // sinon voir next sibling et recommencer la partie d'avant
        // next sibling = null : voir parent next sibling si nul voir parent next sibling etc

        getchar();
}

void ei_app_invalidate_rect(ei_rect_t* rect)
{

}

void ei_app_quit_request(void)
{

}

ei_widget_t* ei_app_root_widget(void)
{

}

ei_surface_t ei_app_root_surface(void)
{

}
void explore(ei_widget_t* widget)
{

        widget->wclass->drawfunc(widget, widget->screen_location ,pick_surface , widget->parent->content_rect)
        if (widget->children_tail != NULL){
                explore(widget->children_tail);
                ei_widget_t* current = widget->children_tail->next_sibling;
                while (current != NULL){
                      explore(current);
                      current = current->next_sibling;
                }
        }

}
