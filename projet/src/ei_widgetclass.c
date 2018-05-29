#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ei_widgetclass.h"
#include "ei_frame.h"

ei_widgetclass_t* CLASSES;
ei_widgetclass_t FRAME;
ei_w

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
				strcpy(FRAME.name, "frame");
				FRAME.allocfunc = &ei_frame_allocfunc_t;
				FRAME.releasefunc = &ei_frame_releasefunc_t;
				FRAME.drawfunc = &ei_frame_drawfunc_t;
				FRAME.setdefaultsfunc = &ei_frame_setdefaultsfunc_t;
				ei_widgetclass_register(&FRAME);
}

void			ei_button_register_class 	()
{

}

void			ei_toplevel_register_class 	()
{

}
