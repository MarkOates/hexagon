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
      ADVANCED_CODE_EDITOR,
      CODE_EDITOR,
      ONE_LINE_INPUT_BOX,
      GIT_COMMIT_MESSAGE_INPUT_BOX,
      FILE_NAVIGATOR,
      COMPONENT_NAVIGATOR,
      PROJECT_COMPONENT_NAVIGATOR,
      KEYBOARD_INPUTS_MODAL,
      NEW_COMPONENT_MAKER,
      MISSING_FILE,
   }; // these types should not be included within the base class

private:
   StageInterface::type_t type;
   bool render_on_hud;
   placement3d place;

public:
   StageInterface(StageInterface::type_t type);
   virtual ~StageInterface();

   StageInterface::type_t get_type();
   std::string get_type_name();
   placement3d &get_place();
   void set_place(placement3d place);
   void set_render_on_hud(bool render_on_hud);
   bool get_render_on_hud();
   bool infer_is_modal(); // this should be removed from the base class

   virtual void render() = 0;
   virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) = 0;
   virtual void process_event(ALLEGRO_EVENT &event) = 0;
   virtual void destroy();
};




