#include <allegro5/allegro.h>

#include <Hexagon/Elements/TextMesh.hpp>

#include <allegro_flare/placement3d.h> // for placement3d


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

   Hexagon::Elements::TextMesh text_mesh(a_valid_font, 123, 70);

   text_mesh.initialize();

   random_fill(text_mesh);

   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   place.size = vec3d(text_mesh.calculate_width(), text_mesh.calculate_height(), 0);

   for (unsigned i=0; i<60; i++)
   {
      al_clear_to_color(al_color_name("black"));
      random_fill(text_mesh);

      place.start_transform();
      text_mesh.render();
      place.restore_transform();
      al_flip_display();
   }

   al_destroy_font(a_valid_font);
   al_destroy_display(display);
   al_uninstall_system();

   return 0;
}
