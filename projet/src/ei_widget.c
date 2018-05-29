#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ei_widget.h"
#include "ei_frame.h"
#include "ei_widgetclass.h"
#include "ei_application.h"
#include "ei_button.h"
#include "ei_utils.h"

extern ei_widgetclass_t* CLASSES;

ei_widget_t*		ei_widget_create		(ei_widgetclass_name_t	class_name,
							 ei_widget_t*		parent)
{
				ei_widgetclass_t* widgetclass = ei_widgetclass_from_name(class_name);
				ei_widget_t* new_widget = (ei_widget_t*)(widgetclass->allocfunc());
				widgetclass->setdefaultsfunc(new_widget);
				new_widget -> parent = parent;
				if (parent != NULL) {
								new_widget -> parent -> children_head = new_widget;
				}
				new_widget -> wclass = widgetclass;
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
		if (color != NULL)	{
				frame -> color = color;
		}
		else if (frame -> color == NULL) {
				frame -> color = &ei_default_background_color;
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
		else if (frame -> relief == NULL){
				frame -> relief = ei_relief_none;
		}
		if (text != NULL)	{
				frame -> text = text;
				frame -> image = NULL;
		}
		if (text_font != NULL)	{
				frame -> font = text_font;
		}
		else if (frame -> font == NULL)	{
				frame -> font = &ei_default_font;
		}
		if (text_color != NULL)	{
				frame -> color_text = text_color;
		}
		else if (frame -> color_text == NULL) {
				frame -> color_text = &ei_font_default_color;
		}
		if (text_anchor != NULL)	{
				frame -> anchor_text = text_anchor;
		}
		else if (frame -> anchor_text == NULL)	{
				ei_anchor_t anchor_ref_text = ei_anc_center;
				frame -> anchor_text = &anchor_ref_text;
		}
		if (img != NULL)	{
				frame -> image = img;
				frame -> text = NULL;
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
										// SEGMENTATION FAULT
										// getchar();
										ei_size_t surface_minimum = hw_surface_get_size(*(frame->image));
										// getchar();// C'EST LA
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
		widget -> content_rect = &(widget -> screen_location);
		ei_app_invalidate_rect(&(widget -> screen_location));
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
	 	/* pour les parametres par défauts :
	 	*		Parameters obey the "default" protocol: if a parameter is "NULL" and it has never
	 	*		been defined before, then a default value should be used (default values are
	 	*		specified for each parameter). If the parameter is "NULL" but was defined on a
	 	*		previous call, then its value must not be changed.
	 	*/
 		ei_button_t* button = (ei_button_t*)widget;
 		if ((img != NULL) && (text != NULL)){
		printf("attention monsieur le programmeur, il ne faut pas une image et un texte");
			exit(1000);
		}
		if (color != NULL)	{
				button -> color = color;
		}
		else if (button -> color == NULL) {
				button -> color = &ei_default_background_color;
		}
		if (border_width != NULL)	{
						button -> border_width = border_width;
		}
		else if (button -> border_width == NULL){
						button -> border_width = &k_default_button_border_width;
		}
		if (corner_radius != NULL)	{
						button -> corner_radius = corner_radius;
		}
		else if (button -> corner_radius == NULL){
						button -> corner_radius = &k_default_button_corner_radius;
		}
		if (relief != NULL)	{
				button -> relief = relief;
		}
		else if (button -> relief == NULL){
				ei_relief_t def_relief = ei_relief_raised;
				button -> relief = &def_relief;
		}
		if (text != NULL)	{
				button -> text = text;
				button -> img = NULL;
		}
		if (text_font != NULL)	{
				button -> text_font = text_font;
		}
		else if (button -> text_font == NULL)	{
				button -> text_font = &ei_default_font;
		}
		if (text_color != NULL)	{
				button -> text_color = text_color;
		}
		else if (button -> text_color == NULL) {
				button -> text_color = &ei_font_default_color;
		}
		if (text_anchor != NULL)	{
				button -> text_anchor = text_anchor;
		}
		else if (button -> text_anchor == NULL)	{
				ei_anchor_t anchor_ref_text = ei_anc_center;
				button -> text_anchor = &anchor_ref_text;
		}
		if (img != NULL)	{
				button -> img = img;
				button -> text = NULL;
		}
		if (img_rect != NULL)	{
				button -> img_rect = img_rect;
		}
		if (img_anchor != NULL)	{
						button -> img_anchor = img_anchor;
		}
		else if (button -> img_anchor == NULL) {
						ei_anchor_t anchor_ref_img = ei_anc_center;
						button -> img_anchor = &anchor_ref_img;
					}
		if (requested_size != NULL) {
						widget -> requested_size = *requested_size;
		}
		else{
						if (button -> img != NULL){
										// SEGMENTATION FAULT
										// getchar();
										ei_size_t surface_minimum = hw_surface_get_size(*(button->img));
										// getchar();// C'EST LA
										surface_minimum.width += 2* (*border_width);
										surface_minimum.height += 2* (*border_width);
										widget -> requested_size = surface_minimum;
						}
						if (button -> text != NULL){
										ei_surface_t surface_text;
										surface_text = hw_text_create_surface(*(button -> text), button -> text_font , *(button -> text_color));
										ei_size_t surface_minimum = hw_surface_get_size(surface_text);
										surface_minimum.width += 2* (*border_width);
										surface_minimum.height += 2* (*border_width);
										widget -> requested_size = surface_minimum;
						}
		}
		//TODO : EVENT HANDLING
		widget -> content_rect = &(widget -> screen_location);
		ei_app_invalidate_rect(&(widget -> screen_location));
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
