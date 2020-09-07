

#include <Hexagon/LayoutToStagesCreator.hpp>
#include <allegro_flare/useful_php.h>
#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Hexagon/MissingFile/Stage.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


LayoutToStagesCreator::LayoutToStagesCreator(std::vector<StageInterface *>* stages, Hexagon::StageFactory* stage_factory, Hexagon::Layout* layout, AllegroFlare::FontBin* font_bin, int code_editor_height, int code_editor_width, ALLEGRO_COLOR text_color, ALLEGRO_COLOR backfill_color)
   : stages(stages)
   , stage_factory(stage_factory)
   , layout(layout)
   , font_bin(font_bin)
   , code_editor_height(code_editor_height)
   , code_editor_width(code_editor_width)
   , text_color(text_color)
   , backfill_color(backfill_color)
{
}


LayoutToStagesCreator::~LayoutToStagesCreator()
{
}


void LayoutToStagesCreator::set_stages(std::vector<StageInterface *>* stages)
{
   this->stages = stages;
}


std::vector<StageInterface *>* LayoutToStagesCreator::get_stages()
{
   return stages;
}


int LayoutToStagesCreator::get_code_editor_height()
{
   return code_editor_height;
}


int LayoutToStagesCreator::get_code_editor_width()
{
   return code_editor_width;
}


void LayoutToStagesCreator::create()
{
for (auto &file : layout->get_files())
{
   std::string filename = std::get<0>(file);
   std::string file_type = std::get<1>(file);
   placement3d place = std::get<2>(file);

   place_and_load_code_editor(filename, file_type, place);
}
return;

}

bool LayoutToStagesCreator::place_and_load_code_editor(std::string filename, std::string file_category, placement3d place)
{
if (!(stages))
   {
      std::stringstream error_message;
      error_message << "LayoutToStagesCreator" << "::" << "place_and_load_code_editor" << ": error: " << "guard \"stages\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(layout))
   {
      std::stringstream error_message;
      error_message << "LayoutToStagesCreator" << "::" << "place_and_load_code_editor" << ": error: " << "guard \"layout\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "LayoutToStagesCreator" << "::" << "place_and_load_code_editor" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
bool file_exists = Blast::FileExistenceChecker(filename).exists();

StageInterface *stage = nullptr;

if (file_exists)
{
   Hexagon::AdvancedCodeEditor::Stage *code_editor_stage =
      new Hexagon::AdvancedCodeEditor::Stage(font_bin, 123, 70);

   code_editor_stage->initialize();

   std::string file_contents = php::file_get_contents(filename);
   code_editor_stage->set_content(file_contents);
   //code_editor_stage->set_base_font_color(text_color);
   //code_editor_stage->set_backfill_color(backfill_color);

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
} // namespace Hexagon


