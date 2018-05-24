#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ei_application.h"
#include "ei_event.h"
#include "hw_interface.h"
#include "ei_widget.h"
#include "ei_geometrymanager.h"
#include "ei_button.h"
#include <stdbool.h>


extern ei_widgetclass_t* CLASSES;
ei_widget_t* ROOT;
void explore(ei_widget_t* widget);
ei_surface_t surface_fenetre_syst;
ei_surface_t surface_offscreen;

int ei_main(int argc, char** argv)
{
  hw_init();
  ei_size_t	screen_size		= {600, 600};
  surface_fenetre_syst = hw_create_window(&screen_size, true);
  surface_offscreen = hw_surface_create(surface_fenetre_syst, &screen_size, false);
  ei_app_create(&screen_size, EI_FALSE);
  ei_point_t centre = {300,300};
  int rayon = 50;
  float debut_arc =90;
  float fin_arc = 0;
  ei_color_t	frame_color		= {0x88, 0x88, 0x88, 0xff};
  ei_linked_point_t* first_point = arc(centre,rayon,debut_arc,fin_arc);
  ei_draw_polygon (surface_fenetre_syst, first_point,frame_color, NULL);


  ei_app_run();
  ei_app_free();

  	return (EXIT_SUCCESS);
}
