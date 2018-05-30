#include <stdlib.h>

#include "ei_draw.h"
#include "ei_frame.h"
#include "ei_types.h"
#include "ei_utils.h"
#include "ei_widgetclass.h"
#include "hw_interface.h"
#include "ei_application.h"
#include "ei_button.h"
extern ei_font_t ei_default_font;
extern ei_surface_t surface_fenetre_syst;
/**
 *\brief    Fonction utilitaire pour copy_surfaces :
 *
 *@param    anchor      the anchor point of surface to copy
 *@param    surface     the surface to copy
 *@param    rect        the rectangle on which the surface is to be copied
 *@param    copy_rect   the rectangle of the image that is to be copied (returned)
 *                      the origin may be negative !! (if img is smaller than rectangle)
 *
 */
void retrieve_rect_surface     (ei_anchor_t*   anchor,
                                    ei_surface_t*   surface,
                                    ei_rect_t*      rect,
                                    ei_rect_t*      copy_rect)
{
    // association ancrage-surface avec coordonnées: on renvoie le rectangle de l'image à copier
    ei_size_t surface_size = hw_surface_get_size(*surface);
    copy_rect -> size = rect -> size;
    switch (*anchor) {
            case 0:
            case 1://center
                    (copy_rect->top_left).x = surface_size.width / 2 - (rect->size).width / 2;
                    (copy_rect->top_left).y = surface_size.height / 2 - (rect->size).height / 2;
                    break;
            case 2://north
                    (copy_rect->top_left).x = surface_size.width / 2 - (rect->size).width / 2;
                    break;
            case 3://north_east
                    (copy_rect->top_left).x = surface_size.width - (rect->size).width;
                    break;
            case 4://east
                    (copy_rect->top_left).x = surface_size.width - (rect->size).width;
                    (copy_rect->top_left).y = surface_size.height / 2 - (rect->size).height /2;
                    break;
            case 5:
                    (copy_rect->top_left).x = surface_size.width - (rect->size).width;
                    (copy_rect->top_left).y = surface_size.height - (rect->size).height;
                    break;
            case 6://south
                    (copy_rect->top_left).x = surface_size.width / 2 - (rect->size).width / 2;
                    (copy_rect->top_left).y = surface_size.height - (rect->size).height;
                    break;
            case 7:
                    (copy_rect->top_left).y = surface_size.height - (rect->size).height;
                    break;
            case 8://west
                    (copy_rect->top_left).y = surface_size.height / 2 - (rect->size).height / 2;
                    break;
            case 9: //north_west
            default:
                    break;
    }
}

/**
 *\brief    Fonction utilitaire pour drawfunc :
 *@param    target_surface the surface on which to copy
 *@param    surface     the surface to copy
 *@param    cible        the rectangle on which the surface is to be copied
 *@param    rect_a_copier     part of the surface to copy
 *
 */
void affiche_surface(ei_surface_t   target_surface,
                    ei_surface_t*   surface,
                    ei_rect_t*      cible,
                    ei_rect_t    rect_a_copier)
{
    ei_bool_t vrai = EI_TRUE;
    ei_bool_t faux = EI_FALSE;
    if((rect_a_copier.top_left).x < 0 || (rect_a_copier.top_left).y < 0){
        //dans le cas où l'image est plus petite que le cadre, on cree une surface de taille le rectangle
        ei_surface_t surface_temp = hw_surface_create(surface_fenetre_syst, &(rect_a_copier.size), vrai);
        hw_surface_lock(surface_temp);
        //on colle l'image dans la surface temporaire
        ei_rect_t rect_cible_image = ei_rect(ei_point_zero(),hw_surface_get_size(*surface));
        if ((rect_a_copier.top_left).x < 0){
            rect_cible_image.top_left.x = - (rect_a_copier.top_left).x;
        }
        if ((rect_a_copier.top_left).y < 0){
            rect_cible_image.top_left.y = - (rect_a_copier.top_left).y;
        }
        ei_copy_surface(surface_temp, &rect_cible_image, *surface, NULL, faux);
        //on colle la surface temporaire dans le rectangle cible
        ei_copy_surface(target_surface, cible, surface_temp, NULL, vrai);
        hw_surface_unlock(surface_temp);
        hw_surface_free(surface_temp);
    }
    else{
        ei_copy_surface(target_surface, cible, *surface, &rect_a_copier, vrai);
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
          // on aurait pu factoriser cette partie qui est aussi dans draw_button
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
         if ((*((ei_frame_t*)widget) -> relief) == ei_relief_raised){
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
         }
         if ((*((ei_frame_t*)widget) -> relief) == ei_relief_sunken){
                 ///<instanciation du rectangle de taille rectangle - border
                 ei_fill(surface,&couleur_bot,&rectangle);
                 ///< on dessine d'abord un cadre clair
                 ei_linked_point_t* triangle_bot=chemin_centre(rectangle);
                 ei_draw_polygon(surface,triangle_bot,couleur_top,&rectangle);
                 /// < triangle du bas
                 ei_fill(surface, ((ei_frame_t*)widget) -> color, &rectangle_sans_border);
                 ///< filling the surface with the frame colour
                 ei_fill(pick_surface, ((ei_frame_t*)widget) -> color, clipper);
                 ///< filling the offscreen surface with the frame colour
         }
         if ((*((ei_frame_t*)widget) -> relief)== ei_relief_none){
                ei_fill(surface,((ei_frame_t*)widget) -> color, &rectangle);
         }
         if (((ei_frame_t*)widget) -> text != NULL ){
                ei_anchor_t* ancrage = ((ei_frame_t*)widget) -> anchor_text;
                char* text = *(((ei_frame_t*)widget) -> text);
                ei_font_t* font = ((ei_frame_t*)widget) -> font;
                ei_color_t* color = ((ei_frame_t*)widget) -> color_text;
                ei_surface_t surface_text = hw_text_create_surface(text, *font, *color);
                ei_rect_t rect_a_copier = ei_rect_zero();
                retrieve_rect_surface(ancrage, &surface_text, clipper, &rect_a_copier);
                affiche_surface(surface_fenetre_syst, &surface_text, clipper, rect_a_copier);
                // ei_draw_text pas opti.. on l'appelle pas. ILs voulaient qu'on l'utilise, ils passent une anchor.
         }
         if (((ei_frame_t*)widget) -> image != NULL && ((ei_frame_t*)widget) -> rect != NULL){
                ei_anchor_t* ancrage = ((ei_frame_t*)widget) -> anchor_image;
                ei_surface_t* surface = ((ei_frame_t*)widget) -> image;
                ei_rect_t*  cible = *((ei_frame_t*)widget) -> rect;
                ei_rect_t rect_a_copier = ei_rect_zero();
                retrieve_rect_surface(ancrage, surface, cible, &rect_a_copier);
                affiche_surface(surface_fenetre_syst, surface, cible, rect_a_copier);
         }
 }

 ei_linked_point_t* chemin_centre(ei_rect_t rectangle)
 {
   int plus_court_cote = min(rectangle.size.width,rectangle.size.height);
   ei_linked_point_t* point_du_haut = malloc(sizeof(ei_linked_point_t));
   ei_linked_point_t* point_centre_haut = malloc(sizeof(ei_linked_point_t));
   ei_linked_point_t* point_centre_bas = malloc(sizeof(ei_linked_point_t));
   ei_linked_point_t* point_du_bas = malloc(sizeof(ei_linked_point_t));
   ei_linked_point_t* point_bas_droit = malloc(sizeof(ei_linked_point_t));
   (point_du_haut -> point).x = rectangle.top_left.x + rectangle.size.width;
   (point_du_haut -> point).y = rectangle.top_left.y;
   point_du_haut -> next = point_centre_haut;
   point_centre_haut -> point.x =rectangle.top_left.x + rectangle.size.width -0.5* plus_court_cote;
   point_centre_haut -> point.y =rectangle.top_left.y + 0.5*plus_court_cote;
   point_centre_haut -> next = point_centre_bas;
   point_centre_bas -> point.x =rectangle.top_left.x + 0.5*plus_court_cote;
   point_centre_bas -> point.y =rectangle.top_left.y + rectangle.size.height - 0.5*plus_court_cote;
   point_centre_bas -> next = point_du_bas;
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
