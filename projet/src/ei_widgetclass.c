#include <stdlib.h>
#include <string.h>

#include "ei_widgetclass.h"
#include "ei_frame.h"

ei_widgetclass_t* CLASSES = NULL;

void			ei_widgetclass_register		(ei_widgetclass_t* widgetclass)
{
				widgetclass -> next = NULL;
				if (CLASSES == NULL) {
								CLASSES = widgetclass;
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
				ei_widgetclass_t* current = CLASSES;
				if (current == NULL) {
								printf("Pas de classes enregistrée");
								exit(5);
				}
				while (strcmp(current -> name, name) != 0) {
								current = current -> next;
								if (current == NULL) {
												printf("Classe pas enregistrée");
												exit(7);
								}
				}
				return current;
}

void			ei_frame_register_class 	()
{
				ei_widgetclass_t frame;
				// ei_widgetclass_name_t name_class;
				// name_class[0] = 'f';
				// name_class[1] = 'r';
				// name_class[2] = 'a';
				// name_class[3] = 'm';
				// name_class[4] = 'e';
				strcpy(frame.name, "frame");
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
