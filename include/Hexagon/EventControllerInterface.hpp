#pragma once



#include <allegro5/allegro.h>
#include <Hexagon/ActionData.hpp>



class EventControllerInterface
{
public:
   EventControllerInterface();
   virtual ~EventControllerInterface();

   virtual void process_local_event(std::string event_name, ActionData action_data1=ActionData()) = 0;
   virtual void process_event(ALLEGRO_EVENT &event) = 0;
};



