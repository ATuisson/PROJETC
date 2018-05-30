/**
 *  @file	bind_structure.h
 *  @brief	Allows the binding and unbinding of callbacks to events.
 *
 *  \author
 *  Created by Lucas Basile et Thomas on 28.05.18.
 *
 */
#ifndef BIND_STRUCTURE_H
#define BIND_STRUCTURE_H

#include <stdlib.h>
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_event.h"
#include "hw_interface.h"

typedef struct bind_structure_t {
        ei_eventtype_t eventtype;
        ei_widget_t* widget;
        ei_tag_t tag;
        ei_callback_t callback;
        void* user_param;
        struct bind_structure_t* next;
} bind_structure_t;

ei_color_t id_to_rgba (ei_surface_t surface, uint32_t* id);

ei_widget_t* recherche_widget(uint32_t id, ei_widget_t* root);

void traitement(struct ei_event_t event);

#endif
