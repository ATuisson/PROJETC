/**
 *  @file	bind_structure.h
 *  @brief	Structure used to bind/unbind of callback to events, and some utilitary functions.
 *
 *  \author
 *  Created by Lucas Basile et Thomas on 28.05.18.
 *
 */
#include "hw_interface.h"

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
