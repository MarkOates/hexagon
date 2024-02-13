#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/ActionQueueRecording.hpp>
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
#include <cstdint>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class Stage : public StageInterface
      {
      public:
         static constexpr uint32_t MODE_EDIT = 0;
         static constexpr uint32_t MODE_INSERT = 1;
         static constexpr char* ACTION_SET_TO_EDIT_MODE = (char*)"set_to_edit_mode";
         static constexpr char* ACTION_SET_TO_INSERT_MODE = (char*)"set_to_insert_mode";

      private:
         AllegroFlare::FontBin* font_bin;
         int num_columns;
         int num_rows;
         Hexagon::Elements::TextMesh text_mesh;
         std::string filename;
         bool represents_symlink;
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
         std::vector<Hexagon::AdvancedCodeEditor::Selection> selections_APPEARS_DEPRECIATED;
         Hexagon::AdvancedCodeEditor::Selection search_regex_selections;
         ActionQueueRecording action_queue_recording;
         bool currently_playing_action_queue_recording;
         ALLEGRO_COLOR syntax_highlight_color;
         ALLEGRO_COLOR on_color;
         ALLEGRO_COLOR comment_color;
         ALLEGRO_COLOR clear_color;
         bool show_line_too_long;
         int max_line_length;
         ALLEGRO_COLOR null_space_color;
         ALLEGRO_COLOR backfill_color;
         void initialize_surface_render();
         bool refresh_search_regex_selections_on_current_line();
         bool indent_unindent_lines(bool indent=true, int num_spaces_to_indent=2);
         ALLEGRO_FONT* obtain_text_font();
         int cursor_get_x();
         int cursor_get_y();
         void refresh_dirty_cells_on_surface_render_respecting_first_row_offset();
         void refresh_dirty_cells_on_text_mesh();
         void refresh_text_mesh_respecting_first_row_offset();
         void filter_text_mesh_for_syntax_highlights();
         void filter_text_mesh_for_comments();
         void filter_text_mesh_for_test_case();
         void filter_text_mesh_for_line_too_long();
         void refresh_text_mesh();

      protected:


      public:
         Stage(AllegroFlare::FontBin* font_bin=nullptr, int num_columns=0, int num_rows=0);
         virtual ~Stage();

         void set_filename(std::string filename);
         void set_represents_symlink(bool represents_symlink);
         void set_input_buffer(std::string input_buffer);
         void set_current_search_regex(std::string current_search_regex);
         void set_syntax_highlight_color(ALLEGRO_COLOR syntax_highlight_color);
         void set_on_color(ALLEGRO_COLOR on_color);
         void set_comment_color(ALLEGRO_COLOR comment_color);
         void set_clear_color(ALLEGRO_COLOR clear_color);
         void set_show_line_too_long(bool show_line_too_long);
         void set_max_line_length(int max_line_length);
         void set_null_space_color(ALLEGRO_COLOR null_space_color);
         void set_backfill_color(ALLEGRO_COLOR backfill_color);
         int get_num_columns() const;
         int get_num_rows() const;
         std::string get_filename() const;
         bool get_represents_symlink() const;
         std::string get_input_buffer() const;
         bool get_initialized() const;
         float get_offset_y() const;
         float get_offset_y_updated_at() const;
         int get_first_row_offset() const;
         ALLEGRO_BITMAP* get_surface_render() const;
         bool get_currently_playing_action_queue_recording() const;
         ALLEGRO_COLOR get_syntax_highlight_color() const;
         ALLEGRO_COLOR get_on_color() const;
         ALLEGRO_COLOR get_comment_color() const;
         ALLEGRO_COLOR get_clear_color() const;
         bool get_show_line_too_long() const;
         int get_max_line_length() const;
         ALLEGRO_COLOR get_null_space_color() const;
         ALLEGRO_COLOR get_backfill_color() const;
         Hexagon::AdvancedCodeEditor::AdvancedCodeEditor &get_advanced_code_editor_ref();
         std::string &get_input_buffer_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         Hexagon::AdvancedCodeEditor::Selection &get_search_regex_selections_ref();
         void initialize();
         virtual void destroy() override;
         bool refresh_search_regex_selections();
         bool refresh_search_regex_selections_on_select_lines(std::vector<int> line_nums={});
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
         bool cursor_move_to_start_of_file();
         bool cursor_move_to_first_non_whitespace_character();
         bool cursor_move_to_end_of_line();
         bool cursor_jump_to_next_word();
         bool cursor_jump_to_next_word_or_last_char();
         bool cursor_jump_to_previous_word();
         bool cursor_jump_up_half_page();
         void append_action_to_action_queue_recording(std::string action_name="[unset-action_name]", ActionData action_data1={});
         void clear_action_queue_recording();
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
         std::string grab_word_under_cursor();
         bool delete_word_under_cursor();
         bool delete_to_end_of_line();
         bool delete_to_next_word();
         bool delete_to_next_word_or_end_of_line();
         bool join_lines();
         bool split_lines();
         bool delete_line();
         bool insert_string_from_input_buffer();
         bool insert_lines(std::vector<std::string> lines_to_insert={});
         void set_content(std::string content="");
         bool toggle_commenting_out_current_line();
         bool insert_three_spaces_at_start_of_line();
         std::set<int> get_line_indices_currently_under_selection();
         bool indent_lines();
         bool unindent_lines();
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
         bool replay_action_queue_recording();
         bool yank_selected_text_to_clipboard();
         bool paste_selected_text_from_clipboard();
         bool replace_content_with_contents_of_clipboard();
         static std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> build_local_events_dictionary();
         static AllegroFlare::KeyboardCommandMapper build_keyboard_command_mapping_for_edit_mode();
         static AllegroFlare::KeyboardCommandMapper build_keyboard_command_mapping_for_insert_mode();
         bool cursor_move_to(int x=0, int y=0);
         virtual void render() override;
         virtual void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         virtual void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
         std::vector<std::string> get_lines();
         Hexagon::AdvancedCodeEditor::Cursor get_cursor();
         bool is_in_edit_mode();
         bool is_in_insert_mode();
         int calculate_natural_width();
         int calculate_half_num_rows();
         int calculate_one_third_num_rows();
         int calculate_natural_height();
         void refresh_render_surfaces();
         Hexagon::DirtyGrid build_dirty_grid_from_lines_respecting_offset();
      };
   }
}



