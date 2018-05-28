#ifndef EI_BUTTON_H
#define EI_BUTTON_H
#include "ei_types.h"
#include "ei_widget.h"

ei_linked_point_t* arc(ei_point_t centre,
                       int rayon,
                       float debut_arc,
                       float fin_arc);

ei_linked_point_t* rounded_frame(ei_rect_t rectangle,
                                int rayon);


#endif
