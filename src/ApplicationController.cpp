

#include <ApplicationController.hpp>
#include <Hexagon/System/System.hpp>
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
#include <Hexagon/CppCompiler/CompileRunner.hpp>
#include <Hexagon/FullScreenOverlay/Stage.hpp>
#include <Hexagon/CodeRangeExtractor.hpp>
#include <Hexagon/CodeMessagePoint.hpp>
#include <Hexagon/CodeMessagePointsOverlay.hpp>
#include <Hexagon/StageInterface.hpp>
#include <Hexagon/KeyboardInputsModal/Stage.hpp>
#include <Hexagon/EventControllerInterface.hpp>
#include <Hexagon/CodeEditor/EventController.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <Hexagon/FileSystemNode.hpp>
#include <Hexagon/FileNavigator/Stage.hpp>
#include <Hexagon/ComponentNavigator/Stage.hpp>
#include <Hexagon/RerunOutputWatcher/Stage.hpp>
#include <Hexagon/LayoutPlacements.hpp>
#include <NcursesArt/ProjectComponentBasenameExtractor.hpp>
#include <NcursesArt/ProjectFilenameGenerator.hpp>
#include <Hexagon/System/Renderer.hpp>
#include <Hexagon/System/System.hpp>
#include <stdexcept>
#include <sstream>
#include <allegro5/allegro.h>
#include <sstream>




ApplicationController::ApplicationController(Hexagon::System::Config config)
   : config(config)
   , display(nullptr)
   , event_queue(nullptr)
   , primary_timer(nullptr)
   , motion()
   , system(nullptr)
   , user_event_source()
   , shutdown_program(false)
{
}


ApplicationController::~ApplicationController()
{
}


void ApplicationController::initialize_allegro_config_display_event_queue_and_timer()
{
if (!al_init()) std::cerr << "al_init() failed" << std::endl;
if (!al_init_font_addon()) std::cerr << "al_init_font_addon() failed" << std::endl;
if (!al_init_ttf_addon()) std::cerr << "al_init_ttf_addon() failed" << std::endl;
if (!al_init_primitives_addon()) std::cerr << "al_init_primitives_addon() failed" << std::endl;
if (!al_install_keyboard()) std::cerr << "al_install_keyboard() failed" << std::endl;

config.initialize();

al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 32, ALLEGRO_SUGGEST);
al_set_new_display_flags(ALLEGRO_RESIZABLE);
al_set_new_display_flags(ALLEGRO_NOFRAME);
//al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
display = al_create_display(
   config.get_initial_display_width(),
   config.get_initial_display_height());
if (!display) std::cerr << "al_create_display() failed" << std::endl;
al_set_window_title(display, "[ProjectName] - Hexagon");

int display_width = al_get_display_width(display);
int display_height = al_get_display_height(display);

event_queue = al_create_event_queue();
al_register_event_source(event_queue, al_get_keyboard_event_source());
al_register_event_source(event_queue, al_get_display_event_source(display));

primary_timer = al_create_timer(1.0/60.0);
al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
al_start_timer(primary_timer);

al_init_user_event_source(&user_event_source);
al_register_event_source(event_queue, &user_event_source);

}

void ApplicationController::initialize()
{
initialize_allegro_config_display_event_queue_and_timer();
verify_presence_of_temp_files_and_assign_to_global_constants();

system = new System(display, config, motion);
system->initialize();

}

void ApplicationController::shutdown()
{
al_destroy_event_queue(event_queue);
al_destroy_display(display);
//delete system;
//al_uninstall_system();

}

void ApplicationController::emit_user_event(ALLEGRO_EVENT user_event)
{
al_emit_user_event(&user_event_source, &user_event, NULL);
return;

}

void ApplicationController::run_program()
{
initialize();
draw_hexagon_logo_and_wait_for_keypress(al_get_display_width(display), al_get_display_height(display));
run_event_loop();
shutdown();

}

void ApplicationController::run_event_loop()
{
if (!(system))
   {
      std::stringstream error_message;
      error_message << "ApplicationController" << "::" << "run_event_loop" << ": error: " << "guard \"system\" not met";
      throw std::runtime_error(error_message.str());
   }
while(!shutdown_program)
{
   ALLEGRO_EVENT this_event;
   al_wait_for_event(event_queue, &this_event);
   global::profiler.clear();

   system->process_event(this_event);

   bool refresh = true;

   switch(this_event.type)
   {
   case ALLEGRO_EVENT_DISPLAY_CLOSE:
      shutdown_program = true;
      break;
   case ALLEGRO_EVENT_DISPLAY_RESIZE:
      al_acknowledge_resize(display);
      system->acknowledge_display_resize(display);
      //note that each rezie will cause the display to reload, and will be a bit laggy
      //refresh = false;
      break;
   case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
      system->acknowledge_display_switch_out(display);
      break;
   case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
      system->acknowledge_display_switch_in(display);
      break;
   case ALLEGRO_EVENT_TIMER:
      motion.update(al_get_time());
      //refresh = true;
      if (motion.get_num_active_animations() == 0) continue;
      break;
   }

   if (refresh)
   {
      //clear_notifications();

      //for (auto &stage : system.stages)
      //{
      //   StageInterface::type_t type = stage->get_type();
      //   if (type == CodeEditor::Stage::ONE_LINE_INPUT_BOX || type == CodeEditor::Stage::CODE_EDITOR)
      //   {
      //      bool this_stage_content_is_modified = static_cast<CodeEditor::Stage *>(stage)->get_content_is_modified();
      //      if (this_stage_content_is_modified) add_notification(NOTIFICATION_FILE_IS_UNSAVED);
      //   }
      //}

      //if (!is_last_compiled_error_messages_empty())
      //{
      //   std::vector<std::string> error_message_lines = Blast::StringSplitter(get_last_compiled_error_messages(), '\n').split();
      //   for (auto &error_message_line : error_message_lines)
      //   {
      //      add_notification(error_message_line);
      //   }
      //}

      //system.hud.set_notifications2({ "[ - ]" });
      //system.hud.set_notifications(notifications);

      //al_clear_to_color(al_color_name("black"));
      ALLEGRO_COLOR backfill_color = config.get_backfill_color();
      al_clear_to_color(backfill_color);

      Hexagon::System::Renderer renderer(system, display, &backfill_color);
      renderer.render();

      al_flip_display();

      bool drop_backed_up_primary_timer_events = true;
      if (drop_backed_up_primary_timer_events)
      {
         ALLEGRO_EVENT next_event;
         while (al_peek_next_event(event_queue, &next_event)
              && next_event.type == ALLEGRO_EVENT_TIMER
              && next_event.timer.source == primary_timer)
           al_drop_next_event(event_queue);
      }
   }
}
return;

}

void ApplicationController::verify_presence_of_temp_files_and_assign_to_global_constants()
{
std::string regex_temp_filename = config.get_regex_temp_filename();
if (!php::file_exists(regex_temp_filename))
{
   std::stringstream error_message;
   error_message << "Error: there is no \"" << regex_temp_filename << "\" located in the directory tree.  "
                 << "It has to be present for hexagon to work.";
   throw std::runtime_error(error_message.str());
}

std::string clipboard_temp_filename = config.get_clipboard_temp_filename();
if (!php::file_exists(clipboard_temp_filename))
{
   std::stringstream error_message;
   error_message << "Error: there is no \"" << clipboard_temp_filename << "\" located in the directory tree. "
                 << "It has to be present for hexagon to work.";
   throw std::runtime_error(error_message.str());
}

std::string file_navigator_selection_filename = config.get_file_navigator_selection_filename();
if (!php::file_exists(file_navigator_selection_filename))
{
   std::stringstream error_message;
   error_message << "Error: there is no \"" << file_navigator_selection_filename
                 << "\" located in the directory tree.  It has to be present for hexagon to work.";
   throw std::runtime_error(error_message.str());
}

std::string make_command_filename = config.get_make_command_filename();
if (!php::file_exists(make_command_filename))
{
   std::stringstream error_message;
   error_message << "Error: there is no \"" << make_command_filename
                 << "\" located in the directory tree.  It has to be present for hexagon to work.";
   throw std::runtime_error(error_message.str());
}

// assign confirmed values to globals

REGEX_TEMP_FILENAME = regex_temp_filename;
CLIPBOARD_TEMP_FILENAME = clipboard_temp_filename;
FILE_NAVIGATOR_SELECTION_FILENAME = file_navigator_selection_filename;
MAKE_COMMAND_FILENAME = make_command_filename;

return;

}

void ApplicationController::draw_hexagon_logo_and_wait_for_keypress(int display_width, int display_height)
{
float logo_radius = 64;

std::string logo_font_filename = "Expansiva_bold.otf";
ALLEGRO_FONT *expansiva_font = al_load_font(resource_path({"data", "fonts"}, logo_font_filename).c_str(), 23, 0);
if (!expansiva_font) throw std::runtime_error("could not load 'Expansiva bold.ttf'");

std::string detail_text_font_filename = "Purista Medium.otf";
ALLEGRO_FONT *purista_font =
  al_load_font(resource_path({"data", "fonts"}, detail_text_font_filename).c_str(), 16, 0);
if (!purista_font) throw std::runtime_error("could not load 'Purista Medium.otf'");

Hexagon::Logo logo(
  display_width/2,
  display_height/2,
  logo_radius,
  expansiva_font,
  al_color_html("#bc2d48"),
  2.25);
logo.render();

std::string allegro_version_string = build_allegro_version_string();
al_draw_text(purista_font, al_color_html("#bc2d48"),
   display_width/2, display_height/2 + logo_radius * 2.0, ALLEGRO_ALIGN_CENTER,
   allegro_version_string.c_str());

al_flip_display();

// wait for keypress
{
  ALLEGRO_EVENT_QUEUE *wait_for_keypress_event_queue;
  ALLEGRO_EVENT event;

  al_install_keyboard();
  wait_for_keypress_event_queue = al_create_event_queue();
  al_register_event_source(wait_for_keypress_event_queue, al_get_keyboard_event_source());

  do
    al_wait_for_event(wait_for_keypress_event_queue, &event);
  while (event.type != ALLEGRO_EVENT_KEY_DOWN);

  al_destroy_event_queue(wait_for_keypress_event_queue);
}

return;

}

std::string ApplicationController::build_allegro_version_string()
{
uint32_t version = al_get_allegro_version();
int major = version >> 24;
int minor = (version >> 16) & 255;
int revision = (version >> 8) & 255;
int release = version & 255;

std::stringstream result;
result << "Allegro v" << major << "." << minor << "." << revision << " r" << release;
return result.str();

}


