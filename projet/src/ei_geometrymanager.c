#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include"ei_geometrymanager.h"
#include"ei_placer.c"
#include"ei_types.h"
#include"ei_utils.h"
#include"ei_application.h"

ei_geometrymanager_t* MANAGERS;
ei_geometrymanager_t PLACER;

void			ei_geometrymanager_register	(ei_geometrymanager_t* geometrymanager)
{
		geometrymanager -> next = NULL;
		if (MANAGERS == NULL) {
					MANAGERS = geometrymanager;
		}
		else {
					ei_geometrymanager_t* current = MANAGERS;
					while(current -> next != NULL) {
							current = current -> next;
					}
					current -> next = geometrymanager;
		}
}

ei_geometrymanager_t*	ei_geometrymanager_from_name	(ei_geometrymanager_name_t name)
{
		ei_geometrymanager_t* current = MANAGERS;
		if (current == NULL) {
				printf("Pas de gestionnaire de géométrie enregistré");
				exit(10);
		}
		while (strcmp(current -> name, name) != 0)	{
				current = current -> next;
				if (current == NULL)	{
						printf("Gestionnaire de géométrie pas enregistré");
						exit(12);
				}
		}
		return current;
}

/**
 * \brief	Tell the geometry manager in charge of a widget to forget it. This removes the
 *		widget from the screen. If the widget is not currently managed, this function
 *		returns silently.
 *		Side effects:
 *		<ul>
 *			<li> the \ref ei_geometrymanager_releasefunc_t of the geometry manager in
 *				charge of this widget is called, </li>
 *			<li> the geom_param field of the widget is freed, </li>
 *			<li> the current screen_location of the widget is invalided (which will
 *				trigger a redraw), </li>
 *			<li> the screen_location of the widget is reset to 0. </li>
 *		</ul>
 *
 * @param	widget		The widget to unmap from the screen.
 */
void			ei_geometrymanager_unmap	(ei_widget_t*		widget)
{
				if (widget -> geom_params == NULL){
						return;
				}
				ei_geometrymanager_t manager = *(widget -> geom_params -> manager);
				manager.releasefunc(widget);
				free(widget -> geom_params);
				ei_app_invalidate_rect(&(widget -> screen_location));
				widget -> screen_location = ei_rect_zero();
}

void 			ei_register_placer_manager 	()
{
				strcpy(PLACER.name, "placer");
				PLACER.runfunc = &ei_placer_runfunc_t;
				PLACER.releasefunc = &ei_placer_releasefunc_t;
				ei_geometrymanager_register(&PLACER);
}

/**
 * \brief	Configures the geometry of a widget using the "placer" geometry manager.
 * 		If the widget was already managed by another geometry manager, then it is first
 *		removed from the previous geometry manager.
 * 		If the widget was already managed by the "placer", then this calls simply updates
 *		the placer parameters: arguments that are not NULL replace previous values.
 * 		When the arguments are passed as NULL, the placer uses default values (detailed in
 *		the argument descriptions below). If no size is provided (either absolute or
 *		relative), then the requested size of the widget is used, i.e. the minimal size
 *		required to display its content.
 *
 * @param	widget		The widget to place.
 * @param	anchor		How to anchor the widget to the position defined by the placer
 *				(defaults to ei_anc_northwest).
 * @param	x		The absolute x position of the widget (defaults to 0) in the
 *				parent's reference.
 * @param	y		The absolute y position of the widget (defaults to 0) in the
 *				parent's reference.
 * @param	width		The absolute width for the widget (defaults to the requested width
 *				of the widget if rel_width is NULL, or 0 otherwise).
 * @param	height		The absolute height for the widget (defaults to the requested height
 *				of the widget if rel_height is NULL, or 0 otherwise).
 * @param	rel_x		The relative x position of the widget: 0.0 corresponds to the left
 *				side of the parent, 1.0 to the right side (defaults to 0.0).
 * @param	rel_y		The relative y position of the widget: 0.0 corresponds to the top
 *				side of the parent, 1.0 to the bottom side (defaults to 0.0).
 * @param	rel_width	The relative width of the widget: 0.0 corresponds to a width of 0,
 *				1.0 to the width of the parent (defaults to 0.0).
 * @param	rel_height	The relative height of the widget: 0.0 corresponds to a height of 0,
 *				1.0 to the height of the parent (defaults to 0.0).
 */
void			ei_place			(ei_widget_t*		widget,
							 ei_anchor_t*		anchor,
							 int*			x,
							 int*			y,
							 int*			width,
							 int*			height,
							 float*			rel_x,
							 float*			rel_y,
							 float*			rel_width,
							 float*			rel_height)
{
		if (widget -> geom_params == NULL){
						///< on associe le placeur au widget.
						ei_placer_param_t* placeur_params = calloc(1,sizeof(ei_placer_param_t));
						placeur_params -> anchor = NULL;
						placeur_params -> x = NULL;
						placeur_params -> y = NULL;
						placeur_params -> width = NULL;
						placeur_params -> height = NULL;
						placeur_params -> rel_x = NULL;
						placeur_params -> rel_y = NULL;
						placeur_params -> rel_width = NULL;
						placeur_params -> rel_height = NULL;
						(placeur_params -> param_generic).manager = &PLACER;
						widget -> geom_params = (ei_geometry_param_t*)placeur_params;
		}
		if (strcmp((char*)(widget -> geom_params -> manager -> name), "placer") != 0){
						ei_geometrymanager_unmap(widget); ///< on retire l'ancien geometrymanager
						///< on associe le placeur_params au widget.
						ei_placer_param_t* placeur_params = calloc(1,sizeof(ei_placer_param_t));
						placeur_params -> anchor = NULL;
						placeur_params -> x = NULL;
						placeur_params -> y = NULL;
						placeur_params -> width = NULL;
						placeur_params -> height = NULL;
						placeur_params -> rel_x = NULL;
						placeur_params -> rel_y = NULL;
						placeur_params -> rel_width = NULL;
						placeur_params -> rel_height = NULL;
						(placeur_params -> param_generic).manager = &PLACER;
						widget -> geom_params = (ei_geometry_param_t*)placeur_params;
		}
		// on attribue les chans aux parametres du placeur
		ei_placer_param_t* placer = (ei_placer_param_t*)(widget->geom_params);
		if (anchor != NULL)	{
				if (placer->anchor == NULL){
						placer -> anchor = malloc(sizeof(ei_anchor_t));
				}
				placer -> anchor = anchor;
		}
		else if (placer -> anchor == NULL){
				ei_anchor_t* ancre = calloc(1, sizeof(ei_anchor_t));
				*ancre = ei_anc_northwest;
				placer -> anchor = ancre;
		}
		if (x != NULL)	{
				if (placer->x == NULL){
						placer -> x = malloc(sizeof(int));
				}
				placer -> x = x;
		}
		else if (placer -> x == NULL)	{
				int* zero = malloc(sizeof(int));
				*zero = 0;
				placer -> x = zero;
		}
		if (y != NULL)	{
				if (placer->y == NULL){
						placer -> y = malloc(sizeof(int));
				}
				placer -> y = y;
		}
		else if (placer -> y == NULL)	{
				int* zero = malloc(sizeof(int));
				*zero = 0;
				placer -> y = zero;
		}
		if (width != NULL)	{
				if (placer->width == NULL){
						placer -> width = malloc(sizeof(int));
				}
				placer -> width = width;
		}
		else if (placer -> rel_width == NULL)	{
				int* largeur = malloc(sizeof(int));
				*largeur = (widget -> requested_size).width;
				placer -> width = largeur;
		}
		else	{
				if (placer->width == NULL){
						placer -> width = malloc(sizeof(int));
				}
				int zero = 0;
				placer -> width = &zero;
		}
		if (height != NULL)	{
				if (placer->height == NULL){
						placer -> height = malloc(sizeof(int));
				}
				placer -> height = height;
		}
		else if (placer -> rel_height == NULL)	{
				int* hauteur = malloc(sizeof(int));
				*hauteur = (widget -> requested_size).height;
				placer -> height = hauteur;
		}
		else	{
				if (placer->height == NULL){
						placer -> height = malloc(sizeof(int));
				}
				int zero = 0;
				placer -> height = &zero;
		}
		if (rel_x != NULL)	{
				if (placer->rel_x == NULL){
						placer -> rel_x = malloc(sizeof(float));
				}
				placer -> rel_x = rel_x;
		}
		else if (placer -> rel_x == NULL)	{
				float zero = 0.0;
				placer -> rel_x = &zero;
		}
		if (rel_y != NULL)	{
				if (placer->rel_x == NULL){
						placer -> rel_x = malloc(sizeof(float));
				}
				placer -> rel_y = rel_y;
		}
		else if (placer -> rel_y == NULL)	{
				float zero = 0.0;
				placer -> rel_y = &zero;
		}
		if (rel_width != NULL)	{
				if (placer->rel_width == NULL){
						placer -> rel_width = malloc(sizeof(float));
				}
				placer -> rel_width = rel_width;
		}
		else if (placer -> rel_width == NULL)	{
				float zero = 0.0;
				placer -> rel_width = &zero;
		}
		if (rel_height != NULL)	{
				if (placer->rel_height == NULL){
						placer -> rel_height = malloc(sizeof(float));
				}
				placer -> rel_height = rel_height;
		}
		else if (placer -> rel_height == NULL)	{
				float zero = 0.0;
				placer -> rel_height = &zero;
		}
		widget -> geom_params -> manager -> runfunc(widget);
}
