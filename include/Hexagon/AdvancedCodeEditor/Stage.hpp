#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedCodeEditor/AdvancedCodeEditor.hpp>
#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/Elements/TextMesh.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Stage : public StageInterface
      {
      private:
         AllegroFlare::FontBin* font_bin;
         int num_columns;
         int num_rows;
         Hexagon::Elements::TextMesh text_mesh;
         static ALLEGRO_EVENT a_default_empty_event;
         bool initialized;
         Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;

      public:
         Stage(AllegroFlare::FontBin* font_bin=nullptr, int num_columns=0, int num_rows=0);
         virtual ~Stage();


         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         Hexagon::AdvancedCodeEditor::AdvancedCodeEditor &get_advanced_code_editor_ref();
      std::vector<std::string> get_lines();
      Hexagon::AdvancedCodeEditor::Cursor& get_cursor_ref();
      bool delete_character();
      bool join_lines();
      bool split_lines();
      bool delete_line();
      bool insert_lines();
      bool insert_string(std::string string="");
      bool insert_three_spaces_at_start_of_line();
      bool cursor_move_up();
      bool cursor_move_down();
      bool cursor_move_left();
      bool cursor_move_right();
      bool cursor_move_to(int x=0, int y=0);
      void initialize();
      void set_content(std::string content="");
      virtual void render() override;
      virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
      virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      ALLEGRO_FONT* obtain_text_font();
      bool is_cursor_in_bounds();
      bool is_cursor_on_last_line();
      void refresh_text_mesh();
      };
   }
}



