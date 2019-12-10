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
#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Blast/CommandLineFlaggedArgumentsParser.hpp>
#include <lib/camera.h>
#include <AllegroFlare/Config.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/System/Action/DestroyAllCodeEditorStages.hpp>
#include <Hexagon/System/Action/AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection.hpp>
#include <Hexagon/System/Action/CreateThreeSplitFromComponent.hpp>
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




//std::vector<std::string> notifications = {};

//void add_notification(std::string notification)
//{
   //notifications.push_back(notification);
//}

//void remove_notification(std::string notification)
//{
   //notifications.push_back(notification);
//}

//void clear_notifications()
//{
   //notifications.clear();
//}



//#include <Hexagon/RailsMinitestTestResultToCodeMessagePointConverter.hpp>
//class RailsMinitestTestResultToCodeMessagePointConverter
//{
//private:
   //RailsMinitestTestResult rails_minitest_test_result;

//public:
   //RailsMinitestTestResultToCodeMessagePointConverter(RailsMinitestTestResult rails_minitest_test_result)
      //: rails_minitest_test_result(rails_minitest_test_result)
   //{}

   //CodeMessagePoint convert()
   //{
      //CodeMessagePoint::type_t code_message_point_type = CodeMessagePoint::NONE;
      //if (rails_minitest_test_result.test_state == RailsMinitestTestResult::ERROR) code_message_point_type = CodeMessagePoint::ERROR;
      //else if (rails_minitest_test_result.test_state == RailsMinitestTestResult::FAILURE) code_message_point_type = CodeMessagePoint::TEST_FAILURE;
      //return CodeMessagePoint(0, rails_minitest_test_result.error_line_number, 0, 0, rails_minitest_test_result.test_result_output, code_message_point_type);
   //}
//};



//class SystemConfig
//{
//private:
   //static const std::string DEFAULT_NAVIGATOR_DIRECTORY_KEY;

   //std::string config_filename;
   //AllegroFlare::Config config;

//public:
   //SystemConfig()
      //: config_filename("/Users/markoates/Repos/me/config/hexagon.boot.cfg")
      //, config(config_filename)
   //{}

   //void initialize()
   //{
      //config.load();
   //}

   //std::string get_default_navigator_directory()
   //{
      //return config.get_or_default_str("", DEFAULT_NAVIGATOR_DIRECTORY_KEY, "/Users/markoates/Repos/hexagon");
   //}
//};
//const std::string SystemConfig::DEFAULT_NAVIGATOR_DIRECTORY_KEY = "default_navigator_directory";



#include "Hexagon/System/System.hpp"



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
   ALLEGRO_DISPLAY *display = al_create_display(System::get_display_default_width(), System::get_display_default_height());
   if (!display) std::cerr << "al_create_display() failed" << std::endl;
   al_set_window_title(display, "[ProjectName] - Hexagon");

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


   Hexagon::Logo logo(display_width/2, display_height/2 - logo_radius * 1.4, logo_radius, expansiva_font, al_color_html("#bc2d48"), 2.5);
   logo.render();

   al_flip_display();

   // wait for keypress
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


   //al_hide_mouse_cursor(display); // this is disabled because there are a small handfull of sideeffects
                                    // 1) prior app focus (before h launches) is not returned after h is closed
                                    // 2) it messes with the normal expected mouse visibility outside of the window
   al_flip_display();

   Motion motion;
   AllegroFlare::FontBin fonts;
   fonts.set_path("data/fonts");


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
   system.initialize();


   // create the first stage


   // initialize first stage


   Hexagon::Hud hud(display, fonts);
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

         system.camera.setup_camera_perspective(al_get_backbuffer(display));
         al_clear_depth_buffer(1000);

         for (auto &stage : system.stages)
         {
            bool is_focused = (system.get_frontmost_stage() == stage);
            ALLEGRO_FONT *font = fonts[system.get_global_font_str()];
            stage->render(is_focused, display, font, al_get_text_width(font, " "), al_get_font_line_height(font));
         }


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


