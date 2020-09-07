

#include <Hexagon/System/Renderer.hpp>
#include <Hexagon/shared_globals.hpp>
#include <Hexagon/shared_globals.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <Hexagon/MissingFile/Stage.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/RerunOutputWatcher/Stage.hpp>
#include <Hexagon/Elements/Window.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace System
{


Renderer::Renderer(::System* system, ALLEGRO_DISPLAY* display, ALLEGRO_COLOR* backfill_color)
   : system(system)
   , display(display)
   , backfill_color(backfill_color)
{
}


Renderer::~Renderer()
{
}


ALLEGRO_COLOR* Renderer::get_backfill_color()
{
   return backfill_color;
}


bool Renderer::render()
{
if (!(system))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"system\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(display))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"display\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(backfill_color))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"backfill_color\" not met";
      throw std::runtime_error(error_message.str());
   }
al_clear_to_color(*get_backfill_color());
//al_clear_to_color(al_color_html("5b5c60"));

system->camera.setup_camera_perspective(al_get_backbuffer(display));
al_clear_depth_buffer(1000);

global::profiler.start("all stages");

ALLEGRO_FONT *font = system->font_bin[system->get_global_font_str()];
int cell_width = al_get_text_width(font, " ");
int cell_height = al_get_font_line_height(font);

for (auto &stage : system->stages)
{
   if (stage->get_render_on_hud()) continue;

   std::stringstream profile_timer_element_label;
   profile_timer_element_label << "Stage [" << stage->get_type_name() << "]                    " << stage;
   global::profiler.start(profile_timer_element_label.str());

   bool is_focused = (system->get_frontmost_stage() == stage);
   ALLEGRO_FONT *font = system->font_bin[system->get_global_font_str()];


   // for now, we're going to assign these values here so that render() can be argument-free
   if (stage->get_type() == StageInterface::CODE_EDITOR)
   {
      Hexagon::CodeEditor::Stage *code_editor_stage = static_cast<Hexagon::CodeEditor::Stage *>(stage);
      code_editor_stage->set_display(display);
      code_editor_stage->set_font(font);
      code_editor_stage->set_cell_width(cell_width);
      code_editor_stage->set_cell_height(cell_height);
   }

   stage->render();

   if (is_focused) // for now, we're just going to do this as an experiment in assessing focused state in the UI
   {
      placement3d place = stage->get_place();
      Hexagon::Elements::Window window(place.size.x, place.size.y);

      window.set_outer_line_color(ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f});
      window.set_outer_line_opacity(0.2);
      window.set_outer_line_thickness(4.0);

      place.start_transform();
      window.draw();
      place.restore_transform();
   }

   global::profiler.pause(profile_timer_element_label.str());
}
global::profiler.pause("all stages");

system->hud.draw();

return true;

}
} // namespace System
} // namespace Hexagon


