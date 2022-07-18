

#include <Hexagon/MultiplexMenu/Renderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace MultiplexMenu
{


Renderer::Renderer(AllegroFlare::FontBin* font_bin, Hexagon::MultiplexMenu::MultiplexMenu* multiplex_menu)
   : font_bin(font_bin)
   , multiplex_menu(multiplex_menu)
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
   //Hexagon::MultiplexMenu::MultiplexMenuPage
   render_page();
}

void Renderer::render_page(Hexagon::MultiplexMenu::MultiplexMenuPage* page)
{
   //Hexagon::MultiplexMenu::MultiplexMenuPage
   return;
}
} // namespace MultiplexMenu
} // namespace Hexagon


