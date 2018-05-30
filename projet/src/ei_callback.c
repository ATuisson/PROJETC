/**
 * @file	ei_callback.h
 *
 * @brief 	Definition of all callback functions
 *
 *  Created by Lucas Thomas et Basile on 28/05/18.
 */
#include "ei_callback.h"

extern ei_surface_t surface_fenetre_syst;
extern ei_surface_t surface_offscreen;

ei_bool_t enfonce_bouton_souris(ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
        printf("Coucou\n");
        ei_mouse_event_t mouse = (event -> param).mouse;
        ei_widget_t* widget_souris = ei_widget_pick(&(mouse.where));
        if (widget_souris == NULL) {
                printf("Coucou1\n");
                return EI_TRUE;
        }
        if (strcmp(widget_souris->wclass->name, "button") != 0) {
                printf("Coucou2\n");
                return EI_TRUE;
        }
        if (event -> type == ei_ev_mouse_buttondown) {
                printf("Coucou3\n");
                ei_relief_t relief = ei_relief_sunken;
                ei_button_configure(widget_souris, NULL,NULL,NULL,NULL,&relief,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
                return EI_FALSE;
        }
}

ei_bool_t relache_bouton_souris(ei_widget_t* widget, struct ei_event_t* event, void* user_param)
{
        ei_mouse_event_t mouse = (event -> param).mouse;
        ei_widget_t* widget_souris = ei_widget_pick(&(mouse.where));
        if (widget_souris == NULL) {
                return EI_TRUE;
        }
        if (strcmp(widget_souris->wclass->name, "button") != 0) {
                return EI_TRUE;
        }
        if (event -> type == ei_ev_mouse_buttondown) {
                ei_relief_t relief = ei_relief_raised;
                ei_button_configure(widget_souris, NULL,NULL,NULL,NULL,&relief,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
                return EI_FALSE;
        }
}
