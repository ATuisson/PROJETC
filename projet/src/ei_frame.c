#include <stdlib.h>

#include "ei_draw.h"
#include "ei_frame.h"
#include "ei_types.h"
#include "ei_utils.h"
#include "ei_widgetclass.h"
#include "hw_interface.h"
#include "ei_application.h"
#include "ei_utils.h"


/**
 *\brief    Fonction utilitaire pour ei_frame_drawfunc_t :
 *
 *@param    anchor  the anchor point of the text (north north_west)
 *@param    surface the surface on which the text is to be drawn
 *@param    point   the point that is to be returned
 *
 */
void associate_point_anchor     (ei_anchor_t*    anchor,
                                ei_rect_t    rect,
                                ei_point_t* point)
{
    // association ancrage-surface avec coordonnées
    switch (*anchor) {
            case 1:
                    point->x = rect.top_left.x + rect.size.width / 2;
                    point->y = rect.top_left.y + rect.size.height / 2;
                    break;
            case 2:
                    point->x = rect.top_left.x + rect.size.width / 2;
                    point->y = rect.top_left.y;
                    break;
            case 3:
                    point->x = rect.top_left.x + rect.size.width;
                    point->y = rect.top_left.y;
                    break;
            case 4:
                    point->x = rect.top_left.x + rect.size.width;
                    point->y = rect.top_left.y + rect.size.height / 2;
                    break;
            case 5:
                    point->x = rect.top_left.x + rect.size.width;
                    point->y = rect.top_left.y + rect.size.height;
                    break;
            case 6:
                    point->x = rect.top_left.x + rect.size.width / 2;
                    point->y = rect.top_left.y + rect.size.height;
                    break;
            case 7:
                    point->x = rect.top_left.x;
                    point->y = rect.top_left.y + rect.size.height;
                    break;
            case 8:
                    point->x = rect.top_left.x;
                    point->y = rect.top_left.y + rect.size.height / 2;
                    break;
            case 9: //defaut : topleft corner
                    point->x = rect.top_left.x;
                    point->y = rect.top_left.y;
                    break;
            default:
                    point->x = rect.top_left.x;
                    point->y = rect.top_left.y;
    }
}

/**
  *\brief allocate the memory for frame
 */
void* ei_frame_allocfunc_t()
{
        ei_frame_t* widframe = calloc(1, sizeof(ei_frame_t));
        widframe -> color = calloc(1, sizeof(ei_color_t));
        widframe -> border_width = calloc(1, sizeof(int));
        widframe -> relief = calloc(1, sizeof(ei_relief_t));
        widframe -> font = calloc(1, sizeof(ei_font_t));
        widframe -> color_text = calloc(1, sizeof(ei_color_t));
        widframe -> anchor_text = calloc(1, sizeof(ei_anchor_t));
        widframe -> anchor_image = calloc(1, sizeof(ei_anchor_t));
        return widframe;
}

/**
 * \brief	A function that draws widgets of a class.
 *
 * @param	widget		A pointer to the widget instance to draw.
 * @param	surface		Where to draw the widget. The actual location of the widget in the
 *				surface is stored in its "screen_location" field.
 * @param	pick_surface	The surface used for picking (i.e. find the widget below the mouse pointer).
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle
 *				(expressed in the surface reference frame).
 */
void ei_frame_drawfunc_t(struct ei_widget_t*	widget,
    							ei_surface_t	surface,
    					        ei_surface_t	pick_surface,
    							ei_rect_t*		clipper)
{
        ei_rect_t* rectangle = widget -> content_rect;
        ei_fill(surface, ((ei_frame_t*)widget) -> color, rectangle);  ///< filling the surface with the frame colour
        ei_fill(pick_surface, ((ei_frame_t*)widget) -> color, clipper);  ///< filling the offscreen surface with the frame colour
        if (((ei_frame_t*)widget) -> text != NULL ){
                ei_point_t point = ei_point_zero();
                associate_point_anchor(((ei_frame_t*)widget) -> anchor_text, *rectangle, &point);
                ///< adressing the top-left corner as a point from its anchor
                ei_draw_text(surface, &point, *(((ei_frame_t*)widget) -> text), \
                        ((ei_frame_t*)widget) -> font, *(((ei_frame_t*)widget) -> color_text), clipper);
                        ///< Drawing said text on the surface
        }
        if (((ei_frame_t*)widget) -> image != NULL){
                ei_copy_surface (surface, clipper, ((ei_frame_t*)widget) -> image, \
                        *(((ei_frame_t*)widget) -> rect), hw_surface_has_alpha(((ei_frame_t*)widget) -> image));
                        ///< drawing image if exists
        }
}

/**
 * \brief	A function that releases the memory used by a FRAME widget before it is destroyed.
 *		The \ref ei_widget_t structure itself, passed as parameter, must *not* by freed by
 *		these functions. Can be set to NULL in \ref ei_widgetclass_t if no memory is used by
 *		a class of widget.
 *
 * @param	widget		The widget which resources are to be freed.
 */
void ei_frame_releasefunc_t(struct ei_widget_t* widget)
{
        free(((ei_frame_t*)widget) -> color);
        free(((ei_frame_t*)widget) -> border_width);
        free(((ei_frame_t*)widget) -> relief);
        free(((ei_frame_t*)widget) -> text);
        free(((ei_frame_t*)widget) -> font);
        free(((ei_frame_t*)widget) -> color_text);
        free(((ei_frame_t*)widget) -> anchor_text);
        free(((ei_frame_t*)widget) -> image);
        free(((ei_frame_t*)widget) -> rect);
        free(((ei_frame_t*)widget) -> anchor_image);
}

void ei_frame_setdefaultsfunc_t(struct ei_widget_t*   widget)
{
        ei_color_t default_color = ei_default_background_color;
        ei_color_t text_defaut_color = ei_font_default_color;
        int sero = 0;
        ei_relief_t relief = ei_relief_none;
        ei_anchor_t anchor = ei_anc_center;
        ((ei_frame_t*)widget) -> text = NULL;
        ((ei_frame_t*)widget) -> border_width = &sero;
        ((ei_frame_t*)widget) -> relief = &relief;
        ((ei_frame_t*)widget) -> color = &default_color;
        ((ei_frame_t*)widget) -> font = &ei_default_font;
        ((ei_frame_t*)widget) -> color_text = &text_defaut_color;
        ((ei_frame_t*)widget) -> anchor_text = &anchor;
        ((ei_frame_t*)widget) -> image = NULL;
        ((ei_frame_t*)widget) -> rect = NULL;
        ((ei_frame_t*)widget) -> anchor_image = &anchor;
        widget -> requested_size = ei_size_zero();
}
