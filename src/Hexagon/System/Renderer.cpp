

#include <Hexagon/System/Renderer.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>


namespace Hexagon
{
namespace System
{


Renderer::Renderer(::System* system, ALLEGRO_DISPLAY* display)
   : system(system)
   , display(display)
{
}


Renderer::~Renderer()
{
}


bool Renderer::render()
{
if (!system)
{
   std::stringstream error_message;
   error_message << "[System::Renderer error:] cannot render() with a nullptr system";
   throw std::runtime_error(error_message.str());
}
if (!display)
{
   std::stringstream error_message;
   error_message << "[System::Renderer error:] cannot render() with a nullptr display";
   throw std::runtime_error(error_message.str());
}

al_clear_to_color(al_color_name("black"));

system->camera.setup_camera_perspective(al_get_backbuffer(display));
al_clear_depth_buffer(1000);

return true;

}
} // namespace System
} // namespace Hexagon


