#include <allegro5/allegro.h>
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <Blast/KeyboardCommandMapper.hpp>


#include <Hexagon/FileNavigator/Stage.hpp>


void simple_debugger(std::string message="")
{
   al_init();
   al_create_display(1600, 1200);
   al_clear_to_color(al_color_name("violet"));
   ALLEGRO_FONT *font = al_create_builtin_font();
   al_draw_text(font, al_color_name("white"), 10, 10, 0, message.c_str());
   al_flip_display();
   usleep(0.2 * 1000000);
}


void run_program()
{
   Hexagon::FileNavigator::Stage *stage = new Hexagon::FileNavigator::Stage;


   std::vector<std::string> commands = {
      "change_to_yellow",
   };


   for (auto &command : commands)
   {
      stage->process_local_event(command);
      stage->render();
      al_flip_display();
      usleep(0.2 * 1000000);
   }
}


int main(int argv, char **argc)
{
   simple_debugger();

   run_program();

   return 0;
}
