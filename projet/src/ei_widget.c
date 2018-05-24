#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ei_widget.h"
#include "ei_frame.h"
#include "ei_widgetclass.h"

extern ei_widgetclass_t* CLASSES;

ei_widget_t*		ei_widget_create		(ei_widgetclass_name_t	class_name,
							 ei_widget_t*		parent)
{
				ei_widgetclass_t* current = CLASSES;
				while (strcmp(current -> name, class_name) != 0) {
								current = current -> next;
				}
				ei_widget_t* new_widget = NULL;
}

void			ei_widget_destroy		(ei_widget_t*		widget)
{

}

ei_widget_t*		ei_widget_pick			(ei_point_t*		where)
{

}

void			ei_frame_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 const ei_color_t*	color,
							 int*			border_width,
							 ei_relief_t*		relief,
							 char**			text,
							 ei_font_t*		text_font,
							 ei_color_t*		text_color,
							 ei_anchor_t*		text_anchor,
							 ei_surface_t*		img,
							 ei_rect_t**		img_rect,
							 ei_anchor_t*		img_anchor)
{
	/* pour les parametres par défauts :
	*		Parameters obey the "default" protocol: if a parameter is "NULL" and it has never
	*		been defined before, then a default value should be used (default values are
	*		specified for each parameter). If the parameter is "NULL" but was defined on a
	*		previous call, then its value must not be changed.
	*/
		ei_frame_t* frame = (ei_frame_t*)widget;
		if ((img != NULL) && (text != NULL)){
			printf("attention monsieur le programmeur, il ne faut pas une image et un texte");
			exit(1000);
		}
		if (requested_size != NULL)	{
				widget -> requested_size = *requested_size;
		}
		if (color != NULL)	{
				frame -> color = color;
		}
		if (border_width != NULL)	{
						frame -> border_width = border_width;
		}
		else if (frame -> border_width == NULL){
						int zero = 0;
						frame -> border_width = &zero ;
		}
		if (relief != NULL)	{
				frame -> relief = relief;
		}
		if (text != NULL)	{
				frame -> text = text;
		}
		if (text_font != NULL)	{
				frame -> font = text_font;
		}
		if (text_color != NULL)	{
				frame -> color_text = text_color;
		}
		if (text_anchor != NULL)	{
				frame -> anchor_text = text_anchor;
		}
		if (img != NULL)	{
				frame -> image = img;
		}
		if (img_rect != NULL)	{
				frame -> rect = img_rect;
		}
		if (img_anchor != NULL)	{
						frame -> anchor_image = img_anchor;
		}
		else if (frame -> anchor_image == NULL) {
						ei_anchor_t anchor_ref_img = ei_anc_center;
						frame -> anchor_text = &anchor_ref_img;
					}
		if (requested_size != NULL) {
						widget -> requested_size = *requested_size;
		}
		else{
						if (frame -> image != NULL){
										ei_size_t surface_minimum = hw_surface_get_size(*img);
										surface_minimum.width += 2* (*border_width);
										surface_minimum.height += 2* (*border_width);
										widget -> requested_size = surface_minimum;
						}
						if (frame -> text != NULL){
										ei_surface_t surface_text;
										surface_text = hw_text_create_surface(*(frame -> text), frame -> font , *(frame -> color_text));
										ei_size_t surface_minimum = hw_surface_get_size(surface_text);
										surface_minimum.width += 2* (*border_width);
										surface_minimum.height += 2* (*border_width);
										widget -> requested_size = surface_minimum;
						}
		}
}

void			ei_button_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 const ei_color_t*	color,
							 int*			border_width,
							 int*			corner_radius,
							 ei_relief_t*		relief,
							 char**			text,
							 ei_font_t*		text_font,
							 ei_color_t*		text_color,
							 ei_anchor_t*		text_anchor,
							 ei_surface_t*		img,
							 ei_rect_t**		img_rect,
							 ei_anchor_t*		img_anchor,
							 ei_callback_t*		callback,
							 void**			user_param)
{

}


void			ei_toplevel_configure		(ei_widget_t*		widget,
							 ei_size_t*		requested_size,
							 ei_color_t*		color,
							 int*			border_width,
							 char**			title,
							 ei_bool_t*		closable,
							 ei_axis_set_t*		resizable,
						 	 ei_size_t**		min_size)
{

}
