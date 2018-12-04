#include <iostream>
#include <sstream>
#include <algorithm>


#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


#include <allegro_flare/placement2d.h>
#include <allegro_flare/placement3d.h>
#include <allegro_flare/useful_php.h>
#include <allegro_flare/render_cache.h>


#include <Blast/StringSplitter.hpp>
#include <Blast/KeyboardCommandMapper.hpp>
#include <Blast/ShellCommandExecutor.hpp>
#include <Blast/CommandLineFlaggedArgumentsParser.hpp>
#include <lib/camera.h>


using namespace Blast;


#include <Hexagon/Logo.hpp>
#include <Hexagon/RegexMatcher.hpp>


using namespace Hexagon;



#include <Hexagon/shared_globals.hpp>
//std::string REGEX_TEMP_FILENAME = "regex.txt";
//std::string CLIPBOARD_TEMP_FILENAME = "clipboard.txt";
//std::string FILE_NAVIGATOR_SELECTION_FILENAME = "file_navigator_selection.txt";
//std::string FILE_NAVIGATOR_SELECTION_last_content = "";



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



#include <Hexagon/util.hpp>



#include <Hexagon/ClipboardData.hpp>



#include <Hexagon/ActionData.hpp>


#include <Hexagon/Action.hpp>



#include <Hexagon/ActionQueueRecording.hpp>

#include <Hexagon/CodePoint.hpp>
#include <Hexagon/CodeRange.hpp>


class RailsMinitestTestResult
{
public:
   enum test_state_t
   {
      UNKNOWN,
      RUNNING,
      PASS,
      FAILURE,
      SKIPPED,
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
   case RailsMinitestTestResult::SKIPPED:
      out << "skip";
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
            else if (possible_test_line_output_tokens[2] == " S") test_state = RailsMinitestTestResult::SKIPPED;

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

               if (current_rails_minitest_test_result->test_state == RailsMinitestTestResult::ERROR)
               {
                  // attempt to extract the error line by matching the final line
                  std::string final_line_regex_expression = "bin/rails test .+_test\\.rb:";
                  std::vector<std::pair<int, int>> matches = RegexMatcher(source_test_output_line, final_line_regex_expression).get_match_info();
                  if (matches.size() == 1 && matches[0].first == 0)
                  {
                     std::cout << "Found Matched Error Line!" << std::endl;
                     std::vector<std::string> splits = StringSplitter(source_test_output_line, ':').split();
                     if (splits.size() != 2) throw std::runtime_error("RailsTestOutputParser: unexpected number of splits, expecting 2");
                     std::string number = splits.back();
                     bool number_contains_only_number_characters = (number.find_first_not_of("0123456789") == std::string::npos);
                     if (!number_contains_only_number_characters) throw std::runtime_error("RailsTestOutputParser: unexpected characters in expected number string");
                     current_rails_minitest_test_result->error_line_number = atoi(number.c_str());
                  }
               }
               else
               {
                  // attempt to extract the error line by matching the code in the [] brackets

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



void command_line_exec_callback(std::string new_content)
{
   std::cout << "####>" << new_content << "<####" << std::endl;
}



class RailsMinitestTestRunner
{
private:
   std::string test_filename;

public:
   RailsMinitestTestRunner(std::string test_filename)
      : test_filename(test_filename)
   {}
   ~RailsMinitestTestRunner() {}

   std::string get_execution_command()
   {
      std::stringstream test_command_string;
      test_command_string << "bin/rails test " << test_filename << " -v";
      return test_command_string.str();
   }

   std::string run()
   {
      ShellCommandExecutor shell_command_executor(get_execution_command());
      std::string output = shell_command_executor.execute(command_line_exec_callback);
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





#include <Hexagon/CodeRangeExtractor.hpp>


#include <Hexagon/CodeMessagePoint.hpp>




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
      else if (rails_minitest_test_result.test_state == RailsMinitestTestResult::FAILURE) code_message_point_type = CodeMessagePoint::TEST_FAILURE;
      return CodeMessagePoint(0, rails_minitest_test_result.error_line_number, 0, 0, rails_minitest_test_result.test_result_output, code_message_point_type);
   }
};




#include <Hexagon/CodeMessagePointsOverlay.hpp>





class SystemWideMotion : public Motion {};


SystemWideMotion motion;





#include <Hexagon/StageInterface.hpp>


class KeyboardInputsModal : public StageInterface
{
private:
   KeyboardCommandMapper *keyboard_command_mapper;

public:
   KeyboardInputsModal(KeyboardCommandMapper *keyboard_command_mapper)
      : StageInterface(KEYBOARD_INPUTS_MODAL)
      , keyboard_command_mapper(keyboard_command_mapper)
   {}

   virtual void render(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height)
   {
      if (!display) throw std::runtime_error("[KeyboardInputsModal] error: display cannot be a nullptr.");
      if (!font) throw std::runtime_error("[KeyboardInputsModal] error: font cannot be a nullptr.");

      placement3d &place = get_place();

      float border_thickness = 5.0;
      place.size = vec3d(500.0, 400.0, 0.0);
      place.align = vec3d(0.5, 0.5, 0.0);
      place.rotation = vec3d(place.rotation.x, place.rotation.y, place.rotation.z);

      place.start_transform();
      al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, color::black);
      al_draw_rounded_rectangle(0 - border_thickness, 0 - border_thickness, place.size.x + border_thickness, place.size.y + border_thickness, 8.0, 8.0, color::dimgray, border_thickness);
      place.restore_transform();
   }

   virtual void process_local_event(std::string event_name, ActionData action_data=ActionData()) {}
   virtual void process_event(ALLEGRO_EVENT &event) {}
   virtual bool save_file() { return true; }
};



#include <string>
#include <vector>



#include <Hexagon/EventControllerInterface.hpp>



#include <Hexagon/StageRenderer.hpp>




#include <Hexagon/StageEventController.hpp>



/* begin
class Stage : public StageInterface
{
public:
   enum mode_t
   {
      EDIT,
      INSERT,
   };

   //enum type_t
   //{
      //NONE,
      //CODE_EDITOR,
      //ONE_LINE_INPUT_BOX,
   //};

private:
   friend class StageRenderer;

   std::vector<std::string> lines;
   int cursor_x;
   int cursor_y;

   mode_t mode;
   //type_t type;

   std::string filename;

   // presentation

   //placement2d place;
   int first_line_number;

public:
   Stage(std::string filename, mode_t mode=EDIT, type_t type=CODE_EDITOR)
      : StageInterface(type)
      , cursor_x(0)
      , cursor_y(0)
      , mode(mode)
      //, type(type)
      , filename(filename)
      //, place(place)
      , first_line_number(0)
      , code_message_points_overlays()
      , currently_grabbing_visual_selection(false)
      , selections()
   {
      code_message_points_overlays.push_back(CodeMessagePointsOverlay(al_color_name("dogerblue"), {}));
   }

   // accessors

   void set_cursor_x(int cursor_x)
   {
      this->cursor_x = cursor_x;
      set_current_selection_end_x(cursor_x + 1);
   }

   void set_cursor_y(int cursor_y)
   {
      this->cursor_y = cursor_y;
      set_current_selection_end_y(cursor_y);
   }

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

   placement3d &get_place_ref()
   {
      return get_place();
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

   std::vector<std::string> const &get_lines_ref()
   {
      return lines;
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
      if (mode == EDIT) return (currently_grabbing_visual_selection ? "EDIT - VISUAL" : "EDIT");
      if (mode == INSERT) return "INSERT";
      return "---";
   }

   // inference

   int infer_num_lines_to_draw()
   {
      return 50;
   }

   // actions

   bool move_cursor_up()
   {
      if (num_lines() <= 0) return false;
      set_cursor_y(cursor_y - 1);
      return true;
   }
   bool move_cursor_down()
   {
      if (cursor_y >= num_lines()) return false;
      set_cursor_y(cursor_y + 1);
      return true;
   }
   bool move_cursor_left()
   {
      set_cursor_x(cursor_x - 1);
      return true;
   }
   bool move_cursor_right()
   {
      set_cursor_x(cursor_x + 1);
      return true;
   }
   bool move_cursor_to_top_of_screen()
   {
      set_cursor_y(first_line_number);
      return true;
   }
   bool move_cursor_to_middle_of_screen()
   {
      set_cursor_y(first_line_number + infer_num_lines_to_draw()/2);
      return true;
   }
   bool move_cursor_to_bottom_of_screen()
   {
      set_cursor_y(first_line_number + infer_num_lines_to_draw()-1);
      return true;
   }
   bool move_cursor_jump_to_next_word()
   {
      std::string vim_equivelent_word_jump_regex = "([0-9a-zA-Z_]+)|([^0-9a-zA-Z_ \\s]+)";      // vimdoc.sourceforge.net/htmldoc/motion.html#word
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
   bool move_cursor_jump_to_next_big_word()
   {
      std::string vim_equivelent_word_jump_regex = "[^\\s]+";      // vimdoc.sourceforge.net/htmldoc/motion.html#word
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
   bool jump_cursor_to_end_of_next_word()
   {
      std::string vim_equivelent_word_jump_regex = "([0-9a-zA-Z_]+)|([^0-9a-zA-Z_ \\s]+)";      // vimdoc.sourceforge.net/htmldoc/motion.html#word
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
   bool jump_cursor_to_end_of_next_big_word()
   {
      std::string vim_equivelent_word_jump_regex = "[^\\s]+";      // vimdoc.sourceforge.net/htmldoc/motion.html#word
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
   bool move_cursor_jump_to_previous_word()
   {
      int position = 0;

      position = rfind_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { set_cursor_x(position); }

      position = rfind_non_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { set_cursor_x(position); return true; }

      return false;
   }
   bool move_cursor_jump_to_previous_big_word()
   {
      int position = 0;

      position = rfind_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { set_cursor_x(position); }

      position = rfind_non_whitespace(current_line_ref(), cursor_x);
      if (position != -1) { set_cursor_x(position); return true; }

      return false;
   }
   bool move_cursor_to_start_of_line()
   {
      set_cursor_x(0);
      return true;
   }
   bool move_cursor_to_end_of_line()
   {
      set_cursor_x(current_line_ref().length());
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
   bool insert_lines(std::vector<std::string> &lines_to_insert)
   {
      int range_safe_y = std::min(std::max(0, cursor_y), (int)lines.size());
      lines.insert(lines.begin() + range_safe_y, lines_to_insert.begin(), lines_to_insert.end());
      return true;
   }
   bool insert_string(std::string string)
   {
      current_line_ref().insert(cursor_x, string);
      return true;
   }
   bool save_file() override
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
   //bool showing_code_message_points;
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
               || (message_point_y == (most_viable_code_point->get_y() - 1) && message_point.get_x() < most_viable_code_point->get_x())
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
         set_cursor_x(most_viable_code_point->get_x() + most_viable_code_point->get_cursor_placement_offset());
         set_cursor_y(most_viable_code_point->get_y()-1);
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

      std::string regex_expression = regex_input_file_lines[0];
      std::size_t carat_position = regex_expression.find_last_of('^');
      int cursor_placement_offset = (carat_position == std::string::npos) ? 0 : carat_position;

      if (regex_expression.empty()) return true;

      regex_expression.erase(std::remove(regex_expression.begin() + 1, regex_expression.end(), '^'), regex_expression.end());

      std::vector<CodeMessagePoint> results;
      for (unsigned i=0; i<lines.size(); i++)
      {
         RegexMatcher regex_matcher(lines[i], regex_expression);
         std::vector<std::pair<int, int>> match_positions = regex_matcher.get_match_info();
         for (auto &match_position : match_positions)
         {
            results.push_back(CodeMessagePoint(match_position.first, i+1, match_position.second, cursor_placement_offset, "[match]", CodeMessagePoint::POSITION));
         }
      }
      set_code_message_points(results);

      return true;
   }

   // presentation

   // actions

   bool offset_first_line_number(int delta)
   {
      first_line_number += delta;
      if (first_line_number < 0) first_line_number = 0;
      if (first_line_number >= lines.size()) first_line_number = lines.size()-1;
      return true;
   }

   bool offset_cursor_position_y(int delta)
   {
      set_cursor_y(cursor_y + delta);
      if (cursor_y < 0) set_cursor_y(0);
      if (cursor_y >= lines.size()) set_cursor_y(lines.size()-1);
      return true;
   }

   bool move_stage_up(float distance=100)
   {
      get_place().position.y += distance;
      return true;
   }

   bool move_stage_down(float distance=100)
   {
      get_place().position.y -= distance;
      return true;
   }

   bool offset_first_line_to_vertically_center_cursor(int distance_from_top=20)
   {
      first_line_number = cursor_y - distance_from_top;
      return true;
   }

   bool scale_stage_delta(float delta)
   {
      get_place().scale += vec3d(delta, delta, 1.0);
      return true;
   }

   //bool toggle_showing_code_message_points()
   //{
      //showing_code_message_points = !showing_code_message_points;
      //return true;
   //}

   bool create_visual_selection_at_current_cursor_location()
   {
      selections.push_back(CodeRange(cursor_x, cursor_y, cursor_x+1, cursor_y));
      return true;
   }

   bool destroy_current_visual_selection()
   {
      selections.clear();
      return true;
   }

   bool toggle_currently_grabbing_visual_selection()
   {
      currently_grabbing_visual_selection = !currently_grabbing_visual_selection;
      //std::cout << " - visual mode: " << currently_grabbing_visual_selection << std::endl;
      if (currently_grabbing_visual_selection) create_visual_selection_at_current_cursor_location();
      else destroy_current_visual_selection();
      return true;
   }

   // rendering

   // partials

   bool currently_grabbing_visual_selection;
   std::vector<CodeRange> selections;

   void draw_selections(int cell_width, int cell_height)
   {
      for (auto &selection : selections)
      {
         //std::cout << " drawing selection " << selection << std::endl;
         CodeRangeRenderer(get_lines_ref(), selection, first_line_number, cell_width, cell_height).render();
      }
   }

   bool set_current_selection_end_x(int x)
   {
      if (selections.empty()) return true;
      selections.back().set_cursor_end_x(x);
      return true;
   }

   bool set_current_selection_end_y(int y)
   {
      if (selections.empty()) return true;
      selections.back().set_cursor_end_y(y);
      return true;
   }

   bool yank_selected_text_to_clipboard()
   {
      if (selections.empty()) throw std::runtime_error(">BOOM< cannot yank selected text; No text selection is currently active");
      std::vector<std::string> extracted_selection = CodeRangeExtractor(get_lines_ref(), selections.back()).extract();
      ClipboardData::store(extracted_selection);
      return true;
   }

   bool paste_selected_text_from_clipboard()
   {
      std::vector<std::string> retrieved_clipboard_data = ClipboardData::retrieve();
      insert_lines(retrieved_clipboard_data);

      return true;
   }

   // complete

   void render_as_input_box(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height)
   {
      get_place().start_transform();

      float roundness = 6;
      float padding = 6;
      al_draw_filled_rounded_rectangle(0-padding*2, 0-padding*2, get_place().size.x+padding*2, get_place().size.y+padding*2, roundness, roundness, al_color_name("black"));
      al_draw_rounded_rectangle(0-padding, 0-padding, get_place().size.x+padding, get_place().size.y+padding, roundness, roundness, al_color_name("dodgerblue"), 3.0);

      float _cursor_y = cursor_y - first_line_number;
      switch(mode)
      {
      case EDIT:
         al_draw_filled_rectangle(cursor_x*cell_width, _cursor_y*cell_height, cursor_x*cell_width + cell_width, _cursor_y*cell_height + cell_height, al_color_name("gray"));
         break;
      case INSERT:
         al_draw_line(cursor_x*cell_width, _cursor_y*cell_height, cursor_x*cell_width, _cursor_y*cell_height + cell_height, al_color_name("gray"), 3);
         break;
      }

      draw_selections(cell_width, cell_height);

      int line_height = al_get_font_line_height(font);
      for (int i=0; i<lines.size(); i++)
      {
         al_draw_text(font, al_color_name("dodgerblue"), 0, i*line_height, ALLEGRO_ALIGN_LEFT, lines[i].c_str());
      }

      get_place().restore_transform();
   }

   void render(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height) override
   {
      //place = this->place;

      if (get_type() == ONE_LINE_INPUT_BOX) { render_as_input_box(display, font, cell_width, cell_height); return; }

      StageRenderer stage_renderer(this, font, display, cell_width, cell_height);
      stage_renderer.render();

      return;
   }

   void process_local_event(std::string event_name, ActionData action_data1=ActionData()) override
   {
      StageEventController stage_event_controller(this);
      stage_event_controller.process_local_event(event_name, action_data1);
   }

   void process_event(ALLEGRO_EVENT &event) override
   {
      StageEventController stage_event_controller(this);
      stage_event_controller.process_event(event);
   }
};
*/


#include <Hexagon/Stage.hpp>







class FileSystemNode
{
private:
   ALLEGRO_FS_ENTRY *entry;
   std::vector<FileSystemNode *> children;

public:
   FileSystemNode(ALLEGRO_FS_ENTRY *entry)
      : entry(entry)
      , children({})
   {
      //children = FileSystemNode::create_fs_entry_children(this);
   }
   ~FileSystemNode()
   {
      al_destroy_fs_entry(entry);
      for (auto &child : children) delete child;
   }

   ALLEGRO_FS_ENTRY *get_entry() { return entry; }

   void create_children()
   {
      for (auto &child : children) delete child;
      children.clear();

      this->children = FileSystemNode::create_fs_entry_children(this);
   }

   std::vector<FileSystemNode *> &get_children_ref()
   {
      return children;
   }

   int infer_num_children()
   {
      return children.size();
   }

   bool infer_is_directory()
   {
      return (al_get_fs_entry_mode(entry) & ALLEGRO_FILEMODE_ISDIR) == ALLEGRO_FILEMODE_ISDIR;
   }

   std::string infer_full_name()
   {
      return al_get_fs_entry_name(entry);
   }

   std::string infer_folder_name()
   {
      ALLEGRO_PATH *path = al_create_path(infer_full_name().c_str());
      if (!path) throw std::runtime_error("infer_folder_name(): cannot create path");
      std::string folder_name = al_get_path_tail(path);
      al_destroy_path(path);
      return folder_name;
   }

   std::string infer_basename()
   {
      ALLEGRO_PATH *path = al_create_path(infer_full_name().c_str());
      if (!path) throw std::runtime_error("infer_basename(): cannot create path");
      std::string filename = al_get_path_filename(path);
      al_destroy_path(path);
      return filename;
   }

   //

   static std::vector<FileSystemNode *> create_fs_entry_children(FileSystemNode *node)
   {
      std::vector<FileSystemNode *> results;

      //ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(directory.c_str());

      if(al_open_directory(node->get_entry()))
      {
         ALLEGRO_FS_ENTRY* fs_entry;
         while((fs_entry = al_read_directory(node->get_entry())))
         {
            results.push_back(new FileSystemNode(fs_entry)); //al_get_fs_entry_name(file));
            //al_destroy_fs_entry(file);
         }
      }
      else
      {
         //std::cout << "could not open directory \"" << directory << "\"" << std::endl;
      }

      //al_destroy_fs_entry(dir);

      return results;
   }
};




class FileNavigator;

class FileNavigatorEventController : public EventControllerInterface
{
private:
   FileNavigator *file_navigator;

public:
   FileNavigatorEventController(FileNavigator *file_navigator);
   ~FileNavigatorEventController();

   static const std::string MOVE_CURSOR_UP;
   static const std::string MOVE_CURSOR_DOWN;

   virtual void process_local_event(std::string event_name, ActionData action_data1=ActionData()) override;
   virtual void process_event(ALLEGRO_EVENT &event) override;
};




class FileNavigator : public StageInterface
{
private:
   //std::vector<FileSystemNode *> file_system_entries;
   FileSystemNode *current_node;
   //bool visible_and_active;
   int cursor_y;

public:
   FileNavigator(std::string directory)
      //: file_system_entries()
      : StageInterface(StageInterface::FILE_NAVIGATOR)
      , current_node(new FileSystemNode(al_create_fs_entry(directory.c_str())))
      //, visible_and_active(false)
      , cursor_y(0)
      //, place()
   {
      //current_node = current_directory_fs_entry = al_create_fs_entry(al_get_current_directory());
      current_node->create_children();
   }

   ~FileNavigator() {}

   // property accessors

   void set_cursor_y(int cursor_y) { this->cursor_y = cursor_y; }
   //void set_file_system_entries(std::vector<FileSystemNode *> file_system_entries)   {      this->file_system_entries = file_system_entries;   }
   //bool get_visible_and_active() { return visible_and_active; }

   // initializers

   //bool set_

   // inferences

   FileSystemNode *infer_current_selection()
   {
      if (!current_node) return nullptr;
      if (cursor_y < 0 || cursor_y >= current_node->infer_num_children()) return nullptr;
      return current_node->get_children_ref()[cursor_y];
   }

   std::string infer_current_selection_name()
   {
      FileSystemNode *node = infer_current_selection();
      if (!node) return "";
      return node->infer_full_name();
   }

   // actions

   bool move_cursor_y_delta(int delta)
   {
      set_cursor_y(cursor_y + delta);
      if (cursor_y < 0) set_cursor_y(0);
      if (cursor_y >= current_node->infer_num_children()) set_cursor_y(current_node->infer_num_children()-1);
      return true;
   }

   bool move_cursor_up()
   {
      return move_cursor_y_delta(-1);
   }

   bool move_cursor_down()
   {
      return move_cursor_y_delta(1);
   }

   //bool show()
   //{
      //visible_and_active = true;
      //return true;
   //}

   //bool hide()
   //{
      //visible_and_active = false;
      //return true;
   //}

   //static const std::string SHOW;
   //static const std::string HIDE;

   void process_local_event(std::string event_name, ActionData action_data1=ActionData()) override
   {
      FileNavigatorEventController file_navigator_event_controller(this);
      file_navigator_event_controller.process_local_event(event_name, action_data1);
   }

   void process_event(ALLEGRO_EVENT &event) override
   {
      FileNavigatorEventController file_navigator_event_controller(this);
      file_navigator_event_controller.process_event(event);
   }

   bool save_file() override
   {
      FILE_NAVIGATOR_SELECTION_last_content = infer_current_selection_name();
      //std::cout << "  -- current inferred selection: " << infer_current_selection_name() << std::endl;
      //std::cout << "  -- filename for saving: " << FILE_NAVIGATOR_SELECTION_FILENAME << std::endl;
      //std::vector<std::string> lines = { infer_current_selection_name() };
      //if (!::save_file(lines, FILE_NAVIGATOR_SELECTION_FILENAME)) throw std::runtime_error("FileNavigator::save_file(): an error occurred");
      //else std::cout << "  -- Save file appears to have saved as expected" << std::endl;
      return true;
   }

   // void renderers

   //placement3d place;

   void render(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, int cell_width, int cell_height) override
   //void render(placement2d place, ALLEGRO_FONT *font) override
   {
      //placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0.0);
      //place.size = vec3d(al_get_display_width(display)/3, al_get_display_height(display)/3*2, 0.0);
      //place.scale = vec3d(0.6, 0.6, 1.0);

      //if (!visible_and_active) return;


      placement3d &place = get_place();
      get_place().start_transform();

      float roundness = 6.0;
      float padding_x = cell_width*2;
      float padding_y = cell_width;
      std::cout << " size: " << place.size.x << ", " << place.size.y << std::endl;
      al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, roundness, roundness, al_color_name("black"));
      al_draw_rounded_rectangle(0, 0, place.size.x, place.size.y, roundness, roundness, al_color_name("green"), 3.0);

      int line_height = al_get_font_line_height(font);
      int line_count = 0;
      ALLEGRO_COLOR text_color;

      // draw the current node name
      //std::string current_node_label = current_node->infer_is_directory()
      al_draw_text(font, al_color_name("aliceblue"), 0, line_height * -1, ALLEGRO_ALIGN_LEFT, current_node->infer_full_name().c_str());

      // draw the children of the current node
      for (auto &file_system_entry : current_node->get_children_ref())
      {
         bool is_directory = file_system_entry->infer_is_directory();

         std::string current_node_label = is_directory ? file_system_entry->infer_basename() : file_system_entry->infer_basename();

         float y = line_height * line_count;

         if (line_count == cursor_y)
         {
            //text_color = al_color_name("black");
            al_draw_filled_rectangle(0, padding_y+y, place.size.x, padding_y+y+line_height, al_color_name("green"));
            al_draw_filled_rectangle(0, padding_y+y, cell_width, padding_y+y+line_height, al_color_name("lime"));
            //al_draw_filled_rectangle(0, padding_y+y, cell_width, padding_y+y+line_height, al_color_name("lime"));
         }
         //else
         //{
            text_color = is_directory ? al_color_name("aquamarine") : al_color_name("lime");
         //}
         al_draw_text(font, text_color, padding_x+0, padding_y+line_height * line_count, ALLEGRO_ALIGN_LEFT, current_node_label.c_str());
         line_count++;
      }

      place.restore_transform();
   }
};



FileNavigatorEventController::FileNavigatorEventController(FileNavigator *file_navigator)
   : file_navigator(file_navigator)
{}



FileNavigatorEventController::~FileNavigatorEventController() {}



void FileNavigatorEventController::process_local_event(std::string event_name, ActionData action_data1)
{
   std::cout << "FileNavigator::" << event_name << std::endl;

   try
   {
      bool executed = false;

      if (event_name == MOVE_CURSOR_UP) { file_navigator->move_cursor_up(); executed = true; }
      if (event_name == MOVE_CURSOR_DOWN) { file_navigator->move_cursor_down(); executed = true; }

      if (!executed) std::cout << "???? cannot execute \"" << event_name << "\".  It does not exist." << std::endl;
   }
   catch (const std::exception &exception)
   {
      std::cout << "💥 cannot execute \"" << event_name << "\"" << std::endl;
   }
}



void FileNavigatorEventController::process_event(ALLEGRO_EVENT &event)
{
   KeyboardCommandMapper keyboard_command_mapper;
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_J, false, false, false, { MOVE_CURSOR_DOWN });
   keyboard_command_mapper.set_mapping(ALLEGRO_KEY_K, false, false, false, { MOVE_CURSOR_UP });

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
}



const std::string FileNavigatorEventController::MOVE_CURSOR_UP = "MOVE_CURSOR_UP";
const std::string FileNavigatorEventController::MOVE_CURSOR_DOWN = "MOVE_CURSOR_DOWN";



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



std::vector<std::string> get_directory_listing_recursive(std::string directory)
{
   if (!al_is_system_installed()) al_init();

   std::vector<std::string> results;
   ALLEGRO_FS_ENTRY* dir = al_create_fs_entry(directory.c_str());

   if(al_open_directory(dir))
   {
      ALLEGRO_FS_ENTRY* file;
      while((file=al_read_directory(dir)))
      {
         results.push_back(al_get_fs_entry_name(file));
         al_destroy_fs_entry(file);
      }
   }
   else
   {
      std::cout << "could not open directory \"" << directory << "\"" << std::endl;
   }

   al_destroy_fs_entry(dir);

   return results;
}




class System
{
public:
   std::vector<StageInterface *> stages;
   //FileNavigator file_navigator;
   ALLEGRO_DISPLAY *display;
   Camera camera;

   System(ALLEGRO_DISPLAY *display)
      : stages({})
      //, file_navigator(al_get_current_directory())
      , display(display)
      , camera(0, 0, 0)
   {
      //camera.zoom_pos -= 3.1;
      //camera.position.x += 20;
      //camera.position.y -= 10;
      //camera.set45_isometric();
      //ALLEGRO_FS_ENTRY *current_directory_fs_entry = al_create_fs_entry(al_get_current_directory());
      //file_navigator.set_file_system_entries(get_directory_listing_recursive(al_get_current_directory()));
   }

   // retrieval

   StageInterface *get_frontmost_stage()
   {
      if (stages.size() == 0)
      {
         std::cout << "Attempted to get front-most stage, but none was present." << std::endl;
         return nullptr;
      }
      return stages.back();
   }

   Stage *get_frontmost_stage_stage()
   {
      StageInterface::type_t type = get_frontmost_stage()->get_type();
      if (type == Stage::ONE_LINE_INPUT_BOX || type == Stage::CODE_EDITOR)
      {
         return static_cast<Stage *>(get_frontmost_stage());
      }
      return nullptr;
   }

   // inference

   bool is_current_stage_in_edit_mode()
   {
      Stage *stage = get_frontmost_stage_stage();
      if (!stage) return false;
      return stage->get_mode() == Stage::EDIT;
   }

   bool is_current_stage_a_modal()
   {
      StageInterface *frontmost_stage = get_frontmost_stage();
      return frontmost_stage && frontmost_stage->infer_is_modal();
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
      Stage *stage = get_frontmost_stage_stage();
      if (!stage) throw std::runtime_error("cannot run tests on current stage -- not a stage stage");

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
      //Stage *stage = get_frontmost_stage_stage();
      //if (!stage) throw std::runtime_error("Cannot save_current_stage; current stage is not a stage stage");
      get_frontmost_stage()->save_file();
      return true;
   }

   bool refresh_regex_hilights_on_stage()
   {
      Stage *stage = get_frontmost_stage_stage();
      if (!stage) throw std::runtime_error("Cannot refresh_regex_hilights_on_stage; current stage is not a stage stage");
      stage->refresh_regex_message_points();
      return true;
   }

   bool set_regex_input_box_modal_to_insert_mode()
   {
      get_frontmost_stage()->process_local_event(StageEventController::SET_INSERT_MODE);
      return true;
   }

   bool spawn_regex_input_box_modal()
   {
      //placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/3, 0.0);
      placement3d place(0.0, 0.0, 0.0);
      place.size = vec3d(300, 25, 0.0);
      place.scale = vec3d(1.3, 1.3, 1.0);
      place.rotation = vec3d(0.0, 0.0, 0.0);

      Stage *stage = new Stage(REGEX_TEMP_FILENAME, Stage::EDIT, Stage::ONE_LINE_INPUT_BOX);
      stage->set_place(place);
      stages.push_back(stage);

      std::vector<std::string> file_contents;

      stage->set_content(std::vector<std::string>{"", ""});

      return true;
   }

   bool spawn_file_navigator()
   {
      //placement3d place(0.0, 0.0, 0.0);
      //place.size = vec3d(al_get_display_width(display)/3, al_get_display_height(display)/3*2, 0.0);
      //place.scale = vec3d(0.6, 0.6, 1.0);

      placement3d place(0, 0, 0);
      place.size = vec3d(al_get_display_width(display), al_get_display_height(display), 0.0);
      place.align = vec3d(0.5, 0.5, 0.0);
      place.scale = vec3d(0.9, 0.9, 0.0);

      //placement3d place(0.0, 0.0, 0.0);
      //place.size = vec3d(300, 35, 0.0);
      //place.scale = vec3d(1.2, 1.2, 1.0);
      //place.rotation = vec3d(0.0, 0.0, 0.0);

      FileNavigator *file_navigator = new FileNavigator(al_get_current_directory());
       file_navigator->set_place(place);
      //file_navigator.set_child_nodes();
      stages.push_back(file_navigator);
      //file_navigator.show();
      return true;
   }

   bool destroy_topmost_stage()
   {
      if (stages.size() == 1) std::cout << "WARNING: destroying topmost stage. There is only 1 stage in the system and there will be none after this action." << std::endl;
      //if (stages.size() == 1) throw std::runtime_error("Cannot destroy current modal. There is only 1 stage in the system");
      delete stages.back();
      stages.pop_back();
      return true;
   }

   bool jump_to_next_code_point_on_stage()
   {
      get_frontmost_stage()->process_local_event(StageEventController::JUMP_TO_NEXT_CODE_POINT);
      return true;
   }

   bool run_make()
   {
      CppCompiler::CompileRunner compile_runner("foobar");
      std::string compile_output = compile_runner.run();
      //CppCompiler::CompileOutputToCodeMessagePointSetter(compile_output, this);
      return true;
   }

   bool offset_first_line_to_vertically_center_cursor_on_stage()
   {
      get_frontmost_stage()->process_local_event(StageEventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR);
      return true;
   }

   bool attempt_to_open_file_navigation_selected_path()
   {
      std::vector<std::string> results = { FILE_NAVIGATOR_SELECTION_last_content };
      //if (!::read_file(results, FILE_NAVIGATOR_SELECTION_FILENAME)) { throw std::runtime_error("Could not attempt_to_open_file_navigation_selected_path: read_file failed"); return false; }

      if (results.empty()) throw std::runtime_error("Could not attempt_to_open_file_navigation_selected_path: expected filename was empty.");
      std::string filename = results[0];

      //placement3d place(100, 20, 0.0);
      //place.size = vec3d(400, 400, 0.0);
      //place.align = vec3d(0, 0, 0);
      //place.scale = vec3d(0.65, 0.65, 1.0);
      placement3d place(0, 0, 0);
      place.size = vec3d(al_get_display_width(display), al_get_display_height(display), 0.0);
      place.align = vec3d(0.5, 0.5, 0.0);
      place.scale = vec3d(0.9, 0.9, 0.0);
      //place.scale = vec3d(0.0, 0.0, 0.0);


      ALLEGRO_FS_ENTRY *fs_entry = al_create_fs_entry(filename.c_str());

      if (!fs_entry)
      {
         std::stringstream error_message;
         error_message << "Could not attempt_to_open_file_navigation_selected_path: fs_entry could not be created. al_get_errno() returned with " << al_get_errno() << std::endl;
         throw std::runtime_error(error_message.str().c_str());
      }
      //std::cout << "XXXX" << filename << "XXXXX" << std::endl;

      FileSystemNode file_system_node(fs_entry);

      if (file_system_node.infer_is_directory())
      {
         FileNavigator *file_navigator = new FileNavigator(file_system_node.infer_full_name());
         file_navigator->set_place(place);
         //file_navigator.set_child_nodes();
         stages.push_back(file_navigator);
      }
      else // if it's a file
      {
         std::vector<std::string> file_contents = {};
         if (!::read_file(file_contents, filename)) throw std::runtime_error("Could not open the selected file");

         Stage *stage = new Stage(filename);// place);

         stage->set_place(place);
         stage->set_content(file_contents);
         stages.push_back(stage);
      }

      //al_destroy_fs_entry(fs_entry);
      return true;
   }

   bool submit_current_modal()
   {
      switch (get_frontmost_stage()->get_type())
      {
      case StageInterface::ONE_LINE_INPUT_BOX:
         process_local_event(SAVE_CURRENT_STAGE);
         process_local_event(DESTROY_TOPMOST_STAGE);
         process_local_event(REFRESH_REGEX_HILIGHTS_ON_STAGE);
         process_local_event(JUMP_TO_NEXT_CODE_POINT_ON_STAGE);
         process_local_event(OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE);
         break;
      case StageInterface::FILE_NAVIGATOR:
         process_local_event(SAVE_CURRENT_STAGE);  // saves the modal (commits its contents to database)
         process_local_event(DESTROY_TOPMOST_STAGE);  // destroys the modal
         //process_local_event(SAVE_CURRENT_STAGE);  // saves the stage (hopefully its a code editor) (commits its contents to database)
         process_local_event(ATTEMPT_TO_OPEN_FILE_NAVIGATION_SELECTED_PATH);
         //process_local_event(REFRESH_REGEX_HILIGHTS_ON_STAGE);
         //process_local_event(JUMP_TO_NEXT_CODE_POINT_ON_STAGE);
         //process_local_event(OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE);
         break;
      default:
         throw std::runtime_error("submit_current_modal(): invalid modal type");
         break;
      }
      return true;
   }

   bool escape_current_modal()
   {
      process_local_event(DESTROY_TOPMOST_STAGE);
      return true;
   }

   bool spawn_keyboard_inputs_modal()
   {
      KeyboardInputsModal *keyboard_input_modal = new KeyboardInputsModal(nullptr);
      stages.push_back(keyboard_input_modal);
   }

   // events

   static const std::string ROTATE_STAGE_RIGHT;
   static const std::string ROTATE_STAGE_LEFT;
   static const std::string RUN_PROJECT_TESTS;
   static const std::string RUN_MAKE;
   static const std::string SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL;
   static const std::string DESTROY_TOPMOST_STAGE;
   static const std::string ESCAPE_CURRENT_MODAL;
   static const std::string SAVE_CURRENT_STAGE;
   static const std::string REFRESH_REGEX_HILIGHTS_ON_STAGE;
   static const std::string SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE;
   static const std::string JUMP_TO_NEXT_CODE_POINT_ON_STAGE;
   static const std::string OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE;
   static const std::string SUBMIT_CURRENT_MODAL;
   static const std::string SHOW_FILE_NAVIGATOR;
   static const std::string HIDE_FILE_NAVIGATOR;
   static const std::string SPAWN_FILE_NAVIGATOR;
   static const std::string DESTROY_FILE_NAVIGATOR;
   static const std::string ATTEMPT_TO_OPEN_FILE_NAVIGATION_SELECTED_PATH;
   static const std::string SPAWN_KEYBOARD_INPUTS_MODAL;

   void process_local_event(std::string event_name)
   {
      std::cout << "System::" << event_name << std::endl;

      try
      {
         bool executed = false;

         if (event_name == ROTATE_STAGE_RIGHT) { executed = true; rotate_stage_right(); }
         else if (event_name == ROTATE_STAGE_LEFT) { executed = true; rotate_stage_left(); }
         else if (event_name == RUN_PROJECT_TESTS) { executed = true; run_project_tests(); }
         else if (event_name == SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL) { executed = true; spawn_regex_input_box_modal(); }
         else if (event_name == DESTROY_TOPMOST_STAGE) { destroy_topmost_stage(); executed = true; }
         else if (event_name == ESCAPE_CURRENT_MODAL) { executed = true; escape_current_modal(); }
         else if (event_name == SAVE_CURRENT_STAGE) { executed = true; save_current_stage(); }
         else if (event_name == REFRESH_REGEX_HILIGHTS_ON_STAGE) { executed = true; refresh_regex_hilights_on_stage(); }
         else if (event_name == SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE) { executed = true; set_regex_input_box_modal_to_insert_mode(); }
         else if (event_name == JUMP_TO_NEXT_CODE_POINT_ON_STAGE) { executed = true; jump_to_next_code_point_on_stage(); }
         else if (event_name == SUBMIT_CURRENT_MODAL) { executed = true; submit_current_modal(); }
         //else if (event_name == ESCAPE_CURRENT_MODAL) { executed = true; escape_current_modal(); }
         else if (event_name == OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE) { executed = true; offset_first_line_to_vertically_center_cursor_on_stage(); }
         else if (event_name == RUN_MAKE) { executed = true; run_make(); }
         else if (event_name == SPAWN_FILE_NAVIGATOR) { spawn_file_navigator(); executed = true; }
         else if (event_name == ATTEMPT_TO_OPEN_FILE_NAVIGATION_SELECTED_PATH) { attempt_to_open_file_navigation_selected_path(); executed = true; }
         else if (event_name == SPAWN_KEYBOARD_INPUTS_MODAL) { spawn_keyboard_inputs_modal(); executed = true; }

         if (!executed) std::cout << "???? cannot execute \"" << event_name << "\".  It does not exist." << std::endl;
      }
      catch (const std::exception &exception)
      {
         std::cout << ">BOOM< cannot execute \"" << event_name << "\".  The following exception occurred: " << exception.what() << std::endl;
      }
   }

   void process_event(ALLEGRO_EVENT &event)
   {
      KeyboardCommandMapper keyboard_command_mapper;
      //if (file_navigator.get_visible_and_active())
      //{
         //file_navigator.process_event(event);
         //return;
      //}

      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, false, false, true, { ROTATE_STAGE_RIGHT });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_CLOSEBRACE, false, false, true, { ROTATE_STAGE_LEFT });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_T, false, false, true, { SAVE_CURRENT_STAGE, RUN_PROJECT_TESTS });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_M, false, false, true, { SAVE_CURRENT_STAGE, RUN_MAKE });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, true, false, false, { DESTROY_TOPMOST_STAGE });
      if (is_current_stage_a_modal())
      {
         keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, { ESCAPE_CURRENT_MODAL });
         keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER, false, false, false, { SUBMIT_CURRENT_MODAL });
      }
      else
      {
         keyboard_command_mapper.set_mapping(ALLEGRO_KEY_TAB, false, false, false, { SPAWN_FILE_NAVIGATOR });

         if (is_current_stage_in_edit_mode())
         {
            keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, false, false, { SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL, SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE });
            keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, true,  false, false, { SPAWN_KEYBOARD_INPUTS_MODAL });
         }
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

      if (!event_caught)
      {
         //if (file_navigator.get_visible_and_active()) file_navigator.process_event(event);
         get_frontmost_stage()->process_event(event);
      }
   }

private:
};


const std::string System::ROTATE_STAGE_RIGHT = "ROTATE_STAGE_RIGHT";
const std::string System::ROTATE_STAGE_LEFT = "ROTATE_STAGE_LEFT";
const std::string System::RUN_PROJECT_TESTS = "RUN_PROJECT_TESTS";
const std::string System::RUN_MAKE = "RUN_MAKE";
const std::string System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL = "SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL";
const std::string System::SAVE_CURRENT_STAGE = "SAVE_CURRENT_STAGE";
const std::string System::DESTROY_TOPMOST_STAGE = "DESTROY_TOPMOST_STAGE";
const std::string System::ESCAPE_CURRENT_MODAL = "ESCAPE_CURRENT_MODAL";
const std::string System::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE = "OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE";
const std::string System::REFRESH_REGEX_HILIGHTS_ON_STAGE = "REFRESH_REGEX_HILIGHTS_ON_STAGE";
const std::string System::SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE = "SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE";
const std::string System::JUMP_TO_NEXT_CODE_POINT_ON_STAGE = "JUMP_TO_NEXT_CODE_POINT_ON_STAGE";
const std::string System::SUBMIT_CURRENT_MODAL = "SUBMIT_CURRENT_MODAL";
const std::string System::SPAWN_FILE_NAVIGATOR = "SPAWN_FILE_NAVIGATOR";
const std::string System::DESTROY_FILE_NAVIGATOR = "DESTROY_FILE_NAVIGATOR";
const std::string System::ATTEMPT_TO_OPEN_FILE_NAVIGATION_SELECTED_PATH = "ATTEMPT_TO_OPEN_FILE_NAVIGATION_SELECTED_PATH";
const std::string System::SPAWN_KEYBOARD_INPUTS_MODAL = "SPAWN_KEYBOARD_INPUTS_MODAL";




void run_program(std::vector<std::string> filenames)
{
   if (!al_init()) std::cerr << "al_init() failed" << std::endl;
   if (!al_init_font_addon()) std::cerr << "al_init_font_addon() failed" << std::endl;
   if (!al_init_ttf_addon()) std::cerr << "al_init_ttf_addon() failed" << std::endl;

   if (!al_install_keyboard()) std::cerr << "al_install_keyboard() failed" << std::endl;

   al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 32, ALLEGRO_SUGGEST);
   al_set_new_display_flags(ALLEGRO_RESIZABLE);

   al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
   ALLEGRO_DISPLAY *display = al_create_display(2880-200-250, 1800-200-250);
   ALLEGRO_FONT *consolas_font = al_load_font(resource({"data", "fonts"}, "consolas.ttf").c_str(), 22, 0);
   REGEX_TEMP_FILENAME = resource({"data", "tmp"}, "regex.txt");
   CLIPBOARD_TEMP_FILENAME = resource({"data", "tmp"}, "clipboard.txt");
   FILE_NAVIGATOR_SELECTION_FILENAME = resource({"data", "tmp"}, "file_navigator_selection.txt");

   int display_width = al_get_display_width(display);
   int display_height = al_get_display_height(display);

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_display_event_source(display));

   ALLEGRO_TIMER *primary_timer = al_create_timer(1.0/60.0);
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_start_timer(primary_timer);

   float logo_radius = 60;
   Logo logo(display_width/2, display_height/2 - logo_radius * 1.4, logo_radius, al_color_name("darkviolet"), 3);
   logo.render();
   al_draw_text(consolas_font, al_color_name("darkviolet"), display_width/2, display_height/2, ALLEGRO_ALIGN_CENTER, "hexagon");


   al_flip_display();


   std::string first_filename = filenames.empty() ? "" : filenames[0];


   //placement2d place(100, 20, 400, 400);
   placement3d place(0, 0, 0);
   place.size = vec3d(al_get_display_width(display), al_get_display_height(display), 0.0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.scale = vec3d(0.9, 0.9, 0.0);


   //placement2d file_navigator_placement(al_get_display_width(display)/2, al_get_display_height(display)/3*2, al_get_display_width(display), al_get_display_height(display));
   //file_navigator_placement.align = vec2d(0.5, 0.5);
   //file_navigator_placement.scale = vec2d(1, 1);

   bool shutdown_program = false;
   bool first_load = true;

   placement3d rudimentary_camera_place(0, 0, 0);
   rudimentary_camera_place.size = vec3d(al_get_display_width(display), al_get_display_height(display), 0.0);

   System system(display);

   for (auto &filename : filenames)
   {
      Stage *stage = new Stage(filename);
      stage->set_place(place);

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

      bool refresh = true;

      switch(this_event.type)
      {
      case ALLEGRO_EVENT_DISPLAY_CLOSE:
         shutdown_program = true;
         break;
      case ALLEGRO_EVENT_DISPLAY_RESIZE:
         al_acknowledge_resize(display);
         //note that each rezie will cause the display to reload, and will be a bit laggy
         //refresh = false;
         break;
      case ALLEGRO_EVENT_TIMER:
         continue;
         break;
      }

      if (refresh)
      {
         al_clear_to_color(al_color_name("black"));

         //rudimentary_camera_place.start_reverse_transform();

         system.camera.setup_camera_perspective(al_get_backbuffer(display));
         //system.camera.zoom_pos -= 0.2;
         al_clear_depth_buffer(1000);
         //al_draw_filled_rectangle(0, 0, 2000, 2000, al_color_name("orange"));
         //al_draw_filled_circle(0, 0, 20, al_color_name("deeppink"));

         //file_navigator_placement.size = vec2d(al_get_display_width(display)/3, al_get_display_height(display)/3*2);
         //file_navigator_placement.position = vec2d(al_get_display_width(display)/2, al_get_display_height(display)/2);

         for (auto &stage : system.stages)
         {
            stage->render(display, consolas_font, al_get_text_width(consolas_font, " "), al_get_font_line_height(consolas_font));
         }
         //system.file_navigator.render(file_navigator_placement, consolas_font);
         //rudimentary_camera_place.restore_transform();
         al_flip_display();
         //rudimentary_camera_place.restore_transform();
      }
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


