/**
 * @file    frame.h
 * @brief definition and description of frame class and associated functions
 *
 * \author
 * Created by Thomas, Lucas and Basile on 18.05.2018
 *
 */

#ifndef EI_FRAME_H
#define EI_FRAME_H

#include "ei_widgetclass.h"
#include "ei_widget.h"
#include "ei_types.h"

/**
 * \brief A structure that stores specific information about a frame widget class
 */
typedef struct ei_frame_t {
        ei_widget_t          widget; ///< Structure commune entre tous les widgets
        const ei_color_t*     color; ///< Couleur du cadre
        int*                  border_width; ///< largeur de la bordure du cadre
        ei_relief_t*          relief; ///< Relief du cadre
        char**                text; ///< Chaine de caractère à insérer
        ei_font_t*            font; ///< Police d'écriture
        ei_color_t*           color_text; ///< couleur du texte
        ei_anchor_t*          anchor_text; ///< Ancrage du texte
        ei_surface_t*         image; ///< Eventuelle image à dessiner à la place du texte
        ei_rect_t**           rect; ///< Rectangle correspondant à une sous-partie de l'image
        ei_anchor_t*          anchor_image; ///< Ancrage de l'image
} ei_frame_t;

/**
 * \brief	memory allocation for frame widgetclass structure
 *
 * @return		A block of memory with all bytes set to 0.
 */
void* ei_frame_allocfunc_t ();

/**
 * \brief	memory liberation for frame widgetclass structure
 *
 * @param   widget      the frame to be freed
 */
void ei_frame_releasefunc_t (struct ei_widget_t*    widget);

/**
 * \brief   A function drawing the frame widgetclass
 *
 * @param as the widgetclass_drawfunc_t parameters
 */
void ei_frame_drawfunc_t (struct ei_widget_t*   widget,
                          ei_surface_t  surface,
                          ei_surface_t  pick_surface,
                          ei_rect_t*    clipper);


/**
 * \brief   A function for default values of a class
 *
 * @param as the widgetclass_setdefautlsfunc_t parameters
 */
void ei_frame_setdefaultsfunc_t (struct ei_widget_t*   widget);

#endif
