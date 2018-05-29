/**
 *  @file	ei_draw.c
 *  @brief	Graphical primitives to text, and operation of drawing
 *		surface
 *
 *  \author
 *  Created by thomas, lucas, basile on 18.05.18.
 *
 */
#include <stdlib.h>
#include "ei_draw.h"
#include "hw_interface.h"
#include "ei_application.h"
#include "ei_utils.h"
/**
 * \brief	Draws text by calling \ref hw_text_create_surface.
 *
 * @param	surface 	Where to draw the text. The surface must be *locked* by
 *				\ref hw_surface_lock.
 * @param	where		Coordinates, in the surface, where to anchor the top-left corner of
 *				the rendered text.
 * @param	text		The string of the text. Can't be NULL.
 * @param	font		The font used to render the text. If NULL, the \ref ei_default_font
 *				is used.
 * @param	color		The text color. The alpha parameter is not used.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle.
 */
void			ei_draw_text		(ei_surface_t		surface,
						 const ei_point_t*	where,
						 const char*		text,
						 const ei_font_t	font,
						 const ei_color_t	color,
						 const ei_rect_t*	clipper)
{

		ei_surface_t surface_text = hw_text_create_surface(text, font, color);
		ei_bool_t faux = EI_FALSE;
		// on cree une surface temporaire sur l'offscreen
		ei_size_t taille_surface = hw_surface_get_size(surface);
		ei_surface_t surface_temp = hw_surface_create(surface, &taille_surface, faux);
		// on copie l'ecran vers la surface temporaire
		int i = ei_copy_surface(surface_temp, NULL, surface, NULL, faux);
		// on colle le texte sur cette surface, au bon endroit
		ei_size_t text_size = ei_size_zero();
		hw_text_compute_size(text, font, &(text_size.width), &(text_size.height));
		ei_rect_t rect_cible = ei_rect(*where, text_size);
		int j = ei_copy_surface(surface_temp, &rect_cible, surface_text, NULL, faux);
		// on copie le clipper de la surface temporaire, on colle sur le clipper de la surface principale
		int k = ei_copy_surface(surface, clipper, surface_temp, clipper, faux);
		// on arrête si ça a pas marché
		if (i + j + k != 0){
			exit(666);
		}
		hw_surface_free(surface_text);
		hw_surface_free(surface_temp);
}

uint32_t		ei_map_rgba		(ei_surface_t surface, const ei_color_t* color)
{
				int ir = 0;
				int ig = 0;
				int ib = 0;
				int ia = 0;
				hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);
				uint32_t res = 0;
				res += (color->red)*2^((ir)*8);
				res += (color->green)*2^((ig)*8);
				res += (color->blue)*2^((ib)*8);
				res += (color->alpha)*2^((ia)*8);
				return res;
}
