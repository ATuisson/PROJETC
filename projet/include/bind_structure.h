/**
 *  @file	bind_structure.h
 *  @brief	Allows the binding and unbinding of callbacks to events.
 *
 *  \author
 *  Created by Lucas Basile et Thomas on 28.05.18.
 *
 */
#ifndef BIND_STRUCTURE_H
#define BIND_STRUCTURE_H

#include <stdlib.h>
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_event.h"
#include "hw_interface.h"

/**
 * \Structure représentant le lien entre un type d'évènement, un widget/tag, et
 *  le callback associé, et pouvant être chainée
 */
typedef struct bind_structure_t {
        ei_eventtype_t eventtype; ///< Le type d'évènement
        ei_widget_t* widget; ///< le widget concerné par l'évènement
        ei_tag_t tag; ///< le tag associé à une classe de widget (peut-être "all", "button" ou "top-level")
        ei_callback_t callback; ///< Fonction traitant à appelé lors de l'évènement.
        void* user_param; ///< Un paramètre donné par l'utilisateur qui sera passé au callback.
        struct bind_structure_t* next; ///< la structure suivante
} bind_structure_t;

/**
 * @brief	Retourne la couleur associée à un type uint32_t en prenant en compte
 *        l'encodage des couleurs sur la surface.
 *
 * @param	surface		Surface dont on recupère la configuration RGBA.
 *
 * @param id
 *
 * @return			The top-most widget at this location, or NULL if there is no widget
 *				at this location (except for the root widget).
 */
ei_color_t id_to_rgba (ei_surface_t surface, uint32_t* id);

ei_widget_t* recherche_widget(uint32_t id, ei_widget_t* root);

void traitement(struct ei_event_t event);

#endif
