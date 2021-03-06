#include <allegro5/allegro.h>
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/KeyboardCommandMapper.hpp>


#include <Hexagon/FileNavigator/Stage.hpp>



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


void simple_debugger(std::string message="")
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();
   al_create_display(1600, 1200);
   al_clear_to_color(al_color_name("violet"));
   ALLEGRO_FONT *font = al_create_builtin_font();
   al_draw_text(font, al_color_name("white"), 10, 10, 0, message.c_str());
   al_flip_display();
   al_destroy_font(font);
   usleep(0.2 * 1000000);
}


void run_program()
{
   ALLEGRO_DISPLAY *display = al_get_current_display();
   int display_width = al_get_display_width(display);
   int display_height = al_get_display_height(display);
   placement3d place(display_width/2, display_height/2, 0);
   place.size = vec3d(400, 650, 0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.rotation = vec3d(0.0, 0.0, 0.0);
 

   Hexagon::FileNavigator::Stage *stage = new Hexagon::FileNavigator::Stage;
   stage->set_place(place);
   //ALLEGRO_FONT *font = al_create_builtin_font();
   std::string helvetica_font_filename = resource_path({ "data", "fonts" }, "Helvetica.ttf");
   ALLEGRO_FONT *font = al_load_font(helvetica_font_filename.c_str(), 32, 0);

   std::vector<std::vector<std::string>> command_sets = {
      { "set_node_root_to_system_root_directory", "refresh_list", "move_cursor_to_top" },
      { "set_node_root_to_user_directory", "refresh_list", "move_cursor_to_top" },
      { "set_node_root_to_repos_directory", "refresh_list", "move_cursor_to_top" },
      { "move_cursor_down" },
      { "move_cursor_down" },
      { "move_cursor_down" },
      { "move_cursor_down" },
      { "set_node_root_to_parent_directory", "refresh_list", "move_cursor_to_top" },
      { "move_cursor_down" },
      { "move_cursor_up" },
      { "move_cursor_up" },
      { "move_cursor_down" },
      { "move_cursor_down" },
      { "set_node_root_to_current_selection_if_folder", "refresh_list", "move_cursor_to_top" },
   };


   for (auto &command_set : command_sets)
   {
      al_clear_to_color(al_color_name("black"));

      for (auto &command : command_set)
      {
         stage->process_local_event(command);
      }

      stage->set_is_focused(true);
      stage->set_display(nullptr);
      stage->set_font(font);

      stage->render();

      al_flip_display();

      usleep(0.1 * 1000000);
   }

   al_destroy_font(font);
}


int main(int argv, char **argc)
{
   simple_debugger();

   run_program();

   usleep(1.0 * 1000000);

   return 0;
}
