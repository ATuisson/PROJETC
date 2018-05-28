
#include <stdlib.h>
#include <math.h>
#include "ei_draw.h"
#include "ei_frame.h"
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
                cellule_cour = arc_bas_gauche;
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
                cellule_cour = arc_bas_gauche -> next;
                while (cellule_cour -> next != NULL){
                        cellule_cour = cellule_cour -> next;
                }
                return rectangle_fait;

        }
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
        ei_linked_point_t* chemin_du_centre_val = malloc(sizeof(ei_linked_point_t));
        ei_linked_point_t* point_du_haut = malloc(sizeof(ei_linked_point_t));
        point_du_haut -> point.x = rectangle.top_left.x + largeur - plus_court_cote;
        point_du_haut -> point.y = rectangle.top_left.y + plus_court_cote;
        ei_linked_point_t* point_du_bas = malloc(sizeof(ei_linked_point_t));
        point_du_haut -> next = point_du_bas;
        point_du_bas -> point.x = rectangle.top_left.x + plus_court_cote;
        point_du_bas -> point.y = rectangle.top_left.y + hauteur - plus_court_cote;
        chemin_du_centre_val -> point = centre_haut_droit;
        chemin_du_centre_val -> next = point_du_haut;
        point_du_bas -> next = NULL;
        return chemin_du_centre_val;
}
