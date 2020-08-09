#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedCodeEditor/AdvancedCodeEditor.hpp>
#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <Hexagon/Elements/TextMesh.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <functional>
#include <map>
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
         std::string filename;
         Hexagon::AdvancedCodeEditor::AdvancedCodeEditor advanced_code_editor;
         std::string input_buffer;
         int mode;
         static ALLEGRO_EVENT a_default_empty_event;
         bool initialized;
         ALLEGRO_BITMAP* surface_render;

      public:
         Stage(AllegroFlare::FontBin* font_bin=nullptr, int num_columns=0, int num_rows=0);
         virtual ~Stage();

         void set_filename(std::string filename);
         void set_input_buffer(std::string input_buffer);

         std::string get_filename();
         std::string get_input_buffer();
         bool get_initialized();
         ALLEGRO_BITMAP* get_surface_render();
         Hexagon::AdvancedCodeEditor::AdvancedCodeEditor &get_advanced_code_editor_ref();
         std::string &get_input_buffer_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      void initialize();
      virtual void destroy() override;
      bool save_file();
      bool set_to_edit_mode();
      bool set_to_insert_mode();
      bool cursor_move_up();
      bool cursor_move_down();
      bool cursor_move_left();
      bool cursor_move_right();
      bool cursor_move_to_start_of_line();
      bool cursor_move_to_end_of_line();
      bool cursor_jump_to_next_word();
      bool cursor_jump_to_previous_word();
      bool delete_character();
      bool join_lines();
      bool split_lines();
      bool delete_line();
      bool insert_string_from_input_buffer();
      bool insert_lines(std::vector<std::string> lines_to_insert={});
      void set_content(std::string content="");
      bool insert_three_spaces_at_start_of_line();
      bool insert_blank_line();
      static std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> build_local_events_dictionary();
      static KeyboardCommandMapper build_keyboard_command_mapping_for_edit_mode();
      static KeyboardCommandMapper build_keyboard_command_mapping_for_insert_mode();
      bool cursor_move_to(int x=0, int y=0);
      virtual void render() override;
      virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
      virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      ALLEGRO_FONT* obtain_text_font();
      std::vector<std::string> get_lines();
      Hexagon::AdvancedCodeEditor::Cursor get_cursor();
      bool is_in_edit_mode();
      bool is_in_insert_mode();
      void refresh_render_surfaces();
      void refresh_dirty_cells_on_surface_render();
      void refresh_dirty_cells_on_text_mesh();
      void refresh_text_mesh();
      };
   }
}



