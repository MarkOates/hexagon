#include <allegro5/allegro.h>

#include <Hexagon/Elements/TextMesh.hpp>

#include <allegro_flare/placement3d.h> // for placement3d
#include <AllegroFlare/FontBin.hpp>


static int random_int(int min, int max)
{
   return rand()%(max-min+1) + min;
}


template<class T>
T random_element(std::vector<T> &elements)
{
   return elements[random_int(0, elements.size()-1)];
}


void random_fill(Hexagon::Elements::TextMesh &text_mesh)
{
   std::vector<ALLEGRO_COLOR> colors = {
     al_color_name("red"),
     al_color_name("chartreuce"),
     al_color_name("dodgerblue"),
     al_color_name("orange"),
     al_color_name("yellow"),
     al_color_name("mint"),
     al_color_name("white"),
   };

   for (unsigned y=0; y<text_mesh.get_num_rows(); y++)
   {
      for (unsigned x=0; x<text_mesh.get_num_columns(); x++)
      {
         text_mesh.set_cell_background_color(x, y, random_element<ALLEGRO_COLOR>(colors));
         text_mesh.set_cell_character(x, y, rand()%256);
      }
   }
}


class TextMeshWindow
{
private:
   static int DEFAULT_NUM_ROWS;
   static int DEFAULT_NUM_COLUMNS;
   ALLEGRO_DISPLAY *display;
   AllegroFlare::FontBin *font_bin;
   Hexagon::Elements::TextMesh text_mesh;
   placement3d place;

   ALLEGRO_FONT *get_default_text_font()
   {
      if (!font_bin) throw std::runtime_error("TextMeshWindow needs a valid font_bin");
      font_bin->operator[]("consolas.ttf -23");
   }

public:
   TextMeshWindow(ALLEGRO_DISPLAY *display, AllegroFlare::FontBin *font_bin)
      : display(display)
      , text_mesh(get_default_text_font(), DEFAULT_NUM_COLUMNS, DEFAULT_NUM_ROWS)
   {}

   void initialize()
   {
      text_mesh.initialize();
      place.size = vec3d(text_mesh.calculate_width(), text_mesh.calculate_height(), 0);
      place.scale = vec3d(0.5, 0.5, 0.5);
   }

   void update()
   {
      random_fill(text_mesh);
   }

   void draw()
   {
      place.start_transform();
      text_mesh.render();
      place.restore_transform();
   }
};


int TextMeshWindow::DEFAULT_NUM_ROWS = 122;
int TextMeshWindow::DEFAULT_NUM_COLUMNS = 70;


int main(int argc, char **argv)
{
   srand(time(0));

   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1280*2, 720*2);
   al_clear_to_color(al_color_name("black"));
   ALLEGRO_FONT *a_valid_font = al_create_builtin_font();

   Hexagon::Elements::TextMesh text_mesh(a_valid_font, 123, 70);

   text_mesh.initialize();

   random_fill(text_mesh);

   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   place.size = vec3d(text_mesh.calculate_width(), text_mesh.calculate_height(), 0);
   place.scale = vec3d(0.5, 0.5, 0.5);

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
