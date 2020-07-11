#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <Hexagon/Elements/FontCharacterMapGrid.hpp>
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
         Hexagon::Elements::FontCharacterMapGrid font_character_map_grid;
         static ALLEGRO_EVENT a_default_empty_event;
         bool is_focused;
         ALLEGRO_DISPLAY* display;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;

      public:
         Stage(::CodeEditor::CodeEditor code_editor=::CodeEditor::CodeEditor{}, Hexagon::Elements::FontCharacterMapGrid font_character_map_grid={});
         virtual ~Stage();

         void set_is_focused(bool is_focused);
         void set_display(ALLEGRO_DISPLAY* display);
         void set_font(ALLEGRO_FONT* font);
         void set_cell_width(int cell_width);
         void set_cell_height(int cell_height);

         ::CodeEditor::CodeEditor get_code_editor();
         Hexagon::Elements::FontCharacterMapGrid get_font_character_map_grid();
         bool get_is_focused();
         ALLEGRO_DISPLAY* get_display();
         ALLEGRO_FONT* get_font();
         int get_cell_width();
         int get_cell_height();
         ::CodeEditor::CodeEditor &get_code_editor_ref();
         Hexagon::Elements::FontCharacterMapGrid &get_font_character_map_grid_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      virtual void render() override;
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      };
   }
}



