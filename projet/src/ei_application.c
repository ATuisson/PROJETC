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
        hw_init();
        surface_fenetre_syst = hw_create_window(main_window_size, fullscreen);
        ei_bool_t faux = EI_FALSE;
        surface_offscreen = hw_surface_create(surface_fenetre_syst, main_window_size, faux);
        ei_frame_register_class();
        ei_color_t root_color = {20,20,20,255};
        ei_point_t root_top_left_point = {0, 0};
        ei_rect_t root_screen_location = {root_top_left_point, *main_window_size};
        uint32_t pick_id = ei_map_rgba(surface_offscreen, &root_color);
        ei_widget_t root_temp = {CLASSES, pick_id, &root_color, NULL, NULL, NULL, NULL, NULL, *main_window_size, root_screen_location, &root_screen_location};
        ROOT = &root_temp;
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
        widget->wclass->drawfunc(widget,surface_fenetre_syst, surface_offscreen,
                                                  widget->parent->content_rect);
        if (widget->children_tail != NULL){
                explore(widget->children_tail);
                ei_widget_t* current = widget->children_tail->next_sibling;
                while (current != NULL){
                      explore(current);
                      current = current->next_sibling;
                }
        }

}
