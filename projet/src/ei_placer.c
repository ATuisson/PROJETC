#include <stdlib.h>
#include "ei_frame.h"
#include "ei_placer.h"
#include "ei_utils.h"
#include "ei_application.h"
/**
 * \brief	A function that runs the placeur computation for this widget. This may trigger
 *		placeur computation for this widget's parent and the other children of the parent.
 *
 * @param	widget		The widget instance for which to compute placeur.
 */
void ei_placer_runfunc_t (ei_widget_t* widget){
        ei_placer_t* placeur = (ei_placer_t*)(widget -> geom_params);
        // on change le screen location selon les parametres
        //TODO : gérer le placement relatif, les collisions, l'ancrage
        ei_rect_t rect_parent = (widget -> parent).screen_location;
        ei_point_t new_origin = ei_point(placeur -> x, placeur -> y);
        ei_size_t new_size = ei_size(placeur -> width, placeur -> height);
        widget->screen_location = {ei_point_add(new_origin, rect_parent -> top_left), new_size};
        ei_app_invalidate_rect(&(widget->screen_location));
}

/**
 * \brief	A function called when a widget ceases to be managed by placeur.
 *		Most of the work is done in \ref ei_geometrymanager_unmap. This function hook is
 *		only provided to trigger recomputation when the disappearance of a widget has an
 *		effect on the geometry of other widgets.
 *
 * @param	widget		The widget instance that must be forgotten by the placeur.
 */
void ei_placer_releasefunc_t (ei_widget_t* widget){
        ei_placer_t* placeur = (ei_placer_t*)(widget -> geom_params);
        placeur -> manager = NULL;
        free(placeur -> anchor);
        free(placeur -> x);
        free(placeur -> y);
        free(placeur -> width);
        free(placeur -> height);
        free(placeur -> rel_x);
        free(placeur -> rel_y);
        free(placeur -> rel_width);
        free(placeur -> rel_height);
        free(placeur);
}
