#ifndef EI_BUTTON_H
#define EI_BUTTON_H
#include "ei_types.h"
#include "ei_widget.h"

/**
 * \brief	Converts the three red, green and blue component of a color in a 32 bits integer
 *		using the order of the channels of the surface. This integer can be stored directly
 *		in the pixels memory of the surface (ie. \ref hw_surface_get_buffer).
 *
 * @param	surface		The surface where to store this pixel.
 * @param	color		The color to convert, can't be NULL.
 *
 * @return 			The 32 bit integer corresponding to the color. The alpha component
 *				of the color is ignored in the case of surfaces that don't have an
 *				alpha channel.
 */
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


void draw_button (struct ei_widget_t*  widget,
                            ei_surface_t        surface,
                            ei_surface_t        pick_surface,
                            ei_rect_t*          clipper);


int min(int a,int b);


typedef struct ei_button_t		{ei_widget_t		widget;
							 ei_color_t*	color;
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
