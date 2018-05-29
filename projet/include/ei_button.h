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


typedef struct ei_button_t		{ei_widget_t		widget;
							 const ei_color_t*	color;
							 int*			border_width;
							 int*			corner_radius;
							 ei_relief_t*		relief;
							 char**			text;
							 ei_font_t*		text_font;
							 ei_color_t*		text_color;
							 ei_anchor_t*		text_anchor;
							 ei_surface_t*		img;
							 ei_rect_t**		img_rect;
							 ei_anchor_t*		img_anchor;
							 ei_callback_t*		callback;
							 void**			user_param;
} ei_button_t;

void* ei_button_allocfunc_t ();

void ei_button_drawfunc_t (struct ei_widget_t*   widget,
                          ei_surface_t  surface,
                          ei_surface_t  pick_surface,
                          ei_rect_t*    clipper);


void ei_button_releasefunc_t (struct ei_widget_t*    widget);

void ei_button_setdefaultsfunc_t (struct ei_widget_t*   widget);
#endif
