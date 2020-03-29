

#include <Hexagon/System/Renderer.hpp>
#include <Hexagon/shared_globals.hpp>
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

for (auto &stage : system->stages)
{
   bool is_focused = (system->get_frontmost_stage() == stage);
   ALLEGRO_FONT *font = system->font_bin[system->get_global_font_str()];
   stage->render(is_focused, display, font, al_get_text_width(font, " "), al_get_font_line_height(font));
}

// this next paragraph may not belong in the renderer
for (auto &stage : system->stages)
{
   StageInterface::type_t type = stage->get_type();
   if (type == CodeEditor::Stage::ONE_LINE_INPUT_BOX || type == CodeEditor::Stage::CODE_EDITOR)
   {
      bool this_stage_content_is_modified = static_cast<CodeEditor::Stage *>(stage)->get_content_is_modified();
      if (this_stage_content_is_modified) add_notification(NOTIFICATION_FILE_IS_UNSAVED);
   }
}

return true;

}
} // namespace System
} // namespace Hexagon


