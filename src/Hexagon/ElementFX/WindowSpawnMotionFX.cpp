

#include <Hexagon/ElementFX/WindowSpawnMotionFX.hpp>



namespace Hexagon
{
namespace ElementFX
{


WindowSpawnMotionFX::WindowSpawnMotionFX(Hexagon::Elements::Window* window)
   : window(window)
{
}


WindowSpawnMotionFX::~WindowSpawnMotionFX()
{
}


std::string WindowSpawnMotionFX::run()
{
return "Hello World!";
}
} // namespace ElementFX
} // namespace Hexagon


