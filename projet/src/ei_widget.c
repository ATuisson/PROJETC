#include <stdio.h>
#include <stdlib.h>
#include "ei_widget.h"
#include "ei_frame.h"

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
		ei_frame_t* frame = (ei_frame_t*)widget;
		if (requested_size != NULL)	{
				widget -> requested_size = *requested_size;
		}
		if (color != NULL)	{
				frame -> color = color;
		}
		if (border_width != NULL)	{
				frame -> border_width = border_width;
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
