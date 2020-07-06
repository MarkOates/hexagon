

#include <Hexagon/System/Renderer.hpp>
#include <Hexagon/shared_globals.hpp>
#include <Hexagon/shared_globals.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>
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
   std::stringstream profile_timer_element_label;
   profile_timer_element_label << "Stage [" << stage->get_type_name() << "]                    " << stage;
   global::profiler.start(profile_timer_element_label.str());

   bool is_focused = (system->get_frontmost_stage() == stage);
   ALLEGRO_FONT *font = system->font_bin[system->get_global_font_str()];


   // for now, we're going to assign these values here so that render() can be argument-free
   if (rendered_with_CodeEditor_Renderer(stage))
   {
      Hexagon::CodeEditor::Stage *code_editor_stage = static_cast<Hexagon::CodeEditor::Stage *>(stage);
      code_editor_stage->set_is_focused(is_focused);
      code_editor_stage->set_display(display);
      code_editor_stage->set_font(font);
      code_editor_stage->set_cell_width(cell_width);
      code_editor_stage->set_cell_height(cell_height);
   }


   stage->render(is_focused, display, font, cell_width, cell_height);



   global::profiler.pause(profile_timer_element_label.str());
}
global::profiler.pause("all stages");

system->hud.draw();

return true;

}

bool Renderer::rendered_with_CodeEditor_Renderer(StageInterface* stage)
{
if (!(stage))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "rendered_with_CodeEditor_Renderer" << ": error: " << "guard \"stage\" not met";
      throw std::runtime_error(error_message.str());
   }
if (stage->get_type() == StageInterface::CODE_EDITOR
  || stage->get_type() == StageInterface::ONE_LINE_INPUT_BOX
  || stage->get_type() == StageInterface::GIT_COMMIT_MESSAGE_INPUT_BOX) return true;
return false;

}
} // namespace System
} // namespace Hexagon


