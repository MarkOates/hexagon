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
      FILE_NAVIGATOR,
      KEYBOARD_INPUTS_MODAL,
      RERUN_OUTPUT_WATCHER,
   };

private:
   StageInterface::type_t type;
   placement3d place;

public:
   StageInterface(StageInterface::type_t type);
   virtual ~StageInterface();

   StageInterface::type_t get_type();
   placement3d &get_place();
   void set_place(placement3d place);
   bool infer_is_modal();

   virtual void render(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height) = 0;
   virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) = 0;
   virtual void process_event(ALLEGRO_EVENT &event) = 0;

   virtual bool save_file() = 0;
};




