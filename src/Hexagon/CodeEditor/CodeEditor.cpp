


#include <Hexagon/CodeEditor/CodeEditor.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <Hexagon/RegexMatcher.hpp> // should be in Blast?
#include <Blast/StringSplitter.hpp>
#include <Hexagon/GitLinesModifiedExtractor.hpp>
#include <Hexagon/Elements/StageInfoOverlay.hpp>
#include <Hexagon/CodeRangeExtractor.hpp>
#include <Hexagon/ClipboardData.hpp>
#include <Hexagon/SymlinkToucher.hpp>
#include <Hexagon/CodeEditor/EventController.hpp>
#include <Hexagon/util.hpp>
#include <Hexagon/shared_globals.hpp>
#include <Hexagon/shared_globals.hpp>
#include <allegro_flare/color.h> // for color::color



#include <Hexagon/CodeEditor/Stage.hpp>



namespace CodeEditor
{



CodeEditor::CodeEditor(std::string filename, std::string file_category, mode_t mode, StageInterface::type_t type)
   //: StageInterface(type)
   : content_is_modified(false)
   , cursor_x(0)
   , cursor_y(0)
   , mode(mode)
   , draw_info_overlay(false)
   , type(type)
   , filename(filename)
   , file_category(file_category)
   , search_regex_expression("")
   //, place(place)
   , first_line_number(0)
   , code_message_points_overlays()
   , currently_grabbing_visual_selection(false)
   , selections()
{
   code_message_points_overlays.push_back(CodeMessagePointsOverlay(al_color_name("dogerblue"), {}));
}



CodeEditor::~CodeEditor()
{}



void CodeEditor::mark_content_is_modified()
{
   content_is_modified = true;
}



void CodeEditor::unmark_content_is_modified()
{
   content_is_modified = false;
}


bool CodeEditor::get_content_is_modified()
{
   return content_is_modified;
}


void CodeEditor::mark_content_contains_errors()
{
   content_contains_errors = true;
}


void CodeEditor::unmark_content_contains_errors()
{
   content_contains_errors = false;
}


bool CodeEditor::get_content_contains_errors()
{
   return this->content_contains_errors;
}


// accessors

void CodeEditor::set_cursor_x(int cursor_x)
{
   this->cursor_x = cursor_x;
   set_current_selection_end_x(cursor_x + 1);
}



void CodeEditor::set_cursor_y(int cursor_y)
{
   this->cursor_y = cursor_y;
   set_current_selection_end_y(cursor_y);
}



std::string CodeEditor::get_filename()
{
   return filename;
}



StageInterface::type_t StageInterface::get_type()
{
   return type;
}



std::string CodeEditor::get_file_category()
{
   return file_category;
}



bool CodeEditor::set_initial_content(std::string content)
{
   set_content(content);
   unmark_content_is_modified();
   return true;
}



bool CodeEditor::set_initial_content(std::vector<std::string> content)
{
   set_content(content);
   unmark_content_is_modified();
   return true;
}



bool CodeEditor::set_content(std::string content)
{
   lines = Blast::StringSplitter(content, '\n').split();
   mark_content_is_modified();
   return true;
}



bool CodeEditor::set_content(std::vector<std::string> content)
{
   lines = content;
   mark_content_is_modified();
   return true;
}


bool CodeEditor::set_search_regex_expression(std::string regex_expression)
{
   this->search_regex_expression = regex_expression;
   return true;
}



CodeEditor::mode_t CodeEditor::get_mode()
{
   return mode;
}



int CodeEditor::get_first_line_number()
{
   return first_line_number;
}



int CodeEditor::get_cursor_x()
{
   return cursor_x;
}



int CodeEditor::get_cursor_y()
{
   return cursor_y;
}



std::string CodeEditor::get_search_regex_expression()
{
   return this->search_regex_expression;
}



// inference

int CodeEditor::num_lines()
{
   return lines.size();
}



int CodeEditor::num_columns()
{
   if (cursor_y >= lines.size()) return -1;
   return lines[cursor_y].length();
}



std::vector<std::string> const &CodeEditor::get_lines_ref()
{
   return lines;
}



std::string &CodeEditor::current_line_ref()
{
   return lines[cursor_y];
}



std::string &CodeEditor::next_line_ref()
{
   return lines[cursor_y+1];
}



std::string CodeEditor::get_current_mode_string()
{
   if (mode == EDIT) return (currently_grabbing_visual_selection ? "EDIT - VISUAL" : "EDIT");
   if (mode == INSERT) return "INSERT";
   return "---";
}



// inference

int CodeEditor::infer_num_lines_to_draw()
{
   return 50;
}



bool CodeEditor::infer_cursor_is_on_line_that_exists()
{
   if (cursor_y < 0) return false;
   if (cursor_y >= num_lines()) return false;
   return true;
}



// actions


bool CodeEditor::move_cursor_up()
{
   if (cursor_y <= 0) return false;

   set_cursor_y(cursor_y - 1);
   return true;
}



bool CodeEditor::move_cursor_down()
{
   if (cursor_y >= (num_lines() - 1)) return false;

   set_cursor_y(cursor_y + 1);
   return true;
}



bool CodeEditor::move_cursor_left()
{
   if (cursor_x <= 0) return false;
   set_cursor_x(cursor_x - 1);
   return true;
}



bool CodeEditor::move_cursor_right()
{
   set_cursor_x(cursor_x + 1);
   return true;
}



bool CodeEditor::move_cursor_to_last_line()
{
   if (num_lines() == 0) return false;

   else set_cursor_y(num_lines() - 1);
   return true;
}


bool CodeEditor::move_cursor_to_top_of_screen()
{
   set_cursor_y(first_line_number);
   return true;
}



bool CodeEditor::move_cursor_to_middle_of_screen()
{
   set_cursor_y(first_line_number + infer_num_lines_to_draw()/2);
   return true;
}



bool CodeEditor::move_cursor_to_bottom_of_screen()
{
   set_cursor_y(first_line_number + infer_num_lines_to_draw()-1);
   return true;
}



bool CodeEditor::move_cursor_jump_to_next_word()
{
   // This regex from vimdoc.sourceforge.net/htmldoc/motion.html#word
   std::string vim_equivelent_word_jump_regex = "([0-9a-zA-Z_]+)|([^0-9a-zA-Z_ \\s]+)";

   RegexMatcher regex_matcher(current_line_ref(), vim_equivelent_word_jump_regex);
   std::vector<std::pair<int, int>> match_positions = regex_matcher.get_match_info();

   for (auto &match_position : match_positions)
   {
      if (match_position.first > cursor_x)
      {
         set_cursor_x(match_position.first);
         return true;
      }


   }

   return false;
}



bool CodeEditor::move_cursor_jump_to_next_big_word()
{
   // this regex from vimdoc.sourceforge.net/htmldoc/motion.html#word
   std::string vim_equivelent_word_jump_regex = "([0-9a-zA-Z_]+)|([^0-9a-zA-Z_ \\s]+)";
   //std::string vim_equivelent_word_jump_regex = "[^\\s]+";

   RegexMatcher regex_matcher(current_line_ref(), vim_equivelent_word_jump_regex);
   std::vector<std::pair<int, int>> match_positions = regex_matcher.get_match_info();

   for (auto &match_position : match_positions)
   {
      if (match_position.first > cursor_x)
      {
         set_cursor_x(match_position.first);
         return true;
      }
   }

   return false;
}



bool CodeEditor::move_cursor_to_end_of_next_word()
{
   // this regex from: vimdoc.sourceforge.net/htmldoc/motion.html#word
   std::string vim_equivelent_word_jump_regex = "([0-9a-zA-Z_]+)|([^0-9a-zA-Z_ \\s]+)";

   RegexMatcher regex_matcher(current_line_ref(), vim_equivelent_word_jump_regex);
   std::vector<std::pair<int, int>> match_positions = regex_matcher.get_match_info();

   for (auto &match_position : match_positions)
   {
      int position = match_position.first + match_position.second - 1;
      if (position > cursor_x)
      {
         set_cursor_x(position);
         return true;
      }
   }

   return false;
}



bool CodeEditor::move_cursor_to_end_of_next_big_word()
{
   // This regex from vimdoc.sourceforge.net/htmldoc/motion.html#word
   std::string vim_equivelent_word_jump_regex = "[^\\s]+";

   RegexMatcher regex_matcher(current_line_ref(), vim_equivelent_word_jump_regex);
   std::vector<std::pair<int, int>> match_positions = regex_matcher.get_match_info();

   for (auto &match_position : match_positions)
   {
      int position = match_position.first + match_position.second - 1;
      if (position > cursor_x)
      {
         set_cursor_x(position);
         return true;
      }
   }

   return false;
}



bool CodeEditor::move_cursor_jump_to_previous_word()
{
   int position = 0;

   position = rfind_whitespace(current_line_ref(), cursor_x);
   if (position != -1) { set_cursor_x(position); }

   position = rfind_non_whitespace(current_line_ref(), cursor_x);
   if (position != -1) { set_cursor_x(position); return true; }

   return false;
}



bool CodeEditor::move_cursor_jump_to_previous_big_word()
{
   int position = 0;

   position = rfind_whitespace(current_line_ref(), cursor_x);
   if (position != -1) { set_cursor_x(position); }

   position = rfind_non_whitespace(current_line_ref(), cursor_x);
   if (position != -1) { set_cursor_x(position); return true; }

   return false;
}



bool CodeEditor::move_cursor_to_start_of_line()
{
   set_cursor_x(0);
   return true;
}



bool CodeEditor::move_cursor_to_end_of_line()
{
   set_cursor_x(current_line_ref().length());
   return true;
}



bool CodeEditor::move_cursor_to_last_character_of_line()
{
   if (!infer_cursor_is_on_line_that_exists())
   {
      set_cursor_x(0);
      return false;
   }

   int pos_to_place_cursor = std::max(0, int(current_line_ref().length())-1);
   set_cursor_x(pos_to_place_cursor);
   return true;
}



bool CodeEditor::move_cursor_to_first_non_whitespace_character()
{
   set_cursor_x(0);
   if (cursor_y < 0) return false;
   if (cursor_y >= num_lines()) return false;

   std::size_t first_non_whitespace_position = current_line_ref().find_first_not_of(" \t\n\r");
   if (first_non_whitespace_position == std::string::npos)
   {
      this->move_cursor_to_end_of_line();
   }
   else
   {
      set_cursor_x(first_non_whitespace_position);
   }
   return true;
}



bool CodeEditor::delete_character()
{
   current_line_ref().erase(cursor_x, 1);
   mark_content_is_modified();
   return true;
}



bool CodeEditor::join_lines()
{
   if ((cursor_y+1) >= num_lines()) return false;
   if (cursor_y < 0) return false;
   lines[cursor_y] += lines[cursor_y+1];
   lines.erase(lines.begin() + cursor_y+1);
   mark_content_is_modified();
   return true;
}



bool CodeEditor::split_lines()
{
   lines.insert(lines.begin() + cursor_y + 1, lines[cursor_y].substr(cursor_x));
   current_line_ref().erase(cursor_x);
   mark_content_is_modified();
   return true;
}



bool CodeEditor::delete_line()
{
   if (cursor_y < 0 || cursor_y >= lines.size()) return false;

   lines.erase(lines.begin()+cursor_y);
   mark_content_is_modified();
   return true;
}



bool CodeEditor::insert_lines(std::vector<std::string> &lines_to_insert)
{
   int range_safe_y = std::min(std::max(0, cursor_y), (int)lines.size());
   lines.insert(lines.begin() + range_safe_y, lines_to_insert.begin(), lines_to_insert.end());
   mark_content_is_modified();
   return true;
}



bool CodeEditor::insert_string(std::string string)
{
   current_line_ref().insert(cursor_x, string);
   mark_content_is_modified();
   return true;
}



bool CodeEditor::save_file_and_touch_if_symlink()
{
   ::save_file(lines, filename);

   Hexagon::SymlinkToucher symlink_toucher(filename);
   symlink_toucher.touch_if_symlink();

   unmark_content_is_modified();
   return true;
}



bool CodeEditor::set_insert_mode()
{
   mode = INSERT;
   return true;
}



bool CodeEditor::set_edit_mode()
{
   mode = EDIT;
   return true;
}



bool CodeEditor::enable_drawing_info_overlay()
{
   draw_info_overlay = true;
   return true;
}



bool CodeEditor::disable_drawing_info_overlay()
{
   draw_info_overlay = false;
   return true;
}



bool CodeEditor::get_draw_info_overlay()
{
   return draw_info_overlay;
}



// plugins
// plugins
// plugins



bool CodeEditor::refresh_git_modified_line_numbers()
{
   GitLinesModifiedExtractor git_lines_modified_extractor(filename);
   git_lines_modified_extractor.execute();
   git_modified_line_numbers = git_lines_modified_extractor.get_lines_modified();
   return true;
}



bool CodeEditor::clear_code_message_points()
{
   code_message_points_overlays.back().code_message_points.clear();
   return true;
}



bool CodeEditor::set_code_message_points(std::vector<CodeMessagePoint> code_message_points)
{
   code_message_points_overlays.back().code_message_points = code_message_points;
   return true;
}



bool CodeEditor::jump_to_next_code_point()
{
   if (code_message_points_overlays.size() == 0) return true;
   CodeMessagePointsOverlay *current_overlay = &code_message_points_overlays[0];
   if (current_overlay->code_message_points.size() == 0) return true;

   CodeMessagePoint *most_viable_code_point = nullptr;
   for (auto &message_point : code_message_points_overlays[0].code_message_points)
   {
      int message_point_y = message_point.get_y() - 1;
      //if (message_point_y < cursor_y) continue;
      if ((message_point_y == cursor_y && message_point.get_x() > cursor_x)
         || (message_point_y > cursor_y)
      )
      {
         // viable because is after current cursor

         // set it as the current viable cursor if one isn't set; else if it's closer then set it
         if (most_viable_code_point == nullptr) most_viable_code_point = &message_point;
         else if (message_point_y < (most_viable_code_point->get_y() - 1)
               || (message_point_y == (most_viable_code_point->get_y() - 1)
               && message_point.get_x() < most_viable_code_point->get_x()
            )
         )
         {
            // more viable than the current option, because it is closer to the cursor
            most_viable_code_point = &message_point;
         }
      }
   }

   if (!most_viable_code_point)
   {
      return false;
   }

   if (most_viable_code_point)
   {
      set_cursor_x(most_viable_code_point->get_x() + most_viable_code_point->get_cursor_placement_offset());
      set_cursor_y(most_viable_code_point->get_y()-1);
   }

   return true;
}



bool CodeEditor::jump_to_previous_code_point()
{
   if (code_message_points_overlays.size() == 0) return true;
   CodeMessagePointsOverlay *current_overlay = &code_message_points_overlays[0];
   if (current_overlay->code_message_points.size() == 0) return true;

   CodeMessagePoint *most_viable_code_point = nullptr;
   for (auto &message_point : code_message_points_overlays[0].code_message_points)
   {
      int message_point_y = message_point.get_y() - 1;
      if ((message_point_y == cursor_y && message_point.get_x() < cursor_x)
          || (message_point_y < cursor_y)
      )
      {
         if (most_viable_code_point == nullptr) most_viable_code_point = &message_point;
         else if (message_point_y > (most_viable_code_point->get_y() - 1)
               || (message_point_y == (most_viable_code_point->get_y() - 1)
               && message_point.get_x() > most_viable_code_point->get_x()
            )
         )
         {
            most_viable_code_point = &message_point;
         }
      }
   }

   if (!most_viable_code_point)
   {
      return false;
   }

   if (most_viable_code_point)
   {
      set_cursor_x(most_viable_code_point->get_x() + most_viable_code_point->get_cursor_placement_offset());
      set_cursor_y(most_viable_code_point->get_y()-1);
   }

   return true;
}



bool CodeEditor::jump_to_next_or_nearest_code_point()
{
   if (code_message_points_overlays.empty()) return true;

   bool jump_to_next_was_successful = jump_to_next_code_point();
   if (!jump_to_next_was_successful) return jump_to_previous_code_point();

   return true;
}



bool CodeEditor::insert_three_spaces_at_start_of_line()
{
   if (!infer_cursor_is_on_line_that_exists()) return false;
   std::string &current_line = current_line_ref();
   current_line.insert(0, "   ");
   mark_content_is_modified();
   return true;
}



// regex matcher plugin

bool CodeEditor::refresh_regex_message_points()
{
   clear_code_message_points();

   std::string regex_expression = get_search_regex_expression();
   std::size_t carat_position = regex_expression.find_last_of('^');
   int cursor_placement_offset = (carat_position == std::string::npos) ? 0 : carat_position;

   if (regex_expression.empty()) return true;

   regex_expression.erase(
     std::remove(regex_expression.begin() + 1, regex_expression.end(), '^'),
     regex_expression.end());

   std::vector<CodeMessagePoint> results;
   for (unsigned i=0; i<lines.size(); i++)
   {
      RegexMatcher regex_matcher(lines[i], regex_expression);
      std::vector<std::pair<int, int>> match_positions = regex_matcher.get_match_info();
      for (auto &match_position : match_positions)
      {
         results.push_back(CodeMessagePoint(
                           match_position.first,
                           i+1,
                           match_position.second,
                           cursor_placement_offset,
                           "[match]",
                           CodeMessagePoint::POSITION
                           ));
      }
   }
   set_code_message_points(results);

   return true;
}



// presentation

// actions

bool CodeEditor::offset_first_line_number(int delta)
{
   first_line_number += delta;
   if (first_line_number < 0) first_line_number = 0;
   if (first_line_number >= lines.size()) first_line_number = lines.size()-1;
   return true;
}



bool CodeEditor::offset_cursor_position_y(int delta)
{
   set_cursor_y(cursor_y + delta);
   if (cursor_y < 0) set_cursor_y(0);
   if (cursor_y >= lines.size()) set_cursor_y(lines.size()-1);
   return true;
}



bool CodeEditor::offset_first_line_to_vertically_center_cursor(int distance_from_top)
{
   first_line_number = cursor_y - distance_from_top;
   return true;
}



//bool toggle_showing_code_message_points()
//{
   //showing_code_message_points = !showing_code_message_points;
   //return true;
//}



bool CodeEditor::create_visual_selection_at_current_cursor_location()
{
   selections.push_back(CodeRange(cursor_x, cursor_y, cursor_x+1, cursor_y));
   return true;
}



bool CodeEditor::destroy_current_visual_selection()
{
   selections.clear();
   return true;
}



bool CodeEditor::toggle_currently_grabbing_visual_selection()
{
   currently_grabbing_visual_selection = !currently_grabbing_visual_selection;
   //std::cout << " - visual mode: " << currently_grabbing_visual_selection << std::endl;
   if (currently_grabbing_visual_selection) create_visual_selection_at_current_cursor_location();
   else destroy_current_visual_selection();
   return true;
}



// partials



bool CodeEditor::set_current_selection_end_x(int x)
{
   if (selections.empty()) return true;
   selections.back().set_cursor_end_x(x);
   return true;
}



bool CodeEditor::set_current_selection_end_y(int y)
{
   if (selections.empty()) return true;
   selections.back().set_cursor_end_y(y);
   return true;
}



bool CodeEditor::yank_selected_text_to_clipboard()
{
   if (selections.empty())
   {
      throw std::runtime_error(">BOOM< cannot yank selected text; No text selection is currently active");
   }
   std::vector<std::string> extracted_selection = CodeRangeExtractor(get_lines_ref(), selections.back()).extract();
   ClipboardData::store(extracted_selection);
   return true;
}



bool CodeEditor::paste_selected_text_from_clipboard()
{
   std::vector<std::string> retrieved_clipboard_data = ClipboardData::retrieve();
   insert_lines(retrieved_clipboard_data);

   return true;
}



} // namespace CodeEditor



