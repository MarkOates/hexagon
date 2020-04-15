#pragma once



#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/placement3d.h>
#include <Hexagon/ActionData.hpp>
#include <string>



class StageInterface
{
public:
   enum type_t
   {
      NONE,
      CODE_EDITOR,
      ONE_LINE_INPUT_BOX,
      GIT_COMMIT_MESSAGE_INPUT_BOX,
      OLD_FILE_NAVIGATOR,
      FILE_NAVIGATOR,
      COMPONENT_NAVIGATOR,
      KEYBOARD_INPUTS_MODAL,
      RERUN_OUTPUT_WATCHER,
      MISSING_FILE,
   }; // these types should not be included within the base class

private:
   StageInterface::type_t type;
   placement3d place;

public:
   StageInterface(StageInterface::type_t type);
   virtual ~StageInterface();

   StageInterface::type_t get_type();
   placement3d &get_place();
   void set_place(placement3d place);
   bool infer_is_modal(); // this should be removed from the base class

   virtual void render(bool is_focused, ALLEGRO_DISPLAY *display=nullptr, ALLEGRO_FONT *font=nullptr, int cell_width=0, int cell_height=0) = 0;
   virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) = 0;
   virtual void process_event(ALLEGRO_EVENT &event) = 0;
};




