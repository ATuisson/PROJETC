#ifndef EI_BUTTON_H
#define EI_BUTTON_H
#include "ei_types.h"
#include "ei_widget.h"
typedef enum {
  ei_bouton_whole = 0,
  ei_bouton_top,
  ei_bouton_bot
} ei_bouton_param_t;
ei_linked_point_t* arc(ei_point_t centre,
                       int rayon,
                       float debut_arc,
                       float fin_arc);

ei_linked_point_t* rounded_frame(ei_rect_t rectangle,
                                int rayon,
                                ei_bouton_param_t param);


ei_linked_point_t* chemin_du_centre(ei_rect_t rectangle,
                                    int largeur,
                                    int hauteur,
                                    int plus_court_cote,
                                    ei_point_t centre_haut_droit);
#endif
