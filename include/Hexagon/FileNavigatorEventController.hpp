#include <Hexagon/EventControllerInterface.hpp>
#include <Hexagon/ActionData.hpp>
#include <allegro5/allegro.h>
#include <string>


class FileNavigator;


class FileNavigatorEventController : public EventControllerInterface
{
private:
   FileNavigator *file_navigator;

public:
   FileNavigatorEventController(FileNavigator *file_navigator);
   ~FileNavigatorEventController();

   static const std::string MOVE_CURSOR_UP;
   static const std::string MOVE_CURSOR_DOWN;

   virtual void process_local_event(std::string event_name, ActionData action_data1=ActionData()) override;
   virtual void process_event(ALLEGRO_EVENT &event) override;
};

