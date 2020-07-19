

#include <Hexagon/ElementFX/WindowSpawnMotionFX.hpp>
#include <Hexagon/Elements/Window.hpp>


namespace Hexagon
{
namespace ElementFX
{


WindowSpawnMotionFX::WindowSpawnMotionFX(Hexagon::Elements::Window window)
   : window(window)
{
}


WindowSpawnMotionFX::~WindowSpawnMotionFX()
{
}


Hexagon::Elements::Window WindowSpawnMotionFX::construct_modified_window()
{
Hexagon::Elements::Window result;

return result;

}
} // namespace ElementFX
} // namespace Hexagon


