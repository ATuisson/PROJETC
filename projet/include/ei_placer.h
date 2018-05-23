/**
 *  @file	ei_placer.h
 *  @brief	absolute and relative placement regarding parent widget
 *
 *  \author
 *  Created by François Bérard on 18.12.11.
 *  Copyright 2011 Ensimag. All rights reserved.
 *
 */

#ifndef EI_PLACER_H
#define EI_PLACER_H

typedef struct ei_placer_t {
        ei_geometry_param_t*        manager;
        ei_anchor_t*        anchor;
        int*        x;
        int*        y;
        int*        width;
        int*        height;
        float*      rel_x;
        float*      rel_y;
        float*      rel_width;
        float*      rel_height;
} ei_placeur_t;


/**
 * \brief	A function that runs the placeur computation for this widget. This may trigger
 *		placer computation for this widget's parent and the other children of the parent.
 *
 * @param	widget		The widget instance for which to compute placeur.
 */
void ei_placeur_runfunc_t (ei_widget_t* widget);

/**
 * \brief	A function called when a widget ceases to be managed by placer.
 *		Most of the work is done in \ref ei_geometrymanager_unmap. This function hook is
 *		only provided to trigger recomputation when the disappearance of a widget has an
 *		effect on the geometry of other widgets.
 *
 * @param	widget		The widget instance that must be forgotten by the placeur.
 */
void ei_placeur_releasefunc_t (ei_widget_t* widget);
#endif
