#include <stdio.h>

#include "ei_draw.h"
#include "ei_application.h"
#include "hw_interface.h"
#include "ei_widgetclass.h"
#include "ei_types.h"

extern ei_widgetclass_t* CLASSES;
ei_widget_t* ROOT;
void explore(ei_widget_t* widget);
ei_surface_t surface_fenetre_syst;
ei_surface_t surface_offscreen;

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{
        hw_init(); //
        ei_bool_t faux = EI_FALSE;
        surface_fenetre_syst = hw_create_window(main_window_size, fullscreen); //
        surface_offscreen = hw_surface_create(surface_fenetre_syst, main_window_size, faux); //
        ei_frame_register_class(); //
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

void ei_app_run(void)
{
        explore(ROOT);
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
      return ROOT;
}

ei_surface_t ei_app_root_surface(void)
{

}

void explore(ei_widget_t* widget)
{
        // suis teubé faut acceder a surface_offscreen et surface_fenetre_syst avec des pointeurs...
        if (widget->parent != NULL) {
                widget->wclass->drawfunc(widget,surface_fenetre_syst, surface_offscreen,
                                                          widget->parent->content_rect);
        }
        else {
          widget->wclass->drawfunc(widget,surface_fenetre_syst, surface_offscreen,
                                                    NULL);
        }
        if (widget->children_head != NULL){
                explore(widget->children_head);
                ei_widget_t* current = widget->children_head->next_sibling;
                while (current != NULL){
                      explore(current);
                      current = current->next_sibling;
                }
        }

}
