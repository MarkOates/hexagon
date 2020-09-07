

#include <Hexagon/System/Action/AttemptToCraeteCodeEditorStageFromFilename.hpp>
#include <sstream>
#include <Hexagon/util.hpp>
#include <allegro_flare/placement3d.h>
#include <vector>
#include <string>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace System
{
namespace Action
{


AttemptToCraeteCodeEditorStageFromFilename::AttemptToCraeteCodeEditorStageFromFilename(std::string filename, int display_default_width, int display_default_height, int stage_width, ALLEGRO_COLOR text_color, ALLEGRO_COLOR backfill_color, std::vector<StageInterface *>* stages)
   : ::Action("System::Action::AttemptToCreateCodeEditorStageFromFilename", ActionData())
   , filename(filename)
   , display_default_width(display_default_width)
   , display_default_height(display_default_height)
   , stage_width(stage_width)
   , text_color(text_color)
   , backfill_color(backfill_color)
   , stages(stages)
{
}


AttemptToCraeteCodeEditorStageFromFilename::~AttemptToCraeteCodeEditorStageFromFilename()
{
}


int AttemptToCraeteCodeEditorStageFromFilename::get_display_default_width()
{
   return display_default_width;
}


int AttemptToCraeteCodeEditorStageFromFilename::get_display_default_height()
{
   return display_default_height;
}


int AttemptToCraeteCodeEditorStageFromFilename::get_stage_width()
{
   return stage_width;
}


bool AttemptToCraeteCodeEditorStageFromFilename::execute()
{
if (!(stages))
   {
      std::stringstream error_message;
      error_message << "AttemptToCraeteCodeEditorStageFromFilename" << "::" << "execute" << ": error: " << "guard \"stages\" not met";
      throw std::runtime_error(error_message.str());
   }
std::vector<std::string> file_contents = {};
if (!::read_file(file_contents, filename))
{
   //TODO: improve this error message
   throw std::runtime_error("Could not open the selected file");
}

//int number_of_files = get_number_of_code_editor_stages();
//float one_third_screen_width = get_display_default_width() / 3;
//float placement_x = one_third_screen_width*number_of_files;
float placement_x = 0;

placement3d place(placement_x, 0, 0);
place.size = vec3d(get_stage_width(), get_display_default_height(), 0.0);
place.align = vec3d(0.5, 0.5, 0.0);
place.scale = vec3d(0.9, 0.9, 0.0);

Hexagon::CodeEditor::Stage *stage = new Hexagon::CodeEditor::Stage(::CodeEditor::CodeEditor{filename});// place);

stage->set_place(place);
stage->set_base_font_color(text_color);
stage->set_backfill_color(backfill_color);
stage->get_code_editor_ref().set_content(file_contents);
stages->push_back(stage);

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


