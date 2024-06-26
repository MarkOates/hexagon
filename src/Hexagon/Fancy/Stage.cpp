

#include <Hexagon/Fancy/Stage.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace Fancy
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(AllegroFlare::FontBin* font_bin)
   : StageInterface(StageInterface::FANCY)
   , font_bin(font_bin)
{
}


Stage::~Stage()
{
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


std::string Stage::run()
{
   return "Hello World!";
}

void Stage::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Fancy::Stage::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Fancy::Stage::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Fancy::Stage::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Fancy::Stage::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // initialize
   float surface_width = 1920;
   float surface_height = 1080;
   float width = surface_width / 5 * 4;
   float height = surface_height / 8 * 6;
   float o = 0.2f;
   ALLEGRO_COLOR fill_color = ALLEGRO_COLOR{1.0f*o, 1.0f*o, 0.0f*o, 1.0f*o};
   ALLEGRO_COLOR font_color = fill_color;
   ALLEGRO_FONT *title_font = obtain_title_font();
   placement3d place = get_place();

   // transform
   place.position.x = surface_width / 2;
   place.position.y = surface_height / 2;
   place.size.x = width;
   place.size.y = height;

   // execute
   place.start_transform();
   al_draw_filled_rectangle(0, 0, width, height, fill_color);
   al_draw_text(title_font, font_color, 20, 10, ALLEGRO_ALIGN_LEFT, "FANCY");
   place.restore_transform();

   // return
   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   return;
}

ALLEGRO_FONT* Stage::obtain_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Fancy::Stage::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Fancy::Stage::obtain_title_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("EurostileExtendedBlack-aka-ExtendedBold.ttf -26");
}


} // namespace Fancy
} // namespace Hexagon


