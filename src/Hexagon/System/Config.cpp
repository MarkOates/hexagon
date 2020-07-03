

#include <Hexagon/System/Config.hpp>
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


std::string Config::FONT_BIN_PATH_KEY = "font_bin_path";


std::string Config::DARK_MODE_KEY = "dark_mode";


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
if (initialized) return;
config.load();
initialized = true;

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

std::string Config::get_font_bin_path()
{
std::string default_font_bin_path = "/Users/markoates/Repos/hexagon/bin/programs/data/fonts";
return config.get_or_default_str("", FONT_BIN_PATH_KEY, default_font_bin_path);

}

bool Config::is_dark_mode()
{
return config.get_or_default_bool("", DARK_MODE_KEY, false);

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


