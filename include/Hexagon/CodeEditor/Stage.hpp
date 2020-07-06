#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace CodeEditor
   {
      class Stage : public StageInterface
      {
      private:
         ::CodeEditor::CodeEditor code_editor;
         static ALLEGRO_EVENT a_default_empty_event;
         int cell_width;
         int cell_height;

      public:
         Stage(::CodeEditor::CodeEditor code_editor=::CodeEditor::CodeEditor{});
         ~Stage();

         void set_cell_width(int cell_width);
         void set_cell_height(int cell_height);

         ::CodeEditor::CodeEditor get_code_editor();
         int get_cell_width();
         int get_cell_height();
         ::CodeEditor::CodeEditor &get_code_editor_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void render(bool is_focused=true, ALLEGRO_DISPLAY* display=nullptr, ALLEGRO_FONT* font=nullptr, int _cell_width=10, int _cell_height=20);
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      };
   }
}



