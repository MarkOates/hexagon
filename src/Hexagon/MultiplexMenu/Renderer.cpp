

#include <Hexagon/MultiplexMenu/Renderer.hpp>

#include <Hexagon/MultiplexMenu/PageRenderer.hpp>
#include <allegro_flare/placement3d.h>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace MultiplexMenu
{


Renderer::Renderer(AllegroFlare::FontBin* font_bin, Hexagon::MultiplexMenu::MultiplexMenu* multiplex_menu, float page_width)
   : font_bin(font_bin)
   , multiplex_menu(multiplex_menu)
   , page_width(page_width)
{
}


Renderer::~Renderer()
{
}


void Renderer::render()
{
   if (!(multiplex_menu))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"multiplex_menu\" not met";
      throw std::runtime_error(error_message.str());
   }
   placement3d place;
   int i=0;
   int num_pages = multiplex_menu->get_num_pages();
   for (auto &page : multiplex_menu->get_page_history())
   {
      bool at_last_page = (i == num_pages-1);
      place.start_transform();
      render_page(page, at_last_page);
      place.restore_transform();
      place.position.x += page_width;
      i++;
   }
   return;
}

float Renderer::get_width()
{
   if (!multiplex_menu) return 0;
   return page_width * multiplex_menu->get_num_pages();
}

void Renderer::render_page(Hexagon::MultiplexMenu::MultiplexMenuPage* page, bool is_active)
{
   Hexagon::MultiplexMenu::PageRenderer page_renderer(font_bin, page, is_active);
   page_renderer.render();
   return;
}


} // namespace MultiplexMenu
} // namespace Hexagon


