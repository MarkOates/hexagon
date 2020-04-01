

#include <Hexagon/Powerbar/Powerbar.hpp>



namespace Hexagon
{
namespace Powerbar
{


Powerbar::Powerbar(std::string box_1_text, std::string box_2_text, std::string box_3_text)
   : box_1_text(box_1_text)
   , box_2_text(box_2_text)
   , box_3_text(box_3_text)
{
}


Powerbar::~Powerbar()
{
}


std::string Powerbar::get_box_1_text()
{
   return box_1_text;
}


std::string Powerbar::get_box_2_text()
{
   return box_2_text;
}


} // namespace Powerbar
} // namespace Hexagon


