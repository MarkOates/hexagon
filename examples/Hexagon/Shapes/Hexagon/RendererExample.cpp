#include <allegro5/allegro.h>
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <Blast/KeyboardCommandMapper.hpp>


#include <allegro_flare/vec3d.h>
#include <allegro_flare/placement2d.h>
#include <allegro_flare/placement3d.h>
#include <Hexagon/Shapes/Hexagon/Renderer.hpp>


int display_w = 1920;
int display_h = 1080;


#include <iostream>

static std::string resource_path(std::vector<std::string> components, std::string filename)
{
   std::string result;

   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   for (auto &component : components) al_append_path_component(path, component.c_str());

   al_set_path_filename(path, filename.c_str());
   result = al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP);

   std::cout << result << std::endl;

   return result;
}


void render_hexagons()
{
   placement2d place(display_w/2, display_h/2, 0, 0);
   place.start_transform();
   float radius = 100;
   //float h_spacing = radius * 2 * 1.1;

   Hexagon::Shapes::Hexagon::Renderer(0, 0, radius, {
      { 5, 13, al_color_name("green"), 3 },
      { 2, 4, al_color_name("chartreuse"), 6 },
   }).render();

   Hexagon::Shapes::Hexagon::Renderer(0, radius*2, radius, {
      { 2, 10, al_color_name("blue"), 3 },
      { 11, 1, al_color_name("dodgerblue"), 6 },
   }).render();

   Hexagon::Shapes::Hexagon::Renderer(radius*1.75, radius, radius, {
      { 8, 10, al_color_name("red"), 6 },
      { 11, 7, al_color_name("brown"), 3 },
   }).render();

   //Hexagon::Shapes::Hexagon::Renderer(h_spacing, -radius, radius, {
      //{ 10, 12, al_color_name("red"), 6 },
      //{ 1, 9, al_color_name("brown"), 3 },
   //}).render();

   place.restore_transform();
}


void run_program()
{
   al_init();
   al_init_font_addon();
   al_init_image_addon();
   al_init_ttf_addon();
   al_create_display(display_w, display_h);

   ALLEGRO_DISPLAY *display = al_get_current_display();
   int display_width = al_get_display_width(display);
   int display_height = al_get_display_height(display);
   placement3d place(display_width/2, display_height/2, 0);
   place.size = vec3d(400, 650, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);
 
   std::string helvetica_font_filename = resource_path({ "data", "fonts" }, "Helvetica.ttf");
   ALLEGRO_FONT *font = al_load_font(helvetica_font_filename.c_str(), 32, 0);

   al_clear_to_color(al_color_name("black"));

   render_hexagons();

   al_save_bitmap("/Users/markoates/Repos/hexagon/tmp/render.png", al_get_backbuffer(display));

   al_flip_display();

   al_destroy_font(font);
}


int main(int argv, char **argc)
{
   //simple_debugger();

   run_program();

   usleep(1.0 * 1000000);

   return 0;
}

