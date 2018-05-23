#include <stdio.h>
#include <stdlib.h>
#include "ei_widget.h"
#include "ei_frame.h"

ei_color_t ei_default_background_color_user = ei_default_background_color;
int ei_default_border_width_user = 0;
ei_relief_t ei_relief_default_user = ei_relief_none;
ei_font_t ei_default_font_user = ei_default_font;
ei_color_t ei_default_font_color_user = ei_font_default_color;
ei_anchor_t text_anchor_default_user = ei_anc_center;
ei_anchor_t img_anchor_default_user = ei_anc_center;


ei_widget_t*		ei_widget_create		(ei_widgetclass_name_t	class_name,
							 ei_widget_t*		parent)
{

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
		// if (requested_size = NULL) {
		//
		// }
		if (requested_size != NULL)	{
						widget -> requested_size = *requested_size;
		}
		if (color = NULL) {
			  		frame -> color = ei_default_background_color_user
		}
		else 	{
						frame -> color = color;
						ei_default_background_color_user = *color;
		}
		if (border_width != NULL)	{
						frame -> border_width = border_width;
						ei_default_border_width_user = *border_width;
		}
		else {
						frame -> border_width = &ei_default_border_width_user;
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
