

#include <Hexagon/AdvancedCodeEditor/AdvancedCodeEditor.hpp>
#include <Blast/StringSplitter.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <algorithm>
#include <array>
#include <array>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


AdvancedCodeEditor::AdvancedCodeEditor()
   : lines({})
   , cursor({})
   , dirty_grid({})
   , SPLIT_LINE_DELIMITER_CHAR('\n')
   , content_is_modified(false)
{
}


AdvancedCodeEditor::~AdvancedCodeEditor()
{
}


std::vector<std::string> AdvancedCodeEditor::get_lines()
{
   return lines;
}


bool AdvancedCodeEditor::get_content_is_modified()
{
   return content_is_modified;
}


std::vector<std::string> &AdvancedCodeEditor::get_lines_ref()
{
   return lines;
}


Hexagon::AdvancedCodeEditor::Cursor &AdvancedCodeEditor::get_cursor_ref()
{
   return cursor;
}


void AdvancedCodeEditor::mark_content_is_modified()
{
   content_is_modified = true;
   return;
}

void AdvancedCodeEditor::unmark_content_is_modified()
{
   content_is_modified = false;
   return;
}

bool AdvancedCodeEditor::set_content(std::string content)
{
   dirty_grid.mark_all_as_dirty(&lines);
   lines = Blast::StringSplitter(content, SPLIT_LINE_DELIMITER_CHAR).split();
   dirty_grid.mark_all_as_dirty(&lines);
   mark_content_is_modified();
   return true;
}

bool AdvancedCodeEditor::insert_string(std::string string)
{
   if (cursor.get_y() >= lines.size()) return false;
   if (cursor.get_y() < 0) return false;
   if (cursor.get_x() > lines[cursor.get_y()].size()) return false;

   // TODO: prevent insertion of newline '\n' characters

   Hexagon::AdvancedCodeEditor::Cursor &cursor = get_cursor_ref();
   std::vector<std::string> &lines = get_lines_ref();

   lines[cursor.get_y()].insert(cursor.get_x(), string);

   dirty_grid.mark_row_as_dirty(cursor.get_y(), cursor.get_x(), lines[cursor.get_y()].length() - cursor.get_x());
   mark_content_is_modified();

   return true;
}

bool AdvancedCodeEditor::delete_character()
{
   if (!is_cursor_in_bounds()) return false;

   Hexagon::AdvancedCodeEditor::Cursor &cursor = get_cursor_ref();
   std::vector<std::string> &lines = get_lines_ref();

   lines[cursor.get_y()].erase(cursor.get_x(), 1);

   dirty_grid.mark_row_as_dirty(cursor.get_y(), cursor.get_x(), lines[cursor.get_y()].length() + 2 - cursor.get_x());
   mark_content_is_modified();

   return true;
}

bool AdvancedCodeEditor::join_lines()
{
   if (!is_cursor_in_vertical_bounds()) return false;
   if (is_cursor_on_last_line()) return false;

   Hexagon::AdvancedCodeEditor::Cursor &cursor = get_cursor_ref();
   std::vector<std::string> &lines = get_lines_ref();

   // from a start position equal to the length of current line, with the length of line below
   dirty_grid.mark_row_as_dirty(cursor.get_y(), lines[cursor.get_y()].length(), lines[cursor.get_y()+1].length());

   // all of the lines below the current line, before change
   for (int row=(cursor.get_y()+1); row<lines.size(); row++)
   {
      dirty_grid.mark_row_as_dirty(row, 0, lines[row].length());
   }

   lines[cursor.get_y()] += lines[cursor.get_y()+1];
   lines.erase(lines.begin() + cursor.get_y()+1);

   // all of the lines below the current line, after change
   for (int row=(cursor.get_y()+1); row<lines.size(); row++)
   {
      dirty_grid.mark_row_as_dirty(row, 0, lines[row].length());
   }

   mark_content_is_modified();

   return true;
}

bool AdvancedCodeEditor::split_lines()
{
   if (!is_cursor_in_bounds()) return false;

   // cells from the curent x, y, to the end of the line
   dirty_grid.mark_row_as_dirty(cursor.get_y(), cursor.get_x(), lines[cursor.get_y()].length() - cursor.get_x());

   // all of the lines below the current line, before change
   for (int row=(cursor.get_y()+1); row<lines.size(); row++)
   {
      dirty_grid.mark_row_as_dirty(row, 0, lines[row].length());
   }

   lines.insert(lines.begin() + cursor.get_y() + 1, lines[cursor.get_y()].substr(cursor.get_x()));
   std::string &current_line = lines[cursor.get_y()];
   current_line.erase(cursor.get_x());

   // all of the lines below the current line, after change
   for (int row=(cursor.get_y()+1); row<lines.size(); row++)
   {
      dirty_grid.mark_row_as_dirty(row, 0, lines[row].length());
   }

   mark_content_is_modified();

   return true;
}

bool AdvancedCodeEditor::delete_line()
{
   if (cursor.get_y() < 0 || cursor.get_y() >= lines.size()) return false;

   // from the current line down, from 0 to the longer of itself and the length of the line below it
   for (int row=cursor.get_y(); row<(lines.size() - 1); row++)
   {
      int longest_length = std::max(lines[row].length(), lines[row + 1].length());
      dirty_grid.mark_row_as_dirty(row, 0, longest_length);
   }

   // append the last line
   if (!lines.empty())
   {
      dirty_grid.mark_row_as_dirty(lines.size()-1, 0, lines[lines.size()-1].length());
   }

   lines.erase(lines.begin()+cursor.get_y());
   mark_content_is_modified();

   return true;
}

bool AdvancedCodeEditor::insert_lines(std::vector<std::string> lines_to_insert)
{
   // TODO: prevent insertion of newline '\n' characters

   int range_safe_y = std::min(std::max(0, cursor.get_y()), (int)lines.size());

   // the current_lines starting from y point of insertion
   for (int row=range_safe_y; row<lines.size(); row++)
   {
      dirty_grid.mark_row_as_dirty(row, 0, lines[row].length());
   }

   lines.insert(lines.begin() + range_safe_y, lines_to_insert.begin(), lines_to_insert.end());

   // the result lines starting from y point of insertion
   for (int row=range_safe_y; row<lines.size(); row++)
   {
      dirty_grid.mark_row_as_dirty(row, 0, lines[row].length());
   }

   mark_content_is_modified();

   return true;
}

bool AdvancedCodeEditor::cursor_set_width(float width)
{
   cursor.set_width(width);
   return true;
}

bool AdvancedCodeEditor::cursor_set_height(float height)
{
   cursor.set_height(height);
   return true;
}

bool AdvancedCodeEditor::cursor_move_up()
{
   cursor.move_up();
   return true;
}

bool AdvancedCodeEditor::cursor_move_down()
{
   cursor.move_down();
   return true;
}

bool AdvancedCodeEditor::cursor_move_left()
{
   cursor.move_left();
   return true;
}

bool AdvancedCodeEditor::cursor_move_right()
{
   cursor.move_right();
   return true;
}

bool AdvancedCodeEditor::cursor_move_to_start_of_line()
{
   cursor.set_x(0);
   return true;
}

bool AdvancedCodeEditor::cursor_move_to_end_of_line()
{
   // if not on a valid line
   if (cursor.get_y() < 0 || cursor.get_y() >= lines.size())
   {
      cursor.set_x(0);
   }
   else
   {
      std::string &current_line = lines[cursor.get_y()];
      cursor.set_x(std::max(0, (int)(current_line.size()-1)));
   }

   return true;
}

bool AdvancedCodeEditor::cursor_move_to_first_non_whitespace_character()
{
   cursor.set_x(0);
   if (cursor.get_y() < 0) return false;
   if (cursor.get_y() >= get_lines_ref().size()) return false;

   std::string &current_line = lines[cursor.get_y()];
   std::size_t first_non_whitespace_position = current_line.find_first_not_of(" \t\n\r");
   if (first_non_whitespace_position == std::string::npos)
   {
      cursor_move_to_end_of_line();
   }
   else
   {
      cursor.set_x(first_non_whitespace_position);
   }
   return true;
}

bool AdvancedCodeEditor::cursor_jump_to_next_word()
{
   if (!is_cursor_in_bounds()) return false;

   // This regex from vimdoc.sourceforge.net/htmldoc/motion.html#word
   std::string vim_equivelent_word_jump_regex = "([0-9a-zA-Z_]+)|([^0-9a-zA-Z_ \\s]+)";
   std::string &current_line = lines[cursor.get_y()];

   RegexMatcher regex_matcher(current_line, vim_equivelent_word_jump_regex);
   std::vector<std::pair<int, int>> match_positions = regex_matcher.get_match_info();

   for (auto &match_position : match_positions)
   {
      if (match_position.first > cursor.get_x())
      {
         cursor.set_x(match_position.first);
         return true;
      }
   }

   return false;
}

bool AdvancedCodeEditor::cursor_jump_to_previous_word()
{
   if (!is_cursor_in_bounds()) return false;

   // This regex from vimdoc.sourceforge.net/htmldoc/motion.html#word
   std::string vim_equivelent_word_jump_regex = "([0-9a-zA-Z_]+)|([^0-9a-zA-Z_ \\s]+)";
   std::string &current_line = lines[cursor.get_y()];

   RegexMatcher regex_matcher(current_line, vim_equivelent_word_jump_regex);
   std::vector<std::pair<int, int>> match_positions = regex_matcher.get_match_info();
   std::reverse(std::begin(match_positions), std::end(match_positions));

   for (auto &match_position : match_positions)
   {
      if (match_position.first < cursor.get_x())
      {
         cursor.set_x(match_position.first);
         return true;
      }
   }

   return false;
}

bool AdvancedCodeEditor::cursor_move_to(int x, int y)
{
   cursor.move_to(x, y);
   return true;
}

bool AdvancedCodeEditor::cursor_set_x(int x)
{
   cursor.set_x(x);
   return true;
}

bool AdvancedCodeEditor::cursor_set_y(int y)
{
   cursor.set_y(y);
   return true;
}

int AdvancedCodeEditor::cursor_get_x()
{
   return cursor.get_x();
}

int AdvancedCodeEditor::cursor_get_y()
{
   return cursor.get_y();
}

bool AdvancedCodeEditor::is_cursor_in_bounds()
{
   if (cursor.get_y() >= lines.size()) return false;
   if (cursor.get_y() < 0) return false;
   if (cursor.get_x() >= lines[cursor.get_y()].size()) return false;
   return true;
}

bool AdvancedCodeEditor::is_cursor_in_vertical_bounds()
{
   if (cursor.get_y() >= lines.size()) return false;
   if (cursor.get_y() < 0) return false;
   return true;
}

bool AdvancedCodeEditor::is_cursor_on_last_line()
{
   if (lines.empty()) return false;
   return cursor.get_y() == (lines.size() - 1);
}

void AdvancedCodeEditor::dirty_grid_clear()
{
   dirty_grid.clear();
   return;
}

std::vector<std::pair<int, int>> AdvancedCodeEditor::get_dirty_cells()
{
   return dirty_grid.build_vector();
}

bool AdvancedCodeEditor::any_dirty_cells()
{
   return !dirty_grid.dirty_cells_empty();
}

int AdvancedCodeEditor::dirty_cell_count()
{
   return dirty_grid.dirty_cells_count();
}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


