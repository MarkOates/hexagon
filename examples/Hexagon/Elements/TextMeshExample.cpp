#include <allegro5/allegro.h>

#include <Hexagon/Elements/TextMesh.hpp>

//#include <AllegroFlare/Random.hpp>


void random_fill(Hexagon::Elements::TextMesh &text_mesh)
{
   for (unsigned y=0; y<text_mesh.get_num_rows(); y++)
   {
      for (unsigned x=0; x<text_mesh.get_num_columns(); x++)
      {
         text_mesh.set_cell_background_color(x, y, al_color_name("chartreuse"));
         text_mesh.set_cell_character(x, y, rand()%256);
      }
   }
}


int main(int argc, char **argv)
{
   srand(time(0));

   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1280, 720);
   al_clear_to_color(al_color_name("black"));
   ALLEGRO_FONT *a_valid_font = al_create_builtin_font();

   Hexagon::Elements::TextMesh text_mesh(a_valid_font, 60, 50);

   text_mesh.initialize();

   random_fill(text_mesh);

   text_mesh.render();
   al_flip_display();

   sleep(1);

   al_destroy_font(a_valid_font);
   al_destroy_display(display);
   al_uninstall_system();

   return 0;
}
