#include "ei_widgetclass.h"
#include "ei_frame.h"

ei_widgetclass_t* CLASSES;

void insertion_classe_enq (ei_widgetclass_t* widgetclass);



static inline char*	ei_widgetclass_stringname	(ei_widgetclass_name_t name)
{

}

void			ei_widgetclass_register		(ei_widgetclass_t* widgetclass)
{
				widgetclass -> next = NULL;
				if (CLASSES == NULL) {
								CLASSES = widgetclass
				}
				else {
								ei_widgetclass_t* current = CLASSES;
								while(current -> next != NULL) {
												current = current -> next;
								}
								current -> next = widgetclass;
				}
}

ei_widgetclass_t*	ei_widgetclass_from_name	(ei_widgetclass_name_t name)
{

}

void			ei_frame_register_class 	()
{
				ei_widgetclass_t frame;
				frame.ei_widgetclass_name_t = "frame";
				frame.allocfunc = &ei_frame_allocfunc_t;
				frame.releasefunc = &ei_frame_releasefunc_t;
				frame.drawfunc = &ei_frame_drawfunc_t;
				frame.setdefaultsfunc = &ei_frame_setdefaultsfunc_t;
				ei_widgetclass_register(&frame);
}

void			ei_button_register_class 	()
{

}

void			ei_toplevel_register_class 	()
{

}

static inline char*	ei_widgetclass_stringname	(ei_widgetclass_name_t name)
{
	return (char*)name;
}
