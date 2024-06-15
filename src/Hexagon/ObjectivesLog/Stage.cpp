

#include <Hexagon/ObjectivesLog/Stage.hpp>

#include <Hexagon/ObjectivesLog/ObjectiveRenderer.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace ObjectivesLog
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(AllegroFlare::FontBin* font_bin, Hexagon::ObjectivesLog::ObjectivesLog* objectives_log)
   : StageInterface(StageInterface::OBJECTIVES_LOG)
   , font_bin(font_bin)
   , objectives_log(objectives_log)
   , cursor_pos(0)
{
}


Stage::~Stage()
{
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


Hexagon::ObjectivesLog::ObjectivesLog* &Stage::get_objectives_log_ref()
{
   return objectives_log;
}


void Stage::render()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ObjectivesLog::Stage::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ObjectivesLog::Stage::render]: error: guard \"font_bin\" not met");
   }
   if (!(objectives_log))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ObjectivesLog::Stage::render]: error: guard \"objectives_log\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ObjectivesLog::Stage::render]: error: guard \"objectives_log\" not met");
   }
   placement3d place = get_place();
   std::vector<Hexagon::ObjectivesLog::Objective> &objectives = objectives_log->get_objectives_ref();
   float objectives_width = 700;
   float objectives_height = 100;
   float spacing = 4;
   float y_cursor = 0;
   int objective_item_num = 0;
   ALLEGRO_COLOR cursor_box_color = ALLEGRO_COLOR{0, 1, 1, 1};
   float cursor_box_thickness = 4.0;
   float cursor_box_roundness = 4.0;

   place.start_transform();
   ALLEGRO_TRANSFORM list_offset_transform;
   al_copy_transform(&list_offset_transform, al_get_current_transform());
   al_use_transform(&list_offset_transform);

   for (auto &objective : objectives)
   {
      bool cursor_is_over_current_objective = (objective_item_num == cursor_pos);
      Hexagon::ObjectivesLog::ObjectiveRenderer objective_renderer(
         font_bin,
         &objective,
         objectives_width,
         objectives_height
      );
      objective_renderer.render();

      if (cursor_is_over_current_objective)
      {
         al_draw_rounded_rectangle(
            0,
            0,
            objectives_width,
            objectives_height,
            cursor_box_roundness,
            cursor_box_roundness,
            cursor_box_color,
            cursor_box_thickness
         );
      }

      al_translate_transform(&list_offset_transform, 0, objectives_height + spacing);
      al_use_transform(&list_offset_transform);
      objective_item_num++;
   }

   place.restore_transform();
   return;
}

void Stage::move_cursor_up()
{
   cursor_pos--;
   if (cursor_pos < 0) cursor_pos = infer_num_list_items() - 1;
   return;
}

void Stage::move_cursor_down()
{
   cursor_pos++;
   if (cursor_pos >= infer_num_list_items()) cursor_pos = 0;
   return;
}

int Stage::infer_num_list_items()
{
   if (!(objectives_log))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ObjectivesLog::Stage::infer_num_list_items]: error: guard \"objectives_log\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ObjectivesLog::Stage::infer_num_list_items]: error: guard \"objectives_log\" not met");
   }
   return objectives_log->get_objectives_ref().size();
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   return;
}


} // namespace ObjectivesLog
} // namespace Hexagon


