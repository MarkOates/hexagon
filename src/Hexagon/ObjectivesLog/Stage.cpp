

#include <Hexagon/ObjectivesLog/Stage.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace ObjectivesLog
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage()
   : StageInterface(StageInterface::OBJECTIVES_LOG)
   , objectives_log()
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
         error_message << "Stage" << "::" << "infer_num_list_items" << ": error: " << "guard \"objectives_log\" not met";
         throw std::runtime_error(error_message.str());
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


