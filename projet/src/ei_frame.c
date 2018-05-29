#include <stdlib.h>

#include "ei_draw.h"
#include "ei_frame.h"
#include "ei_types.h"
#include "ei_utils.h"
#include "ei_widgetclass.h"
#include "hw_interface.h"
#include "ei_application.h"


/**
 *\brief    Fonction utilitaire pour ei_frame_drawfunc_t :
 *
 *@param    anchor  the anchor point of the text (north north_west)
 *@param    surface the surface on which the text is to be drawn
 *@param    point   the point that is to be returned
 *
 */
void associate_point_anchor     (ei_anchor_t*    anchor,
                                ei_surface_t    surface,
                                ei_point_t* point)
{
    // association ancrage-surface avec coordonnées
    ei_rect_t rect = hw_surface_get_rect(surface);
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
 ei_linked_point_t* chemin_centre(ei_rect_t rectangle);
 void ei_frame_drawfunc_t(struct ei_widget_t*	widget,
     							ei_surface_t	surface,
     					        ei_surface_t	pick_surface,
     							ei_rect_t*		clipper)
 {
         ei_color_t couleur_fond = *(((ei_frame_t*)widget) -> color);
         ei_color_t couleur_top;//on augmente
         ei_color_t couleur_bot;//on baisse
         if (couleur_fond.red >= 5)
                 couleur_bot.red = couleur_fond.red -5;
         else
                 couleur_bot.red = couleur_fond.red;
         if (couleur_fond.green >= 5)
                 couleur_bot.green = couleur_fond.green -5;
         else
                couleur_bot.green = couleur_fond.green;
         if (couleur_fond.blue >= 5)
                 couleur_bot.blue = couleur_fond.blue -5;
         else
                couleur_bot.blue = couleur_fond.blue;
         if (couleur_fond.red <= 251)
                 couleur_top.red = couleur_fond.red +5;
         else
                 couleur_top.red = couleur_fond.red;
         if (couleur_fond.green <= 251)
                 couleur_top.green = couleur_fond.green +5;
         else
                 couleur_top.green = couleur_fond.green +5;
         if (couleur_fond.blue <= 251)
                 couleur_top.blue = couleur_fond.blue +5;
         else
                 couleur_top.blue = couleur_fond.blue;
         couleur_top.alpha = couleur_fond.alpha;
         couleur_bot.alpha = couleur_fond.alpha;
         ei_rect_t rectangle = widget -> screen_location;
         ei_size_t taille_rectangle = (widget->screen_location).size;
         ei_point_t point_du_rectangle = (widget->screen_location).top_left;
         ///<instanciation du rectangle de taille totale du frame
         ei_point_t point_du_rectangle_sans_border;
         point_du_rectangle_sans_border.x = point_du_rectangle.x + *(((ei_frame_t*)widget) -> border_width);
         point_du_rectangle_sans_border.y = point_du_rectangle.y + *(((ei_frame_t*)widget)->border_width);
         ei_size_t taille_rectangle_sans_border = {taille_rectangle.width -2* (*(((ei_frame_t*)widget)->border_width)), taille_rectangle.height - 2*(*(((ei_frame_t*)widget)->border_width))};
         ei_rect_t  rectangle_sans_border = {point_du_rectangle_sans_border, taille_rectangle_sans_border};
         ///<instanciation du rectangle de taille rectangle - border
         ei_fill(surface,&couleur_top,&rectangle);
         ///< on dessine d'abord un cadre clair
         ei_linked_point_t* triangle_bot=chemin_centre(rectangle);
         ei_draw_polygon(surface,triangle_bot,couleur_bot,&rectangle);
         /// < triangle du bas
         ei_fill(surface, ((ei_frame_t*)widget) -> color, &rectangle_sans_border);
         ///< filling the surface with the frame colour
         ei_fill(pick_surface, ((ei_frame_t*)widget) -> color, clipper);
         ///< filling the offscreen surface with the frame colour
         if (((ei_frame_t*)widget) -> text != NULL ){
                 ei_point_t* point = NULL;
                 associate_point_anchor(((ei_frame_t*)widget) -> anchor_text, surface, point);
                 ///< adressing the top-left corner as a point from its anchor
                 ei_draw_text(surface, point, *(((ei_frame_t*)widget) -> text), \
                         ((ei_frame_t*)widget) -> font, *(((ei_frame_t*)widget) -> color_text), clipper);
                         ///< Drawing said text on the surface
         }
         if (((ei_frame_t*)widget) -> image != NULL){
           // quand tu modifiera cela TNL, modifie l'équivalent dans ei_button_drawfunc
                 ei_copy_surface (surface, clipper, ((ei_frame_t*)widget) -> image, \
                         *(((ei_frame_t*)widget) -> rect), hw_surface_has_alpha(((ei_frame_t*)widget) -> image));
                         ///< drawing image if exists
         }
 }
 ei_linked_point_t* chemin_centre(ei_rect_t rectangle)
 {
   ei_linked_point_t* point_du_haut = malloc(sizeof(ei_linked_point_t));
   ei_linked_point_t* point_du_bas = malloc(sizeof(ei_linked_point_t));
   ei_linked_point_t* point_bas_droit = malloc(sizeof(ei_linked_point_t));
   (point_du_haut -> point).x = rectangle.top_left.x + rectangle.size.width;
   (point_du_haut -> point).y = rectangle.top_left.y;
   point_du_haut -> next = point_du_bas;
   point_du_bas -> point.x = rectangle.top_left.x;
   point_du_bas -> point.y = rectangle.top_left.y + rectangle.size.height;
   point_du_bas -> next = point_bas_droit;
   point_bas_droit -> point.x = rectangle.top_left.x + rectangle.size.width;
   point_bas_droit -> point.y = rectangle.top_left.y + rectangle.size.height;
   point_bas_droit -> next = NULL;
   return point_du_haut;
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
        *(((ei_frame_t*)widget) -> border_width) = sero;
        *(((ei_frame_t*)widget) -> relief) = relief;
        *(((ei_frame_t*)widget) -> color) = default_color;
        *(((ei_frame_t*)widget) -> font) = ei_default_font;
        *(((ei_frame_t*)widget) -> color_text) = text_defaut_color;
        *(((ei_frame_t*)widget) -> anchor_text) = anchor;
        ((ei_frame_t*)widget) -> image = NULL;
        ((ei_frame_t*)widget) -> rect = NULL;
        *(((ei_frame_t*)widget) -> anchor_image) = anchor;
        widget -> requested_size = ei_size_zero();
}
