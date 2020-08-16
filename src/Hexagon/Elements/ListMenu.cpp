

#include <Hexagon/Elements/ListMenu.hpp>



namespace Hexagon
{
namespace Elements
{


ListMenu::ListMenu(AllegroFlare::FontBin* font_bin)
   : font_bin(font_bin)
{
}


ListMenu::~ListMenu()
{
}


std::string ListMenu::run()
{
return "Hello World!";
}
} // namespace Elements
} // namespace Hexagon


