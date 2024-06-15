

#include <Hexagon/LayoutToStagesCreator.hpp>

#include <Blast/FileExistenceChecker.hpp>
#include <allegro_flare/useful_php.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


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


std::vector<StageInterface *>* LayoutToStagesCreator::get_stages() const
{
   return stages;
}


int LayoutToStagesCreator::get_code_editor_height() const
{
   return code_editor_height;
}


int LayoutToStagesCreator::get_code_editor_width() const
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
      error_message << "[Hexagon::LayoutToStagesCreator::place_and_load_code_editor]: error: guard \"stages\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::LayoutToStagesCreator::place_and_load_code_editor]: error: guard \"stages\" not met");
   }
   if (!(stage_factory))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::LayoutToStagesCreator::place_and_load_code_editor]: error: guard \"stage_factory\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::LayoutToStagesCreator::place_and_load_code_editor]: error: guard \"stage_factory\" not met");
   }
   if (!(layout))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::LayoutToStagesCreator::place_and_load_code_editor]: error: guard \"layout\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::LayoutToStagesCreator::place_and_load_code_editor]: error: guard \"layout\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::LayoutToStagesCreator::place_and_load_code_editor]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::LayoutToStagesCreator::place_and_load_code_editor]: error: guard \"font_bin\" not met");
   }
   bool file_exists = Blast::FileExistenceChecker(filename).exists();

   StageInterface *stage = nullptr;

   if (file_exists)
   {
      stage = stage_factory->create_advanced_code_editor(filename, 123, 70);
   }
   else
   {
      stage = stage_factory->create_missing_file(filename);
   }

   stage->set_place(place);
   stages->push_back(stage);

   return true;
}


} // namespace Hexagon


