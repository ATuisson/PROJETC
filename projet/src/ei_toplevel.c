#include <stdlib.h>
#include "ei_placer.h"
#include "ei_draw.h"
#include "ei_frame.h"
#include "ei_types.h"
#include "ei_utils.h"
#include "ei_widgetclass.h"
#include "hw_interface.h"
#include "ei_application.h"
#include "ei_button.h"
#include "ei_toplevel.h"

extern ei_font_t ei_default_font;
extern ei_surface_t surface_fenetre_syst;

void ei_toplevel_drawfunc_t(struct ei_widget_t* widget,
                            ei_surface_t       surface,
                            ei_surface_t  pick_surface,
                            ei_rect_t*         clipper)
/**
 * prendre le content_rect et la screen_location, puis à l'inverse de button
 * et de frame, rajouter border_width a chaque coté, et en haut rajouter l'espace
 * correspondant à la taille en majuscule d'une lettre de la font puis encore un
 * border_width et deplacer la screen location pour que ça correspond à ce que
 * l'on voit.
 */
 {
   ei_toplevel_t* toplevel = (ei_toplevel_t*)widget;
   /// le rectangle ici, est les rectangle sans border et sans et sans le texte en haut
   ei_rect_t border_rect = widget -> screen_location;
   ei_rect_t content_rect = *(widget -> content_rect);
   ei_size_t border_rect_size = border_rect.size;
   ei_point_t content_rect_origin = content_rect.top_left;
   /// le rectangle ici, sera celui plus sombre avec le border et le text.
   int* hauteur_txt = NULL;
   int* largeur_txt = NULL;
   char* test_text = "AA";
   hw_text_compute_size(test_text,ei_default_font,largeur_txt,hauteur_txt);
   content_rect_origin.x = content_rect_origin.x + *(toplevel->border_width);
   content_rect_origin.y = content_rect_origin.y + 2*(*(toplevel->border_width))+ (*hauteur_txt);
   border_rect_size.width = border_rect_size.width + 2*(*(toplevel -> border_width));
   border_rect_size.height = border_rect_size.height + 3*(*(toplevel->border_width)) + (*hauteur_txt);
   border_rect.size = border_rect_size;
   content_rect.top_left = content_rect_origin;
   /// On dessine les rectangles border_text et screen location
   ei_fill(surface,&ei_default_title_color, &border_rect);
   ei_fill(surface,(toplevel -> color), &content_rect);
   ei_fill(pick_surface,&ei_default_title_color, &border_rect);
   ///bouton de fermeture.
   ei_size_t button_size = {*hauteur_txt,*hauteur_txt};
   ei_color_t	button_color		= {0xff, 0x00, 0x00, 0xff};
   int		button_border_width	= 2;
   int		button_corner_radius	= (int)0.5*(*hauteur_txt);
   ei_relief_t	button_relief		= ei_relief_raised;
   //ei_callback_t	button_callback 	= button_press;
   //instanciation du callback.
   ei_widget_t* button_fermeture;
   button_fermeture = ei_widget_create("button", widget);
   ei_button_configure	(button_fermeture, &button_size, &button_color,
          &button_border_width, &button_corner_radius, &button_relief, NULL, NULL, NULL, NULL,
          NULL, NULL, NULL, NULL, NULL); //y'a un callback mais pas programmé.
   int button_fermeture_x = (int)0.5*(*hauteur_txt);
   int button_fermeture_y = *(toplevel->border_width);
   ei_place(button_fermeture, NULL, &button_fermeture_x, &button_fermeture_y, NULL, NULL, NULL, NULL, NULL, NULL);
   char* text = *(toplevel->title);
   ei_surface_t surface_text = hw_text_create_surface(text, ei_default_font, ei_font_default_color);
   ei_rect_t rect_a_copier = hw_surface_get_rect(surface_text);
   ei_rect_t rect_cible = {{2*(*hauteur_txt), *(toplevel->border_width)},{border_rect_size.width - (*hauteur_txt)*2 - *(toplevel->border_width), *hauteur_txt}};
   affiche_surface(surface_fenetre_syst, &surface_text, &rect_cible, rect_a_copier);
   // ei_draw_text pas opti.. on l'appelle pas. ILs voulaient qu'on l'utilise, ils passent une anchor.
   ei_widget_t* button_dimension;
   button_dimension = ei_widget_create("button", widget);
   ei_size_t button_dimension_size ={10,10};
   ei_relief_t button_dimension_relief = ei_relief_none;
   int button_dimension_border = 0;
   int button_dimension_radius = 0;
   ei_button_configure	(button_dimension, &button_dimension_size, &ei_default_title_color,
          &button_dimension_border, &button_dimension_radius, &button_dimension_relief, NULL, NULL, NULL, NULL,
          NULL, NULL, NULL, NULL, NULL);
  // meme soucis pour callback.
   int button_dimension_x = border_rect_size.width - 10;
   int button_dimension_y = border_rect_size.height - 10;
   ei_place(button_dimension, NULL, &button_dimension_x, &button_dimension_y, NULL, NULL, NULL, NULL, NULL, NULL);
 }

void ei_toplevel_setdefaultsfunc_t(struct ei_widget_t* widget)
{
        int default_border = 4;
        ei_size_t default_requested_size;
        default_requested_size.width = 320;
        default_requested_size.height = 240;
        ei_size_t default_requested_min_size;
        default_requested_min_size.width =160;
        default_requested_min_size.height =120;
        char** default_title = "Toplevel";
        ei_bool_t default_closable = EI_TRUE;
        ei_axis_set_t default_resizable = ei_axis_both;
        ei_color_t default_color = ei_default_background_color;

        *((ei_toplevel_t*)widget) -> requested_size = default_requested_size;
        *((ei_toplevel_t*)widget) -> color = default_color;
        *((ei_toplevel_t*)widget) -> border_width = default_border;
        *((ei_toplevel_t*)widget) -> title = default_title;
        *((ei_toplevel_t*)widget) -> closable = default_closable;
        *((ei_toplevel_t*)widget) -> resizable = default_resizable;
        **((ei_toplevel_t*)widget) -> min_size = default_requested_min_size;
        widget -> requested_size = ei_size_zero();
}
void ei_toplevel_releasefunc_t(struct ei_widget_t* widget)
{
        free(((ei_toplevel_t*)widget) -> requested_size);
        free(((ei_toplevel_t*)widget) -> color);
        free(((ei_toplevel_t*)widget) -> border_width);
        free(((ei_toplevel_t*)widget) -> title);
        free(((ei_toplevel_t*)widget) -> closable);
        free(((ei_toplevel_t*)widget) -> resizable);
        free(((ei_toplevel_t*)widget) -> min_size);
}

void* ei_toplevel_allocfunc_t()
{
        ei_toplevel_t* widtoplevel = calloc(1, sizeof(ei_toplevel_t));
        widtoplevel -> color = calloc(1, sizeof(ei_color_t));
        widtoplevel -> border_width = calloc(1, sizeof(int));
        widtoplevel -> requested_size = calloc(1, sizeof(ei_size_t));
        widtoplevel -> closable = calloc(1, sizeof(ei_bool_t));
        widtoplevel -> resizable = calloc(1, sizeof(ei_axis_set_t));

        return widtoplevel;
}
