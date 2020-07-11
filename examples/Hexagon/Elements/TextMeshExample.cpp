#include <allegro5/allegro.h>

#include <Hexagon/Elements/TextMesh.hpp>


int main(int argc, char **argv)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1280, 720);
   al_clear_to_color(al_color_name("black"));
   ALLEGRO_FONT *a_valid_font = al_create_builtin_font();

   Hexagon::Elements::TextMesh text_mesh(a_valid_font, 30, 20);

   text_mesh.initialize();

   for (unsigned y=0; y<text_mesh.get_num_rows(); y++)
   {
      for (unsigned x=0; x<text_mesh.get_num_columns(); x++)
      {
         text_mesh.set_cell_background_color(x, y, al_color_name("red"));
         text_mesh.set_cell_character(x, y, 'a');
      }
   }

   text_mesh.render();
   al_flip_display();

   sleep(1);

   al_destroy_font(a_valid_font);
   al_uninstall_system();

   return 0;
}
