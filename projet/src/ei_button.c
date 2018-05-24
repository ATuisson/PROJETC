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
        float debut_rad = debut_arc*2*(3,14159265/360);
        float fin_rad = fin_arc*2*(3,14159265/360);

        // on decompose l'arc en pas_de_la_fonction +1 points.
        int Nomb_sub = 100;
        int pas_sub = (fin_rad - debut_rad)/Nomb_sub;
        //on x croissant y decroissant
        //on initialise le premier point.
        ei_point_t point_cour = {centre.x + cos(debut_arc),centre.y -sin(debut_arc)};
        ei_linked_point_t* cellule_cour;
        arc = cellule_cour;
        cellule_cour -> point = point_cour;
        ei_linked_point_t* cellule_suiv;
        int k;
        //while ((point_cour.x != centre.x + cos(fin_arc)) && (point_cour.y != centre.y + sin(fin_arc))){
        for (k=0; k==Nomb_sub; k++){
                point_cour.x = centre.x + cos(debut_rad + pas_sub*k);
                point_cour.y = centre.y - sin(debut_rad + pas_sub*k);
                cellule_suiv -> point = point_cour;
                cellule_cour -> next = cellule_suiv;
                cellule_cour = cellule_suiv;
        }
}
