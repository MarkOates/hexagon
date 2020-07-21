

#include <Hexagon/Layout.hpp>
#include <allegro_flare/useful_php.h>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Hexagon/MissingFile/Stage.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


Layout::Layout(std::string project_root, std::vector<StageInterface *>* stages, std::vector<std::tuple<std::string, std::string, placement3d>> files, std::string daemus_command, int code_editor_height, int code_editor_width, ALLEGRO_COLOR text_color, ALLEGRO_COLOR backfill_color)
   : project_root(project_root)
   , stages(stages)
   , files(files)
   , daemus_command(daemus_command)
   , code_editor_height(code_editor_height)
   , code_editor_width(code_editor_width)
   , text_color(text_color)
   , backfill_color(backfill_color)
{
}


Layout::~Layout()
{
}


void Layout::set_stages(std::vector<StageInterface *>* stages)
{
   this->stages = stages;
}


void Layout::set_files(std::vector<std::tuple<std::string, std::string, placement3d>> files)
{
   this->files = files;
}


std::string Layout::get_project_root()
{
   return project_root;
}


std::vector<StageInterface *>* Layout::get_stages()
{
   return stages;
}


std::vector<std::tuple<std::string, std::string, placement3d>> Layout::get_files()
{
   return files;
}


std::string Layout::get_daemus_command()
{
   return daemus_command;
}


int Layout::get_code_editor_height()
{
   return code_editor_height;
}


int Layout::get_code_editor_width()
{
   return code_editor_width;
}


bool Layout::place_and_load_code_editor(std::string filename, std::string file_category, float x, float y, placement3d place)
{
if (!(stages))
   {
      std::stringstream error_message;
      error_message << "Layout" << "::" << "place_and_load_code_editor" << ": error: " << "guard \"stages\" not met";
      throw std::runtime_error(error_message.str());
   }
bool file_exists = Blast::FileExistenceChecker(filename).exists();

StageInterface *stage = nullptr;

if (file_exists)
{
   Hexagon::CodeEditor::Stage *code_editor_stage = new Hexagon::CodeEditor::Stage({filename, file_category});
   std::string file_contents = php::file_get_contents(filename);
   code_editor_stage->get_code_editor_ref().set_initial_content(file_contents);
   code_editor_stage->set_base_font_color(text_color);
   code_editor_stage->set_backfill_color(backfill_color);

   stage = code_editor_stage;
}
else
{
   stage = new Hexagon::MissingFile::Stage(filename);
}

stage->set_place(place);
stages->push_back(stage);

return true;

}

void Layout::create()
{
for (auto &file : files)
{
   std::string filename = std::get<0>(file);
   std::string file_type = std::get<1>(file);
   placement3d place = std::get<2>(file);
   float x = place.position.x;
   float y = place.position.y;

   place_and_load_code_editor(filename, file_type, x, y, place);
}
return;

}
} // namespace Hexagon


