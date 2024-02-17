

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>

#include <AllegroFlare/Timer.hpp>
#include <Blast/StringJoiner.hpp>
#include <Hexagon/AdvancedCodeEditor/EventController.hpp>
#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <Hexagon/AdvancedCodeEditor/SearchRegexToSelectionsConverter.hpp>
#include <Hexagon/ClipboardData.hpp>
#include <Hexagon/CodeRangeExtractor.hpp>
#include <Hexagon/StringIndenter.hpp>
#include <Hexagon/SymlinkToucher.hpp>
#include <Hexagon/WordRangesFinder.hpp>
#include <Hexagon/util.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


ALLEGRO_EVENT Stage::a_default_empty_event = {};


Stage::Stage(AllegroFlare::FontBin* font_bin, int num_columns, int num_rows)
   : StageInterface(StageInterface::ADVANCED_CODE_EDITOR)
   , font_bin(font_bin)
   , num_columns(num_columns)
   , num_rows(num_rows)
   , text_mesh({nullptr, num_columns, num_rows})
   , filename("untitled.txt")
   , represents_symlink(false)
   , advanced_code_editor({})
   , input_buffer("")
   , mode(0)
   , initialized(false)
   , offset_y(0.0f)
   , offset_y_updated_at(0.0f)
   , first_row_offset(0)
   , surface_render(nullptr)
   , current_search_regex("")
   , code_message_point_manager({})
   , visual_selections({})
   , currently_grabbing_visual_selection(false)
   , full_line_visual_selections({})
   , currently_grabbing_full_line_visual_selection(false)
   , selections_APPEARS_DEPRECIATED({})
   , search_regex_selections(Hexagon::AdvancedCodeEditor::Selection{})
   , action_queue_recording({})
   , currently_playing_action_queue_recording(false)
   , syntax_highlight_color(ALLEGRO_COLOR{0.75f, 0.96f, 1.0f, 1.0f})
   , on_color(ALLEGRO_COLOR{1.0f, 1.0f, 0.0f, 1.0f})
   , comment_color(ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 0.5f})
   , clear_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f})
   , show_line_too_long(false)
   , max_line_length(120)
   , null_space_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.3f})
   , backfill_color(ALLEGRO_COLOR{0.06, 0.06, 0.06, 0.06})
{
}


Stage::~Stage()
{
}


void Stage::set_filename(std::string filename)
{
   this->filename = filename;
}


void Stage::set_represents_symlink(bool represents_symlink)
{
   this->represents_symlink = represents_symlink;
}


void Stage::set_input_buffer(std::string input_buffer)
{
   this->input_buffer = input_buffer;
}


void Stage::set_current_search_regex(std::string current_search_regex)
{
   this->current_search_regex = current_search_regex;
}


void Stage::set_syntax_highlight_color(ALLEGRO_COLOR syntax_highlight_color)
{
   this->syntax_highlight_color = syntax_highlight_color;
}


void Stage::set_on_color(ALLEGRO_COLOR on_color)
{
   this->on_color = on_color;
}


void Stage::set_comment_color(ALLEGRO_COLOR comment_color)
{
   this->comment_color = comment_color;
}


void Stage::set_clear_color(ALLEGRO_COLOR clear_color)
{
   this->clear_color = clear_color;
}


void Stage::set_show_line_too_long(bool show_line_too_long)
{
   this->show_line_too_long = show_line_too_long;
}


void Stage::set_max_line_length(int max_line_length)
{
   this->max_line_length = max_line_length;
}


void Stage::set_null_space_color(ALLEGRO_COLOR null_space_color)
{
   this->null_space_color = null_space_color;
}


void Stage::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


int Stage::get_num_columns() const
{
   return num_columns;
}


int Stage::get_num_rows() const
{
   return num_rows;
}


std::string Stage::get_filename() const
{
   return filename;
}


bool Stage::get_represents_symlink() const
{
   return represents_symlink;
}


std::string Stage::get_input_buffer() const
{
   return input_buffer;
}


bool Stage::get_initialized() const
{
   return initialized;
}


float Stage::get_offset_y() const
{
   return offset_y;
}


float Stage::get_offset_y_updated_at() const
{
   return offset_y_updated_at;
}


int Stage::get_first_row_offset() const
{
   return first_row_offset;
}


ALLEGRO_BITMAP* Stage::get_surface_render() const
{
   return surface_render;
}


bool Stage::get_currently_playing_action_queue_recording() const
{
   return currently_playing_action_queue_recording;
}


ALLEGRO_COLOR Stage::get_syntax_highlight_color() const
{
   return syntax_highlight_color;
}


ALLEGRO_COLOR Stage::get_on_color() const
{
   return on_color;
}


ALLEGRO_COLOR Stage::get_comment_color() const
{
   return comment_color;
}


ALLEGRO_COLOR Stage::get_clear_color() const
{
   return clear_color;
}


bool Stage::get_show_line_too_long() const
{
   return show_line_too_long;
}


int Stage::get_max_line_length() const
{
   return max_line_length;
}


ALLEGRO_COLOR Stage::get_null_space_color() const
{
   return null_space_color;
}


ALLEGRO_COLOR Stage::get_backfill_color() const
{
   return backfill_color;
}


Hexagon::AdvancedCodeEditor::AdvancedCodeEditor &Stage::get_advanced_code_editor_ref()
{
   return advanced_code_editor;
}


std::string &Stage::get_input_buffer_ref()
{
   return input_buffer;
}


ALLEGRO_EVENT &Stage::get_a_default_empty_event_ref()
{
   return a_default_empty_event;
}


Hexagon::AdvancedCodeEditor::Selection &Stage::get_search_regex_selections_ref()
{
   return search_regex_selections;
}


void Stage::initialize()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Stage::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Stage::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::initialize: error: guard \"font_bin\" not met");
   }
   if (initialized) return;

   text_mesh.set_font(obtain_text_font());
   text_mesh.initialize();

   initialize_surface_render();

   advanced_code_editor.cursor_set_width(text_mesh.get_cell_width());
   advanced_code_editor.cursor_set_height(text_mesh.get_cell_height());

   get_place().size = vec3d(
      calculate_natural_width(),
      calculate_natural_height(),
      0
   );

   initialized = true;
   return;
}

void Stage::initialize_surface_render()
{
   ALLEGRO_STATE previous_render_state;
   al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP);
   // TODO: may choose to add some bitmap flags
   surface_render = al_create_bitmap(
      calculate_natural_width(),
      calculate_natural_height()
   );
   al_set_target_bitmap(surface_render);
   al_clear_to_color(clear_color);
   al_restore_state(&previous_render_state);
   return;
}

void Stage::destroy()
{
   if (surface_render) al_destroy_bitmap(surface_render);
   initialized = false;
   return;
}

bool Stage::refresh_search_regex_selections()
{
   if (current_search_regex.empty())
   {
      search_regex_selections.clear();
   }
   else
   {
      Hexagon::AdvancedCodeEditor::SearchRegexToSelectionsConverter converter(
         current_search_regex, get_lines());
      search_regex_selections = converter.convert();
   }
   return true;
}

bool Stage::refresh_search_regex_selections_on_select_lines(std::vector<int> line_nums)
{
   // HERE
   // 1) clear selections on select lines
   search_regex_selections.clear_select_lines(line_nums);

   if (current_search_regex.empty()) return true;

   // 2) get select lines
   std::map<int, std::string> select_lines = advanced_code_editor.get_select_lines(line_nums);

   // 3) run SearchRegexToSelectionsConverter on these lines (TODO)
   Hexagon::AdvancedCodeEditor::SearchRegexToSelectionsConverter converter(current_search_regex);

   std::vector<CodeRange> result_ranges;
   for (auto &select_line : select_lines)
   {
      Hexagon::AdvancedCodeEditor::SearchRegexToSelectionsConverter converter(
         current_search_regex, std::vector<std::string>({ select_line.second })
      );
      std::vector<CodeRange> created_ranges = converter.convert();

      // 3.1) convert the result selections to their expected line nums
      for (auto &regex_selection : created_ranges)
      {
         int this_line_num = select_line.first;
         regex_selection.move(0, this_line_num);

         // 3.2) insert the selections into the existing search_regex_selections
         search_regex_selections.add(regex_selection);
      }
   }

   return true;
}

void Stage::set_code_message_points(std::vector<CodeMessagePoint> code_message_points)
{
   code_message_point_manager.set_code_message_points(code_message_points);
   return;
}

bool Stage::save_file()
{
   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();
   ::save_file(lines, filename);
   advanced_code_editor.unmark_content_is_modified();
   return true;
}

bool Stage::save_file_and_touch_if_symlink()
{
   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();
   Hexagon::SymlinkToucher symlink_toucher(filename); // this is only needed because of rerun

   ::save_file(lines, filename);
   symlink_toucher.touch_if_symlink();
   advanced_code_editor.unmark_content_is_modified();

   return true;
}

bool Stage::set_to_edit_mode()
{
   mode = MODE_EDIT;
   return true;
}

bool Stage::set_to_insert_mode()
{
   mode = MODE_INSERT;
   if (currently_grabbing_visual_selection) toggle_currently_grabbing_visual_selection();
   if (currently_grabbing_full_line_visual_selection) toggle_currently_grabbing_full_line_visual_selection();
   return true;
}

bool Stage::cursor_move_up()
{
   bool result = advanced_code_editor.cursor_move_up();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_move_down()
{
   bool result = advanced_code_editor.cursor_move_down();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_move_left()
{
   bool result = advanced_code_editor.cursor_move_left();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_move_right()
{
   bool result = advanced_code_editor.cursor_move_right();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_move_to_start_of_line()
{
   bool result = advanced_code_editor.cursor_move_to_start_of_line();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_move_to_start_of_file()
{
   bool result = advanced_code_editor.cursor_move_to_start_of_file();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_move_to_first_non_whitespace_character()
{
   bool result = advanced_code_editor.cursor_move_to_first_non_whitespace_character();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_move_to_end_of_line()
{
   bool result = advanced_code_editor.cursor_move_to_end_of_line();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_jump_to_next_word()
{
   bool result = advanced_code_editor.cursor_jump_to_next_word();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_jump_to_next_word_or_last_char()
{
   bool result = advanced_code_editor.cursor_jump_to_next_word_or_last_char();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_jump_to_previous_word()
{
   bool result = advanced_code_editor.cursor_jump_to_previous_word();
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::cursor_jump_up_half_page()
{
   // TODO: account for "surface_render"
   int new_y = advanced_code_editor.cursor_get_y() - num_rows / 2;
   if (new_y < 0) new_y = 0;
   bool result = advanced_code_editor.cursor_set_y(new_y); // TODO also only allow this behavior if will go out
                                                           // of bounds and not if already out of bounds going
                                                           // further out of bounds
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

void Stage::append_action_to_action_queue_recording(std::string action_name, ActionData action_data1)
{
   action_queue_recording.append_action(Action(action_name, action_data1));
   return;
}

void Stage::clear_action_queue_recording()
{
   action_queue_recording.clear_actions();
   return;
}

bool Stage::cursor_jump_down_half_page()
{
   // TODO: account for "surface_render"
   int new_y = advanced_code_editor.cursor_get_y() + num_rows / 2;
   int num_lines = advanced_code_editor.get_lines_ref().size();
   if (new_y >= (num_lines - 1)) new_y = num_lines - 1; // TODO also only allow this behavior if will go out of
                                                        // bounds and not if already out of bounds going further
                                                        // out of bounds

   bool result = advanced_code_editor.cursor_set_y(new_y);
   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

bool Stage::first_row_offset_move_up()
{
   // TODO: account for "surface_render"
   first_row_offset -= 1;
   refresh_text_mesh_respecting_first_row_offset(); // <-- this can be optimized
   return true;
}

bool Stage::first_row_offset_move_down()
{
   // TODO: account for "surface_render"
   first_row_offset += 1;
   refresh_text_mesh_respecting_first_row_offset(); // <-- this can be optimized
   return true;
}

bool Stage::first_row_offset_jump_to(int new_offset)
{
   // TODO: account for "surface_render"
   first_row_offset = new_offset;
   refresh_text_mesh_respecting_first_row_offset(); // <-- this can be optimized
   return true;
}

bool Stage::first_row_offset_jump_up_half_page()
{
   // TODO: account for "surface_render"
   first_row_offset = first_row_offset - calculate_half_num_rows();
   refresh_text_mesh_respecting_first_row_offset(); // <-- this can be optimized
   return true;
}

bool Stage::first_row_offset_jump_down_half_page()
{
   // TODO: account for "surface_render"
   first_row_offset = first_row_offset + calculate_half_num_rows();
   refresh_text_mesh_respecting_first_row_offset(); // <-- this can be optimized
   return true;
}

bool Stage::first_row_offset_adjust_so_cursor_is_vertically_centered()
{
   // TODO: account for "surface_render"
   first_row_offset = cursor_get_y() - calculate_one_third_num_rows();
   refresh_text_mesh_respecting_first_row_offset(); // <-- this can be optimized
   return true;
}

bool Stage::cursor_jump_to_next_code_message_point()
{
   return true;
}

bool Stage::cursor_jump_to_previous_code_message_point()
{
   return true;
}

bool Stage::cursor_jump_to_next_search_regex_selection()
{
   // TODO: account for "surface_render"
   CodePoint next_position = search_regex_selections.find_next_from(cursor_get_x(), cursor_get_y());
   cursor_move_to(next_position.get_x(), next_position.get_y());
   first_row_offset_jump_to(cursor_get_y() - 20); // TODO get a constant offset other than 20
   refresh_text_mesh_respecting_first_row_offset(); // <-- this can be optimized
   refresh_current_visual_selection_end_to_current_cursor_position();
   return true;
}

bool Stage::cursor_jump_to_previous_search_regex_selection()
{
   CodePoint previous_position = search_regex_selections.find_previous_from(cursor_get_x(), cursor_get_y());
   cursor_move_to(previous_position.get_x(), previous_position.get_y());
   first_row_offset_jump_to(cursor_get_y() - 20); // TODO get a constant offset other than 20
   refresh_text_mesh_respecting_first_row_offset(); // <-- this can be optimized
   refresh_current_visual_selection_end_to_current_cursor_position();
   return true;
}

bool Stage::delete_character()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::delete_character]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::delete_character: error: guard \"initialized\" not met");
   }
   bool result = advanced_code_editor.delete_character();
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   if (result) refresh_search_regex_selections_on_current_line();
   refresh_current_visual_selection_end_to_current_cursor_position(); // TODO: only do if result == true
   return result;
}

bool Stage::refresh_search_regex_selections_on_current_line()
{
   return refresh_search_regex_selections_on_select_lines({cursor_get_y()});
}

std::string Stage::grab_word_under_cursor()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::grab_word_under_cursor]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::grab_word_under_cursor: error: guard \"initialized\" not met");
   }
   if (cursor_get_y() < 0) return "";
   if (cursor_get_y() >= advanced_code_editor.get_lines_ref().size()) return "";

   // get word ranges
   std::string line_content = advanced_code_editor.get_lines_ref()[cursor_get_y()];
   Hexagon::WordRangesFinder word_ranges_finder(line_content, cursor_get_x());

   std::pair<int, int> found_word_ranges = word_ranges_finder.find_ranges();
   // if word ranges are invalid, return false
   if (!word_ranges_finder.is_valid(found_word_ranges)) return "";

   std::string word_under_cursor = line_content.substr(found_word_ranges.first, found_word_ranges.second);

   return word_under_cursor;
}

bool Stage::delete_word_under_cursor()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::delete_word_under_cursor]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::delete_word_under_cursor: error: guard \"initialized\" not met");
   }
   if (cursor_get_y() < 0) return false;
   if (cursor_get_y() >= advanced_code_editor.get_lines_ref().size()) return false;

   // get word ranges
   std::string line_content = advanced_code_editor.get_lines_ref()[cursor_get_y()];
   Hexagon::WordRangesFinder word_ranges_finder(line_content, cursor_get_x());

   std::pair<int, int> found_word_ranges = word_ranges_finder.find_ranges();
   // if word ranges are invalid, return false
   if (!word_ranges_finder.is_valid(found_word_ranges)) return false;

   // move cursor to beginning of inside word
   cursor_move_to(found_word_ranges.first, cursor_get_y());

   // delete n characters, the length of the word
   // if any delete_character() returns false, set the result to false
   bool result = true;
   int num_characters_to_delete = found_word_ranges.second;
   for (int i=0; i<num_characters_to_delete; i++)
   {
      bool this_deletion = advanced_code_editor.delete_character();
      if (!this_deletion) result = false;
   }

   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   refresh_current_visual_selection_end_to_current_cursor_position(); // TODO: consider on if result == true
   if (result) refresh_search_regex_selections_on_current_line();

   return result;
}

bool Stage::delete_to_end_of_line()
{
   bool result = advanced_code_editor.delete_to_end_of_line();
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   if (result) refresh_search_regex_selections_on_current_line();
   return result;
}

bool Stage::delete_to_next_word()
{
   bool result = advanced_code_editor.delete_to_next_word();
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   if (result) refresh_search_regex_selections_on_current_line();
   return result;
}

bool Stage::delete_to_next_word_or_end_of_line()
{
   bool result = advanced_code_editor.delete_to_next_word_or_end_of_line();
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   if (result) refresh_search_regex_selections_on_current_line();
   return result;
}

bool Stage::join_lines()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::join_lines]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::join_lines: error: guard \"initialized\" not met");
   }
   bool join_lines_was_successful = advanced_code_editor.join_lines();
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   if (join_lines_was_successful)
   {
      // 1) clear search_regex_selections on current line and line below it
      search_regex_selections.clear_select_lines({cursor_get_y(), cursor_get_y()+1});
      // 2) move subsequent search_regex_selections up one line
      search_regex_selections.pull_up_from(cursor_get_y()+1, 1);
      // 3) refresh search_regex_selections on newly joined line
      refresh_search_regex_selections_on_select_lines({cursor_get_y()});
   }
   refresh_current_visual_selection_end_to_current_cursor_position();
   return join_lines_was_successful;
}

bool Stage::split_lines()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::split_lines]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::split_lines: error: guard \"initialized\" not met");
   }
   bool split_was_successful = advanced_code_editor.split_lines();
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   if (split_was_successful)
   {
      // 1) delete the regex selections on this line
      search_regex_selections.clear_select_lines({cursor_get_y()});
      // 2) push down all regex selections from this line down
      search_regex_selections.push_down_from(cursor_get_y(), 1);
      // 3) refresh selections on the two lines from the split (TODO)
      refresh_search_regex_selections_on_select_lines({cursor_get_y(), cursor_get_y()+1});
   }
   refresh_current_visual_selection_end_to_current_cursor_position();
   return split_was_successful;
}

bool Stage::delete_line()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::delete_line]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::delete_line: error: guard \"initialized\" not met");
   }
   bool delete_line_was_successful = advanced_code_editor.delete_line();
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   if (delete_line_was_successful)
   {
      search_regex_selections.clear_select_lines({cursor_get_y()});
      search_regex_selections.pull_up_from(cursor_get_y()+1, 1);
   }
   refresh_current_visual_selection_end_to_current_cursor_position();
   return delete_line_was_successful;
}

bool Stage::insert_string_from_input_buffer()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::insert_string_from_input_buffer]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::insert_string_from_input_buffer: error: guard \"initialized\" not met");
   }
   bool result = advanced_code_editor.insert_string(input_buffer);
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   refresh_current_visual_selection_end_to_current_cursor_position(); // TODO: consider only if result == true
   if (result) refresh_search_regex_selections_on_current_line();
   return result;
}

bool Stage::insert_lines(std::vector<std::string> lines_to_insert)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::insert_lines]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::insert_lines: error: guard \"initialized\" not met");
   }
   bool result = advanced_code_editor.insert_lines(lines_to_insert);
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();

   // reposition regular expression highlights
   search_regex_selections.push_down_from(cursor_get_y(), lines_to_insert.size());

   refresh_current_visual_selection_end_to_current_cursor_position();
   return result;
}

void Stage::set_content(std::string content)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::set_content]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::set_content: error: guard \"initialized\" not met");
   }
   advanced_code_editor.set_content(content);
   advanced_code_editor.unmark_content_is_modified();
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   if (currently_grabbing_visual_selection) toggle_currently_grabbing_visual_selection();
   if (currently_grabbing_full_line_visual_selection) toggle_currently_grabbing_full_line_visual_selection();
   search_regex_selections.clear();
   return;
}

bool Stage::toggle_commenting_out_current_line()
{
   // TODO, this currently only adds the comment
   if (cursor_get_y() < 0) return false;
   if (cursor_get_y() >= advanced_code_editor.get_lines_ref().size()) return false;

   std::string current_line_content = advanced_code_editor.get_lines_ref()[cursor_get_y()];
   int previous_cursor_x = cursor_get_x();
   std::size_t first_non_whitespace_character_pos = current_line_content.find_first_not_of(" ");

   // are the first two characters comments?
   bool current_line_starts_with_comment_chars = false;
   if (current_line_content.substr(first_non_whitespace_character_pos, 2) == "\/\/")
      current_line_starts_with_comment_chars = true;

   if (!current_line_starts_with_comment_chars)
   {
      // insert two slashes
      advanced_code_editor.cursor_set_x(first_non_whitespace_character_pos);
      advanced_code_editor.insert_string("\/\/");
      if (previous_cursor_x >= first_non_whitespace_character_pos)
      {
         advanced_code_editor.cursor_set_x(previous_cursor_x+2);
      }
   }
   else
   {
      // remove two slashes
      advanced_code_editor.cursor_set_x(first_non_whitespace_character_pos);
      advanced_code_editor.delete_character();
      advanced_code_editor.delete_character();
      if (previous_cursor_x >= first_non_whitespace_character_pos)
      {
         advanced_code_editor.cursor_set_x(previous_cursor_x-2);
      }
   }

   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   refresh_current_visual_selection_end_to_current_cursor_position();
   refresh_search_regex_selections_on_current_line();

   return true;
}

bool Stage::insert_three_spaces_at_start_of_line()
{
   if (cursor_get_y() < 0) return false;
   if (cursor_get_y() >= advanced_code_editor.get_lines_ref().size()) return false;

   int previous_cursor_x = cursor_get_x();

   advanced_code_editor.cursor_set_x(0);
   advanced_code_editor.insert_string("   ");
   advanced_code_editor.cursor_set_x(previous_cursor_x+3);

   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();

   refresh_current_visual_selection_end_to_current_cursor_position();
   refresh_search_regex_selections_on_current_line();

   return true;
}

std::set<int> Stage::get_line_indices_currently_under_selection()
{
   std::set<int> result;
   if (currently_grabbing_visual_selection)
   {
      for (auto &visual_selection : visual_selections)
      {
         std::set<int> line_numbers = visual_selection.infer_line_numbers();
         result.insert(line_numbers.begin(), line_numbers.end());
      }
   }
   if (currently_grabbing_full_line_visual_selection)
   {
      for (auto &full_line_visual_selection : full_line_visual_selections)
      {
         std::set<int> line_numbers = full_line_visual_selection.infer_line_numbers();
         result.insert(line_numbers.begin(), line_numbers.end());
      }
   }
   return result;
}

bool Stage::indent_lines()
{
   return indent_unindent_lines(true, 2);
}

bool Stage::unindent_lines()
{
   return indent_unindent_lines(false, 2);
}

bool Stage::indent_lines_by_single_space()
{
   return indent_unindent_lines(true, 1);
}

bool Stage::unindent_lines_by_single_space()
{
   return indent_unindent_lines(false, 1);
}

bool Stage::indent_unindent_lines(bool indent, int num_spaces_to_indent)
{
   // TODO: Test this method
   if (cursor_get_y() < 0) return false;
   if (cursor_get_y() >= advanced_code_editor.get_lines_ref().size()) return false;

   // Grab the lines under selection
   std::set<int> line_numbers = get_line_indices_currently_under_selection();

   // If no lines are selected, use the cursor's current y location
   // TODO: Test this condition
   if (line_numbers.empty()) line_numbers.insert(cursor_get_y());

   std::vector<int> line_numbers_as_vector(line_numbers.begin(), line_numbers.end());
   std::map<int, std::string> select_lines = advanced_code_editor.get_select_lines(line_numbers_as_vector);
   std::vector<std::string> select_lines_raw;
   for (auto &select_line : select_lines) select_lines_raw.push_back(select_line.second);

   if (indent)
   {
      select_lines_raw = Hexagon::StringIndenter::indent_lines(select_lines_raw, num_spaces_to_indent);
   }
   else
   {
      select_lines_raw = Hexagon::StringIndenter::unindent_lines(select_lines_raw, num_spaces_to_indent);
   }
   std::map<int, std::string> select_lines_result = select_lines;

   // TODO: Validate select_lines_raw and select_lines_result are the same size

   int i=0;
   for (auto &select_line_result : select_lines_result)
   {
      select_line_result.second = select_lines_raw[i];
      i++;
   }

   advanced_code_editor.set_select_lines(select_lines_result);

   // Do all the dirty refreshing
   if (advanced_code_editor.any_dirty_cells()) refresh_render_surfaces();
   refresh_current_visual_selection_end_to_current_cursor_position();
   refresh_search_regex_selections_on_select_lines(line_numbers_as_vector);

   return true;
}

bool Stage::insert_blank_line()
{
   bool result = insert_lines({ {} });
   return result;
}

bool Stage::create_visual_selection_at_current_cursor_location()
{
   visual_selections.push_back(CodeRange(cursor_get_x(), cursor_get_y(), cursor_get_x()+1, cursor_get_y()));
   return true;
}

bool Stage::destroy_current_visual_selection()
{
   visual_selections.clear();
   return true;
}

bool Stage::toggle_currently_grabbing_visual_selection()
{
   // TODO: have this untoggle if either full_line or not

   // if either is on, turn them both off
   if (currently_grabbing_visual_selection || currently_grabbing_full_line_visual_selection)
   {
      currently_grabbing_visual_selection = false;
      destroy_current_visual_selection();
      currently_grabbing_full_line_visual_selection = false;
      destroy_current_full_line_visual_selection();
   }
   // else if both are off turn on visual
   else
   {
      currently_grabbing_visual_selection = true;
      create_visual_selection_at_current_cursor_location();
   }
   return true;
}

bool Stage::create_full_line_visual_selection_at_current_cursor_location()
{
   full_line_visual_selections.push_back(
      CodeRange(cursor_get_x(), cursor_get_y(), cursor_get_x()+1, cursor_get_y())
   );
   return true;
}

bool Stage::destroy_current_full_line_visual_selection()
{
   full_line_visual_selections.clear();
   return true;
}

bool Stage::toggle_currently_grabbing_full_line_visual_selection()
{
   // TODO: have this untoggle if either full_line or not

   // if either is on, turn them both off
   if (currently_grabbing_visual_selection || currently_grabbing_full_line_visual_selection)
   {
      currently_grabbing_visual_selection = false;
      destroy_current_visual_selection();
      currently_grabbing_full_line_visual_selection = false;
      destroy_current_full_line_visual_selection();
   }
   // else if both are off turn on full line visual
   else
   {
      currently_grabbing_full_line_visual_selection = true;
      create_full_line_visual_selection_at_current_cursor_location();
   }
   return true;
}

bool Stage::set_current_visual_selection_end_x(int x_pos)
{
   // TODO: write test for this conditional behavior
   if (visual_selections.empty() && full_line_visual_selections.empty()) return true;
   if (!visual_selections.empty() && !full_line_visual_selections.empty())
   {
      throw std::runtime_error("unexpected state, both visual_slections and full_line_visual_selections");
   }

   if (!visual_selections.empty())
   {
      visual_selections.back().set_cursor_end_x(x_pos);
   }
   else if (!full_line_visual_selections.empty())
   {
      full_line_visual_selections.back().set_cursor_end_x(x_pos);
   }
   return true;
}

bool Stage::set_current_visual_selection_end_y(int y_pos)
{
   // TODO: write test for this conditional behavior
   if (visual_selections.empty() && full_line_visual_selections.empty()) return true;
   if (!visual_selections.empty() && !full_line_visual_selections.empty())
   {
      throw std::runtime_error("unexpected state, both visual_slections and full_line_visual_selections");
   }

   if (!visual_selections.empty())
   {
      visual_selections.back().set_cursor_end_y(y_pos);
   }
   else if (!full_line_visual_selections.empty())
   {
      full_line_visual_selections.back().set_cursor_end_y(y_pos);
   }
   return true;
}

bool Stage::refresh_current_visual_selection_end_to_current_cursor_position()
{
   // TODO: write test for this conditional behavior
   if (visual_selections.empty() && full_line_visual_selections.empty()) return true;
   if (!visual_selections.empty() && !full_line_visual_selections.empty())
   {
      throw std::runtime_error("unexpected state, both visual_slections and full_line_visual_selections");
   }

   if (!visual_selections.empty())
   {
      visual_selections.back().set_cursor_end_x(cursor_get_x());
      visual_selections.back().set_cursor_end_y(cursor_get_y());
   }
   else if (!full_line_visual_selections.empty())
   {
      full_line_visual_selections.back().set_cursor_end_x(cursor_get_x());
      full_line_visual_selections.back().set_cursor_end_y(cursor_get_y());
   }
   return true;
}

bool Stage::replay_action_queue_recording()
{
   Hexagon::AdvancedCodeEditor::EventController event_controller(this, build_local_events_dictionary());
   return false;

   //currently_playing_action_queue_recording = true;
   //for (auto &action : action_queue_recording.get_actions_ref())
   //{
      //std::string action_name = action.get_name();
      //ActionData action_data1 = action.get_data1();

      //event_controller.process_local_event(action_name, action_data1);
   //}
   //currently_playing_action_queue_recording = false;
   //return true;
}

bool Stage::yank_selected_text_to_clipboard()
{
   // TODO: write test for this conditional behavior
   if (visual_selections.empty() && full_line_visual_selections.empty())
   {
      throw std::runtime_error("aosoadsofaodfaofd");
      return false;
   }
   if (!visual_selections.empty() && !full_line_visual_selections.empty())
   {
      throw std::runtime_error("unexpected state, both visual_slections and full_line_visual_selections");
   }

   if (!visual_selections.empty())
   {
      CodeRange visual_selection = visual_selections.back();
      std::vector<std::string> extracted_selection = Hexagon::CodeRangeExtractor(
         &advanced_code_editor.get_lines_ref(),
         &visual_selection
      ).extract();
      ClipboardData::store(extracted_selection);
   }
   else if (!full_line_visual_selections.empty())
   {
      CodeRange full_line_visual_selection = full_line_visual_selections.back();
      std::vector<std::string> extracted_selection = Hexagon::CodeRangeExtractor(
         &advanced_code_editor.get_lines_ref(),
         &full_line_visual_selection
      ).extract_full_lines();
      ClipboardData::store(extracted_selection);
   }
   else
   {
      // TODO: improve this error message
      throw std::runtime_error("RarsoxxxadsofXfjaodfij");
      return false;
   }
   return true;
}

bool Stage::paste_selected_text_from_clipboard()
{
   std::vector<std::string> retrieved_clipboard_data = ClipboardData::retrieve();
   insert_lines(retrieved_clipboard_data);
   return true;
}

bool Stage::replace_content_with_contents_of_clipboard()
{
   std::vector<std::string> retrieved_clipboard_data = ClipboardData::retrieve();
   Blast::StringJoiner joiner(retrieved_clipboard_data, "\n");
   set_content(joiner.join());
   return true;
}

std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> Stage::build_local_events_dictionary()
{
   std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> local_events = {
      // modification
      { "delete_character", &Hexagon::AdvancedCodeEditor::Stage::delete_character },
      { "delete_word_under_cursor", &Hexagon::AdvancedCodeEditor::Stage::delete_word_under_cursor },
      { "delete_to_end_of_line", &Hexagon::AdvancedCodeEditor::Stage::delete_to_end_of_line },
      { "delete_to_next_word", &Hexagon::AdvancedCodeEditor::Stage::delete_to_next_word },
      { "delete_to_next_word_or_end_of_line",
         &Hexagon::AdvancedCodeEditor::Stage::delete_to_next_word_or_end_of_line },
      { "split_lines", &Hexagon::AdvancedCodeEditor::Stage::split_lines },
      { "join_lines", &Hexagon::AdvancedCodeEditor::Stage::join_lines },
      { "delete_line", &Hexagon::AdvancedCodeEditor::Stage::delete_line },
      { "toggle_commenting_out_current_line",
         &Hexagon::AdvancedCodeEditor::Stage::toggle_commenting_out_current_line },
      { "insert_string_from_input_buffer", &Hexagon::AdvancedCodeEditor::Stage::insert_string_from_input_buffer },
      { "insert_blank_line", &Hexagon::AdvancedCodeEditor::Stage::insert_blank_line },
      { "insert_three_spaces_at_start_of_line",
         &Hexagon::AdvancedCodeEditor::Stage::insert_three_spaces_at_start_of_line },
      { "indent_lines", &Hexagon::AdvancedCodeEditor::Stage::indent_lines},
      { "unindent_lines", &Hexagon::AdvancedCodeEditor::Stage::unindent_lines},
      { "indent_lines_by_single_space", &Hexagon::AdvancedCodeEditor::Stage::indent_lines_by_single_space},
      { "unindent_lines_by_single_space", &Hexagon::AdvancedCodeEditor::Stage::unindent_lines_by_single_space},


      // modes
      { ACTION_SET_TO_EDIT_MODE, &Hexagon::AdvancedCodeEditor::Stage::set_to_edit_mode },
      { ACTION_SET_TO_INSERT_MODE, &Hexagon::AdvancedCodeEditor::Stage::set_to_insert_mode },


      // cursor movement
      { "cursor_move_up", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_up },
      { "cursor_move_down", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_down },
      { "cursor_move_left", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_left },
      { "cursor_move_right", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_right },
      { "cursor_move_to_start_of_line", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_to_start_of_line },
      { "cursor_move_to_start_of_file", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_to_start_of_file },
      { "cursor_move_to_end_of_line", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_to_end_of_line },
      { "cursor_move_to_first_non_whitespace_character",
         &Hexagon::AdvancedCodeEditor::Stage::cursor_move_to_first_non_whitespace_character },
      { "cursor_jump_to_next_word_or_last_char",
         &Hexagon::AdvancedCodeEditor::Stage::cursor_jump_to_next_word_or_last_char },
      { "cursor_jump_to_previous_word", &Hexagon::AdvancedCodeEditor::Stage::cursor_jump_to_previous_word },
      { "cursor_jump_up_half_page", &Hexagon::AdvancedCodeEditor::Stage::cursor_jump_up_half_page },
      { "cursor_jump_down_half_page", &Hexagon::AdvancedCodeEditor::Stage::cursor_jump_down_half_page },
      { "cursor_jump_to_next_search_regex_selection",
         &Hexagon::AdvancedCodeEditor::Stage::cursor_jump_to_next_search_regex_selection },
      { "cursor_jump_to_previous_search_regex_selection",
         &Hexagon::AdvancedCodeEditor::Stage::cursor_jump_to_previous_search_regex_selection },


      // first_row_offset
      { "first_row_offset_move_up", &Hexagon::AdvancedCodeEditor::Stage::first_row_offset_move_up },
      { "first_row_offset_move_down", &Hexagon::AdvancedCodeEditor::Stage::first_row_offset_move_down },
      { "first_row_offset_jump_up_half_page",
         &Hexagon::AdvancedCodeEditor::Stage::first_row_offset_jump_up_half_page },
      { "first_row_offset_jump_down_half_page",
         &Hexagon::AdvancedCodeEditor::Stage::first_row_offset_jump_down_half_page },
      { "first_row_offset_adjust_so_cursor_is_vertically_centered",
         &Hexagon::AdvancedCodeEditor::Stage::first_row_offset_adjust_so_cursor_is_vertically_centered },


      // visual_selections
      { "toggle_currently_grabbing_visual_selection",
        &Hexagon::AdvancedCodeEditor::Stage::toggle_currently_grabbing_visual_selection },
      { "toggle_currently_grabbing_full_line_visual_selection",
        &Hexagon::AdvancedCodeEditor::Stage::toggle_currently_grabbing_full_line_visual_selection },


      // file_saving
      { "save_file", &Hexagon::AdvancedCodeEditor::Stage::save_file },


      // clipboard
      { "yank_selected_text_to_clipboard",
        &Hexagon::AdvancedCodeEditor::Stage::yank_selected_text_to_clipboard },
      { "paste_selected_text_from_clipboard",
        &Hexagon::AdvancedCodeEditor::Stage::paste_selected_text_from_clipboard },
      { "replace_content_with_contents_of_clipboard",
        &Hexagon::AdvancedCodeEditor::Stage::replace_content_with_contents_of_clipboard },


      // action queue
      { "replay_action_queue_recording",
        &Hexagon::AdvancedCodeEditor::Stage::replay_action_queue_recording },

   };
   return local_events;
}

AllegroFlare::KeyboardCommandMapper Stage::build_keyboard_command_mapping_for_edit_mode()
{
   AllegroFlare::KeyboardCommandMapper result;
   result.set_mapping(ALLEGRO_KEY_K, 0, { "cursor_move_up" });
   result.set_mapping(ALLEGRO_KEY_J, 0, { "cursor_move_down" });
   result.set_mapping(ALLEGRO_KEY_J, ALLEGRO_KEYMOD_SHIFT, { "join_lines" });
   result.set_mapping(ALLEGRO_KEY_H, 0, { "cursor_move_left" });
   result.set_mapping(ALLEGRO_KEY_L, 0, { "cursor_move_right" });
   result.set_mapping(ALLEGRO_KEY_0, 0, { "cursor_move_to_start_of_line" });
   result.set_mapping(ALLEGRO_KEY_4, ALLEGRO_KEYMOD_SHIFT, { "cursor_move_to_end_of_line" });
   result.set_mapping(ALLEGRO_KEY_W, 0, { "cursor_jump_to_next_word_or_last_char" });
   result.set_mapping(ALLEGRO_KEY_B, 0, { "cursor_jump_to_previous_word" });
   result.set_mapping(ALLEGRO_KEY_U, AllegroFlare::KeyboardCommandMapper::CTRL, {
      "cursor_jump_up_half_page",
      "first_row_offset_adjust_so_cursor_is_vertically_centered",
      });
   result.set_mapping(ALLEGRO_KEY_D, AllegroFlare::KeyboardCommandMapper::CTRL, {
      "cursor_jump_down_half_page",
      "first_row_offset_adjust_so_cursor_is_vertically_centered",
      });
   result.set_mapping(ALLEGRO_KEY_B, 0, { "cursor_jump_to_previous_word" });
   result.set_mapping(ALLEGRO_KEY_N, 0, { "cursor_jump_to_next_search_regex_selection" });
   result.set_mapping(ALLEGRO_KEY_N, ALLEGRO_KEYMOD_SHIFT, { "cursor_jump_to_previous_search_regex_selection" });
   result.set_mapping(ALLEGRO_KEY_Y, AllegroFlare::KeyboardCommandMapper::CTRL, { "first_row_offset_move_up" });
   result.set_mapping(ALLEGRO_KEY_E, AllegroFlare::KeyboardCommandMapper::CTRL, { "first_row_offset_move_down" });
   result.set_mapping(ALLEGRO_KEY_X, 0, { "delete_character" });
   result.set_mapping(ALLEGRO_KEY_BACKSPACE, ALLEGRO_KEYMOD_SHIFT, { "delete_line" });
   result.set_mapping(ALLEGRO_KEY_S, AllegroFlare::KeyboardCommandMapper::COMMAND, { "save_file" });
   result.set_mapping(ALLEGRO_KEY_I, 0, { "set_to_insert_mode" });
   result.set_mapping(ALLEGRO_KEY_SLASH, AllegroFlare::KeyboardCommandMapper::SHIFT, {
      "toggle_commenting_out_current_line"
      });
   result.set_mapping(ALLEGRO_KEY_Z, 0, {
      "first_row_offset_adjust_so_cursor_is_vertically_centered",
      });
   result.set_mapping(ALLEGRO_KEY_I, ALLEGRO_KEYMOD_SHIFT, {
      "cursor_move_to_first_non_whitespace_character",
      "set_to_insert_mode",
      });
   result.set_mapping(ALLEGRO_KEY_S, 0, {
      "delete_character",
      "set_to_insert_mode",
      });
   result.set_mapping(ALLEGRO_KEY_A, 0, {
      "cursor_move_right",
      "set_to_insert_mode",
      });
   result.set_mapping(ALLEGRO_KEY_A, ALLEGRO_KEYMOD_SHIFT, {
      "cursor_move_to_end_of_line",
      "cursor_move_right",
      "set_to_insert_mode",
      });
   result.set_mapping(ALLEGRO_KEY_O, 0, {
      "cursor_move_down",
      "insert_blank_line",
      "cursor_move_to_start_of_line",
      "set_to_insert_mode",
      });
   result.set_mapping(ALLEGRO_KEY_O, ALLEGRO_KEYMOD_SHIFT, {
      "insert_blank_line",
      "cursor_move_to_start_of_line",
      "set_to_insert_mode",
      });
   result.set_mapping(ALLEGRO_KEY_FULLSTOP, ALLEGRO_KEYMOD_SHIFT, {
      "indent_lines", //"insert_three_spaces_at_start_of_line",
      });
   result.set_mapping(ALLEGRO_KEY_COMMA, ALLEGRO_KEYMOD_SHIFT, {
      "unindent_lines",
      });
   result.set_mapping(
      ALLEGRO_KEY_FULLSTOP,
      AllegroFlare::KeyboardCommandMapper::COMMAND | AllegroFlare::KeyboardCommandMapper::SHIFT,
      { "indent_lines_by_single_space", });
   result.set_mapping(
      ALLEGRO_KEY_COMMA,
      AllegroFlare::KeyboardCommandMapper::COMMAND | AllegroFlare::KeyboardCommandMapper::SHIFT,
      { "unindent_lines_by_single_space", });
   result.set_mapping(ALLEGRO_KEY_V, 0, { "toggle_currently_grabbing_visual_selection" });
   result.set_mapping(ALLEGRO_KEY_V, ALLEGRO_KEYMOD_SHIFT, {
      "toggle_currently_grabbing_full_line_visual_selection"
   });
   result.set_mapping(ALLEGRO_KEY_Y, 0, { "yank_selected_text_to_clipboard" });
   result.set_mapping(ALLEGRO_KEY_P, ALLEGRO_KEYMOD_SHIFT, { "paste_selected_text_from_clipboard" });
   result.set_mapping(ALLEGRO_KEY_ENTER, 0, { "cursor_move_down", "insert_blank_line" });
   result.set_mapping(ALLEGRO_KEY_ENTER, ALLEGRO_KEYMOD_SHIFT, { "insert_blank_line" });
   result.set_mapping(ALLEGRO_KEY_P,
         AllegroFlare::KeyboardCommandMapper::COMMAND | AllegroFlare::KeyboardCommandMapper::SHIFT,
         { "replace_content_with_contents_of_clipboard" }
   );
   result.set_mapping(ALLEGRO_KEY_FULLSTOP, 0, { "replay_action_queue_recording" });

   return result;
}

AllegroFlare::KeyboardCommandMapper Stage::build_keyboard_command_mapping_for_insert_mode()
{
   AllegroFlare::KeyboardCommandMapper result;
   result.set_mapping(ALLEGRO_KEY_UP, 0, { "cursor_move_up" });
   result.set_mapping(ALLEGRO_KEY_DOWN, 0, { "cursor_move_down" });
   result.set_mapping(ALLEGRO_KEY_LEFT, 0, { "cursor_move_left" });
   result.set_mapping(ALLEGRO_KEY_RIGHT, 0, { "cursor_move_right" });

   result.set_mapping(ALLEGRO_KEY_ENTER, 0, { "split_lines", "cursor_move_down", "cursor_move_to_start_of_line" });
   result.set_mapping(ALLEGRO_KEY_BACKSPACE, 0, { "cursor_move_left", "delete_character" });

   result.set_mapping(ALLEGRO_KEY_OPENBRACE, AllegroFlare::KeyboardCommandMapper::CTRL, { "set_to_edit_mode" });
   result.set_mapping(ALLEGRO_KEY_S, AllegroFlare::KeyboardCommandMapper::COMMAND, { "save_file" });
   return result;
}

bool Stage::cursor_move_to(int x, int y)
{
   advanced_code_editor.cursor_move_to(x, y);
   return true;
}

void Stage::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::render: error: guard \"initialized\" not met");
   }
   placement3d &place = get_place();
   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

   std::vector<Hexagon::AdvancedCodeEditor::Selection> selections = {
      Hexagon::AdvancedCodeEditor::Selection{
         //std::vector<CodeRange>{ CodeRange{4, 5, 10, 6} },
      },
   };


   //ALLEGRO_COLOR null_space_color = ALLEGRO_COLOR{0, 0, 0, 0.3};

   Hexagon::AdvancedCodeEditor::Renderer renderer(
      &text_mesh,
      surface_render,
      &advanced_code_editor.get_cursor_ref(),
      &selections,
      &search_regex_selections,
      &visual_selections,
      &full_line_visual_selections,
      &code_message_point_manager.get_code_message_points_ref(),
      &lines,
      place.size.x,
      place.size.y,
      is_in_insert_mode(),
      0.0f,
      first_row_offset,
      true, // show line numbers
      obtain_text_font(),
      advanced_code_editor.get_content_is_modified(),
      represents_symlink,
      advanced_code_editor.is_cursor_in_bounds()
   );

   renderer.set_backfill_color(get_backfill_color());
   renderer.set_null_space_color(get_null_space_color());
   renderer.set_line_numbers_color(get_on_color());

   place.start_transform();
   renderer.render();
   place.restore_transform();

   return;
}

void Stage::process_local_event(std::string event_name, ActionData action_data)
{
   Hexagon::AdvancedCodeEditor::EventController event_controller(this, build_local_events_dictionary());
   event_controller.process_local_event(event_name, action_data);
   return;
}

void Stage::process_event(ALLEGRO_EVENT& event)
{
   AllegroFlare::KeyboardCommandMapper keyboard_command_mapping;
   if (is_in_insert_mode()) keyboard_command_mapping = build_keyboard_command_mapping_for_insert_mode();
   else if (is_in_edit_mode()) keyboard_command_mapping = build_keyboard_command_mapping_for_edit_mode();

   Hexagon::AdvancedCodeEditor::EventController event_controller(
         this,
         build_local_events_dictionary(),
         keyboard_command_mapping
      );
   event_controller.process_event(event);
   return;
}

ALLEGRO_FONT* Stage::obtain_text_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Stage::obtain_text_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::obtain_text_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Menlo-Regular.ttf -20");
}

std::vector<std::string> Stage::get_lines()
{
   return advanced_code_editor.get_lines();
}

Hexagon::AdvancedCodeEditor::Cursor Stage::get_cursor()
{
   return advanced_code_editor.get_cursor_ref();
}

int Stage::cursor_get_x()
{
   return advanced_code_editor.get_cursor_ref().get_x();
}

int Stage::cursor_get_y()
{
   return advanced_code_editor.get_cursor_ref().get_y();
}

bool Stage::is_in_edit_mode()
{
   return mode == MODE_EDIT;
}

bool Stage::is_in_insert_mode()
{
   return mode == MODE_INSERT;
}

int Stage::calculate_natural_width()
{
   return num_columns * text_mesh.get_cell_width();
}

int Stage::calculate_half_num_rows()
{
   return num_rows / 2;
}

int Stage::calculate_one_third_num_rows()
{
   return num_rows / 3;
}

int Stage::calculate_natural_height()
{
   return num_rows * text_mesh.get_cell_height();
}

void Stage::refresh_render_surfaces()
{
   AllegroFlare::Timer timer;

   //std::cout << "------------" << std::endl;
   //std::cout << "-num dirty cells: " << advanced_code_editor.dirty_cell_count() << std::endl;

   timer.reset(); timer.start();
   //refresh_dirty_cells_on_text_mesh();
   refresh_text_mesh_respecting_first_row_offset();
   //timer.pause(); std::cout << " refresh_dirty_cells_on_text_mesh: "
   //                         << timer.get_elapsed_time_microseconds() << std::endl;

   timer.reset(); timer.start();
   refresh_dirty_cells_on_surface_render_respecting_first_row_offset();
   //timer.pause(); std::cout << " refresh_dirty_cells_on_surface_render_respecting_first_row_offset: "
   //                         << timer.get_elapsed_time_microseconds() << std::endl;

   advanced_code_editor.dirty_grid_clear();

   return;
}

void Stage::refresh_dirty_cells_on_surface_render_respecting_first_row_offset()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::refresh_dirty_cells_on_surface_render_respecting_first_row_offset]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::refresh_dirty_cells_on_surface_render_respecting_first_row_offset: error: guard \"initialized\" not met");
   }
   ALLEGRO_STATE previous_render_state;
   al_store_state(&previous_render_state, ALLEGRO_STATE_TARGET_BITMAP | ALLEGRO_STATE_BLENDER);
   al_set_target_bitmap(surface_render);
   al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);

   std::vector<std::pair<int, int>> transposed_dirty_cells;
   for (auto dirty_cell : advanced_code_editor.get_dirty_cells())
   {
      std::get<1>(dirty_cell) -= first_row_offset;
      transposed_dirty_cells.push_back(dirty_cell);
   }

   text_mesh.render_only_select_cells(transposed_dirty_cells);
      //advanced_code_editor.get_dirty_cells());

   al_restore_state(&previous_render_state);
   return;
}

void Stage::refresh_dirty_cells_on_text_mesh()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::refresh_dirty_cells_on_text_mesh]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::refresh_dirty_cells_on_text_mesh: error: guard \"initialized\" not met");
   }
   char clear_char = '\0';
   //ALLEGRO_COLOR clear_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};
   //ALLEGRO_COLOR on_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

   int text_mesh_max_x = num_columns;
   int text_mesh_max_y = num_rows;

   for (auto &cell : advanced_code_editor.get_dirty_cells())
   {
      char char_to_set = clear_char;
      ALLEGRO_COLOR color_to_set = clear_color;
      int &x = cell.first;
      int &y = cell.second;

      if (y >= text_mesh_max_y) continue;
      if (x >= text_mesh_max_x) continue;

      if (y < lines.size())
      {
         if (x < lines[y].size())
         {
            char_to_set = lines[y][x];
            color_to_set = on_color;
         }
      }

      text_mesh.set_cell_character(x, y, char_to_set);
      text_mesh.set_cell_color(x, y, color_to_set);
   }
   return;
}

void Stage::refresh_text_mesh_respecting_first_row_offset()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::refresh_text_mesh_respecting_first_row_offset]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::refresh_text_mesh_respecting_first_row_offset: error: guard \"initialized\" not met");
   }
   // TODO: optimize this. It does no need to wipe and refresh the entire mesh,
   // it should be able to move existing vertexes by the previous offset.
   // There's definitely some fun research to be done here.

   char clear_char = '\0';
   //ALLEGRO_COLOR clear_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};
   //ALLEGRO_COLOR on_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

   for (unsigned y=0; y<num_rows; y++)
   {
      for (unsigned x=0; x<num_columns; x++)
      {
         char char_to_set = clear_char;
         ALLEGRO_COLOR color_to_set = clear_color;

         int this_row_num = first_row_offset + y;
         if (this_row_num >= 0 && this_row_num < lines.size())
         {
            if (x < lines[this_row_num].size())
            {
               char_to_set = lines[this_row_num][x];
               color_to_set = on_color;
            }
         }

         text_mesh.set_cell_character(x, y, char_to_set);
         text_mesh.set_cell_color(x, y, color_to_set);
      }
   }
   filter_text_mesh_for_syntax_highlights();
   filter_text_mesh_for_comments();
   filter_text_mesh_for_test_case();
   if (show_line_too_long) filter_text_mesh_for_line_too_long();
   return;
}

void Stage::filter_text_mesh_for_syntax_highlights()
{
   //ALLEGRO_COLOR highlight_color = al_color_html("f590b2"); // pink
   //ALLEGRO_COLOR highlight_color = al_color_html("a2a0f5"); // a purpley color
   ALLEGRO_COLOR highlight_color = get_syntax_highlight_color();
   //ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};
   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

   std::vector<std::string> strings_to_match = {
      "properties:",
      "  - class:",
      "  - name:",
      "    constructor_arg:",
      "    getter:",
      "    const:",
      "    exposed:",
      "    constexpr:",
      "    static:",
      "    type:",
      "    setter: before_initialized", // TODO: Nice feature would be to make this "before_initialized" orange
      "    setter:",
      "    init_with:",
      "    getter_ref:",
      "    private:",
      "    guards:",
      "    parameters:",
      "      - name:",
      "        type:",
      "        default_argument:",
      "        default_argument_dependency_symbols:",
      "    body:",
      "    body_dependency_symbols:",
      "enums:",
      "  - name:",
      "  - enumerators:",
      "    enumerators:",
      "  - type:",
      "    type:",
      "  - start_from:",
      "    start_from:",
      "headers:",
      "parent_classes:",
      "    class:",
      "    scope:",
      "methods:",
      //"functions:",
      "    virtual:",
      "    override:",
      "dependencies:",
      "  - symbol:",
      "    headers:",
      "documentation:",
      "  - overview:", // Consider "overview", "overview_html" or "overview_markdown"
      "  - todos:",
      "  - notes:",
   };

   for (unsigned y=0; y<num_rows; y++)
   {
      int this_row_num = first_row_offset + y;
      if (this_row_num >= 0 && this_row_num < lines.size())
      {
         std::string &this_line = lines[this_row_num];
         for (auto &string_to_match : strings_to_match)
         {
            if (this_line.find(string_to_match) == std::size_t(0))
            {
               int num_characters_to_process = std::min((int)string_to_match.size(), num_columns);
               for (unsigned c=0; c<num_characters_to_process; c++)
               {
                  text_mesh.set_cell_color(c, y, highlight_color);
               }
            }
         }
      }
   }
   return;
}

void Stage::filter_text_mesh_for_comments()
{
   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();
   //std::string string_to_match = " //";
   std::string string_to_match = "//";

   for (unsigned y=0; y<num_rows; y++)
   {
      int this_row_num = first_row_offset + y;
      if (this_row_num >= 0 && this_row_num < lines.size())
      {
         std::string &this_line = lines[this_row_num];
         //for (auto &string_to_match : strings_to_match)
         //{
            std::size_t found_pos = this_line.find(string_to_match);
            if (found_pos != std::string::npos)
            {
               int end_to_process = std::min((int)this_line.size(), num_columns);
               for (unsigned c=found_pos; c<end_to_process; c++)
               {
                  text_mesh.set_cell_color(c, y, comment_color);
               }
            }
         //}
      }
   }
   return;
}

void Stage::filter_text_mesh_for_test_case()
{
   //ALLEGRO_COLOR highlight_color = ALLEGRO_COLOR{0.5f, 0.5f, 0.5f, 0.5f};
   //ALLEGRO_COLOR highlight_color = al_color_html("a2a0f5"); // a purpley color
   ALLEGRO_COLOR highlight_color = get_syntax_highlight_color();
   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();
   std::vector<std::string> strings_to_match = {
      "TEST(",
      "TEST_F(",
   };

   for (unsigned y=0; y<num_rows; y++)
   {
      int this_row_num = first_row_offset + y;
      if (this_row_num >= 0 && this_row_num < lines.size())
      {
         std::string &this_line = lines[this_row_num];
         for (auto &string_to_match : strings_to_match)
         {
            std::size_t found_pos = this_line.find(string_to_match);
            if (found_pos == std::size_t(0))
            {
               // test line matched
               int num_characters_to_process = std::min((int)this_line.size(), num_columns);
               for (unsigned c=0; c<num_characters_to_process; c++)
               {
                  text_mesh.set_cell_color(c, y, highlight_color);
               }
               // TODO: check one line forward
               // if any ) is present at end-of-line
            }
         }
      }
   }
   return;
}

void Stage::filter_text_mesh_for_line_too_long()
{
   ALLEGRO_COLOR line_too_long_color = ALLEGRO_COLOR{0.9f, 0.4f, 0.42f, 1.0f};
   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

   for (unsigned y=0; y<num_rows; y++)
   {
      int this_row_num = first_row_offset + y;
      if (this_row_num < 0 && this_row_num >= lines.size()) continue;
      bool this_line_is_too_long = false;

      std::string &this_line = lines[this_row_num];
      
      if (this_line.size() > max_line_length) this_line_is_too_long = true;

      if (this_line_is_too_long)
      {
         int num_characters_to_process = std::min((int)this_line.size(), num_columns);
         for (unsigned c=0; c<num_characters_to_process; c++)
         {
            text_mesh.set_cell_color(c, y, line_too_long_color);
         }
      }
   }
   return;
}

void Stage::refresh_text_mesh()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Stage::refresh_text_mesh]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Stage::refresh_text_mesh: error: guard \"initialized\" not met");
   }
   char clear_char = '\0';

   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();

   for (unsigned y=0; y<num_rows; y++)
   {
      for (unsigned x=0; x<num_columns; x++)
      {
         char char_to_set = clear_char;
         ALLEGRO_COLOR color_to_set = clear_color;

         if (y < lines.size())
         {
            if (x < lines[y].size())
            {
               char_to_set = lines[y][x];
               color_to_set = on_color;
            }
         }

         text_mesh.set_cell_character(x, y, char_to_set);
         text_mesh.set_cell_color(x, y, color_to_set);
      }
   }
   return;
}

Hexagon::DirtyGrid Stage::build_dirty_grid_from_lines_respecting_offset()
{
   std::vector<std::string> &lines = advanced_code_editor.get_lines_ref();
   Hexagon::DirtyGrid result;

   for (int row=0; row<num_rows; row++)
   {
      int line_num_to_render = row + first_row_offset;
      if (line_num_to_render < 0 || line_num_to_render >= lines.size()) continue;

      result.mark_row_as_dirty(row, 0, lines[line_num_to_render].length());
   }
   return result;
}


} // namespace AdvancedCodeEditor
} // namespace Hexagon


