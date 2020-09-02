

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
#include <Hexagon/ComponentNavigator/Stage.hpp>
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
   if (stage->get_render_on_hud()) continue;

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

   // another for now...
   if (stage->get_type() == StageInterface::COMPONENT_NAVIGATOR)
   {
      Hexagon::AdvancedComponentNavigator::Stage *advanced_component_navigator_stage =
         static_cast<Hexagon::AdvancedComponentNavigator::Stage *>(stage);
      advanced_component_navigator_stage->set_is_focused(is_focused);
      advanced_component_navigator_stage->set_display(display);
      advanced_component_navigator_stage->set_font(font);
      advanced_component_navigator_stage->set_cell_width(cell_width);
      advanced_component_navigator_stage->set_cell_height(cell_height);

      // TODO: ^^^ set these values at factory time
   }

   if (stage->get_type() == StageInterface::MISSING_FILE)
   {
      Hexagon::MissingFile::Stage* missing_file_stage = static_cast<Hexagon::MissingFile::Stage *>(stage);
      missing_file_stage->set_is_focused(is_focused);
      missing_file_stage->set_display(display);
      missing_file_stage->set_font(font);
      missing_file_stage->set_cell_width(cell_width);
      missing_file_stage->set_cell_height(cell_height);
   }

   if (stage->get_type() == StageInterface::FILE_NAVIGATOR)
   {
      Hexagon::FileNavigator::Stage *file_navigator_stage = static_cast<Hexagon::FileNavigator::Stage *>(stage);
      file_navigator_stage->set_is_focused(is_focused);
      file_navigator_stage->set_display(display);
      file_navigator_stage->set_font(font);
      file_navigator_stage->set_cell_width(cell_width);
      file_navigator_stage->set_cell_height(cell_height);
   }

   if (stage->get_type() == StageInterface::RERUN_OUTPUT_WATCHER)
   {
      Hexagon::RerunOutputWatcher::Stage *rerun_output_watcher_stage =
         static_cast<Hexagon::RerunOutputWatcher::Stage *>(stage);
      rerun_output_watcher_stage->set_font(font);
   }

   if (stage->get_type() == StageInterface::OLD_COMPONENT_NAVIGATOR)
   {
      Hexagon::ComponentNavigator::Stage *component_navigator_stage =
         static_cast<Hexagon::ComponentNavigator::Stage *>(stage);
      component_navigator_stage->set_font(font);
      component_navigator_stage->set_cell_width(cell_width);
      component_navigator_stage->set_cell_height(cell_height);
   }


   stage->render();



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


