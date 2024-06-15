

#include <Hexagon/System/Action/CreateCodeEditorStageFromFilename.hpp>

#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/util.hpp>
#include <allegro_flare/placement3d.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


namespace Hexagon
{
namespace System
{
namespace Action
{


CreateCodeEditorStageFromFilename::CreateCodeEditorStageFromFilename(std::string filename, int display_default_width, int display_default_height, int stage_width, int stage_height, ALLEGRO_COLOR text_color, ALLEGRO_COLOR backfill_color, std::vector<StageInterface *>* stages, Hexagon::StageFactory* stage_factory)
   : ::Action("System::Action::CreateCodeEditorStageFromFilename", ActionData())
   , filename(filename)
   , display_default_width(display_default_width)
   , display_default_height(display_default_height)
   , stage_width(stage_width)
   , stage_height(stage_height)
   , text_color(text_color)
   , backfill_color(backfill_color)
   , stages(stages)
   , stage_factory(stage_factory)
{
}


CreateCodeEditorStageFromFilename::~CreateCodeEditorStageFromFilename()
{
}


int CreateCodeEditorStageFromFilename::get_display_default_width() const
{
   return display_default_width;
}


int CreateCodeEditorStageFromFilename::get_display_default_height() const
{
   return display_default_height;
}


int CreateCodeEditorStageFromFilename::get_stage_width() const
{
   return stage_width;
}


int CreateCodeEditorStageFromFilename::get_stage_height() const
{
   return stage_height;
}


bool CreateCodeEditorStageFromFilename::execute()
{
   if (!(stages))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::System::Action::CreateCodeEditorStageFromFilename::execute]: error: guard \"stages\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::System::Action::CreateCodeEditorStageFromFilename::execute]: error: guard \"stages\" not met");
   }
   if (!(stage_factory))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::System::Action::CreateCodeEditorStageFromFilename::execute]: error: guard \"stage_factory\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::System::Action::CreateCodeEditorStageFromFilename::execute]: error: guard \"stage_factory\" not met");
   }
   std::vector<std::string> file_contents = {};
   if (!::read_file(file_contents, filename))
   {
      //TODO: improve this error message
      throw std::runtime_error("Could not open the selected file");
   }

   placement3d place(0, 0, 0);
   place.size = vec3d(get_stage_width(), get_stage_height(), 0.0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.scale = vec3d(0.9, 0.9, 0.0);

   StageInterface *stage = stage_factory->create_code_editor(filename, "undefined");
   Hexagon::CodeEditor::Stage *code_editor_stage = static_cast<Hexagon::CodeEditor::Stage *>(stage);

   code_editor_stage->set_place(place);
   code_editor_stage->set_base_font_color(text_color);
   code_editor_stage->set_backfill_color(backfill_color);
   code_editor_stage->get_code_editor_ref().set_content(file_contents);

   stages->push_back(code_editor_stage);

   return true;
}


} // namespace Action
} // namespace System
} // namespace Hexagon


