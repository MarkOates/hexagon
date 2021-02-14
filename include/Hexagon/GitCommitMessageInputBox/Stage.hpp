#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace GitCommitMessageInputBox
   {
      class Stage : public StageInterface
      {
      private:
         ::CodeEditor::CodeEditor code_editor;
         static ALLEGRO_EVENT a_default_empty_event;
         bool is_focused;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;
         ALLEGRO_COLOR base_font_color;
         ALLEGRO_COLOR backfill_color;
         std::string state;

      public:
         Stage(::CodeEditor::CodeEditor code_editor=::CodeEditor::CodeEditor{});
         virtual ~Stage();

         void set_is_focused(bool is_focused);
         void set_display(ALLEGRO_DISPLAY* display);
         void set_font(ALLEGRO_FONT* font);
         void set_cell_width(int cell_width);
         void set_cell_height(int cell_height);
         void set_base_font_color(ALLEGRO_COLOR base_font_color);
         void set_backfill_color(ALLEGRO_COLOR backfill_color);

         ::CodeEditor::CodeEditor get_code_editor();
         bool get_is_focused();
         ALLEGRO_DISPLAY* get_display();
         ALLEGRO_FONT* get_font();
         int get_cell_width();
         int get_cell_height();
         ALLEGRO_COLOR get_base_font_color();
         ALLEGRO_COLOR get_backfill_color();
         ::CodeEditor::CodeEditor &get_code_editor_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void change_state_to_submitted_and_pending_destruction();
      bool is_state_to_submitted_and_pending_destruction();
      virtual void render() override;
      void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      int code_editor_char_count();
      };
   }
}



