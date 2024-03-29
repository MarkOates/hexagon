


#include <Hexagon/shared_globals.hpp>


#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>


std::string REGEX_TEMP_FILENAME = "regex.txt";
std::string CLIPBOARD_TEMP_FILENAME = "clipboard.txt";
std::string FILE_NAVIGATOR_SELECTION_FILENAME = "file_navigator_selection.txt";
std::string FILE_NAVIGATOR_SELECTION_last_content = "";
std::string MAKE_COMMAND_FILENAME = "make_command.txt";
std::string DEFAULT_CONTENT_FILENAME = "default.txt";
std::string BACKFILL_COLOR_HEX = "5b5c90";



std::string TEST_RUN_DUMP_FULL_PATH =
   "/Users/markoates/Repos/hexagon/bin/programs/data/builds/dumps/component_test_run.txt";



std::string NOTIFICATION_FILE_IS_UNSAVED = "file is unsaved";



static std::string last_compiled_error_messages = "";
static int last_compiler_run_exit_code = -1;


void clear_last_compiled_error_messages()
{
   last_compiled_error_messages = "";
}


void set_last_compiled_error_messages(std::string val)
{
   last_compiled_error_messages = val;
}


std::string get_last_compiled_error_messages()
{
   return last_compiled_error_messages;
}


bool is_last_compiled_error_messages_empty()
{
   return last_compiled_error_messages == "";
}



void set_last_compiler_run_exit_code(int exit_code)
{
   last_compiler_run_exit_code = exit_code;
}

int get_last_compiler_run_exit_code()
{
   return last_compiler_run_exit_code;
}


bool hexagon_is_light_mode()
{
   return false;
}


float hexagon_get_backfill_opacity()
{
   return 0.8f;
}


ALLEGRO_COLOR hexagon_get_base_text_color()
{
   if (hexagon_is_light_mode())
   {
      return al_color_name("black");
   }
   else
   {
      return al_color_name("white");
   }
}

bool hexagon_window_frameless()
{
   return true;
}




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


namespace global
{
   AllegroFlare::Profiler profiler;
}
