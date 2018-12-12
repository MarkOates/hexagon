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
#include <Hexagon/Stage.hpp>



class FileSystemNode;

bool file_system_order_compare(FileSystemNode const *a, FileSystemNode const *b);



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

   bool infer_is_directory() const
   {
      return (al_get_fs_entry_mode(entry) & ALLEGRO_FILEMODE_ISDIR) == ALLEGRO_FILEMODE_ISDIR;
   }

   std::string infer_full_name() const
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

      if(al_open_directory(node->get_entry()))
      {
         ALLEGRO_FS_ENTRY* fs_entry;
         while((fs_entry = al_read_directory(node->get_entry())))
         {
            results.push_back(new FileSystemNode(fs_entry));
            std::sort(results.begin(), results.end(), file_system_order_compare);
         }
      }
      else
      {
      }

      //std::sort(results.begin(), results.end());

      return results;
   }
};




bool file_system_order_compare(FileSystemNode const *a, FileSystemNode const *b)
{
   if (a->infer_is_directory() != b->infer_is_directory())
   {
      if (a->infer_is_directory()) return true;
      return false;
   }
   else
   {
     return strcmp(a->infer_full_name().c_str(), b->infer_full_name().c_str()) < 0;
   }
}




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
      place.scale = vec3d(1.4, 1.4, 1.0);
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
      placement3d place(0, 0, 0);
      place.size = vec3d(al_get_display_width(display)/2, al_get_display_height(display)/3*2, 0.0);
      place.align = vec3d(0.5, 0.5, 0.0);
      place.scale = vec3d(0.9, 0.9, 0.0);

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
         placement3d place(0, 0, 0);
         place.size = vec3d(al_get_display_width(display)/2, al_get_display_height(display)/3*2, 0.0);
         place.align = vec3d(0.5, 0.5, 0.0);
         place.scale = vec3d(0.9, 0.9, 0.0);

         FileNavigator *file_navigator = new FileNavigator(file_system_node.infer_full_name());
         file_navigator->set_place(place);
         //file_navigator.set_child_nodes();
         stages.push_back(file_navigator);
      }
      else // if it's a file
      {
         std::vector<std::string> file_contents = {};
         if (!::read_file(file_contents, filename)) throw std::runtime_error("Could not open the selected file");

         placement3d place(0, 0, 0);
         place.size = vec3d(al_get_display_width(display), al_get_display_height(display), 0.0);
         place.align = vec3d(0.5, 0.5, 0.0);
         place.scale = vec3d(0.9, 0.9, 0.0);

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


