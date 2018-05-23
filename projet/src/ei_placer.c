#include "ei_frame.h"
#include <stdlib.h>


/**
 * \brief	A function that runs the placeur computation for this widget. This may trigger
 *		placeur computation for this widget's parent and the other children of the parent.
 *
 * @param	widget		The widget instance for which to compute placeur.
 */
void ei_placeur_runfunc_t (ei_widget_t* widget){

}

/**
 * \brief	A function called when a widget ceases to be managed by placeur.
 *		Most of the work is done in \ref ei_geometrymanager_unmap. This function hook is
 *		only provided to trigger recomputation when the disappearance of a widget has an
 *		effect on the geometry of other widgets.
 *
 * @param	widget		The widget instance that must be forgotten by the placeur.
 */
void ei_placeur_releasefunc_t (ei_widget_t* widget){

}
