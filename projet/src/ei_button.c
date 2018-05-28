#include <stdlib.h>
#include <math.h>
#include "ei_draw.h"
#include "ei_frame.h"
#include "ei_types.h"
#include "ei_widgetclass.h"
#include "hw_interface.h"
#include "ei_button.h"
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
        int pas_sub = (fin_rad - debut_rad)/Nomb_sub;
        //on x croissant y decroissant
        //on initialise le premier point.
        ei_point_t point_cour = {centre.x + cos(debut_rad),centre.y -sin(debut_rad)};
        ei_linked_point_t* cellule_cour = malloc(sizeof(ei_linked_point_t));
        cellule_cour -> point = point_cour;
        arc = cellule_cour;
        int k;
        //while ((point_cour.x != centre.x + cos(fin_arc)) && (point_cour.y != centre.y + sin(fin_arc))){
        for (k=0; k==Nomb_sub; k++){
                ei_linked_point_t* cellule_suiv =  malloc(sizeof(ei_linked_point_t));
                point_cour.x = centre.x + cos(debut_rad + pas_sub*k);
                point_cour.y = centre.y - sin(debut_rad + pas_sub*k);
                cellule_suiv -> point = point_cour;
                cellule_cour -> next = cellule_suiv;
                cellule_cour = cellule_suiv;
        }
        return arc;
}

ei_linked_point_t* rounded_frame (ei_rect_t rectangle,
                                  int rayon){
        // on doit faire 4 arc en plus des segments droit.
        // les segment requierent que deux points.
        ei_linked_point_t* rectangle_fait;
        // ei_point_t point_cour;
        // point_cour.x = rectangle.top_left.x +rayon;
        // point_cour.y = rectangle.top_left.y;
        // // pour les 4 arcs, il faut faire 4 appels à la fonction arc
        int abscisse_d = rectangle.top_left.x + rectangle.size.width - rayon;
        int abscisse_g = rectangle.top_left.x + rayon;
        int ordonne_b = rectangle.top_left.y + rectangle.size.height - rayon;
        int ordonne_h = rectangle.top_left.y + rayon;
        ei_linked_point_t* arc_haut_gauche;
        ei_point_t centre_haut_gauche = {abscisse_g ,ordonne_h};
        arc_haut_gauche = arc(centre_haut_gauche,rayon,180,90);
        ei_linked_point_t* arc_haut_droit;
        ei_point_t centre_haut_droit = {abscisse_d, ordonne_h};
        arc_haut_droit = arc(centre_haut_droit,rayon,90,0);
        ei_point_t centre_bas_droit = {abscisse_d,ordonne_b};
        ei_linked_point_t* arc_bas_droit;
        arc_bas_droit = arc (centre_bas_droit,rayon,0,-90);
        ei_point_t centre_bas_gauche = {abscisse_g,ordonne_b };
        ei_linked_point_t* arc_bas_gauche;
        arc_bas_gauche = arc(centre_bas_gauche,rayon,-90,-180);
        ei_linked_point_t* cellule_cour;
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
        cellule_cour -> next = arc_haut_gauche;
        return(rectangle_fait);
}
