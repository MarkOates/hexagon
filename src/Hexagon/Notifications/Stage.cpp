

#include <Hexagon/Notifications/Stage.hpp>



namespace Hexagon
{
namespace Notifications
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(std::string body_text)
   : StageInterface(StageInterface::NOTIFICATION)
   , body_text(body_text)
   , component(body_text)
{
}


Stage::~Stage()
{
}


void Stage::set_body_text(std::string body_text)
{
   this->body_text = body_text;
}


std::string Stage::get_body_text()
{
   return body_text;
}


Hexagon::Notifications::Notification &Stage::get_component_ref()
{
   return component;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


void Stage::render()
{
   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   return;
}
} // namespace Notifications
} // namespace Hexagon


