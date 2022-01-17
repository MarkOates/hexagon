#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedCodeEditor/AdvancedCodeEditor.hpp>
#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>
#include <Hexagon/AdvancedCodeEditor/Selection.hpp>
#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <Hexagon/CodeMessagePoint.hpp>
#include <Hexagon/CodeMessagePointManager.hpp>
#include <Hexagon/CodeRange.hpp>
#include <Hexagon/DirtyGrid.hpp>
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
         float offset_y;
         float offset_y_updated_at;
         int first_row_offset;
         ALLEGRO_BITMAP* surface_render;
         std::string current_search_regex;
         Hexagon::CodeMessagePointManager code_message_point_manager;
         std::vector<CodeRange> visual_selections;
         bool currently_grabbing_visual_selection;
         std::vector<CodeRange> full_line_visual_selections;
         bool currently_grabbing_full_line_visual_selection;
         std::vector<Hexagon::AdvancedCodeEditor::Selection> selections;
         Hexagon::AdvancedCodeEditor::Selection search_regex_selections;

      public:
         Stage(AllegroFlare::FontBin* font_bin=nullptr, int num_columns=0, int num_rows=0);
         virtual ~Stage();

         void set_filename(std::string filename);
         void set_input_buffer(std::string input_buffer);
         void set_current_search_regex(std::string current_search_regex);
         int get_num_columns();
         int get_num_rows();
         std::string get_filename();
         std::string get_input_buffer();
         bool get_initialized();
         float get_offset_y();
         float get_offset_y_updated_at();
         int get_first_row_offset();
         ALLEGRO_BITMAP* get_surface_render();
         Hexagon::AdvancedCodeEditor::AdvancedCodeEditor &get_advanced_code_editor_ref();
         std::string &get_input_buffer_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         void initialize();
         virtual void destroy() override;
         bool refresh_search_regex_selections();
         void set_code_message_points(std::vector<CodeMessagePoint> code_message_points={});
         bool save_file();
         bool save_file_and_touch_if_symlink();
         bool set_to_edit_mode();
         bool set_to_insert_mode();
         bool cursor_move_up();
         bool cursor_move_down();
         bool cursor_move_left();
         bool cursor_move_right();
         bool cursor_move_to_start_of_line();
         bool cursor_move_to_first_non_whitespace_character();
         bool cursor_move_to_end_of_line();
         bool cursor_jump_to_next_word();
         bool cursor_jump_to_previous_word();
         bool cursor_jump_up_half_page();
         bool cursor_jump_down_half_page();
         bool first_row_offset_move_up();
         bool first_row_offset_move_down();
         bool first_row_offset_jump_to(int new_offset=0);
         bool first_row_offset_jump_up_half_page();
         bool first_row_offset_jump_down_half_page();
         bool first_row_offset_adjust_so_cursor_is_vertically_centered();
         bool cursor_jump_to_next_code_message_point();
         bool cursor_jump_to_previous_code_message_point();
         bool cursor_jump_to_next_search_regex_selection();
         bool cursor_jump_to_previous_search_regex_selection();
         bool delete_character();
         bool join_lines();
         bool split_lines();
         bool delete_line();
         bool insert_string_from_input_buffer();
         bool insert_lines(std::vector<std::string> lines_to_insert={});
         void set_content(std::string content="");
         bool insert_three_spaces_at_start_of_line();
         bool insert_blank_line();
         bool create_visual_selection_at_current_cursor_location();
         bool destroy_current_visual_selection();
         bool toggle_currently_grabbing_visual_selection();
         bool create_full_line_visual_selection_at_current_cursor_location();
         bool destroy_current_full_line_visual_selection();
         bool toggle_currently_grabbing_full_line_visual_selection();
         bool set_current_visual_selection_end_x(int x_pos=0);
         bool set_current_visual_selection_end_y(int y_pos=0);
         bool refresh_current_visual_selection_end_to_current_cursor_position();
         bool yank_selected_text_to_clipboard();
         bool paste_selected_text_from_clipboard();
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
         int cursor_get_x();
         int cursor_get_y();
         bool is_in_edit_mode();
         bool is_in_insert_mode();
         int calculate_natural_width();
         int calculate_half_num_rows();
         int calculate_one_third_num_rows();
         int calculate_natural_height();
         void refresh_render_surfaces();
         void refresh_dirty_cells_on_surface_render_respecting_first_row_offset();
         void refresh_dirty_cells_on_text_mesh();
         void refresh_text_mesh_respecting_first_row_offset();
         void filter_text_mesh_for_syntax_highlights();
         void filter_text_mesh_for_comments();
         void refresh_text_mesh();
         Hexagon::DirtyGrid build_dirty_grid_from_lines_respecting_offset();
      };
   }
}



