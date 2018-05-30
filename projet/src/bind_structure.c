/**
 *  @file	bind_structure.h
 *  @brief	Structure used to bind/unbind of callback to events, and some utilitary functions.
 *
 *  \author
 *  Created by Lucas Basile et Thomas on 28.05.18.
 *
 */
 #include "bind_structure.h"

extern bind_structure_t *EVENTTAB[8];

ei_color_t id_to_rgba (ei_surface_t surface, uint32_t* id) {
        int ir;
        int ig;
        int ib;
        int ia;
        hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);
        ei_color_t pick_color;
        uint8_t* id_tronque = (uint8_t*)id;
        pick_color.red = *(id_tronque+ir);
        pick_color.green = *(id_tronque+ig);
        pick_color.blue = *(id_tronque+ib);
        pick_color.alpha = *(id_tronque+ia);
        return pick_color;
}

ei_widget_t* recherche_widget(uint32_t id, ei_widget_t* widget)
{
        if (widget -> pick_id == id) {
                return widget;
        }
        if (widget->children_head != NULL){
                return recherche_widget(id, widget->children_head);
                ei_widget_t* current = widget->children_head->next_sibling;
                while (current != NULL){
                      return recherche_widget(id, current);
                      current = current->next_sibling;
                }
        }
        return NULL;
}

void traitement(struct ei_event_t event)
{
        bind_structure_t* courant = EVENTTAB[event -> type];
        while (courant != NULL) {
                courant -> callback(NULL, &event, courant -> user_param);
        }
}
