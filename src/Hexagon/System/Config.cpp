

#include <Hexagon/System/Config.hpp>
#include <sstream>


namespace Hexagon
{
namespace System
{


std::string Config::INITIAL_DISPLAY_WIDTH_KEY = "initial_display_width";


std::string Config::INITIAL_DISPLAY_HEIGHT_KEY = "initial_display_height";


std::string Config::DEFAULT_NAVIGATOR_DIRECTORY_KEY = "default_navigator_directory";


Config::Config(std::string config_filename)
   : config_filename(config_filename)
   , config(config_filename)
   , initialized(false)
{
}


Config::~Config()
{
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
} // namespace System
} // namespace Hexagon


