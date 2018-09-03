#include <iostream>


#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>




void run_program()
{
   if (!al_init()) std::cerr << "al_init() failed" << std::endl;
   if (!al_init_font_addon()) std::cerr << "al_init_font_addon() failed" << std::endl;
   if (!al_init_ttf_addon()) std::cerr << "al_init_ttf_addon() failed" << std::endl;

   ALLEGRO_PATH *resource_path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_change_directory(al_path_cstr(resource_path, ALLEGRO_NATIVE_PATH_SEP));
   al_destroy_path(resource_path);

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_FONT *consolas_font = al_load_font("data/fonts/consolas.ttf", 28, 0);

   int display_width = al_get_display_width(display);
   int display_height = al_get_display_height(display);

   al_draw_text(consolas_font, al_color_name("white"), display_width/2, display_height/2, ALLEGRO_ALIGN_CENTER, "Hello world.");
   al_flip_display();

   sleep(3);
}



int main(int, char**) {
  run_program();
  return 0;
}

