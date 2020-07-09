

#include <Hexagon/Elements/FlashingGrid.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


FlashingGrid::FlashingGrid()
{
}


FlashingGrid::~FlashingGrid()
{
}


void FlashingGrid::render()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "FlashingGrid" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
return;

}
} // namespace Elements
} // namespace Hexagon


