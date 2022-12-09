

#include <Hexagon/Errors.hpp>

#include <sstream>


namespace Hexagon
{


Errors::Errors()
{
}


Errors::~Errors()
{
}


std::string Errors::build_error_message(std::string from, std::string message)
{
   const std::string CONSOLE_COLOR_RED = "\033[1;31m";
   const std::string CONSOLE_COLOR_DEFAULT = "\033[0m";
   std::stringstream result;
   result << CONSOLE_COLOR_RED << "[" << from << "] error: " << message << CONSOLE_COLOR_DEFAULT << std::endl;
   return result.str();
}


} // namespace Hexagon


