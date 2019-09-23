#include <allegro5/allegro.h>

//void simple_debugger(std::string message="")
//{
   //al_init();
   //al_create_display(800, 800);
   //al_clear_to_color(al_color_name("violet"));
   //ALLEGRO_FONT *font = al_create_builtin_font();
   //al_draw_text(font, al_color_name("white"), 10, 10, 0, message.c_str());
   //al_flip_display();
   //usleep(0.2 * 1000000);
//}

#include <iostream>

int main(int argv, char **argc)
{
   //simple_debugger();
   std::cout << "WORKS!!" << std::endl;
   return 0;
}
