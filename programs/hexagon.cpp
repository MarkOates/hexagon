#include <iostream>
#include <sstream>
#include <algorithm>


#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


#include <allegro_flare/placement2d.h>
#include <allegro_flare/useful_php.h>


#include <Blast/StringSplitter.hpp>
#include <Blast/KeyboardCommandMapper.hpp>
#include <Blast/ShellCommandExecutor.hpp>
#include <Blast/CommandLineFlaggedArgumentsParser.hpp>

using namespace Blast;


#include <Hexagon/Logo.hpp>
#include <Hexagon/RegexMatcher.hpp>


using namespace Hexagon;



std::string REGEX_TEMP_FILENAME = "regex.txt";



std::string resource(std::vector<std::string> components, std::string filename="")
{
   std::string result;

   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   for (auto &component : components) al_append_path_component(path, component.c_str());

   al_set_path_filename(path, filename.c_str());
   result = al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP);

   std::cout << result << std::endl;

   return result;
}



std::string::size_type rfind_first_not_of(const std::string& s,
        const std::string& delims, std::string::size_type pos)
{
    std::string::size_type p = pos;
    while (delims.find(s[p]) != std::string::npos) {
        if (p == 0) // not found
            return std::string::npos;
        --p;
    }
    return p;
}

std::string::size_type rfind_first_of(const std::string& s,
        const std::string& delims, std::string::size_type pos)
{
    std::string::size_type p = pos;
    while (delims.find(s[p]) == std::string::npos) {
        if (p == 0) // not found
            return std::string::npos;
        --p;
    }
    return p;
}

#include <iostream>       // std::cout
#include <string>         // std::string
#include <cstddef>        // std::size_t

int find_whitespace(std::string &string, int current_cursor_position)
{
  std::size_t position = string.find_first_of(" \n\r\t", current_cursor_position);
  if (position != std::string::npos) return position;
  return 0;
}

int find_non_whitespace(std::string &string, int current_cursor_position)
{
  std::size_t position = string.find_first_not_of(" \n\r\t", current_cursor_position);
  if (position != std::string::npos) return position;
  return 0;
}

int rfind_whitespace(std::string &string, int current_cursor_position)
{
  std::size_t position = rfind_first_of(string, " \n\r\t", current_cursor_position);
  if (position != std::string::npos) return position;
  return 0;
}

int rfind_non_whitespace(std::string &string, int current_cursor_position)
{
  std::size_t position = rfind_first_not_of(string, " \n\r\t", current_cursor_position);
  if (position != std::string::npos) return position;
  return 0;
}


#include <fstream>

bool read_file(std::vector<std::string> &lines, std::string filename)
{
   std::ifstream file(filename);

   lines.clear();

   if (file.is_open())
   {
      std::string line;
      while (getline(file, line)) { lines.push_back(line); }
      file.close();
   }

   return true;
}

bool save_file(std::vector<std::string> &lines, std::string filename)
{
   std::ofstream file(filename);

   if (file.is_open())
   {
      for (auto &line : lines) file << line << '\n';
      file.close();
   }
   else
   {
      throw std::runtime_error("couldn't save file -- file failed at is_open()");
   }

   return true;
}



class GitLinesModifiedExtractor
{
private:
   std::string filename;
   std::vector<int> lines_modified;
   bool executed;

public:
   GitLinesModifiedExtractor(std::string filename)
      : filename(filename)
      , lines_modified()
      , executed(false)
   {}
   ~GitLinesModifiedExtractor()
   {
   }

   void execute()
   {
      if (executed) return;

      std::stringstream git_changed_lines_shell_command;
      git_changed_lines_shell_command << "git blame " << filename << " | grep -n '^0\\{8\\} ' | cut -f1 -d:";
      ShellCommandExecutor shell_command_executor(git_changed_lines_shell_command.str());
      std::string output = shell_command_executor.execute();
      std::vector<std::string> line_numbers_str = StringSplitter(output, '\n').split();
      lines_modified.clear();
      lines_modified.resize(line_numbers_str.size());
      for (auto &line_number_str : line_numbers_str)
         lines_modified.push_back(atoi(line_number_str.c_str()));
      executed = true;
   }

   std::vector<int> get_lines_modified()
   {
      return lines_modified;
   }
};



class RailsMinitestTestResult
{
public:
   enum test_state_t
   {
      UNKNOWN,
      RUNNING,
      PASS,
      FAILURE,
      ERROR,
   };

   std::string test_name;
   std::string test_time_in_seconds;
   std::string test_result;
   test_state_t test_state;
   std::string test_result_output;
   int error_line_number;

   RailsMinitestTestResult(std::string test_name, std::string test_time_in_seconds, std::string test_result, test_state_t test_state)
      : test_name(test_name)
      , test_time_in_seconds(test_time_in_seconds)
      , test_result(test_result)
      , test_state(test_state)
      , test_result_output("")
      , error_line_number(-1)
   {}
   ~RailsMinitestTestResult() {}

   test_state_t get_test_state() const { return test_state; }
};



std::ostream &operator<<(std::ostream &out, RailsMinitestTestResult::test_state_t const &t)
{
   switch(t)
   {
   case RailsMinitestTestResult::UNKNOWN:
      out << "unprocessed";
   break;
   case RailsMinitestTestResult::RUNNING:
      out << "running";
   break;
   case RailsMinitestTestResult::PASS:
      out << "pass";
   break;
   case RailsMinitestTestResult::FAILURE:
      out << "failure";
   break;
   case RailsMinitestTestResult::ERROR:
      out << "error";
   break;
   }

   return out;
}



std::ostream &operator<<(std::ostream &out, RailsMinitestTestResult const &t)
{
   if (t.test_result == " F") out << "FAILED!!: ";
   out << t.test_name << "||||" << t.test_time_in_seconds << "||||" << t.test_result << "||||" << t.test_state << "||||" << std::endl << "######" << t.test_result_output << std::endl << "######";

   return out;
}



class RailsTestOutputParser
{
private:
   bool processed;
   std::string source_test_output;
   std::vector<RailsMinitestTestResult> test_result_lines;

public:
   RailsTestOutputParser(std::string source_test_output)
      : processed(false)
      , source_test_output(source_test_output)
      , test_result_lines()
   {}

   void process()
   {
      if (processed) return;

      test_result_lines.clear();
      std::vector<std::string> source_test_output_lines = StringSplitter(source_test_output, '\n').split();

      RailsMinitestTestResult *current_rails_minitest_test_result = nullptr;

      for (auto &source_test_output_line : source_test_output_lines)
      {
         std::vector<std::string> possible_test_line_output_tokens = StringSplitter(source_test_output_line, '=').split();
         if (possible_test_line_output_tokens.size() == 3)
         {
            // assume it is a valid test output line

            // 1) "close" the current rails minitest test result (if there is one)
            if (current_rails_minitest_test_result) test_result_lines.push_back(*current_rails_minitest_test_result);

            RailsMinitestTestResult::test_state_t test_state = RailsMinitestTestResult::UNKNOWN;
            if (possible_test_line_output_tokens[2] == " E") test_state = RailsMinitestTestResult::ERROR;
            else if (possible_test_line_output_tokens[2] == " F") test_state = RailsMinitestTestResult::FAILURE;
            else if (possible_test_line_output_tokens[2] == " .") test_state = RailsMinitestTestResult::PASS;

            // 2) create a new one
            current_rails_minitest_test_result = new RailsMinitestTestResult({
               possible_test_line_output_tokens[0],
               possible_test_line_output_tokens[1],
               possible_test_line_output_tokens[2],
               test_state,
            });
         }
         else
         {
            // append the line to the current test (if there is one)
            if (current_rails_minitest_test_result)
            {
               current_rails_minitest_test_result->test_result_output += source_test_output_line + "\n";

               // attempt to extract the error line number from the file
               std::vector<std::string> dot_split_tokens = StringSplitter(source_test_output_line, '.').split();

               if (dot_split_tokens.size() <= 1) { /* there should be at least 2 tokens */ }
               else if (dot_split_tokens.back().size() <= 5) { /* not a valid foramt for this token */ }
               else
               {
                  std::string last_token = dot_split_tokens.back();
                  std::string prefix = last_token.substr(0, 3);
                  std::string postfix = last_token.substr(last_token.size()-2);
                  std::string number = last_token.substr(3, last_token.size() - 3 - 2);
                  bool number_contains_only_number_characters = (number.find_first_not_of("0123456789") == std::string::npos);

                  if (prefix == "rb:" && postfix == "]:" && number_contains_only_number_characters)
                  {
                     // format matches "rb:[0-9]\]:" expression
                     current_rails_minitest_test_result->error_line_number = atoi(number.c_str());
                  }
               }
            }
         }
      }

      if (current_rails_minitest_test_result) test_result_lines.push_back(*current_rails_minitest_test_result);

      processed = true;
   }

   std::vector<RailsMinitestTestResult> const &get_test_result_lines()
   {
      if (!processed) process();

      return test_result_lines;
   }
};



class RailsMinitestTestRunner
{
private:
   std::string test_filename;

public:
   RailsMinitestTestRunner(std::string test_filename)
      : test_filename(test_filename)
   {}
   ~RailsMinitestTestRunner() {}

   std::string run()
   {
      std::stringstream test_command_string;
      test_command_string << "bin/rails test " << test_filename << " -v";
      ShellCommandExecutor shell_command_executor(test_command_string.str());
      std::string output = shell_command_executor.execute();
      return output;
   }
};



namespace CppCompiler
{
   class CompileRunner
   {
   private:
      std::string filename;

   public:
      CompileRunner(std::string filename)
         : filename(filename)
      {}
      ~CompileRunner() {}

      std::string run()
      {
         std::stringstream make_command_string;
         make_command_string << "make";
         ShellCommandExecutor shell_command_executor(make_command_string.str());
         std::string output = shell_command_executor.execute();
         std::cout << output << std::endl;
         return output;
      }
   };
};



class CodeMessagePoint
{
public:
   enum type_t
   {
      NONE,
      ERROR,
      POSITION,
   };

private:
   int x, y, length;
   std::string message;
   type_t type;

public:
   CodeMessagePoint(int x, int y, int length, std::string message, type_t type)
      : x(x)
      , y(y)
      , length(length)
      , message(message)
      , type(type)
   {}
   ~CodeMessagePoint()
   {}

   int get_x() { return x; }
   int get_x2() { return x + length; }
   int get_y() { return y; }
   int get_length() { return length; }
   std::string get_message() { return message; }
   type_t get_type() { return type; }
};



class CodeMessagePointRenderer
{
private:
   CodeMessagePoint code_message_point;
   bool showing_code_message_points;
   int current_line_number_offset;
   int line_height;
   int character_width;
   ALLEGRO_FONT *font;
   placement2d place;
   int cursor_x;
   int cursor_y;

public:
   CodeMessagePointRenderer(CodeMessagePoint code_message_point, ALLEGRO_FONT *font, bool showing_code_message_points, int current_line_number_offset, int line_height, int character_width, int cursor_x, int cursor_y)
      : code_message_point(code_message_point)
      , showing_code_message_points(showing_code_message_points)
      , current_line_number_offset(current_line_number_offset)
      , line_height(line_height)
      , character_width(character_width)
      , font(font)
      , place(0, 0, 2200, 500)
      , cursor_x(cursor_x)
      , cursor_y(cursor_y)
   {
      if (!font) throw std::runtime_error("font not valid in CodeMessagePointRenderer");
   }

   void render()
   {
      float horizontal_padding = 20;
      place.position = vec2d(code_message_point.get_x() * character_width, (code_message_point.get_y()-1)*line_height - (current_line_number_offset)*line_height + line_height*0.5);
      place.align = vec2d(0, 0);
      place.start_transform();

      switch(code_message_point.get_type())
      {
      case CodeMessagePoint::POSITION:
         {
            ALLEGRO_COLOR color = al_color_name("dodgerblue");
            ALLEGRO_COLOR outline_color = al_color_name("yellow");
            ALLEGRO_STATE blender_state;
            float padding_x = 2;
            float padding_y = 2;
            float radius = 3;
            float outline_thickness = 2.0;
            bool cursor_at_code_point = ((cursor_x >= code_message_point.get_x()) && (cursor_x < code_message_point.get_x2()) && (code_message_point.get_y()-1) == cursor_y);
            if (!cursor_at_code_point)
            {
               float opacity = 0.6;
               color.r *= opacity; color.g *= opacity, color.b *= opacity; color.a *= opacity;
            }
            al_store_state(&blender_state, ALLEGRO_STATE_BLENDER);
            al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
            al_draw_filled_rounded_rectangle(0-padding_x, -line_height/2.0-padding_y, std::max(10, code_message_point.get_length()*character_width)+padding_x, line_height/2.0+padding_y, radius, radius, color);
            if (cursor_at_code_point) al_draw_rounded_rectangle(0-padding_x, -line_height/2.0-padding_y, std::max(10, code_message_point.get_length()*character_width)+padding_x, line_height/2.0+padding_y, radius, radius, outline_color, outline_thickness);
            al_restore_state(&blender_state);
         }
         break;
      default:
         {
            ALLEGRO_COLOR color = al_color_name("red");
            ALLEGRO_COLOR text_color = al_color_name("white");

            // draw the marker
            al_draw_filled_circle(0, 0, 16, color);

            /// draw the message (if open)
            if (showing_code_message_points)
            {
               al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color);
               al_draw_multiline_text(font, text_color, 10, 10, place.size.x - horizontal_padding*2, line_height, ALLEGRO_ALIGN_LEFT, code_message_point.get_message().c_str());
            }
         }
         break;
      }

      place.restore_transform();
   }
};



class RailsMinitestTestResultToCodeMessagePointConverter
{
private:
   RailsMinitestTestResult rails_minitest_test_result;

public:
   RailsMinitestTestResultToCodeMessagePointConverter(RailsMinitestTestResult rails_minitest_test_result)
      : rails_minitest_test_result(rails_minitest_test_result)
   {}

   CodeMessagePoint convert()
   {
      CodeMessagePoint::type_t code_message_point_type = CodeMessagePoint::NONE;
      if (rails_minitest_test_result.test_state == RailsMinitestTestResult::ERROR) code_message_point_type = CodeMessagePoint::ERROR;
      return CodeMessagePoint(0, rails_minitest_test_result.error_line_number, 0, rails_minitest_test_result.test_result_output, CodeMessagePoint::ERROR);
   }
};



class CodeMessagePointsOverlay
{
public:
   std::string name;
   ALLEGRO_COLOR color;
   std::vector<CodeMessagePoint> code_message_points;

   CodeMessagePointsOverlay(ALLEGRO_COLOR color, std::vector<CodeMessagePoint> code_message_points)
      : color(color)
      , code_message_points(code_message_points)
   {
      float alpha = 0.2;
      color.r *= alpha; color.g *= alpha; color.b *= alpha; color.a *= alpha;
   }

   void render(ALLEGRO_FONT *font, bool showing_code_message_points, int first_line_num, float line_height, int cursor_x, int cursor_y)
   {
      //al_draw_filled_rectangle(0, 0, 2400, 2000, color);
      int character_width = al_get_text_width(font, "x");
      for (auto &code_message_point : code_message_points)
      {
         CodeMessagePointRenderer code_message_point_renderer(code_message_point, font, showing_code_message_points, first_line_num, al_get_font_line_height(font), character_width, cursor_x, cursor_y);
         code_message_point_renderer.render();
      }
   }
};



class SystemWideMotion : public Motion {};


SystemWideMotion motion;




#include <string>
#include <vector>


class Stage
{
public:
   enum mode_t
   {
      EDIT,
      INSERT,
      COMMAND,
   };

   enum type_t
   {
      NONE,
      CODE_EDITOR,
      ONE_LINE_INPUT_BOX,
   };

private:
   std::vector<std::string> lines;
   int cursor_x;
   int cursor_y;

   mode_t mode;
   type_t type;

   std::string filename;

   // presentation

   placement2d place;
   int first_line_num;

public:
   Stage(std::string filename, placement2d place, mode_t mode=EDIT, type_t type=CODE_EDITOR)
      : lines()
      , cursor_x(0)
      , cursor_y(0)
      , mode(mode)
      , type(type)
      , filename(filename)
      , place(place)
      , first_line_num(0)
      , showing_code_message_points(false)
      , code_message_points_overlays()
   {
      code_message_points_overlays.push_back(CodeMessagePointsOverlay(al_color_name("dogerblue"), {}));
   }

   // accessors

   std::string get_filename()
   {
      return filename;
   }

   bool set_content(std::string content)
   {
      lines = StringSplitter(content, '\n').split();
      return true;
   }

   bool set_content(std::vector<std::string> content)
   {
      lines = content;
      return true;
   }

   placement2d &get_place_ref()
   {
      return place;
   }

   type_t get_type()
   {
      return type;
   }

   mode_t get_mode()
   {
      return mode;
   }

   // inference

   int num_lines()
   {
      return lines.size();
   }

   int num_columns()
   {
      if (cursor_y >= lines.size()) return -1;
      return lines[cursor_y].length();
   }

   std::string &current_line_ref()
   {
      return lines[cursor_y];
   }

   std::string &next_line_ref()
   {
      return lines[cursor_y+1];
   }

   std::string get_current_mode_string()
   {
      if (mode == EDIT) return "EDIT";
      if (mode == INSERT) return "INSERT";
      if (mode == COMMAND) return "COMMAND";
      return "---";
   }

   // actions

   bool move_cursor_up()
   {
      if (num_lines() <= 0) return false;
      cursor_y -= 1;
      return true;
   }
   bool move_cursor_down()
   {
      if (cursor_y >= num_lines()) return false;
      cursor_y += 1;
      return true;
   }
   bool move_cursor_left()
   {
      cursor_x -= 1;
      return true;
   }
   bool move_cursor_right()
   {
      cursor_x += 1;
      return true;
   }
   bool move_cursor_jump_to_next_word()
   {
      int position = 0;

      position = find_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; }

      position = find_non_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; return true; }

      return false;
   }
   bool move_cursor_jump_to_next_big_word()
   {
      int position = 0;

      position = find_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; }

      position = find_non_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; return true; }

      return false;
   }
   bool move_cursor_jump_to_previous_word()
   {
      int position = 0;

      position = rfind_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; }

      position = rfind_non_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; return true; }

      return false;
   }
   bool move_cursor_jump_to_previous_big_word()
   {
      int position = 0;

      position = rfind_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; }

      position = rfind_non_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { cursor_x = position; return true; }

      return false;
   }
   bool move_cursor_to_start_of_line()
   {
      cursor_x = 0;
      return true;
   }
   bool move_cursor_to_end_of_line()
   {
      cursor_x = current_line_ref().length();
      return true;
   }
   bool delete_character()
   {
      current_line_ref().erase(cursor_x, 1);
      return true;
   }
   bool join_lines()
   {
      lines[cursor_y] += lines[cursor_y+1];
      lines.erase(lines.begin() + cursor_y+1);
      return true;
   }
   bool split_lines()
   {
     lines.insert(lines.begin() + cursor_y + 1, lines[cursor_y].substr(cursor_x));
     current_line_ref().erase(cursor_x);
     return true;
   }
   bool insert_string(std::string string)
   {
      current_line_ref().insert(cursor_x, string);
      return true;
   }
   bool save_file()
   {
      ::save_file(lines, filename);
      return true;
   }
   // editor mode
   bool set_insert_mode()
   {
      mode = INSERT;
      return true;
   }
   bool set_edit_mode()
   {
      mode = EDIT;
      return true;
   }
   bool set_operator_mode()
   {
      mode = COMMAND;
      return true;
   }


   // plugins

   std::vector<int> git_modified_line_numbers;

   bool refresh_git_modified_line_numbers()
   {
      GitLinesModifiedExtractor git_lines_modified_extractor(filename);
      git_lines_modified_extractor.execute();
      git_modified_line_numbers = git_lines_modified_extractor.get_lines_modified();
      return true;
   }

   //std::vector<CodeMessagePoint> code_message_points;
   bool showing_code_message_points;
   std::vector<CodeMessagePointsOverlay> code_message_points_overlays;

   bool clear_code_message_points()
   {
      code_message_points_overlays.back().code_message_points.clear();
      return true;
   }

   bool set_code_message_points(std::vector<CodeMessagePoint> code_message_points)
   {
      code_message_points_overlays.back().code_message_points = code_message_points;
      return true;
   }

   bool jump_to_next_code_point()
   {
      if (code_message_points_overlays.size() == 0) return true;
      CodeMessagePointsOverlay *current_overlay = &code_message_points_overlays[0];
      if (current_overlay->code_message_points.size() == 0) return true;

      std::cout << "XXXXX" << std::endl;

      CodeMessagePoint *most_viable_code_point = nullptr;
      for (auto &message_point : code_message_points_overlays[0].code_message_points)
      {
         std::cout << "CODE POINT" << std::endl;
         int message_point_y = message_point.get_y() - 1;
         //if (message_point_y < cursor_y) continue;
         if ((message_point_y == cursor_y && message_point.get_x() > cursor_x)
            || (message_point_y > cursor_y)
         )
         {
            // viable because is after current cursor

            std::cout << "   -- viable" << std::endl;
            // set it as the current viable cursor if one isn't set; else if it's closer then set it
            if (most_viable_code_point == nullptr) most_viable_code_point = &message_point;
            else if (message_point_y < (most_viable_code_point->get_y() - 1)
               || (message_point_y == (most_viable_code_point->get_y() - 1) && message_point.get_x() < most_viable_code_point->get_x())
            )
            {
               // more viable than the current option, because it is closer to the cursor
               most_viable_code_point = &message_point;
            }
         }
      }

      if (most_viable_code_point)
      {
         cursor_x = most_viable_code_point->get_x();
         cursor_y = most_viable_code_point->get_y()-1;
      }
      return true;
   }

   bool jump_to_previous_code_point()
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
            std::cout << "  -- viable" << std::endl;
            if (most_viable_code_point == nullptr) most_viable_code_point = &message_point;
            else if (message_point_y > (most_viable_code_point->get_y() - 1)
              || (message_point_y == (most_viable_code_point->get_y() - 1) && message_point.get_x() > most_viable_code_point->get_x())
            )
            {
               most_viable_code_point = &message_point;
            }
         }
      }

      if (most_viable_code_point)
      {
         cursor_x = most_viable_code_point->get_x();
         cursor_y = most_viable_code_point->get_y()-1;
      }
      return true;
   }

   // regex matcher plugin

   bool refresh_regex_message_points()
   {
      clear_code_message_points();

      // get regex expression input from file named REGEX_TEMP_FILENAME
      std::vector<std::string> regex_input_file_lines;
      if (!read_file(regex_input_file_lines, REGEX_TEMP_FILENAME) || regex_input_file_lines.size() == 0) throw std::runtime_error("cannot open expected REGEX_TEMP_FILENAME file for input, or is empty");

      std::string regex_expression = php::trim(regex_input_file_lines[0]);

      if (regex_expression.empty()) return true;

      std::vector<CodeMessagePoint> results;
      for (unsigned i=0; i<lines.size(); i++)
      {
         RegexMatcher regex_matcher(lines[i], regex_expression);
         std::vector<std::pair<int, int>> match_positions = regex_matcher.get_match_info();
         for (auto &match_position : match_positions)
         {
            results.push_back(CodeMessagePoint(match_position.first, i+1, match_position.second, "[match]", CodeMessagePoint::POSITION));
         }
      }
      set_code_message_points(results);

      return true;
   }

   // presentation

   // actions

   bool offset_first_line_num(int delta)
   {
      first_line_num += delta;
      if (first_line_num < 0) first_line_num = 0;
      if (first_line_num >= lines.size()) first_line_num = lines.size()-1;
      return true;
   }

   bool offset_cursor_position_y(int delta)
   {
      cursor_y += delta;
      if (cursor_y < 0) cursor_y = 0;
      if (cursor_y >= lines.size()) cursor_y = lines.size()-1;
      return true;
   }

   bool move_stage_up(float distance=100)
   {
      place.position.y += distance;
      return true;
   }

   bool move_stage_down(float distance=100)
   {
      place.position.y -= distance;
      return true;
   }

   bool offset_first_line_to_vertically_center_cursor(int distance_from_top=20)
   {
      first_line_num = cursor_y - distance_from_top;
      return true;
   }

   bool scale_stage_delta(float delta)
   {
      place.scale += vec2d(delta, delta);
      return true;
   }

   bool toggle_showing_code_message_points()
   {
      showing_code_message_points = !showing_code_message_points;
      return true;
   }

   void render_as_input_box(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height)
   {
      place.start_transform();

      float roundness = 6;
      float padding = 6;
      al_draw_filled_rounded_rectangle(0-padding*2, 0-padding*2, place.size.x+padding*2, place.size.y+padding*2, roundness, roundness, al_color_name("black"));
      al_draw_rounded_rectangle(0-padding, 0-padding, place.size.x+padding, place.size.y+padding, roundness, roundness, al_color_name("dodgerblue"), 3.0);

      float _cursor_y = cursor_y - first_line_num;
      switch(mode)
      {
      case EDIT:
         al_draw_filled_rectangle(cursor_x*cell_width, _cursor_y*cell_height, cursor_x*cell_width + cell_width, _cursor_y*cell_height + cell_height, al_color_name("gray"));
         break;
      case INSERT:
         al_draw_line(cursor_x*cell_width, _cursor_y*cell_height, cursor_x*cell_width, _cursor_y*cell_height + cell_height, al_color_name("gray"), 3);
         break;
      case COMMAND:
         al_draw_line(cursor_x*cell_width, _cursor_y*cell_height, cursor_x*cell_width, _cursor_y*cell_height + cell_height, al_color_name("dodgerblue"), 5);
         break;
      }

      int line_height = al_get_font_line_height(font);
      for (int i=0; i<lines.size(); i++)
      {
         al_draw_text(font, al_color_name("dodgerblue"), 0, i*line_height, ALLEGRO_ALIGN_LEFT, lines[i].c_str());
      }

      place.restore_transform();
   }

   void render(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height)
   {
      if (type == ONE_LINE_INPUT_BOX) { render_as_input_box(display, font, cell_width, cell_height); return; }

      place.start_transform();

      // render cursor
      float _cursor_y = cursor_y - first_line_num;
      switch(mode)
      {
      case EDIT:
         al_draw_filled_rectangle(cursor_x*cell_width, _cursor_y*cell_height, cursor_x*cell_width + cell_width, _cursor_y*cell_height + cell_height, al_color_name("gray"));
         break;
      case INSERT:
         al_draw_line(cursor_x*cell_width, _cursor_y*cell_height, cursor_x*cell_width, _cursor_y*cell_height + cell_height, al_color_name("gray"), 3);
         break;
      case COMMAND:
         al_draw_line(cursor_x*cell_width, _cursor_y*cell_height, cursor_x*cell_width, _cursor_y*cell_height + cell_height, al_color_name("dodgerblue"), 5);
         break;
      }


      // render lines
      int line_height = al_get_font_line_height(font);
      for (int line_number = first_line_num; line_number < lines.size(); line_number++)
      {
         bool line_exists_in_git_modified_line_numbers = std::find(git_modified_line_numbers.begin(), git_modified_line_numbers.end(), (line_number+1)) != git_modified_line_numbers.end();
         if (line_exists_in_git_modified_line_numbers)
         {
            ALLEGRO_COLOR color = al_color_name("orange");
            color.r *= 0.13;
            color.g *= 0.13;
            color.b *= 0.13;
            color.a *= 0.13;
            al_draw_filled_rectangle(0, line_height * (line_number - first_line_num), al_get_display_width(display)*2, line_height * (line_number - first_line_num + 1), color);
         }

         al_draw_text(font, al_color_name("white"), 0, (line_number-first_line_num)*cell_height, ALLEGRO_ALIGN_LEFT, lines[line_number].c_str());
         std::stringstream ss;
         ss << (line_number+1);
         ALLEGRO_COLOR text_color = al_color_name("darkolivegreen");
         if (line_exists_in_git_modified_line_numbers) text_color = al_color_name("orange");
         al_draw_text(font, text_color, -20, (line_number-first_line_num)*cell_height, ALLEGRO_ALIGN_RIGHT, ss.str().c_str());
      }

      for (auto &code_message_points_overlay : code_message_points_overlays)
      {
         code_message_points_overlay.render(font, showing_code_message_points, first_line_num, al_get_font_line_height(font), cursor_x, cursor_y);
      }
      //for (auto &code_message_point : code_message_points)
      //{
         //CodeMessagePointRenderer code_message_point_renderer(code_message_point, font, showing_code_message_points, first_line_num, al_get_font_line_height(font));
         //code_message_point_renderer.render();
      //}

      place.restore_transform();

      // render edit mode
      ALLEGRO_COLOR color;

      switch(mode)
      {
      case EDIT: color = al_color_name("red"); break;
      case INSERT: color = al_color_name("lime"); break;
      case COMMAND: color = al_color_name("dodgerblue"); break;
      default: break;
      }

      al_draw_text(font, color, al_get_display_width(display)/2, al_get_display_height(display)-al_get_font_line_height(font)*2, ALLEGRO_ALIGN_CENTER, get_current_mode_string().c_str());
      al_draw_text(font, al_color_name("gray"), al_get_display_width(display)/2, al_get_display_height(display)-al_get_font_line_height(font)*1, ALLEGRO_ALIGN_CENTER, filename.c_str());
   }

   // events

   static const std::string MOVE_CURSOR_UP;
   static const std::string MOVE_CURSOR_DOWN;
   static const std::string MOVE_CURSOR_LEFT;
   static const std::string MOVE_CURSOR_RIGHT;
   static const std::string MOVE_CURSOR_JUMP_TO_NEXT_WORD;
   static const std::string MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD;
   static const std::string JUMP_TO_NEXT_CODE_POINT;
   static const std::string JUMP_TO_PREVIOUS_CODE_POINT;
   static const std::string DELETE_CHARACTER;
   static const std::string INSERT_STRING;
   static const std::string SET_INSERT_MODE;
   static const std::string SET_EDIT_MODE;
   static const std::string SET_COMMAND_MODE;
   static const std::string JOIN_LINES;
   static const std::string SPLIT_LINES;
   static const std::string MOVE_CURSOR_TO_START_OF_LINE;
   static const std::string MOVE_CURSOR_TO_END_OF_LINE;
   static const std::string SAVE_FILE;
   static const std::string MOVE_STAGE_UP;
   static const std::string MOVE_STAGE_DOWN;
   static const std::string SCALE_STAGE_UP;
   static const std::string SCALE_STAGE_DOWN;
   static const std::string OFFSET_FIRST_LINE_NUM_DOWN;
   static const std::string OFFSET_FIRST_LINE_NUM_UP;
   static const std::string OFFSET_CURSOR_POSITION_Y_DOWN;
   static const std::string OFFSET_CURSOR_POSITION_Y_UP;
   static const std::string REFRESH_GIT_MODIFIED_LINE_NUMBERS;
   static const std::string TOGGLE_SHOWING_CODE_MESSAGE_POINTS;
   static const std::string REFRESH_REGEX_MESSAGE_POINTS;
   static const std::string OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR;

   void process_local_event(std::string event_name, intptr_t data1=0, intptr_t data2=0)
   {
      std::cout << "Stage::" << event_name << std::endl;

      try {
         if (event_name == MOVE_CURSOR_UP) move_cursor_up();
         else if (event_name == MOVE_CURSOR_DOWN) move_cursor_down();
         else if (event_name == MOVE_CURSOR_LEFT) move_cursor_left();
         else if (event_name == MOVE_CURSOR_RIGHT) move_cursor_right();
         else if (event_name == MOVE_CURSOR_JUMP_TO_NEXT_WORD) move_cursor_jump_to_next_word();
         else if (event_name == MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD) move_cursor_jump_to_previous_word();
         else if (event_name == JUMP_TO_NEXT_CODE_POINT) jump_to_next_code_point();
         else if (event_name == JUMP_TO_PREVIOUS_CODE_POINT) jump_to_previous_code_point();
         else if (event_name == DELETE_CHARACTER) delete_character();
         else if (event_name == INSERT_STRING) insert_string(*(std::string *)data1);
         else if (event_name == SET_INSERT_MODE) set_insert_mode();
         else if (event_name == SET_EDIT_MODE) set_edit_mode();
         else if (event_name == SET_COMMAND_MODE) set_operator_mode();
         else if (event_name == JOIN_LINES) join_lines();
         else if (event_name == SPLIT_LINES) split_lines();
         else if (event_name == MOVE_CURSOR_TO_START_OF_LINE) move_cursor_to_start_of_line();
         else if (event_name == MOVE_CURSOR_TO_END_OF_LINE) move_cursor_to_end_of_line();
         else if (event_name == SAVE_FILE) save_file();
         else if (event_name == MOVE_STAGE_UP) move_stage_up();
         else if (event_name == MOVE_STAGE_DOWN) move_stage_down();
         else if (event_name == SCALE_STAGE_UP) scale_stage_delta(0.1);
         else if (event_name == SCALE_STAGE_DOWN) scale_stage_delta(-0.1);
         else if (event_name == OFFSET_FIRST_LINE_NUM_DOWN) offset_first_line_num(10);
         else if (event_name == OFFSET_FIRST_LINE_NUM_UP) offset_first_line_num(-10);
         else if (event_name == OFFSET_CURSOR_POSITION_Y_DOWN) offset_cursor_position_y(10);
         else if (event_name == OFFSET_CURSOR_POSITION_Y_UP) offset_cursor_position_y(-10);
         else if (event_name == REFRESH_GIT_MODIFIED_LINE_NUMBERS) refresh_git_modified_line_numbers();
         else if (event_name == TOGGLE_SHOWING_CODE_MESSAGE_POINTS) toggle_showing_code_message_points();
         else if (event_name == REFRESH_REGEX_MESSAGE_POINTS) refresh_regex_message_points();
         else if (event_name == OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR) offset_first_line_to_vertically_center_cursor();
      }

      catch (const std::exception &e)
      {
         std::cout << "💥 cannot execute \"" << event_name << "\"" << std::endl;
      }
   }

   void process_event(ALLEGRO_EVENT &event)
   {
      //std::map<std::tuple<int, bool, bool, bool>, std::vector<std::string>> mapping;
      //bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, std::vector<std::string> comand_identifier);
      KeyboardCommandMapper edit_mode__keyboard_command_mapper;
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_0, false, false, false, { Stage::MOVE_CURSOR_TO_START_OF_LINE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_I, true,  false, false, { Stage::MOVE_CURSOR_TO_START_OF_LINE, Stage::MOVE_CURSOR_JUMP_TO_NEXT_WORD, Stage::SET_INSERT_MODE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_A, true,  false, false, { Stage::MOVE_CURSOR_TO_END_OF_LINE, Stage::SET_INSERT_MODE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, false, false, false, { Stage::MOVE_CURSOR_DOWN });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, true,  false, false, { Stage::JOIN_LINES });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_K, false, false, false, { Stage::MOVE_CURSOR_UP });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_H, false, false, false, { Stage::MOVE_CURSOR_LEFT });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_L, false, false, false, { Stage::MOVE_CURSOR_RIGHT });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_W, false, false, false, { Stage::MOVE_CURSOR_JUMP_TO_NEXT_WORD });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_B, false, false, false, { Stage::MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_N, false, false, false, { Stage::JUMP_TO_NEXT_CODE_POINT, Stage::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_N, true, false, false, { Stage::JUMP_TO_PREVIOUS_CODE_POINT, Stage::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_X, false, false, false, { Stage::DELETE_CHARACTER });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_I, false, false, false, { Stage::SET_INSERT_MODE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_0, false, false, false, { Stage::MOVE_CURSOR_TO_START_OF_LINE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, true, false, { Stage::SAVE_FILE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_U, false, true, false, { Stage::OFFSET_FIRST_LINE_NUM_UP, Stage::OFFSET_CURSOR_POSITION_Y_UP });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_D, false, true, false, { Stage::OFFSET_FIRST_LINE_NUM_DOWN, Stage::OFFSET_CURSOR_POSITION_Y_DOWN });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_EQUALS, false, true, false, { Stage::SCALE_STAGE_UP });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_MINUS, false, true, false, { Stage::SCALE_STAGE_DOWN });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_O, false, false, false, { Stage::MOVE_CURSOR_TO_END_OF_LINE, Stage::SPLIT_LINES, Stage::MOVE_CURSOR_DOWN, Stage::MOVE_CURSOR_TO_START_OF_LINE, Stage::SET_INSERT_MODE });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_G, false, false, true, { Stage::REFRESH_GIT_MODIFIED_LINE_NUMBERS });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_TAB, false, false, false, { Stage::TOGGLE_SHOWING_CODE_MESSAGE_POINTS });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, false, false, { Stage::REFRESH_REGEX_MESSAGE_POINTS });
      edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_Z, false, false, false, { Stage::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR });
      //edit_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_D, false, false, false, { Stage::SET_COMMAND_MODE, Stage::SET_OPERATOR_DELETE });


      //std::map<std::tuple<int, bool, bool, bool>, std::vector<std::string>> mapping;
      //bool set_mapping(int al_keycode, bool shift, bool ctrl, bool alt, std::vector<std::string> comand_identifier);
      KeyboardCommandMapper insert_mode__keyboard_command_mapper;
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, { Stage::SET_EDIT_MODE });
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, false, true, false, { Stage::SET_EDIT_MODE });
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_BACKSPACE, false, false, false, { Stage::MOVE_CURSOR_LEFT, Stage::DELETE_CHARACTER });
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER, false, false, false, { Stage::SPLIT_LINES, Stage::MOVE_CURSOR_DOWN, Stage::MOVE_CURSOR_TO_START_OF_LINE });
      insert_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_S, false, true, false, { Stage::SAVE_FILE });


      KeyboardCommandMapper operator_mode__keyboard_command_mapper;
      //operator_mode__keyboard_command_mapper.set_mapping(ALLEGRO_KEY_D, false, false, false, { Stage::SET_OPERATOR_MOTION_LINE; });


      switch(mode)
      {
      case EDIT:
         switch(event.type)
         {
         case ALLEGRO_EVENT_KEY_DOWN:
            break;
         case ALLEGRO_EVENT_KEY_UP:
            break;
         case ALLEGRO_EVENT_KEY_CHAR:
            bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL || event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
            bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
            std::vector<std::string> mapped_events = edit_mode__keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl, alt);
            for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
            break;
         }
         break;
      case INSERT:
         switch(event.type)
         {
         case ALLEGRO_EVENT_KEY_DOWN:
            break;
         case ALLEGRO_EVENT_KEY_UP:
            break;
         case ALLEGRO_EVENT_KEY_CHAR:
            bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
            bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL || event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
            bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
            std::vector<std::string> mapped_events = insert_mode__keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl, alt);
            for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
            if (mapped_events.empty())
            {
               char character = (char)(event.keyboard.unichar);
               std::string *string = new std::string(" ");
               string->operator[](0) = character;
               process_local_event(INSERT_STRING, (intptr_t)string);
               process_local_event(MOVE_CURSOR_RIGHT);
               delete string;
            }
            break;
         }
         break;
      case COMMAND:
         switch(event.type)
         {
         case ALLEGRO_EVENT_KEY_CHAR:
           // obtain key mapping, perform it, see if it evaluates to a final complete command
           // evaluate
           process_local_event(SET_EDIT_MODE);
           break;
         }
         break;
      }
   }
};


std::string const Stage::MOVE_CURSOR_UP = "MOVE_CURSOR_UP";
std::string const Stage::MOVE_CURSOR_DOWN = "MOVE_CURSOR_DOWN";
std::string const Stage::MOVE_CURSOR_LEFT = "MOVE_CURSOR_LEFT";
std::string const Stage::MOVE_CURSOR_RIGHT = "MOVE_CURSOR_RIGHT";
std::string const Stage::MOVE_CURSOR_JUMP_TO_NEXT_WORD = "MOVE_CURSOR_JUMP_TO_NEXT_WORD";
std::string const Stage::MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD = "MOVE_CURSOR_JUMP_TO_PREVIOUS_WORD";
std::string const Stage::JUMP_TO_NEXT_CODE_POINT = "JUMP_TO_NEXT_CODE_POINT";
std::string const Stage::JUMP_TO_PREVIOUS_CODE_POINT = "JUMP_TO_PREVIOUS_CODE_POINT";
std::string const Stage::DELETE_CHARACTER = "DELETE_CHARACTER";
std::string const Stage::INSERT_STRING = "INSERT_STRING";
std::string const Stage::SET_INSERT_MODE = "SET_INSERT_MODE";
std::string const Stage::SET_EDIT_MODE = "SET_EDIT_MODE";
std::string const Stage::SET_COMMAND_MODE = "SET_COMMAND_MODE";
std::string const Stage::JOIN_LINES = "JOIN_LINES";
std::string const Stage::SPLIT_LINES = "SPLIT_LINES";
std::string const Stage::MOVE_CURSOR_TO_START_OF_LINE = "MOVE_CURSOR_TO_START_OF_LINE";
std::string const Stage::MOVE_CURSOR_TO_END_OF_LINE = "MOVE_CURSOR_TO_END_OF_LINE";
std::string const Stage::SAVE_FILE = "SAVE_FILE";
std::string const Stage::MOVE_STAGE_UP = "MOVE_STAGE_UP";
std::string const Stage::MOVE_STAGE_DOWN = "MOVE_STAGE_DOWN";
std::string const Stage::OFFSET_FIRST_LINE_NUM_UP = "OFFSET_FIRST_LINE_NUM_UP";
std::string const Stage::OFFSET_FIRST_LINE_NUM_DOWN = "OFFSET_FIRST_LINE_NUM_DOWN";
std::string const Stage::OFFSET_CURSOR_POSITION_Y_UP = "OFFSET_CURSOR_POSITION_Y_UP";
std::string const Stage::OFFSET_CURSOR_POSITION_Y_DOWN = "OFFSET_CURSOR_POSITION_Y_DOWN";
std::string const Stage::SCALE_STAGE_UP = "SCALE_STAGE_UP";
std::string const Stage::SCALE_STAGE_DOWN = "SCALE_STAGE_DOWN";
std::string const Stage::REFRESH_GIT_MODIFIED_LINE_NUMBERS = "REFRESH_GIT_MODIFIED_LINE_NUMBERS";
std::string const Stage::TOGGLE_SHOWING_CODE_MESSAGE_POINTS = "TOGGLE_SHOWING_CODE_MESSAGE_POINTS";
std::string const Stage::REFRESH_REGEX_MESSAGE_POINTS = "REFRESH_REGEX_MESSAGE_POINTS";
std::string const Stage::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR = "OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR";


const std::string sonnet = R"END(Is it thy will thy image should keep open
My heavy eyelids to the weary night?
Dost thou desire my slumbers should be broken,
While shadows like to thee do mock my sight?
Is it thy spirit that thou send'st from thee
So far from home into my deeds to pry,
To find out shames and idle hours in me,
The scope and tenor of thy jealousy?
O, no! thy love, though much, is not so great:
It is my love that keeps mine eye awake;
Mine own true love that doth my rest defeat,
To play the watchman ever for thy sake:
For thee watch I whilst thou dost wake elsewhere,
From me far off, with others all too near.

- William Shakespere)END";



class System
{
public:
   std::vector<Stage *> stages;
   ALLEGRO_DISPLAY *display;

   System(ALLEGRO_DISPLAY *display)
      : stages({})
      , display(display)
   {}

   // retrieval

   Stage *get_frontmost_stage()
   {
      if (stages.size() == 0)
      {
         std::cout << "Attempted to get front-most stage, but none was present." << std::endl;
         return nullptr;
      }
      return stages[0];
   }

   // inference

   bool is_current_stage_in_edit_mode()
   {
      return get_frontmost_stage()->get_mode() == Stage::EDIT;
   }

   bool is_current_stage_a_one_line_input_box()
   {
      return get_frontmost_stage()->get_type() == Stage::ONE_LINE_INPUT_BOX;
   }

   // actions

   bool rotate_stage_right()
   {
      std::rotate(stages.begin(), stages.begin() + 1, stages.end());
      return true;
   }

   bool rotate_stage_left()
   {
      std::rotate(stages.rbegin(), stages.rbegin() + 1, stages.rend());
      return true;
   }

   bool run_project_tests()
   {
      Stage *stage = get_frontmost_stage();

      std::string test_output = RailsMinitestTestRunner(stage->get_filename()).run();
      RailsTestOutputParser rails_test_output_parser(test_output);
      //for (auto &test_result_line : rails_test_output_parser.get_test_result_lines())
      //{
         //std::cout << test_result_line << std::endl;
         //std::cout << "=============================" << std::endl;
      //}

      std::vector<CodeMessagePoint> code_message_points;
      for (auto &minitest_test_result : rails_test_output_parser.get_test_result_lines())
      {
         switch(minitest_test_result.get_test_state())
         {
            case RailsMinitestTestResult::ERROR:
            case RailsMinitestTestResult::FAILURE:
            {
               RailsMinitestTestResultToCodeMessagePointConverter converter(minitest_test_result);
               code_message_points.push_back(converter.convert());
               break;
            }
            default: break;
         }

      }
      stage->clear_code_message_points();
      stage->set_code_message_points({ code_message_points });

      return true;
   }

   bool save_current_stage()
   {
      get_frontmost_stage()->save_file();
   }

   bool refresh_regex_hilights_on_stage()
   {
      get_frontmost_stage()->refresh_regex_message_points();
   }

   bool set_regex_input_box_modal_to_insert_mode()
   {
      get_frontmost_stage()->process_local_event(Stage::SET_INSERT_MODE);
   }

   bool spawn_regex_input_box_modal()
   {
      placement2d place(al_get_display_width(display)/2, al_get_display_height(display)/3, 200, 35);
      place.scale = vec2d(1.2, 1.2);

      stages.insert(stages.begin(), new Stage(REGEX_TEMP_FILENAME, place, Stage::EDIT, Stage::ONE_LINE_INPUT_BOX));
      std::vector<std::string> file_contents;
      //read_file(file_contents, stages[0]->get_filename());
      stages[0]->set_content(std::vector<std::string>{"", ""});
   }

   bool destroy_current_modal()
   {
      if (stages.size() == 1) throw std::runtime_error("Cannot destroy current modal. There is only 1 stage in the system");
      stages.erase(stages.begin());
   }

   bool jump_to_next_code_point_on_stage()
   {
      get_frontmost_stage()->process_local_event(Stage::JUMP_TO_NEXT_CODE_POINT);
      return true;
   }

   bool run_make()
   {
      CppCompiler::CompileRunner compile_runner("foobar");
      std::string compile_output = compile_runner.run();
      //CppCompiler::CompileOutputToCodeMessagePointSetter(compile_output, this);
      return true;
   }


   // events

   static const std::string ROTATE_STAGE_RIGHT;
   static const std::string ROTATE_STAGE_LEFT;
   static const std::string RUN_PROJECT_TESTS;
   static const std::string RUN_MAKE;
   static const std::string SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL;
   static const std::string DESTROY_CURRENT_MODAL;
   static const std::string SAVE_CURRENT_STAGE;
   static const std::string REFRESH_REGEX_HILIGHTS_ON_STAGE;
   static const std::string SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE;
   static const std::string JUMP_TO_NEXT_CODE_POINT_ON_STAGE;

   void process_local_event(std::string event_name)
   {
      std::cout << "System::" << event_name << std::endl;

      try
      {
         if (event_name == ROTATE_STAGE_RIGHT) rotate_stage_right();
         else if (event_name == ROTATE_STAGE_LEFT) rotate_stage_left();
         else if (event_name == RUN_PROJECT_TESTS) run_project_tests();
         else if (event_name == SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL) spawn_regex_input_box_modal();
         else if (event_name == DESTROY_CURRENT_MODAL) destroy_current_modal();
         else if (event_name == SAVE_CURRENT_STAGE) save_current_stage();
         else if (event_name == REFRESH_REGEX_HILIGHTS_ON_STAGE) refresh_regex_hilights_on_stage();
         else if (event_name == SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE) set_regex_input_box_modal_to_insert_mode();
         else if (event_name == RUN_MAKE) run_make();
      }
      catch (const std::exception &exception)
      {
         std::cout << ">BOOM< cannot execute \"" << event_name << "\"" << std::endl;
      }
   }

   void process_event(ALLEGRO_EVENT &event)
   {
      KeyboardCommandMapper keyboard_command_mapper;
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, false, false, true, { ROTATE_STAGE_RIGHT });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_CLOSEBRACE, false, false, true, { ROTATE_STAGE_LEFT });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_T, false, false, true, { SAVE_CURRENT_STAGE, RUN_PROJECT_TESTS });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_M, false, false, true, { SAVE_CURRENT_STAGE, RUN_MAKE });
      if (is_current_stage_in_edit_mode())
      {
        keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, false, false, { SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL, SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE });
      }
      if (is_current_stage_a_one_line_input_box())
      {
         keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER, false, false, false, { SAVE_CURRENT_STAGE, DESTROY_CURRENT_MODAL, REFRESH_REGEX_HILIGHTS_ON_STAGE, JUMP_TO_NEXT_CODE_POINT_ON_STAGE });
      }

      bool event_caught = false;

      switch(event.type)
      {
      case ALLEGRO_EVENT_KEY_UP:
         break;
      case ALLEGRO_EVENT_KEY_DOWN:
         break;
      case ALLEGRO_EVENT_KEY_CHAR:
         bool shift = event.keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
         bool alt = event.keyboard.modifiers & ALLEGRO_KEYMOD_ALT;
         bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL || event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         std::vector<std::string> mapped_events = keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl, alt);
         if (!mapped_events.empty()) event_caught = true;
         for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
         break;
      }

      if (!event_caught) stages[0]->process_event(event);
   }

private:
};


const std::string System::ROTATE_STAGE_RIGHT = "ROTATE_STAGE_RIGHT";
const std::string System::ROTATE_STAGE_LEFT = "ROTATE_STAGE_LEFT";
const std::string System::RUN_PROJECT_TESTS = "RUN_PROJECT_TESTS";
const std::string System::RUN_MAKE = "RUN_MAKE";
const std::string System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL = "SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL";
const std::string System::SAVE_CURRENT_STAGE = "SAVE_CURRENT_STAGE";
const std::string System::DESTROY_CURRENT_MODAL = "DESTROY_CURRENT_MODAL";
const std::string System::REFRESH_REGEX_HILIGHTS_ON_STAGE = "REFRESH_REGEX_HILIGHTS_ON_STAGE";
const std::string System::SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE = "SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE";
const std::string System::JUMP_TO_NEXT_CODE_POINT_ON_STAGE = "JUMP_TO_NEXT_CODE_POINT_ON_STAGE";



void run_program(std::vector<std::string> filenames)
{
   if (!al_init()) std::cerr << "al_init() failed" << std::endl;
   if (!al_init_font_addon()) std::cerr << "al_init_font_addon() failed" << std::endl;
   if (!al_init_ttf_addon()) std::cerr << "al_init_ttf_addon() failed" << std::endl;

   if (!al_install_keyboard()) std::cerr << "al_install_keyboard() failed" << std::endl;

   al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

   al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
   ALLEGRO_DISPLAY *display = al_create_display(2880-200-250, 1800-200-250);
   ALLEGRO_FONT *consolas_font = al_load_font(resource({"data", "fonts"}, "consolas.ttf").c_str(), 30, 0);

   int display_width = al_get_display_width(display);
   int display_height = al_get_display_height(display);

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_display_event_source(display));

   float logo_radius = 60;
   Logo logo(display_width/2, display_height/2 - logo_radius * 1.4, logo_radius, al_color_name("darkviolet"), 3);
   logo.render();
   al_draw_text(consolas_font, al_color_name("darkviolet"), display_width/2, display_height/2, ALLEGRO_ALIGN_CENTER, "hexagon");


   al_flip_display();


   std::string first_filename = filenames.empty() ? "" : filenames[0];


   placement2d place(100, 20, 400, 400);
   place.align = vec2d(0, 0);
   place.scale = vec2d(0.65, 0.65);


   bool shutdown_program = false;
   bool first_load = true;


   System system(display);

   for (auto &filename : filenames)
   {
      Stage *stage = new Stage(filename, place);

      std::vector<std::string> lines;
      read_file(lines, filename);

      stage->set_content(lines);
      system.stages.push_back(stage);
   }


   while(!shutdown_program)
   {
      ALLEGRO_EVENT this_event;
      if (!first_load) al_wait_for_event(event_queue, &this_event);
      first_load = false;

      system.process_event(this_event);

      switch(this_event.type)
      {
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
         shutdown_program = true;
         break;
      }

      al_clear_to_color(al_color_name("black"));
      for (auto &stage : system.stages)
      {
         stage->render(display, consolas_font, al_get_text_width(consolas_font, " "), al_get_font_line_height(consolas_font));
         if (stage->get_type() == Stage::CODE_EDITOR) break;
      }
      al_flip_display();
   }


   al_destroy_event_queue(event_queue);
   al_destroy_font(consolas_font);
   al_destroy_display(display);
}

int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=0; i<argc; i++) args.push_back(argv[i]);
   CommandLineFlaggedArgumentsParser command_line_flagged_arguments_parser(args);

   std::vector<std::vector<std::string>> filenames = command_line_flagged_arguments_parser.get_flagged_args("-f");
   std::vector<std::string> first_filenames_set = filenames.empty() ? std::vector<std::string>{} : filenames[0];

   run_program(first_filenames_set);
   return 0;
}


