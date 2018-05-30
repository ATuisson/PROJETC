/**
 * @file	ei_callback.h
 *
 * @brief 	Definition of all callback functions
 *
 *  Created by Lucas Thomas et Basile on 28/05/18.
 */

#ifndef EI_CALLBACK_H
#define EI_CALLBACK_H

#include <stdlib.h>
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "string.h"
#include "ei_button.h"

/**
 * @brief	Fonction de type callback. Modifie le relief d'un bouton en "sunk" si
 *        ce bouton est en dessous de la souris lors de l'événement "ei_ev_mouse_buttondown".
 *
 * @param	widget		The widget for which the event was generated.
 * @param	event		The event containing all its parameters (type, etc.)
 * @param	user_param	The user parameters that was provided by the caller when registering
 *				this callback.
 *
 * @return			A boolean telling if the event was consumed by the callback or not.
 */
ei_bool_t enfonce_bouton_souris(ei_widget_t* widget, struct ei_event_t* event, void* user_param);

/**
 * @brief	Fonction de type callback. Modifie le relief d'un bouton en "raised" si
 *        ce bouton est en dessous de la souris lors de l'événement "ei_ev_mouse_buttonup".
 *
 * @param	widget		The widget for which the event was generated.
 * @param	event		The event containing all its parameters (type, etc.)
 * @param	user_param	The user parameters that was provided by the caller when registering
 *				this callback.
 *
 * @return			A boolean telling if the event was consumed by the callback or not.
 */
ei_bool_t relache_bouton_souris(ei_widget_t* widget, struct ei_event_t* event, void* user_param);

#endif
