#include <stdlib.h>

#include "ei_types.h"
#include "ei_main.h"
#include "ei_draw.h"
#include "ei_event.h"
#include "ei_button.h"
#include "hw_interface.h"

int ei_main(int argc, char** argv)
{
	ei_surface_t			main_window		= NULL;
	ei_size_t			main_window_size;
	ei_color_t			red			= { 0xff, 0x00, 0x00, 0xff };
	ei_color_t      transp_blue1  = {0x00, 0x00, 0xff, 0x88 };
	ei_color_t			transp_blue2	= {0x00, 0x00, 0xaa, 0x88 };
	ei_color_t      blue  = {0x00, 0x00, 0xbf, 0xff};

	// Init acces to hardware.
	hw_init();

	// Create the main window.
	main_window_size.width	= 640;
	main_window_size.height	= 480;
	main_window = hw_create_window(&main_window_size, EI_FALSE);



	// Fill the main window in red, draw a transparent blue polygon:
	// PARAM DU BOUTON
	ei_bouton_param_t type_bouton1 = ei_bouton_top;
	ei_bouton_param_t type_bouton2 = ei_bouton_bot;
	ei_bouton_param_t type_bouton3 = ei_bouton_whole;
	// Define the polygon vertices.
  ei_point_t point_du_rectangle = {50, 50};
  ei_size_t taille_rectangle = {300, 200};
	ei_rect_t rectangle = {point_du_rectangle, taille_rectangle};
	// border de 10
	ei_point_t point_du_rectangle_sans_border = {60,60};
	ei_size_t taille_rectangle_sans_border = {280,180};
	ei_rect_t rectangle_sans_border = {point_du_rectangle_sans_border, taille_rectangle_sans_border};
  ei_linked_point_t* points1 = rounded_frame(rectangle, 30,type_bouton1);
	ei_linked_point_t* points2 = rounded_frame(rectangle, 30,type_bouton2);
	ei_linked_point_t* points3 = rounded_frame(rectangle_sans_border, 20,type_bouton3);
	// Lock the surface for drawing, fill, draw polygon, unlock, update screen.
	hw_surface_lock(main_window);
	ei_fill(main_window, &red, NULL);
	ei_draw_polygon(main_window, points1, transp_blue1, NULL);
	ei_draw_polygon(main_window, points2, transp_blue2, NULL);
	ei_draw_polygon(main_window, points3, blue, NULL);
	hw_surface_unlock(main_window);
	hw_surface_update_rects(main_window, NULL);
	getchar();


	// Free hardware resources.
	hw_quit();

	// Terminate program with no error code.
	return 0;
}
