#pragma once



#include <Hexagon/CodeMessagePointsOverlay.hpp>
#include <Hexagon/CodeRange.hpp>
#include <Hexagon/StageInterface.hpp>
#include <string>
#include <vector>



namespace CodeEditor
{
   class Renderer;
}



namespace CodeEditor
{
   class CodeEditor : public StageInterface
   {
   public:
      enum mode_t
      {
         EDIT,
         INSERT,
      };

   private:
      friend class ::CodeEditor::Renderer;
      std::vector<std::string> lines;
      int cursor_x;
      int cursor_y;

      mode_t mode;

      bool draw_info_overlay;

      std::string filename;
      std::string file_category;
      std::string search_regex_expression;

      int first_line_number;

      bool content_is_modified;
      void mark_content_is_modified();
      void unmark_content_is_modified();
      bool content_contains_errors;
      void mark_content_contains_errors();
      void unmark_content_contains_errors();

   public:
      CodeEditor(
         std::string filename="unnamed_file.txt",
         std::string file_category="undefined",
         mode_t mode=EDIT,
         type_t type=CODE_EDITOR
         );
      ~CodeEditor();
      // accessors

      void set_cursor_x(int cursor_x);
      void set_cursor_y(int cursor_y);
      std::string get_filename();
      std::string get_file_category();
      bool set_initial_content(std::string content);
      bool set_initial_content(std::vector<std::string> content);
      bool set_content(std::string content);
      bool set_content(std::vector<std::string> content);
      bool set_search_regex_expression(std::string regex_expression);
      placement3d &get_place_ref();
      mode_t get_mode();
      int get_first_line_number();
      int get_cursor_x();
      int get_cursor_y();

      int num_lines();
      int num_columns();
      std::vector<std::string> const &get_lines_ref();
      std::string &current_line_ref();
      std::string &next_line_ref();
      std::string get_current_mode_string();
      std::string get_search_regex_expression();
      int infer_num_lines_to_draw();
      bool infer_cursor_is_on_line_that_exists();

      bool get_content_is_modified();
      bool get_content_contains_errors();

      bool move_cursor_up();
      bool move_cursor_down();
      bool move_cursor_left();
      bool move_cursor_right();
      bool move_cursor_to_last_line();
      bool move_cursor_to_top_of_screen();
      bool move_cursor_to_middle_of_screen();
      bool move_cursor_to_bottom_of_screen();
      bool move_cursor_jump_to_next_word();
      bool move_cursor_jump_to_next_big_word();
      bool move_cursor_to_end_of_next_word();
      bool move_cursor_to_end_of_next_big_word();
      bool move_cursor_jump_to_previous_word();
      bool move_cursor_jump_to_previous_big_word();
      bool move_cursor_to_start_of_line();
      bool move_cursor_to_end_of_line();
      bool move_cursor_to_last_character_of_line();
      bool move_cursor_to_first_non_whitespace_character();
      bool delete_character();
      bool join_lines();
      bool split_lines();
      bool delete_line();
      bool insert_lines(std::vector<std::string> &lines_to_insert);
      bool insert_string(std::string string);
      bool save_file_and_touch_if_symlink();
      bool set_insert_mode();
      bool set_edit_mode();

      // render states

      bool enable_drawing_info_overlay();
      bool disable_drawing_info_overlay();

      // plugins

      std::vector<int> git_modified_line_numbers;

      bool refresh_git_modified_line_numbers();

      //std::vector<CodeMessagePoint> code_message_points;
      //bool showing_code_message_points;
      std::vector<CodeMessagePointsOverlay> code_message_points_overlays;

      bool clear_code_message_points();
      bool set_code_message_points(std::vector<CodeMessagePoint> code_message_points);
      bool jump_to_next_code_point();
      bool jump_to_previous_code_point();
      bool jump_to_next_or_nearest_code_point();
      bool insert_three_spaces_at_start_of_line();

      bool refresh_regex_message_points();

      // presentation

      // actions

      bool offset_first_line_number(int delta);
      bool offset_cursor_position_y(int delta);
      bool move_stage_up(float distance=100);
      bool move_stage_down(float distance=100);
      bool offset_first_line_to_vertically_center_cursor(int distance_from_top=20);
      bool scale_stage_delta(float delta);
      bool create_visual_selection_at_current_cursor_location();
      bool destroy_current_visual_selection();
      bool toggle_currently_grabbing_visual_selection();

      // rendering

      // partials

      bool currently_grabbing_visual_selection;
      std::vector<CodeRange> selections;

      bool set_current_selection_end_x(int x);
      bool set_current_selection_end_y(int y);
      bool yank_selected_text_to_clipboard();
      bool paste_selected_text_from_clipboard();
      // complete

      void render(bool is_focused,
                  ALLEGRO_DISPLAY *display,
                  ALLEGRO_FONT *font,
                  int cell_width,
                  int cell_height
                  ) override;
      void process_local_event(std::string event_name, ActionData action_data1=ActionData()) override;
      void process_event(ALLEGRO_EVENT &event) override;
   };
} // namespace CodeEditor



