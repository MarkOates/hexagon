

#include <Hexagon/Forms/Fun.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace Forms
{


Fun::Fun()
   : buffer("")
{
}


Fun::~Fun()
{
}


std::string Fun::get_buffer() const
{
   return buffer;
}


void Fun::draw(placement3d place, ALLEGRO_COLOR backfill_color)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Forms::Fun::draw]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Forms::Fun::draw]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Forms::Fun::draw]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Forms::Fun::draw]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Forms::Fun::draw]: error: guard \"al_get_target_bitmap()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Forms::Fun::draw]: error: guard \"al_get_target_bitmap()\" not met");
   }
   al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, backfill_color);
   return;
}

int Fun::process_char_input(char input_ch)
{
   static const int DELETE_CHAR = 127;
   static const int SPACEBAR_CHAR = 32;

   static const int RESULT_NO_CHANGE = 0;
   static const int RESULT_BUFFER_CHANGED = 1;

   if (input_ch == DELETE_CHAR)
   {
      if (!buffer.empty())
      {
         std::string buff = buffer;
         buff.erase(buff.size() - 1);
         buffer = buff;
         return RESULT_BUFFER_CHANGED;
      }
   }
   else if (input_ch < SPACEBAR_CHAR)
   {
      return RESULT_NO_CHANGE;
   }
   else
   {
      buffer.append(1, input_ch);
      return RESULT_BUFFER_CHANGED;
   }

   return RESULT_NO_CHANGE;
}


} // namespace Forms
} // namespace Hexagon


