
#include <stdlib.h>
#include <math.h>
#include "ei_draw.h"
#include "ei_button.h"
#include "ei_types.h"
#include "ei_widgetclass.h"
#include "hw_interface.h"
#include "ei_button.h"

int min(int a,int b);

ei_linked_point_t* arc (ei_point_t centre,
                 int rayon,
                 float debut_arc,
                 float fin_arc){

        ei_linked_point_t* arc = NULL;
        //conversion en radian pour la fonction cos de math.h
        float debut_rad = debut_arc*2*(3.14159265/360);
        float fin_rad = fin_arc*2*(3.14159265/360);

        // on decompose l'arc en pas_de_la_fonction +1 points.
        int Nomb_sub = 100;
        float pas_sub = (fin_rad - debut_rad)/Nomb_sub;
        //on x croissant y decroissant
        //on initialise le premier point.
        ei_point_t centre_arc = {centre.x + cos(debut_rad),centre.y -sin(debut_rad)};
        ei_linked_point_t* cellule_cour = malloc(sizeof(ei_linked_point_t));
        (cellule_cour -> point).x = centre.x + rayon*cos((float)(debut_rad));
        (cellule_cour -> point).y = centre.y - rayon*sin(debut_rad);
        arc = cellule_cour;
        int k;
        for (k=1; k<=Nomb_sub; k++){
                ei_linked_point_t* cellule_suiv =  malloc(sizeof(ei_linked_point_t));
                (cellule_suiv -> point).x = centre.x + rayon*cos((float)(debut_rad + pas_sub*k));
                (cellule_suiv -> point).y = centre.y - rayon*sin(debut_rad + pas_sub*k);
                cellule_suiv -> next = NULL;
                cellule_cour -> next = cellule_suiv;
                cellule_cour = cellule_suiv;
        }
        return arc;
      }



ei_linked_point_t* rounded_frame (ei_rect_t rectangle,
                                  int rayon,
                                  ei_bouton_param_t param){
        ei_linked_point_t* rectangle_fait;
        int plus_court_cote;
        int largeur = rectangle.size.width;
        int hauteur = rectangle.size.height;
        plus_court_cote = min(largeur,hauteur);
        int abscisse_d = rectangle.top_left.x + largeur - rayon;
        int abscisse_g = rectangle.top_left.x + rayon;
        int ordonne_b = rectangle.top_left.y + hauteur - rayon;
        int ordonne_h = rectangle.top_left.y + rayon;
        ei_point_t centre_haut_gauche = {abscisse_g ,ordonne_h};
        ei_point_t centre_haut_droit = {abscisse_d, ordonne_h};
        ei_point_t centre_bas_droit = {abscisse_d,ordonne_b};
        ei_point_t centre_bas_gauche = {abscisse_g,ordonne_b };
        ei_linked_point_t* arc_haut_gauche;
        ei_linked_point_t* arc_haut_droit;
        ei_linked_point_t* arc_bas_droit;
        ei_linked_point_t* arc_bas_gauche;
        ei_linked_point_t* cellule_cour;
        if (param == ei_bouton_whole ){
                arc_haut_gauche = arc(centre_haut_gauche,rayon,180,90);
                arc_haut_droit = arc(centre_haut_droit,rayon,90,0);
                arc_bas_droit = arc (centre_bas_droit,rayon,0,-90);
                arc_bas_gauche = arc(centre_bas_gauche,rayon,-90,-180);
                cellule_cour = arc_haut_gauche;
                rectangle_fait = cellule_cour;

                while (cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                cellule_cour -> next = arc_haut_droit;
                while (cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                cellule_cour -> next = arc_bas_droit;
                while (cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                cellule_cour -> next = arc_bas_gauche;
                while (cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                return(rectangle_fait);
        }
        ei_linked_point_t* chemin_du_centre_val = chemin_du_centre(rectangle,largeur,hauteur,plus_court_cote, centre_haut_droit);
        // on peut factoriser ce code... navigation pour while
        // navigation chemin centre pour les deux demi parts.
        if (param == ei_bouton_bot){
                arc_bas_droit = arc (centre_bas_droit,rayon,-90,0);
                arc_haut_droit = arc(centre_haut_droit,rayon,0,45);
                arc_bas_gauche = arc(centre_bas_gauche,rayon,-135,-90);
                cellule_cour = arc_bas_droit;
                rectangle_fait = cellule_cour;
                while(cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                cellule_cour -> next = arc_haut_droit;
                while(cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                // SOUCIS ICI
                // je dois donner la liste de points pour le chemin
                //et quand j'en sors il faut donner le pointeur vers l'arc du bas
                cellule_cour -> next = chemin_du_centre_val;
                while (cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                cellule_cour -> next = arc_bas_gauche;
                while (cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                return rectangle_fait;
        }
        if (param == ei_bouton_top){
                arc_haut_gauche = arc(centre_haut_gauche,rayon,180,90);
                arc_haut_droit = arc(centre_haut_droit,rayon,90,45);
                arc_bas_gauche = arc(centre_bas_gauche,rayon,-135,-180);
                cellule_cour = arc_haut_gauche;
                rectangle_fait = cellule_cour;
                while(cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                cellule_cour -> next = arc_haut_droit;
                while(cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                cellule_cour -> next = chemin_du_centre_val;
                while (cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                cellule_cour -> next = arc_bas_gauche;
                while (cellule_cour -> next ){
                        cellule_cour = cellule_cour -> next;
                }
                return rectangle_fait;

        }

}


int min(int a,int b)
{
        if(a>=b)
        return b;
        else
        return a;
}

ei_linked_point_t* chemin_du_centre(ei_rect_t rectangle,
                                    int largeur,
                                    int hauteur,
                                    int plus_court_cote,
                                    ei_point_t centre_haut_droit)
{
        // ei_linked_point_t* chemin_du_centre_val = malloc(sizeof(ei_linked_point_t));
        ei_linked_point_t* point_du_haut = malloc(sizeof(ei_linked_point_t));
        ei_linked_point_t* point_du_bas = malloc(sizeof(ei_linked_point_t));
        (point_du_haut -> point).x = rectangle.top_left.x + largeur - 0.5*plus_court_cote;
        (point_du_haut -> point).y = rectangle.top_left.y + 0.5*plus_court_cote;
        point_du_haut -> next = point_du_bas;
        point_du_bas -> point.x = rectangle.top_left.x + 0.5*plus_court_cote;
        point_du_bas -> point.y = rectangle.top_left.y + hauteur - 0.5*plus_court_cote;
        // chemin_du_centre_val -> point = centre_haut_droit;
        // chemin_du_centre_val -> next = point_du_haut;
        point_du_bas -> next = NULL;
        return point_du_haut;
}

void button_drawfunc (struct ei_widget_t* widget,
                      ei_surface_t        surface,
                      ei_surface_t   pick_surface,
                      ei_rect_t*          clipper)
{
        ei_rect_t rectangle = widget -> screen_location;
        ei_fill(surface, ((ei_bouton)));
}

void* ei_button_allocfunc_t()
{
        ei_button_t* widbutton = calloc(1, sizeof(ei_button_t));
        widbutton -> color = calloc(1, sizeof(ei_color_t));
        widbutton -> border_width = calloc(1, sizeof(int));
        widbutton -> corner_radius = calloc(1, sizeof(int));
        widbutton -> relief = calloc(1, sizeof(ei_relief_t));
        widbutton -> text = calloc(1, sizeof(char*));
        widbutton -> text_font = calloc(1, sizeof(ei_font_t));
        widbutton -> text_color = calloc(1, sizeof(ei_color_t));
        widbutton -> text_anchor = calloc(1, sizeof(ei_anchor_t));
        widbutton -> img = calloc(1, sizeof(ei_surface_t));
        widbutton -> img_rect = calloc(1, sizeof(ei_rect_t*));
        widbutton -> img_anchor = calloc(1, sizeof(ei_anchor_t));
        widbutton -> callback = calloc(1, sizeof(ei_callback_t));
        widbutton -> user_param = calloc(1, sizeof(void*));
        return widbutton;
}

void ei_button_drawfunc_t (struct ei_widget_t*  widget,
                            ei_surface_t        surface,
                            ei_surface_t        pick_surface,
                            ei_rect_t*          clipper)
{
        ei_rect_t rectangle = widget -> screen_location;
        ei_fill(surface, ((ei_button_t*)widget -> color), &rectangle);
        //TODO : c'est pas le bon draw
}

void ei_button_releasefunc_t(struct ei_widget_t* widget)
{
        free(((ei_button_t*)widget) -> color);
        free(((ei_button_t*)widget) -> border_width);
        free(((ei_button_t*)widget) -> corner_radius);
        free(((ei_button_t*)widget) -> relief);
        free(((ei_button_t*)widget) -> text);
        free(((ei_button_t*)widget) -> text_font);
        free(((ei_button_t*)widget) -> text_color);
        free(((ei_button_t*)widget) -> text_anchor);
        free(((ei_button_t*)widget) -> img);
        free(((ei_button_t*)widget) -> img_rect);
        free(((ei_button_t*)widget) -> img_anchor);
        free(((ei_button_t*)widget) -> callback);
        free(((ei_button_t*)widget) -> user_param);
}

void ei_button_setdefaultsfunc_t(struct ei_widget_t* widget)
{
        ei_relief_t default_relief = k_default_button_border_width;
        int default_radius = k_default_button_corner_radius;
        ei_color_t default_color = ei_default_background_color;
        ei_color_t text_defaut_color = ei_font_default_color;
        ei_relief_t relief = ei_relief_raised;
        ei_anchor_t anchor = ei_anc_center;
        ((ei_button_t*)widget) -> text = NULL;
        ((ei_button_t*)widget) -> border_width = &k;
        ((ei_button_t*)widget) -> relief = &default_relief;
        ((ei_button_t*)widget) -> color = &default_color;
        ((ei_button_t*)widget) -> text_font = &ei_default_font;
        ((ei_button_t*)widget) -> text_color = &text_defaut_color;
        ((ei_button_t*)widget) -> text_anchor = &anchor;
        ((ei_button_t*)widget) -> img = NULL;
        ((ei_button_t*)widget) -> img_rect = NULL;
        ((ei_button_t*)widget) -> img_anchor = &anchor;
        ((ei_button_t*)widget) -> callback = NULL;
        ((ei_button_t*)widget) -> user_param = NULL;
        widget -> requested_size = ei_size_zero();
}
