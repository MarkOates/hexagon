#include <Hexagon/EventControllerInterface.hpp>
#include <Hexagon/ActionData.hpp>
#include <allegro5/allegro.h>
#include <string>


class OldFileNavigator;


class OldFileNavigatorEventController : public EventControllerInterface
{
private:
   OldFileNavigator *file_navigator;

public:
   OldFileNavigatorEventController(OldFileNavigator *file_navigator);
   ~OldFileNavigatorEventController();

   static const std::string MOVE_CURSOR_UP;
   static const std::string MOVE_CURSOR_DOWN;

   virtual void process_local_event(std::string event_name, ActionData action_data1=ActionData()) override;
   virtual void process_event(ALLEGRO_EVENT &event) override;
};

