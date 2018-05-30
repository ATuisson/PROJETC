#ifndef EI_BUTTON_H
#define EI_BUTTON_H
#include "ei_types.h"
#include "ei_widget.h"

/**
 * \brief	enum struct used for different parts of button
 *
 */
typedef enum {
  ei_bouton_whole = 0,
  ei_bouton_top,
  ei_bouton_bot
} ei_bouton_param_t;

/**
 * \brief   returns a linked list to create an arc, depending on parameters
 *
 * @param	centre		the center of the arc
 * @param	rayon       the radius of the arc
 * @param	debut_arc   target of the beginning of the arc, in degrees
 * @param   fin_arc     target of the end of the arc, in degrees
 */
ei_linked_point_t* arc(ei_point_t centre,
                       int rayon,
                       float debut_arc,
                       float fin_arc);

/**
 * \brief	returns       the part of the button depending of the param
 *
 * @param	rectangle	  the rectangle corresponding to the button
 * @param	rayon         the radius of the corners of the button
 * @param	param		  part of the button to be returned
 */
ei_linked_point_t* rounded_frame(ei_rect_t rectangle,
                                int rayon,
                                ei_bouton_param_t param);

/**
 * \brief	returns the path between the two opposite corners of the button for
 *          relief independencies
 *
 * @param	rectangle	    rectangle of the button
 * @param	largeur, hauteur		size of said rectangle
 * @param	plus_court_cote         the shortest of previous ints
 * @param   centre_haut_droit       center of top_right corner of button
 *
 */
ei_linked_point_t* chemin_du_centre(ei_rect_t rectangle,
                                    int largeur,
                                    int hauteur,
                                    int plus_court_cote,
                                    ei_point_t centre_haut_droit);

/**
 * \brief	draws the constant parts of button (no text no image)
 *
 * @param	cf drawfunc
 */
void draw_button (struct ei_widget_t*  widget,
                            ei_surface_t        surface,
                            ei_surface_t        pick_surface,
                            ei_rect_t*          clipper);


int min(int a,int b);

/**
 * \brief	defines the button structure cf widget.h
 *
 */
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

/**
 * \brief	allocates memory for a button widget
 */
void* ei_button_allocfunc_t ();

/**
 * \brief draws a button
 */
void ei_button_drawfunc_t (struct ei_widget_t*   widget,
                          ei_surface_t  surface,
                          ei_surface_t  pick_surface,
                          ei_rect_t*    clipper);

/**
 * \brief releases the allocated memory of a button widget
 */
void ei_button_releasefunc_t (struct ei_widget_t*    widget);

/**
 * \brief attributes default vallues for a button
 */
void ei_button_setdefaultsfunc_t (struct ei_widget_t*   widget);


#endif
