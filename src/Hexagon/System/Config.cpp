

#include <Hexagon/System/Config.hpp>



namespace Hexagon
{
namespace System
{


std::string Config::DEFAULT_NAVIGATOR_DIRECTORY_KEY = "default_navigator_directory";


Config::Config(std::string config_filename)
   : config_filename(config_filename)
   , config(config_filename)
{
}


Config::~Config()
{
}


void Config::initialize()
{
config.load();
}

std::string Config::get_default_navigator_directory()
{
return config.get_or_default_str("", DEFAULT_NAVIGATOR_DIRECTORY_KEY, "/Users/markoates/Repos/hexagon");

}
} // namespace System
} // namespace Hexagon


