#include <allegro5/allegro.h>

#include <Hexagon/Elements/TextMesh.hpp>

#include <allegro5/allegro_ttf.h>
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
   placement3d place;
   AllegroFlare::FontBin *font_bin;
   Hexagon::Elements::TextMesh text_mesh;
   bool initialized;

   ALLEGRO_FONT *get_default_text_font()
   {
      if (!font_bin) throw std::runtime_error("TextMeshWindow needs a valid font_bin");
      return font_bin->auto_get("consolas.ttf -23");
   }

public:
   TextMeshWindow(int x, int y, int z, AllegroFlare::FontBin *font_bin)
      : place(x, y, z)
      , font_bin(font_bin)
      , text_mesh(get_default_text_font(), DEFAULT_NUM_COLUMNS, DEFAULT_NUM_ROWS)
      , initialized(false)
   {}

   void initialize()
   {
      if (initialized) return;

      text_mesh.initialize();
      place.size = vec3d(text_mesh.calculate_width(), text_mesh.calculate_height(), 0);
      place.scale = vec3d(0.5, 0.5, 0.5);

      initialized = true;
   }

   void update()
   {
      if (!initialized) throw std::runtime_error("TextMeshWindow not initialized");

      random_fill(text_mesh);
   }

   void draw()
   {
      if (!initialized) throw std::runtime_error("TextMeshWindow not initialized");

      place.start_transform();
      text_mesh.render();
      place.restore_transform();
   }
};
int TextMeshWindow::DEFAULT_NUM_ROWS = 70;
int TextMeshWindow::DEFAULT_NUM_COLUMNS = 123;


int main(int argc, char **argv)
{
   srand(time(0));

   al_init();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1280*2, 720*2);

   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");

   TextMeshWindow text_mesh_window(al_get_display_width(display)/2, al_get_display_height(display)/2, 0, &font_bin);
   text_mesh_window.initialize();

   for (unsigned i=0; i<60; i++)
   {
      al_clear_to_color(al_color_name("black"));

      text_mesh_window.update();

      text_mesh_window.draw();

      al_flip_display();
   }

   //al_destroy_font(a_valid_font);
   al_destroy_display(display);
   font_bin.clear();
   al_uninstall_system();

   return 0;
}
