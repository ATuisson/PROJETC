#include "ei_application.h"
#include "hw_interface.h"
#include "ei_widgetclass.h"
#include "ei_types.h"
#include <stdio.h>

ei_widget_t* ROOT = NULL;

void ei_app_create(ei_size_t* main_window_size, ei_bool_t fullscreen)
{

        hw_init();
  // il va falloir appeler ei_widgetclass_register ici.
//  surface_fenetre_syst = malloc(main_window_size->width*main_window_size->height*4)
        ei_frame_register_class();
        ei_color_t root_color = {20,20,20,255};
        *ROOT = {CLASSES, 1, root_color, NULL, NULL, NULL, NULL, NULL};
        ei_surface_t surface_fenetre_syst = NULL;
        surface_fenetre_syst = hw_create_window(main_window_size, fullscreen);
}


void ei_app_free(void)
{
        hw_quit();
}

void ei_app_run(void)
{
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
