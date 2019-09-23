#include <allegro5/allegro.h>
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>


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


int main(int argv, char **argc)
{
   simple_debugger();

   return 0;
}
