

#include <Hexagon/System/Config.hpp>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace System
{


std::string Config::INITIAL_DISPLAY_WIDTH_KEY = "initial_display_width";


std::string Config::INITIAL_DISPLAY_HEIGHT_KEY = "initial_display_height";


std::string Config::DEFAULT_NAVIGATOR_DIRECTORY_KEY = "default_navigator_directory";


std::string Config::REGEX_TEMP_FILENAME_KEY = "regex_temp_filename";


std::string Config::CLIPBOARD_TEMP_FILENAME_KEY = "clipboard_temp_filename";


std::string Config::FILE_NAVIGATOR_SELECTION_FILENAME_KEY = "file_navigator_selection_temp_filename";


std::string Config::MAKE_COMMAND_FILENAME_KEY = "make_command_temp_filename";


std::string Config::FOCUSED_COMPONENT_FILENAME_KEY = "focused_component_filename";


std::string Config::FONT_BIN_PATH_KEY = "font_bin_path";


std::string Config::DARK_MODE_KEY = "dark_mode";


std::string Config::HUD_RENDER_FOCUS_TIMER_BAR_KEY = "hud_render_focus_timer_bar";


std::string Config::FULLSCREEN_KEY = "fullscreen";


Config::Config(std::string config_filename)
   : config_filename(config_filename)
   , config(config_filename)
   , initialized(false)
{
}


Config::~Config()
{
}


std::string Config::get_config_filename()
{
   return config_filename;
}


void Config::validate_initialized(std::string function_name)
{
   if (!initialized)
   {
      std::stringstream error_message;
      error_message << "[Hexagon::System::Config error:] cannot call "
                    << "\"" << function_name << "\". "
                    << "This component must be initialized before this function can be used.";
      throw std::runtime_error(error_message.str());
   }
}

void Config::initialize()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Config" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (initialized) return; // TODO, double initialization should raise an exception
   config.load();
   initialized = true;
}

void Config::reload()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Config" << "::" << "reload" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   config.reload(); return;
}

int Config::get_initial_display_width()
{
   validate_initialized(__FUNCTION__);
   return config.get_or_default_int("", INITIAL_DISPLAY_WIDTH_KEY, 2430);
}

int Config::get_initial_display_height()
{
   validate_initialized(__FUNCTION__);
   return config.get_or_default_int("", INITIAL_DISPLAY_HEIGHT_KEY, 1350);
}

std::string Config::get_default_navigator_directory()
{
   validate_initialized(__FUNCTION__);
   return config.get_or_default_str("", DEFAULT_NAVIGATOR_DIRECTORY_KEY, "/Users/markoates/Repos/hexagon");
}

std::string Config::get_regex_temp_filename()
{
   std::string default_filename = resource_path({"data", "tmp"}, "regex.txt");
   return config.get_or_default_str("", REGEX_TEMP_FILENAME_KEY, default_filename);
}

std::string Config::get_clipboard_temp_filename()
{
   std::string default_filename = resource_path({"data", "tmp"}, "clipboard.txt");
   return config.get_or_default_str("", CLIPBOARD_TEMP_FILENAME_KEY, default_filename);
}

std::string Config::get_file_navigator_selection_filename()
{
   std::string default_filename = resource_path({"data", "tmp"}, "file_navigator_selection.txt");
   return config.get_or_default_str("", FILE_NAVIGATOR_SELECTION_FILENAME_KEY, default_filename);
}

std::string Config::get_make_command_filename()
{
   std::string default_filename = resource_path({"data", "tmp"}, "make_command.txt");
   return config.get_or_default_str("", MAKE_COMMAND_FILENAME_KEY, default_filename);
}

std::string Config::get_focused_component_filename()
{
   std::string default_filename = "/Users/markoates/Repos/hexagon/bin/programs/data/tmp/focused_component.txt";
   return config.get_or_default_str("", FOCUSED_COMPONENT_FILENAME_KEY, default_filename);
}

std::string Config::get_font_bin_path()
{
   std::string default_font_bin_path = "/Users/markoates/Repos/hexagon/bin/programs/data/fonts";
   return config.get_or_default_str("", FONT_BIN_PATH_KEY, default_font_bin_path);
}

int Config::get_default_camera_stepback()
{
   return 130;
}

bool Config::is_dark_mode()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Config" << "::" << "is_dark_mode" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   return config.get_or_default_bool("", DARK_MODE_KEY, false);
}

bool Config::is_fullscreen()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Config" << "::" << "is_fullscreen" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   return config.get_or_default_bool("", FULLSCREEN_KEY, false);
}

bool Config::get_hud_render_focus_timer_bar()
{
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Config" << "::" << "get_hud_render_focus_timer_bar" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   return config.get_or_default_bool("", HUD_RENDER_FOCUS_TIMER_BAR_KEY, false);
}

ALLEGRO_COLOR Config::get_backfill_color()
{
   if (is_dark_mode())
   {
      return al_color_name("black");
   }
   else
   {
      return al_color_name("white");
      //return al_color_html("8f9996"); // deep rich gray
      //return al_color_html("8a5b38"); // darker, more true deep brown from lamp
      //return al_color_html("a67d5a"); // color of lamp light against wall

      //return al_color_html("d2dbd6"); // very nice light gray
   }
   //return al_color_html("d2dbd6"); // very nice light gray
   //return al_color_html("8f9996"); // deep rich gray

   //return al_color_html("5b5c60");
   //return al_color_name("black");
}

ALLEGRO_COLOR Config::get_base_text_color()
{
   if (is_dark_mode())
   {
      return al_color_name("white");
   }
   else
   {
      return al_color_name("black");
   }
}

float Config::get_backfill_opacity()
{
   return 0.8f;
}

std::string Config::resource_path(std::vector<std::string> components, std::string filename)
{
   std::string result;

   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   for (auto &component : components) al_append_path_component(path, component.c_str());

   al_set_path_filename(path, filename.c_str());
   result = al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP);

   //std::cout << result << std::endl;

   return result;
}
} // namespace System
} // namespace Hexagon


