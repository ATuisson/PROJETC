/**
 *  @file	ei_event.c
 *  @brief	Allows the binding and unbinding of callbacks to events.
 *
 *  \author
 *  Created by Lucas Basile et Thomas on 28.05.18.
 *
 */
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>

 #include "ei_types.h"
 #include "ei_widget.h"
 #include "ei_event.h"
 #include "bind_structure.h"

bind_structure_t *EVENTTAB[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

 void		ei_bind			(ei_eventtype_t		eventtype,
 					 ei_widget_t*		widget,
 					 ei_tag_t		tag,
 					 ei_callback_t		callback,
 					 void*			user_param)
{
        bind_structure_t* bindage = calloc(1, sizeof(bind_structure_t));
        bindage -> eventtype = eventtype;
        bindage -> widget = widget;
        bindage -> tag = tag;
        bindage -> callback = callback;
        bindage -> next = NULL;
        if (EVENTTAB[eventtype] == NULL) {
                EVENTTAB[eventtype] = bindage;
        }
        else {
                bind_structure_t* current = EVENTTAB[eventtype];
                while(current -> next != NULL) {
                        current = current -> next;
                }
                current -> next = bindage;
        }
}

void		ei_unbind		(ei_eventtype_t		eventtype,
					 ei_widget_t*		widget,
					 ei_tag_t		tag,
					 ei_callback_t		callback,
					 void*			user_param)
{
        bind_structure_t* current = EVENTTAB[eventtype];
        if (current == NULL) {
                printf("Aucun lien n'a ete defini");
        }
        else if (current -> widget == widget &&
                strcmp(current -> tag, tag) == 0 &&
                current -> callback == callback &&
                current -> user_param == user_param) {
                EVENTTAB[eventtype] = current -> next;
                free(current);
        }
        else {
                while (current -> next != NULL) {
                        if (current -> next -> widget == widget &&
                            strcmp(current -> next -> tag, tag) == 0 &&
                            current -> next -> callback == callback &&
                            current -> next -> user_param == user_param) {
                                bind_structure_t* temp = current -> next;
                                current -> next = current -> next -> next;
                                free(temp);
                        }
                }
        }
}
