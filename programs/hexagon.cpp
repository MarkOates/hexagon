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
#include <Blast/CommandLineFlaggedArgumentsParser.hpp>
#include <lib/camera.h>
#include <Hexagon/System/Action/DestroyAllCodeEditorStages.hpp>
#include <Hexagon/Logo.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Hexagon/shared_globals.hpp>
#include <Hexagon/util.hpp>
#include <Hexagon/ClipboardData.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/Action.hpp>
#include <Hexagon/ActionQueueRecording.hpp>
#include <Hexagon/CodePoint.hpp>
#include <Hexagon/CodeRange.hpp>
#include <Hexagon/RailsMinitestTestResult.hpp>
#include <Hexagon/RailsTestOutputParser.hpp>
#include <Hexagon/RailsMinitestTestRunner.hpp>
#include <Hexagon/CppCompiler.hpp>
#include <Hexagon/FullScreenOverlay/Stage.hpp>
#include <Hexagon/CodeRangeExtractor.hpp>
#include <Hexagon/CodeMessagePoint.hpp>
#include <Hexagon/CodeMessagePointsOverlay.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/KeyboardInputsModal/Stage.hpp>
#include <Hexagon/EventControllerInterface.hpp>
#include <Hexagon/CodeEditor/EventController.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/Hud.hpp>
#include <Hexagon/FileSystemNode.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/ComponentNavigator/Stage.hpp>
#include <Hexagon/RerunOutputWatcher/Stage.hpp>
#include <Hexagon/LayoutPlacements.hpp>
#include <NcursesArt/ProjectComponentBasenameExtractor.hpp>
#include <NcursesArt/ProjectFilenameGenerator.hpp>


//#define OUTPUT_CALLING_FRONTMOST_STAGE_MESSAGE (std::cout << "calling get_fontmost_stage() on function " << __FUNCTION__ << std::endl)
#define OUTPUT_CALLING_FRONTMOST_STAGE_MESSAGE (true)




void simple_debugger(std::string message="")
{
   al_init();
   al_create_display(800, 800);
   al_clear_to_color(al_color_name("violet"));
   ALLEGRO_FONT *font = al_create_builtin_font();
   al_draw_text(font, al_color_name("white"), 10, 10, 0, message.c_str());
   al_flip_display();
   usleep(0.2 * 1000000);
}



#define NOTIFICATION_FILE_IS_UNSAVED "file is unsaved"

std::vector<std::string> notifications = {};

void add_notification(std::string notification)
{
   notifications.push_back(notification);
}

void remove_notification(std::string notification)
{
   notifications.push_back(notification);
}

void clear_notifications()
{
   notifications.clear();
}



int get_display_default_width()
{
   return 2430;
}


int get_display_default_height()
{
   return 1350;
}


placement3d get_stage_default_place()
{
   placement3d place(0, 0, 0);
   place.size = vec3d(get_display_default_width(), get_display_default_height(), 0.0);
   place.align = vec3d(0.5, 0.5, 0.0);
   place.scale = vec3d(0.9, 0.9, 0.0);
   return place;
}


void wait_for_keypress()
{
  ALLEGRO_EVENT_QUEUE *event_queue;
  ALLEGRO_EVENT event;
  
  al_install_keyboard();
  event_queue = al_create_event_queue();
  al_register_event_source(event_queue, al_get_keyboard_event_source());

  do
    al_wait_for_event(event_queue, &event);
  while (event.type != ALLEGRO_EVENT_KEY_DOWN);
  
  al_destroy_event_queue(event_queue);
}


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


class ThreeSplitLayout
{
private:
   CodeEditor::Stage *left_stage;
   CodeEditor::Stage *center_stage;
   CodeEditor::Stage *right_stage;

   Hexagon::LayoutPlacements layout;

public:

   static const std::string LEFT_STAGE_KEY;
   static const std::string CENTER_STAGE_KEY;
   static const std::string RIGHT_STAGE_KEY;

   ThreeSplitLayout(CodeEditor::Stage *left_stage, CodeEditor::Stage *center_stage, CodeEditor::Stage *right_stage)
      : left_stage(left_stage)
      , center_stage(center_stage)
      , right_stage(right_stage)
      , layout()
   {
      float stage_position_grid_len = get_display_default_width() / 6.0f;
      float stage_width = get_display_default_width() / 3.0f;
      //float stage_height = get_display_default_height();
      float leftmost_anchor = -stage_position_grid_len * 2;
      float topmost_anchor = get_display_default_width() / 2;

      layout.set_placements({
         { LEFT_STAGE_KEY, placement3d(leftmost_anchor + stage_width * 0, 0, 0) },
         { CENTER_STAGE_KEY, placement3d(leftmost_anchor + stage_width * 1, 0, 0) },
         { RIGHT_STAGE_KEY, placement3d(leftmost_anchor + stage_width * 2, 0, 0) },
      });
      for (auto &placement : layout.get_placements_ref())
      {
         placement.second.align = vec3d(0.5, 0.5, 0.0);
         placement.second.size = vec3d(700, topmost_anchor, 0.0);
         placement.second.scale = vec3d(0.8, 0.8, 0.8);
      }
   }

   void place_stages()
   {
      validate_stages();

      left_stage->set_place(layout.placement_for(LEFT_STAGE_KEY));
      center_stage->set_place(layout.placement_for(CENTER_STAGE_KEY));
      right_stage->set_place(layout.placement_for(RIGHT_STAGE_KEY));
   }

   void validate_stages()
   {
      if (!left_stage) throw std::runtime_error("left_stage is a nullptr");
      if (!center_stage) throw std::runtime_error("center_stage is a nullptr");
      if (!right_stage) throw std::runtime_error("right_stage is a nullptr");
   }
};


const std::string ThreeSplitLayout::LEFT_STAGE_KEY = "LEFT_STAGE_KEY";
const std::string ThreeSplitLayout::CENTER_STAGE_KEY = "CENTER_STAGE_KEY";
const std::string ThreeSplitLayout::RIGHT_STAGE_KEY = "RIGHT_STAGE_KEY";


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


std::string remove_absolute_path_components_from_project_filename(
   std::string project_file_absolute_filename)
{
   std::string mainStr = project_file_absolute_filename;
   std::string toErase;
   size_t pos = 0;


   // Search for the substring in string
   toErase = "/Users/markoates/Repos/";
   pos = mainStr.find(toErase);

   if (pos != std::string::npos)
   {
      // If found then erase it from string
      mainStr.erase(pos, toErase.length());
   }


   // this is also hacky, and will presume that the given path that was passed is
   // _already_ relative to the project directory if true
   if (mainStr == project_file_absolute_filename)
   {
      return project_file_absolute_filename;
   }


   // now erase the project's path component
   toErase = "/";
   pos = mainStr.find(toErase);

   if (pos != std::string::npos)
   {
      // If found then erase it from string
      mainStr.erase(mainStr.begin(), mainStr.begin()+pos+toErase.length());
   }

   std::cout << "MODIFIFIEIED STRINGGGGG: \"" << mainStr << "\"" << std::endl;

   
   return mainStr;
}


class System
{
public:
   std::vector<StageInterface *> stages;
   ALLEGRO_DISPLAY *display;
   Camera camera;
   placement3d file_navigator_initial_place;
   placement3d component_navigator_initial_place;
   Motion &motion;
   std::string last_file_navigator_selection;
   std::string last_component_navigator_selection;
   std::string default_navigator_directory;

   //RerunOutputWatcher *rerun_output_watcher;

   System(ALLEGRO_DISPLAY *display, Motion &motion)
      : stages({})
      //, file_navigator(al_get_current_directory())
      , display(display)
      , camera(0, 0, 0)
      , file_navigator_initial_place(0, 0, 0)
      , component_navigator_initial_place(0, 0, 0)
      , motion(motion)
      , last_file_navigator_selection("")
      , last_component_navigator_selection("")
      , default_navigator_directory("/Users/markoates/Repos/hexagon")
   {
      file_navigator_initial_place.size = vec3d(500, 600, 0);
      file_navigator_initial_place.align = vec3d(0.5, 0.5, 0.5);
      file_navigator_initial_place.scale = vec3d(0.8, 0.8, 1.0);
      file_navigator_initial_place.rotation = vec3d(0.0, 0.02, 0.0);

      component_navigator_initial_place.size = vec3d(800, 700, 0);
      component_navigator_initial_place.align = vec3d(0.5, 0.5, 0.5);
      component_navigator_initial_place.scale = vec3d(0.8, 0.8, 1.0);
      component_navigator_initial_place.rotation = vec3d(0.0, 0.02, 0.0);

      //camera.zoom_pos -= 3.1;
      //camera.position.x += 20;
      //camera.position.y -= 10;
      //camera.set45_isometric();
      //ALLEGRO_FS_ENTRY *current_directory_fs_entry = al_create_fs_entry(al_get_current_directory());
      //file_navigator.set_file_system_entries(get_directory_listing_recursive(al_get_current_directory()));
      //process_local_event(SPAWN_RERUN_OUTPUT_WATCHER);
      process_local_event(SPAWN_FILE_NAVIGATOR);
      //process_local_event(REFRESH_RERUN_OUTPUT_WATCHERS);
   }

   // util
   static std::vector<std::string> get_directory_listing_recursive(std::string directory)
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


   // retrieval

   StageInterface *get_frontmost_stage()
   {
      if (stages.size() == 0) return nullptr;
      return stages.back();
   }

   CodeEditor::Stage *get_frontmost_code_editor_stage() // TODO: rename this function to get_frontmost_code_editor_stage()
   {
      StageInterface *frontmost_stage = get_frontmost_stage();
      if (!frontmost_stage) return nullptr;

      StageInterface::type_t type = frontmost_stage->get_type();
      if (type == CodeEditor::Stage::ONE_LINE_INPUT_BOX || type == CodeEditor::Stage::CODE_EDITOR)
      {
         return static_cast<CodeEditor::Stage *>(get_frontmost_stage());
      }
      return nullptr;
   }

   int get_number_of_code_editor_stages()
   {
      int result = 0;
      for (auto &stage : stages)
      {
         if (stage->get_type() == CodeEditor::Stage::CODE_EDITOR) result++;
      }
      return result;
   }

   // inference

   bool is_current_stage_in_edit_mode()
   {
      CodeEditor::Stage *frontmost_stage = get_frontmost_code_editor_stage();
      if (!frontmost_stage)
      {
         std::cout << "Warning: attempting to infer if is_current_stage_in_edit_mode() but no frontmost stage exists" << std::endl;
         return false;
      }
      return frontmost_stage->get_mode() == CodeEditor::Stage::EDIT;
   }

   bool is_current_stage_a_modal()
   {
      StageInterface *frontmost_stage = get_frontmost_stage();
      if (!frontmost_stage)
      {
         std::cout << "Warning: attempting to infer if is_current_stage_a_modal() but no frontmost stage exists" << std::endl;
         return false;
      }
      return frontmost_stage && frontmost_stage->infer_is_modal();
   }

   bool is_current_stage_a_regex_input_box()
   {
      StageInterface *frontmost_stage = get_frontmost_stage();
      if (!frontmost_stage)
      {
         std::cout << "Warning: attempting to infer if is_current_stage_a_regex_input_box() but no frontmost stage exists" << std::endl;
         return false;
      }
      return frontmost_stage && (frontmost_stage->get_type() == StageInterface::ONE_LINE_INPUT_BOX);
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
      CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
      if (!stage) throw std::runtime_error("cannot run tests on current stage -- not a stage stage");

      std::string test_output = RailsMinitestTestRunner(stage->get_filename()).run();
      Hexagon::RailsTestOutputParser rails_test_output_parser(test_output);
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

   bool attempt_to_flip_to_correlated_component_test_file()
   {
      CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
      // get current stage's filename
      std::string stage_filename = stage->get_filename();
      std::cout << "SAAAHHTAGE FILENAMEEE:::::: " << stage_filename << std::endl;

      stage_filename = remove_absolute_path_components_from_project_filename(stage_filename);
      
      std::cout << "SANITIZED FILEHHHNAMEEE:::::: " << stage_filename << std::endl;
      // use the ProjectComponentBasenameExtractor to extract a possible component name
      NcursesArt::ProjectComponentBasenameExtractor extractor(stage_filename);
      // check if it's a valid component
      if (!extractor.is_identifiable_component())
      {
         std::stringstream error_message;
         error_message << "[attempt_to_flip_to_correlated_component_test_file() error]: "
                       << "could not identify the frontmost stage as an identifiable component"
                       << std::endl;
         throw std::runtime_error(error_message.str());
      }
      // obtain the basename
      std::string basename = extractor.identify_component_basename();
      std::cout << "BASEAMEJEEE:::::: " << basename << std::endl;

      // use the basename with the ProjectFilenameGenerator to generate the desired test filename
      NcursesArt::ProjectFilenameGenerator generator(basename);
      std::string test_filename = generator.generate_test_src_filename();
      // WARNING: this project prefix is a workaround.  This complex state is the result
      // of an inproperly managed file naming system.  It's unclear at this point whether the
      // program is being run as an Application (absolute filenames) or as a binary (relative
      // filenames.  As a result, the project prefix cannot be easily inferred.  For this case,
      // we're going to prefix the file with this hardcoded string and assume the file is in
      // the hexagon repo
      std::string project_prefix = "/Users/markoates/Repos/hexagon/";
      test_filename = project_prefix + test_filename;
      // make sure the file exists before destroying the first one and opening the new file
      if (!php::file_exists(test_filename))
      {
         std::stringstream error_message;
         error_message << "[attempt_to_flip_to_correlated_component_test_file() error]: "
                       << "could not proceed to opening the test filename "
                       << "\"" << test_filename << "\" "
                       << "because it does not exist."
                       << std::endl;
         throw std::runtime_error(error_message.str());
      }
      // save the current stage
      save_current_stage();
      // destroy the current stage
      destroy_topmost_stage();
      // create a new stage
      // WARNING: this selection is a bit of a hack
      last_file_navigator_selection = test_filename;
      attempt_to_create_stage_from_last_file_navigator_selection();
   }

   bool attempt_to_flip_to_correlated_component_quintessence_file()
   {
      CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
      // get current stage's filename
      std::string stage_filename = stage->get_filename();
      std::cout << "SAAAHHTAGE FILENAMEEE:::::: " << stage_filename << std::endl;

      stage_filename = remove_absolute_path_components_from_project_filename(stage_filename);
      
      std::cout << "SANITIZED FILEHHHNAMEEE:::::: " << stage_filename << std::endl;
      // use the ProjectComponentBasenameExtractor to extract a possible component name
      NcursesArt::ProjectComponentBasenameExtractor extractor(stage_filename);
      // check if it's a valid component
      if (!extractor.is_identifiable_component())
      {
         std::stringstream error_message;
         error_message << "[attempt_to_flip_to_correlated_component_quintessence_file() error]: "
                       << "could not identify the frontmost stage as an identifiable component"
                       << std::endl;
         throw std::runtime_error(error_message.str());
      }
      // obtain the basename
      std::string basename = extractor.identify_component_basename();
      std::cout << "BASEAMEJEEE:::::: " << basename << std::endl;

      // use the basename with the ProjectFilenameGenerator to generate the desired quintessence filename
      NcursesArt::ProjectFilenameGenerator generator(basename);
      std::string quintessence_filename = generator.generate_quintessence_filename();
      // WARNING: this project prefix is a workaround.  This complex state is the result
      // of an inproperly managed file naming system.  It's unclear at this point whether the
      // program is being run as an Application (absolute filenames) or as a binary (relative
      // filenames.  As a result, the project prefix cannot be easily inferred.  For this case,
      // we're going to prefix the file with this hardcoded string and assume the file is in
      // the hexagon repo
      std::string project_prefix = "/Users/markoates/Repos/hexagon/";
      quintessence_filename = project_prefix + quintessence_filename;
      // make sure the file exists before destroying the first one and opening the new file
      if (!php::file_exists(quintessence_filename))
      {
         std::stringstream error_message;
         error_message << "[attempt_to_flip_to_correlated_component_quintessence_file() error]: "
                       << "could not proceed to opening the quintessence filename "
                       << """ << quintessence_filename << "" "
                       << "because it does not exist."
                       << std::endl;
         throw std::runtime_error(error_message.str());
      }
      // save the current stage
      save_current_stage();
      // destroy the current stage
      destroy_topmost_stage();
      // create a new stage
      // WARNING: this selection is a bit of a hack
      last_file_navigator_selection = quintessence_filename;
      attempt_to_create_stage_from_last_file_navigator_selection();
   }

   bool save_current_stage()
   {
      CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
      if (!stage) throw std::runtime_error("Cannot save_current_stage; current stage is not a stage stage");

      get_frontmost_code_editor_stage()->save_file();
      process_local_event(REMOVE_FILE_IS_UNSAVED_NOTIFICATION);

      return true;
   }

   bool refresh_regex_hilights_on_stage()
   {
      CodeEditor::Stage *stage = get_frontmost_code_editor_stage();
      if (!stage) throw std::runtime_error("Cannot refresh_regex_hilights_on_stage; current stage is not a stage stage");
      stage->refresh_regex_message_points();
      return true;
   }

   bool set_regex_input_box_modal_to_insert_mode()
   {
      StageInterface *frontmost_stage = get_frontmost_stage();
      if (!frontmost_stage) return false;
      frontmost_stage->process_local_event(CodeEditor::EventController::SET_INSERT_MODE);
      return true;
   }

   bool spawn_regex_input_box_modal()
   {
      //placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/3, 0.0);
      placement3d place(0.0, 0.0, 0.0);
      place.size = vec3d(300, 25, 0.0);
      place.scale = vec3d(1.4, 1.4, 1.0);
      place.rotation = vec3d(0.0, 0.0, 0.0);

      CodeEditor::Stage *stage = new CodeEditor::Stage(REGEX_TEMP_FILENAME, CodeEditor::Stage::EDIT, CodeEditor::Stage::ONE_LINE_INPUT_BOX); // TODO: extract this one line input box from CodeEditor
      stage->set_place(place);
      stages.push_back(stage);

      placement3d& stage_place = stage->get_place();
      stage_place.scale.x = 1.7;
      stage_place.scale.y = 1.7;
      motion.canimate(&stage_place.scale.x, 1.7, 1.5, al_get_time(), al_get_time()+0.3, interpolator::fast_in, nullptr, nullptr);
      motion.canimate(&stage_place.scale.y, 1.7, 1.5, al_get_time(), al_get_time()+0.3, interpolator::fast_in, nullptr, nullptr);

      std::vector<std::string> file_contents;

      stage->set_content(std::vector<std::string>{"", ""});

      return true;
   }

   bool spawn_component_navigator()
   {
      //placement3d component_navigator_initial_place = component_navigator_initial_place;
     
      Hexagon::ComponentNavigator::Stage *component_navigator = new Hexagon::ComponentNavigator::Stage(); //(default_navigator_directory);
      component_navigator->process_local_event("refresh_list");
      component_navigator->set_place(component_navigator_initial_place);
      stages.push_back(component_navigator);

      placement3d& stage_place = component_navigator->get_place();
      motion.cmove_to(&stage_place.rotation.y, 0.0, 0.3, interpolator::tripple_fast_in); //, al_get_time()+0.3, interpolator::fast_in, nullptr, nullptr);
      motion.cmove_to(&stage_place.position.z, 30.0, 0.3, interpolator::tripple_fast_in); //al_get_time(), al_get_time()+0.3, interpolator::fast_in, nullptr, nullptr);
      return true;
   }

   bool spawn_red_overlay()
   {
      Hexagon::FullScreenOverlay::Stage *red_overlay = new Hexagon::FullScreenOverlay::Stage;
      stages.push_back(red_overlay);
   }

   bool spawn_file_navigator()
   {
      //placement3d place(0, 0, 0);
      //place.size = vec3d(100.0, 200.0, 0.0);
      //place.align = vec3d(0.5, 0.5, 0.0);
      //place.scale = vec3d(0.8, 0.8, 0.0);
      //place.rotation = vec3d(0.0, 0.03, 0.0);

      Hexagon::FileNavigator::Stage *file_navigator = new Hexagon::FileNavigator::Stage(default_navigator_directory);
      file_navigator->process_local_event("refresh_list");
      file_navigator->set_place(file_navigator_initial_place);
      //file_navigator.set_child_nodes();
      stages.push_back(file_navigator);

      placement3d& stage_place = file_navigator->get_place();
      //stage_place.scale.x = 1.2;
      //stage_place.scale.y = 1.2;
      motion.cmove_to(&stage_place.rotation.y, 0.0, 0.3, interpolator::tripple_fast_in); //, al_get_time()+0.3, interpolator::fast_in, nullptr, nullptr);
      //motion.cmove_to(&stage_place.scale.y, 1.1, 0.1); //al_get_time(), al_get_time()+0.3, interpolator::fast_in, nullptr, nullptr);
      motion.cmove_to(&stage_place.position.z, 30.0, 0.3, interpolator::tripple_fast_in); //al_get_time(), al_get_time()+0.3, interpolator::fast_in, nullptr, nullptr);
      //file_navigator.show();
      return true;
   }

   bool spawn_rerun_output_watcher()
   {
      float golden_ratio = 0.61803f;
      float x_pos = golden_ratio * get_display_default_width() - get_display_default_width()/2;
      placement3d place(x_pos, -get_display_default_height()/2 + 30, 0);
      place.size = vec3d(0, 0, 0.0);
      place.align = vec3d(0, 0, 0);
      place.scale = vec3d(0.7, 0.7, 0.0);

      Hexagon::RerunOutputWatcher::Stage *rerun_output_watcher = new Hexagon::RerunOutputWatcher::Stage();
      rerun_output_watcher->set_place(place);
      stages.push_back(rerun_output_watcher);
      return true;
   }

   void add_file_is_unsaved_notification()
   {
      add_notification(NOTIFICATION_FILE_IS_UNSAVED);
   }

   void remove_file_is_unsaved_notification()
   {
      remove_notification(NOTIFICATION_FILE_IS_UNSAVED);
   }

   void clear_rerun_output_watchers()
   {
      for (auto &stage : stages)
      {
         if (stage->get_type() == StageInterface::RERUN_OUTPUT_WATCHER)
         {
            Hexagon::RerunOutputWatcher::Stage *watcher = static_cast<Hexagon::RerunOutputWatcher::Stage *>(stage);
            watcher->clear();
         }
      }
   }

   bool refresh_rerun_output_watchers()
   {
      for (auto &stage : stages)
      {
         if (stage->get_type() == StageInterface::RERUN_OUTPUT_WATCHER)
         {
            Hexagon::RerunOutputWatcher::Stage *watcher = static_cast<Hexagon::RerunOutputWatcher::Stage *>(stage);

            std::vector<std::string> file_contents = {};
            if (!::read_file(file_contents, MAKE_COMMAND_FILENAME)) throw std::runtime_error("Could not open the make command file");

            watcher->set_command(file_contents[0]);
            watcher->refresh();
         }
      }
      return true;
   }

   bool destroy_topmost_stage()
   {
      if (stages.size() >= 1)
      {
         delete stages.back();
         stages.pop_back();
         return true;
      }
      else
      {
         throw std::runtime_error("attempted to destroy_topmost_stage(), but no stages are present");
      }
   }

   bool jump_to_next_code_point_on_stage()
   {
      StageInterface *frontmost_stage = get_frontmost_stage();
      if (!frontmost_stage) return false;
      frontmost_stage->process_local_event(CodeEditor::EventController::JUMP_TO_NEXT_CODE_POINT);
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
      StageInterface *frontmost_stage = get_frontmost_stage();
      if (!frontmost_stage) return false;
      frontmost_stage->process_local_event(CodeEditor::EventController::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR);
      return true;
   }

   //bool spawn_file_navigator_if_no_stages_exist()
   //{
      //if (stages.empty()) process_local_event(SPAWN_FILE_NAVIGATOR);
      //return true;
   //}

   bool push_component_navigator_selection()
   {
      StageInterface *frontmost_stage_interface = get_frontmost_stage();
      if (!frontmost_stage_interface || !(frontmost_stage_interface->get_type() == StageInterface::COMPONENT_NAVIGATOR))
      {
         std::stringstream error_message;
         std::string function_name = "push_component_navigator_selection";
         error_message << "Could not " << function_name << ": Either the frontmost_stage_interface is a nullptr OR is not of type StageInterface::COMPONENT_NAVIGATOR." << std::endl;
         throw std::runtime_error(error_message.str().c_str());
      }
      Hexagon::ComponentNavigator::Stage *component_navigator = static_cast<Hexagon::ComponentNavigator::Stage *>(frontmost_stage_interface);

      std::string current_component_navigator_selection = component_navigator->get_current_selection_or_spaced_empty_string();

      last_component_navigator_selection = current_component_navigator_selection;
      return true;
   }

   bool push_file_navigator_selection()
   {
      StageInterface *frontmost_stage_interface = get_frontmost_stage();
      if (!frontmost_stage_interface || !(frontmost_stage_interface->get_type() == StageInterface::FILE_NAVIGATOR))
      {
         std::stringstream error_message;
         std::string function_name = "push_file_navigator_selection";
         error_message << "Could not " << function_name << ": Either the frontmost_stage_interface is a nullptr OR is not of type StageInterface::FILE_NAVIGATOR." << std::endl;
         throw std::runtime_error(error_message.str().c_str());
      }

      Hexagon::FileNavigator::Stage *file_navigator = static_cast<Hexagon::FileNavigator::Stage *>(frontmost_stage_interface);
      std::string current_file_navigator_selection = file_navigator->get_current_selection();

      last_file_navigator_selection = current_file_navigator_selection;
      return true;
   }

   bool attempt_to_create_stage_from_last_file_navigator_selection()
   {
      //throw std::runtime_error("attempt_to_open_file_navigator_file not yet implemented");

      std::string filename = last_file_navigator_selection;

      // validate the selected path is a valid file
      ALLEGRO_FS_ENTRY *fs_entry = al_create_fs_entry(filename.c_str());
      if (!fs_entry)
      {
         std::stringstream error_message;
         error_message << "Could not attempt_to_create_stage_from_last_file_navigator_selection: fs_entry could not be created. al_get_errno() returned with " << al_get_errno() << std::endl;
         throw std::runtime_error(error_message.str().c_str());
      }
      FileSystemNode file_system_node(fs_entry);
      if (file_system_node.infer_is_directory())
      {
         std::stringstream error_message;
         error_message << "Could not attempt_to_create_stage_from_last_file_navigator_selection: is a directory." << std::endl;
         throw std::runtime_error(error_message.str().c_str());
      }
      else // is a valid file
      {
         std::vector<std::string> file_contents = {};
         if (!::read_file(file_contents, filename)) throw std::runtime_error("Could not open the selected file");

         int number_of_files = get_number_of_code_editor_stages();
         float one_third_screen_width = get_display_default_width() / 3;

         placement3d place(one_third_screen_width*number_of_files, 0, 0);
         place.size = vec3d(get_display_default_width()/2, get_display_default_height(), 0.0); //al_get_display_width(display), al_get_display_height(display), 0.0);
         place.align = vec3d(0.5, 0.5, 0.0);
         place.scale = vec3d(0.9, 0.9, 0.0);

         CodeEditor::Stage *stage = new CodeEditor::Stage(filename);// place);

         stage->set_place(place);
         stage->set_content(file_contents);
         stages.push_back(stage);

         //throw std::runtime_error("attempt_to_open_file_navigator_file not yet implemented to open a file");
      }

      // create a new stage
      //std::string
      return true;
   }

   bool destroy_all_code_editor_stages()
   {
      Hexagon::System::Action::DestroyAllCodeEditorStages action(stages);
      return action.managed_execute();
   }

   bool attempt_to_create_stage_from_last_component_navigator_selection()
   {
      std::string component_name = last_component_navigator_selection;

      NcursesArt::ProjectFilenameGenerator project_component_filename_generator(component_name);
      std::string quintessence_filename = std::string("/Users/markoates/Repos/hexagon/") + project_component_filename_generator.generate_quintessence_filename();

      std::string filename = quintessence_filename;

      std::vector<std::string> file_contents = {};
      if (!::read_file(file_contents, filename)) throw std::runtime_error("Could not open the selected file");

      //int number_of_files = get_number_of_code_editor_stages();
      //float one_third_screen_width = get_display_default_width() / 3;

      float one_third_screen_width = get_display_default_width() / 3;
      int number_of_files = 0;

      placement3d place(one_third_screen_width*number_of_files, 0, 0);
      place.size = vec3d(get_display_default_width()/2, get_display_default_height(), 0.0); //al_get_display_width(display), al_get_display_height(display), 0.0);
      place.align = vec3d(0.5, 0.5, 0.0);
      place.scale = vec3d(0.9, 0.9, 0.0);

      CodeEditor::Stage *quintessence_file_stage = new CodeEditor::Stage(filename);

      quintessence_file_stage->set_place(place);
      quintessence_file_stage->set_content(file_contents);
      stages.push_back(quintessence_file_stage);

      return true;
   }

   bool submit_current_modal()
   {
      StageInterface *frontmost_stage = get_frontmost_stage();
      if (!frontmost_stage) return false;

      switch (frontmost_stage->get_type())
      {
      case StageInterface::ONE_LINE_INPUT_BOX:
         process_local_event(SAVE_CURRENT_STAGE);
         process_local_event(DESTROY_TOPMOST_STAGE);
         process_local_event(REFRESH_REGEX_HILIGHTS_ON_STAGE);
         process_local_event(JUMP_TO_NEXT_CODE_POINT_ON_STAGE);
         process_local_event(OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE);
         break;
      case StageInterface::FILE_NAVIGATOR:
         //process_local_event(SAVE_CURRENT_STAGE);  // saves the modal (commits its contents to database)
         process_local_event(PUSH_FILE_NAVIGATOR_SELECTION);
         process_local_event(DESTROY_TOPMOST_STAGE);  // destroys the modal
         process_local_event(ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION);
         //throw std::runtime_error("there is no valid \"submit_current_modal()\" behavior for StageInterface::FILE_NAVIGATOR");
         //process_local_event(ATTEMPT_TO_OPEN_OLD_FILE_NAVIGATION_SELECTED_PATH);
         break;
      case StageInterface::COMPONENT_NAVIGATOR:
         process_local_event(PUSH_COMPONENT_NAVIGATOR_SELECTION);
         process_local_event(DESTROY_TOPMOST_STAGE);
         process_local_event(DESTROY_ALL_CODE_EDITOR_STAGES);
         process_local_event(ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION);
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
      KeyboardInputsModal::Stage *keyboard_input_modal = new KeyboardInputsModal::Stage(nullptr);
      stages.push_back(keyboard_input_modal);
      return true;
   }

   // events

   static const std::string ADD_FILE_IS_UNSAVED_NOTIFICATION;
   static const std::string ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION;
   static const std::string ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION;
   static const std::string ATTEMPT_TO_FLIP_TO_CORRELATED_COMPONENT_QUINTESSENCE_FILE;
   static const std::string ATTEMPT_TO_FLIP_TO_CORRELATED_COMPONENT_TEST_FILE;
   static const std::string CLEAR_RERUN_OUTPUT_WATCHERS;
   static const std::string DESTROY_FILE_NAVIGATOR;
   static const std::string DESTROY_TOPMOST_STAGE;
   static const std::string DESTROY_ALL_CODE_EDITOR_STAGES;
   static const std::string ESCAPE_CURRENT_MODAL;
   static const std::string HIDE_FILE_NAVIGATOR;
   static const std::string JUMP_TO_NEXT_CODE_POINT_ON_STAGE;
   static const std::string OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE;
   static const std::string PUSH_FILE_NAVIGATOR_SELECTION;
   static const std::string PUSH_COMPONENT_NAVIGATOR_SELECTION;
   static const std::string REFRESH_REGEX_HILIGHTS_ON_STAGE;
   static const std::string REFRESH_RERUN_OUTPUT_WATCHERS;
   static const std::string REMOVE_FILE_IS_UNSAVED_NOTIFICATION;
   static const std::string ROTATE_STAGE_LEFT;
   static const std::string ROTATE_STAGE_RIGHT;
   static const std::string RUN_MAKE;
   static const std::string RUN_PROJECT_TESTS;
   static const std::string SAVE_CURRENT_STAGE;
   static const std::string SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE;
   static const std::string SPAWN_COMPONENT_NAVIGATOR;
   static const std::string SPAWN_FILE_NAVIGATOR;
   //static const std::string SPAWN_FILE_NAVIGATOR_IF_NO_STAGES_EXIST;
   static const std::string SPAWN_KEYBOARD_INPUTS_MODAL;
   static const std::string SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL;
   static const std::string SPAWN_RERUN_OUTPUT_WATCHER;
   static const std::string SUBMIT_CURRENT_MODAL;

   void process_local_event(std::string event_name) // this function is 1:1 execute the action.  It does no calling of other actions before or after
   {
      std::cout << "System::" << event_name << std::endl;

      try
      {
         bool executed = false;

         if (event_name == ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION) { attempt_to_create_stage_from_last_file_navigator_selection(); executed = true; }
         else if (event_name == ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION) { attempt_to_create_stage_from_last_component_navigator_selection(); executed = true; }
         //else if (event_name == ESCAPE_CURRENT_MODAL) { executed = true; escape_current_modal(); }
         else if (event_name == ATTEMPT_TO_FLIP_TO_CORRELATED_COMPONENT_QUINTESSENCE_FILE) { attempt_to_flip_to_correlated_component_quintessence_file(); executed = true; }
         else if (event_name == ATTEMPT_TO_FLIP_TO_CORRELATED_COMPONENT_TEST_FILE) { attempt_to_flip_to_correlated_component_test_file(); executed = true; }
         else if (event_name == CLEAR_RERUN_OUTPUT_WATCHERS) { clear_rerun_output_watchers(); executed = true; }
         else if (event_name == DESTROY_TOPMOST_STAGE) { destroy_topmost_stage(); executed = true; }
         else if (event_name == DESTROY_ALL_CODE_EDITOR_STAGES) { destroy_all_code_editor_stages(); executed = true; }
         else if (event_name == ESCAPE_CURRENT_MODAL) { escape_current_modal(); executed = true; }
         else if (event_name == JUMP_TO_NEXT_CODE_POINT_ON_STAGE) { jump_to_next_code_point_on_stage(); executed = true; }
         else if (event_name == OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE) { offset_first_line_to_vertically_center_cursor_on_stage(); executed = true; }
         else if (event_name == PUSH_FILE_NAVIGATOR_SELECTION) { push_file_navigator_selection(); executed = true; }
         else if (event_name == PUSH_COMPONENT_NAVIGATOR_SELECTION) { push_component_navigator_selection(); executed = true; }
         else if (event_name == REFRESH_REGEX_HILIGHTS_ON_STAGE) { refresh_regex_hilights_on_stage(); executed = true; }
         else if (event_name == REFRESH_RERUN_OUTPUT_WATCHERS) { refresh_rerun_output_watchers(); executed = true; }
         else if (event_name == ADD_FILE_IS_UNSAVED_NOTIFICATION) { add_file_is_unsaved_notification(); executed = true; }
         else if (event_name == REMOVE_FILE_IS_UNSAVED_NOTIFICATION) { remove_file_is_unsaved_notification(); executed = true; }
         else if (event_name == ROTATE_STAGE_LEFT) { rotate_stage_left(); executed = true; }
         else if (event_name == ROTATE_STAGE_RIGHT) { rotate_stage_right(); executed = true; }
         else if (event_name == RUN_MAKE) { run_make(); executed = true; }
         else if (event_name == RUN_PROJECT_TESTS) { run_project_tests(); executed = true; }
         else if (event_name == SAVE_CURRENT_STAGE) { save_current_stage(); executed = true; }
         else if (event_name == SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE) { set_regex_input_box_modal_to_insert_mode(); executed = true; }
         else if (event_name == SPAWN_COMPONENT_NAVIGATOR) { spawn_component_navigator(); executed = true; }
         else if (event_name == SPAWN_FILE_NAVIGATOR) { spawn_file_navigator(); executed = true; }
         //else if (event_name == SPAWN_FILE_NAVIGATOR_IF_NO_STAGES_EXIST) { spawn_file_navigator_if_no_stages_exist(); executed = true; }
         else if (event_name == SPAWN_KEYBOARD_INPUTS_MODAL) { spawn_keyboard_inputs_modal(); executed = true; }
         else if (event_name == SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL) { spawn_regex_input_box_modal(); executed = true; }
         else if (event_name == SPAWN_RERUN_OUTPUT_WATCHER) { spawn_rerun_output_watcher(); executed = true; }
         else if (event_name == SUBMIT_CURRENT_MODAL) { submit_current_modal(); executed = true; }

         if (!executed) std::cout << "???? cannot execute \"" << event_name << "\".  It does not exist." << std::endl;
      }
      catch (const std::exception &exception)
      {
         std::cout << ">BOOM< cannot execute \"" << event_name << "\".  The following exception occurred: " << exception.what() << std::endl;
         // add the thing right here
         std::stringstream error_message;
         error_message << "An exception was thrown: \"" << exception.what() << "\"";
         add_notification(error_message.str());
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



                                                 // al_keycodee, shift, ctrl, alt, command, { command_identifier }

      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_BACKQUOTE, true, false, false, false, { ATTEMPT_TO_FLIP_TO_CORRELATED_COMPONENT_TEST_FILE });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_BACKQUOTE, false, false, false, false, { ATTEMPT_TO_FLIP_TO_CORRELATED_COMPONENT_QUINTESSENCE_FILE });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_OPENBRACE, false, false, true, false, { ROTATE_STAGE_RIGHT });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_CLOSEBRACE, false, false, true, false, { ROTATE_STAGE_LEFT });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_T, false, false, true, false, { SAVE_CURRENT_STAGE, RUN_PROJECT_TESTS });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_M, false, false, true, false, { SAVE_CURRENT_STAGE, CLEAR_RERUN_OUTPUT_WATCHERS, REFRESH_RERUN_OUTPUT_WATCHERS });
      //keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, false, { DESTROY_TOPMOST_STAGE, SPAWN_FILE_NAVIGATOR_IF_NO_STAGES_EXIST });
      keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, false, { DESTROY_TOPMOST_STAGE });
      if (is_current_stage_a_modal())
      {
         //keyboard_command_mapper.set_mapping(ALLEGRO_KEY_Q, false, false, false, false, { ESCAPE_CURRENT_MODAL, SPAWN_FILE_NAVIGATOR_IF_NO_STAGES_EXIST });
         //keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ESCAPE, false, false, false, false, { ESCAPE_CURRENT_MODAL, SPAWN_FILE_NAVIGATOR_IF_NO_STAGES_EXIST });
         if (is_current_stage_a_regex_input_box())
         {
           keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER, false, false, false, false, { SUBMIT_CURRENT_MODAL });
         }
         else
         {
            keyboard_command_mapper.set_mapping(ALLEGRO_KEY_ENTER, true, false, false, false, { SUBMIT_CURRENT_MODAL });
         }
      }
      else
      {
         keyboard_command_mapper.set_mapping(ALLEGRO_KEY_TAB, true, false, false, false, { SPAWN_FILE_NAVIGATOR });
         keyboard_command_mapper.set_mapping(ALLEGRO_KEY_TAB, false, false, false, false, { SPAWN_COMPONENT_NAVIGATOR });

         if (is_current_stage_in_edit_mode())
         {
            keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, false, false, false, false, { SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL, SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE });
            keyboard_command_mapper.set_mapping(ALLEGRO_KEY_SLASH, true,  false, false, false, { SPAWN_KEYBOARD_INPUTS_MODAL });
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
         bool ctrl = event.keyboard.modifiers & ALLEGRO_KEYMOD_CTRL;
         bool command = event.keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;
         bool ctrl_or_command = ctrl || command;
         std::vector<std::string> mapped_events = keyboard_command_mapper.get_mapping(event.keyboard.keycode, shift, ctrl_or_command, alt);
         if (!mapped_events.empty()) event_caught = true;
         for (auto &mapped_event : mapped_events) process_local_event(mapped_event);
         break;
      }

      if (!event_caught)
      {
         //if (file_navigator.get_visible_and_active()) file_navigator.process_event(event);
         StageInterface *frontmost_stage = get_frontmost_stage();
         if (frontmost_stage) frontmost_stage->process_event(event);
      }
   }

   std::string get_action_description(std::string action_identifier)
   {
      // std::map<identifier, description>
      static std::map<std::string, std::string> dictionary = {
         { System::DESTROY_FILE_NAVIGATOR, "" },
         { System::DESTROY_TOPMOST_STAGE, "" },
         { System::DESTROY_ALL_CODE_EDITOR_STAGES, "" },
         { System::ESCAPE_CURRENT_MODAL, "" },
         { System::HIDE_FILE_NAVIGATOR, "" },
         { System::JUMP_TO_NEXT_CODE_POINT_ON_STAGE, "" },
         { System::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE, "" },
         { System::REFRESH_REGEX_HILIGHTS_ON_STAGE, "" },
         { System::ADD_FILE_IS_UNSAVED_NOTIFICATION, "" },
         { System::REMOVE_FILE_IS_UNSAVED_NOTIFICATION, "" },
         { System::ROTATE_STAGE_LEFT, "" },
         { System::ROTATE_STAGE_RIGHT, "" },
         { System::RUN_MAKE, "" },
         { System::RUN_PROJECT_TESTS, "" },
         { System::SAVE_CURRENT_STAGE, "" },
         { System::SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE, "" },
         { System::SPAWN_COMPONENT_NAVIGATOR, "" },
         { System::SPAWN_FILE_NAVIGATOR, "" },
         { System::SPAWN_KEYBOARD_INPUTS_MODAL, "" },
         { System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL, "" },
         { System::SPAWN_RERUN_OUTPUT_WATCHER, "" },
         { System::SUBMIT_CURRENT_MODAL, "" },
      };

      for (std::map<std::string, std::string>::iterator it=dictionary.begin(); it!=dictionary.end(); ++it)
      {
         it->second = it->first;
      }

      std::map<std::string, std::string>::iterator it = dictionary.find(action_identifier);
      if (it == dictionary.end())
      {
         std::stringstream error_message;
         error_message << "🛑 Error: stuff stuff stuff stuff" << std::endl;
         throw std::runtime_error(error_message.str());
      }

      return dictionary[action_identifier];
   }

private:
};


const std::string System::ADD_FILE_IS_UNSAVED_NOTIFICATION = "ADD_FILE_IS_UNSAVED_NOTIFICATION";
const std::string System::REMOVE_FILE_IS_UNSAVED_NOTIFICATION = "REMOVE_FILE_IS_UNSAVED_NOTIFICATION";
const std::string System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION = "ATTEMPT_TO_CREATE_STAGE_FROM_LAST_FILE_NAVIGATOR_SELECTION";
const std::string System::ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION = "ATTEMPT_TO_CREATE_STAGE_FROM_LAST_COMPONENT_NAVIGATOR_SELECTION";
const std::string System::ATTEMPT_TO_FLIP_TO_CORRELATED_COMPONENT_QUINTESSENCE_FILE = "ATTEMPT_TO_FLIP_TO_CORRELATED_COMPONENT_QUINTESSENCE_FILE";
const std::string System::ATTEMPT_TO_FLIP_TO_CORRELATED_COMPONENT_TEST_FILE = "ATTEMPT_TO_FLIP_TO_CORRELATED_COMPONENT_TEST_FILE";
const std::string System::CLEAR_RERUN_OUTPUT_WATCHERS = "CLEAR_RERUN_OUTPUT_WATCHERS";
const std::string System::DESTROY_FILE_NAVIGATOR = "DESTROY_FILE_NAVIGATOR";
const std::string System::DESTROY_TOPMOST_STAGE = "DESTROY_TOPMOST_STAGE";
const std::string System::DESTROY_ALL_CODE_EDITOR_STAGES = "DESTROY_ALL_CODE_EDITOR_STAGES";
const std::string System::ESCAPE_CURRENT_MODAL = "ESCAPE_CURRENT_MODAL";
const std::string System::HIDE_FILE_NAVIGATOR = "HIDE_FILE_NAVIGATOR";
const std::string System::JUMP_TO_NEXT_CODE_POINT_ON_STAGE = "JUMP_TO_NEXT_CODE_POINT_ON_STAGE";
const std::string System::OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE = "OFFSET_FIRST_LINE_TO_VERTICALLY_CENTER_CURSOR_ON_STAGE";
const std::string System::PUSH_FILE_NAVIGATOR_SELECTION = "PUSH_FILE_NAVIGATOR_SELECTION";
const std::string System::PUSH_COMPONENT_NAVIGATOR_SELECTION = "PUSH_COMPONENT_NAVIGATOR_SELECTION";
const std::string System::REFRESH_REGEX_HILIGHTS_ON_STAGE = "REFRESH_REGEX_HILIGHTS_ON_STAGE";
const std::string System::REFRESH_RERUN_OUTPUT_WATCHERS = "REFRESH_RERUN_OUTPUT_WATCHERS";
const std::string System::ROTATE_STAGE_LEFT = "ROTATE_STAGE_LEFT";
const std::string System::ROTATE_STAGE_RIGHT = "ROTATE_STAGE_RIGHT";
const std::string System::RUN_MAKE = "RUN_MAKE";
const std::string System::RUN_PROJECT_TESTS = "RUN_PROJECT_TESTS";
const std::string System::SAVE_CURRENT_STAGE = "SAVE_CURRENT_STAGE";
const std::string System::SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE = "SET_REGEX_ONE_LINE_INPUT_BOX_MODAL_TO_INSERT_MODE";
const std::string System::SPAWN_COMPONENT_NAVIGATOR = "SPAWN_COMPONENT_NAVIGATOR";
const std::string System::SPAWN_FILE_NAVIGATOR = "SPAWN_FILE_NAVIGATOR";
//const std::string System::SPAWN_FILE_NAVIGATOR_IF_NO_STAGES_EXIST = "SPAWN_FILE_NAVIGATOR_IF_NO_STAGES_EXIST";
const std::string System::SPAWN_KEYBOARD_INPUTS_MODAL = "SPAWN_KEYBOARD_INPUTS_MODAL";
const std::string System::SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL = "SPAWN_REGEX_ONE_LINE_INPUT_BOX_MODAL";
const std::string System::SPAWN_RERUN_OUTPUT_WATCHER = "SPAWN_RERUN_OUTPUT_WATCHER";
const std::string System::SUBMIT_CURRENT_MODAL = "SUBMIT_CURRENT_MODAL";


void run_program(std::vector<std::string> filenames, std::vector<std::string> components)
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
   ALLEGRO_DISPLAY *display = al_create_display(get_display_default_width(), get_display_default_height());
   if (!display) std::cerr << "al_create_display() failed" << std::endl;
   al_set_window_title(display, "[ProjectName] - Hexagon");
   ALLEGRO_FONT *consolas_font = al_load_font(resource_path({"data", "fonts"}, "consolas.ttf").c_str(), 22, 0);
   if (!consolas_font) throw std::runtime_error("could not load consolas.ttf");

   REGEX_TEMP_FILENAME = resource_path({"data", "tmp"}, "regex.txt");
   if (!php::file_exists(REGEX_TEMP_FILENAME))
   {
      std::stringstream error_message;
      error_message << "🛑 Error: there is no \"" << REGEX_TEMP_FILENAME << "\" located in the directory tree.  It has to be present for hexagon to work.";
      throw std::runtime_error(error_message.str());
   }

   CLIPBOARD_TEMP_FILENAME = resource_path({"data", "tmp"}, "clipboard.txt");
   if (!php::file_exists(CLIPBOARD_TEMP_FILENAME))
   {
      std::stringstream error_message;
      error_message << "🛑 Error: there is no \"" << CLIPBOARD_TEMP_FILENAME << "\" located in the directory tree.  It has to be present for hexagon to work.";
      throw std::runtime_error(error_message.str());
   }

   FILE_NAVIGATOR_SELECTION_FILENAME = resource_path({"data", "tmp"}, "file_navigator_selection.txt");
   if (!php::file_exists(FILE_NAVIGATOR_SELECTION_FILENAME))
   {
      std::stringstream error_message;
      error_message << "🛑 Error: there is no \"" << FILE_NAVIGATOR_SELECTION_FILENAME << "\" located in the directory tree.  It has to be present for hexagon to work.";
      throw std::runtime_error(error_message.str());
   }

   MAKE_COMMAND_FILENAME = resource_path({"data", "tmp"}, "make_command.txt");
   if (!php::file_exists(MAKE_COMMAND_FILENAME))
   {
      std::stringstream error_message;
      error_message << "|----| Error: there is no \"" << MAKE_COMMAND_FILENAME << "\" located in the directory tree.  It has to be present for hexagon to work.";
      throw std::runtime_error(error_message.str());
   }

   int display_width = al_get_display_width(display);
   int display_height = al_get_display_height(display);

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_display_event_source(display));

   ALLEGRO_TIMER *primary_timer = al_create_timer(1.0/60.0);
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_start_timer(primary_timer);

   float logo_radius = 60;

   std::string logo_font_filename = "Expansiva_bold.otf";
   ALLEGRO_FONT *expansiva_font = al_load_font(resource_path({"data", "fonts"}, logo_font_filename).c_str(), 23, 0);
   if (!expansiva_font) throw std::runtime_error("could not load 'Expansiva bold.ttf'");


   Hexagon::Logo logo(display_width/2, display_height/2 - logo_radius * 1.4, logo_radius, expansiva_font, al_color_html("#bc2d48"), 3);
   logo.render();

   al_flip_display();
   wait_for_keypress();


   //al_hide_mouse_cursor(display); // this is disabled because there are a small handfull of sideeffects
                                    // 1) prior app focus (before h launches) is not returned after h is closed
                                    // 2) it messes with the normal expected mouse visibility outside of the window
   al_flip_display();

   Motion motion;


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

   System system(display, motion);


   // create the first stage


   // initialize first stage


   if (filenames.empty())
   {
      //DEFAULT_CONTENT_FILENAME = resource_path({"data", "files"}, "sonnet_lxi.txt");
      //std::cout << "Notice: No filenames were passed when opening the program.  Using the DEFAULT_CONTENT_FILENAME (\"" << DEFAULT_CONTENT_FILENAME << "\") as the initial content for a stage." << std::endl;
      //filenames.push_back(DEFAULT_CONTENT_FILENAME);
      //std::stringstream
      std::cerr << "Warning: No filenames were passed when opening the program.  This may cause the program to crash" << std::endl;
   }


   for (auto &filename : filenames)
   {
      CodeEditor::Stage *stage = new CodeEditor::Stage(filename);
      stage->set_place(place);

      std::vector<std::string> lines;
      read_file(lines, filename);

      stage->set_content(lines);
      system.stages.push_back(stage);

      //

      ThreeSplitLayout layout(stage, stage, stage);
      layout.place_stages();
   }


   Hexagon::Hud hud(display, consolas_font);
   hud.initialize();


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
         motion.update(al_get_time());
         if (motion.get_num_active_animations() == 0) continue;
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


         // refresh the notifications, and grab "content_is_unmodified" states from each stage
         clear_notifications();
         for (auto &stage : system.stages)
         {
            StageInterface::type_t type = stage->get_type();
            if (type == CodeEditor::Stage::ONE_LINE_INPUT_BOX || type == CodeEditor::Stage::CODE_EDITOR)
            {
               bool this_stage_content_is_modified = static_cast<CodeEditor::Stage *>(stage)->get_content_is_modified();
               if (this_stage_content_is_modified) add_notification(NOTIFICATION_FILE_IS_UNSAVED);
            }
         }

         hud.set_notifications(notifications);
         hud.draw();

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
   Blast::CommandLineFlaggedArgumentsParser command_line_flagged_arguments_parser(args);

   std::vector<std::vector<std::string>> filenames = command_line_flagged_arguments_parser.get_flagged_args("-f");
   std::vector<std::string> first_filenames_set = filenames.empty() ? std::vector<std::string>{} : filenames[0];

   std::vector<std::vector<std::string>> components = command_line_flagged_arguments_parser.get_flagged_args("-c");
   std::vector<std::string> first_component_set = components.empty() ? std::vector<std::string>{} : components[0];

   //if (first_filenames_set.empty())
   //{
      //std::string error_message = "🛑 Error: You attempted to run hexagon without a file to edit.  For now, you must open hexagon by specifying a filename after a \"-f\" flag.";
      //throw std::runtime_error(error_message);
   //}

   run_program(first_filenames_set, first_component_set);
   return 0;
}


