#include"ei_geometrymanager.h"
#include"ei_placer.h"
#include"ei_types.h"
#include<stdlib.h>
#include<string.h>

ei_geometrymanager_t* MANAGERS = NULL;
ei_geometrymanager_t* PLACER = NULL;

void			ei_geometrymanager_register	(ei_geometrymanager_t* geometrymanager)
{
		geometrymanager -> next = NULL;
		if (MANAGERS == NULL) {
					MANAGERS = geometrymanager;
		}
		else {
					ei_geometrymanager_t* current = CLASSES;
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
}

void			ei_geometrymanager_unmap	(ei_widget_t*		widget)
{

}

void 			ei_register_placer_manager 	()
{

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
		//TODO : cas ou le widget est associe a un autre manager
		ei_placer_t* placer = (ei_placer_t*)(widget->geom_params);
		if (anchor != NULL)	{
				placer -> anchor = anchor;
		}
		else if (placer -> anchor == NULL){
				ei_anchor_t ancre = ei_anc_northwest;
				placer -> anchor = &ancre;
		}
		if (x != NULL)	{
				placer -> x = x;
		}
		else if (placer -> x == NULL)	{
				int zero = 0;
				placer -> x = &zero;
		}
		if (y != NULL)	{
				placer -> y = y;
		}
		else if (placer -> y == NULL)	{
				int zero = 0;
				placer -> y = &zero;
		}
		if (width != NULL)	{
				placer -> width = width;
		}
		else if (placer -> rel_width == NULL)	{
				placer -> width = &((widget -> requested_size).width);
		}
		else	{
				int zero = 0;
				placer -> width = &zero;
		}
		if (height != NULL)	{
				placer -> height = height;
		}
		else if (placer -> rel_height == NULL)	{
				placer -> height = &((widget -> requested_size).height);
		}
		else	{
				int zero = 0;
				placer -> height = &zero;
		}
		if (rel_x != NULL)	{
				placer -> rel_x = rel_x;
		}
		else if (placer -> rel_x == NULL)	{
				float zero = 0.0;
				placer -> rel_x = &zero;
		}
		if (rel_y != NULL)	{
				placer -> rel_y = rel_y;
		}
		else if (placer -> rel_y == NULL)	{
				float zero = 0.0;
				placer -> rel_y = &zero;
		}
		if (rel_width != NULL)	{
				placer -> rel_width = rel_width;
		}
		else if (placer -> rel_width == NULL)	{
				float zero = 0.0;
				placer -> rel_width = &zero;
		}
		if (rel_height != NULL)	{
				placer -> rel_height = rel_height;
		}
		else if (placer -> rel_width == NULL)	{
				float zero = 0.0;
				placer -> rel_y = &zero;
		}
}
