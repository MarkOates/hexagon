

#include <Hexagon/System/Renderer.hpp>
#include <Hexagon/shared_globals.hpp>
#include <Hexagon/shared_globals.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <Hexagon/shared_globals.hpp>


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

al_clear_to_color(hexagon_get_backfill_color());
//al_clear_to_color(al_color_html("5b5c60"));

system->camera.setup_camera_perspective(al_get_backbuffer(display));
al_clear_depth_buffer(1000);

global::profiler.start("all stages");
for (auto &stage : system->stages)
{
   std::stringstream profile_timer_element_label;
   profile_timer_element_label << "Stage [" << stage->get_type_name() << "]                    " << stage;
   global::profiler.start(profile_timer_element_label.str());

   bool is_focused = (system->get_frontmost_stage() == stage);
   ALLEGRO_FONT *font = system->font_bin[system->get_global_font_str()];
   stage->render(is_focused, display, font, al_get_text_width(font, " "), al_get_font_line_height(font));

   global::profiler.pause(profile_timer_element_label.str());
}
global::profiler.pause("all stages");

system->hud.draw();

return true;

}
} // namespace System
} // namespace Hexagon


