#pragma once



#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <AllegroFlare/Profiler.hpp>



extern std::string REGEX_TEMP_FILENAME;
extern std::string CLIPBOARD_TEMP_FILENAME;
extern std::string FILE_NAVIGATOR_SELECTION_FILENAME;
extern std::string FILE_NAVIGATOR_SELECTION_last_content;
extern std::string MAKE_COMMAND_FILENAME;
extern std::string DEFAULT_CONTENT_FILENAME;
extern std::string BACKFILL_COLOR_HEX;


extern std::string TEST_RUN_DUMP_FULL_PATH;


extern std::string NOTIFICATION_FILE_IS_UNSAVED;



extern std::vector<std::string> notifications;
namespace global
{
   extern AllegroFlare::Profiler profiler;
}

void clear_last_compiled_error_messages();
void set_last_compiled_error_messages(std::string);
std::string get_last_compiled_error_messages();
bool is_last_compiled_error_messages_empty();

void set_last_compiler_run_exit_code(int exit_code);
int get_last_compiler_run_exit_code();

bool is_light_mode();
float hexagon_get_backfill_opacity();
ALLEGRO_COLOR hexagon_get_base_text_color();
bool hexagon_window_frameless();



void add_notification(std::string notification);
void remove_notification(std::string notification);
void clear_notifications();
