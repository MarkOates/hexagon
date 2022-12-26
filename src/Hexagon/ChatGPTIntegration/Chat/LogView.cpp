

#include <Hexagon/ChatGPTIntegration/Chat/LogView.hpp>

#include <Blast/FileExistenceChecker.hpp>
#include <allegro_flare/useful_php.h>


namespace Hexagon
{
namespace ChatGPTIntegration
{
namespace Chat
{


LogView::LogView(std::string source_filename)
   : source_filename(source_filename)
{
}


LogView::~LogView()
{
}


void LogView::set_source_filename(std::string source_filename)
{
   this->source_filename = source_filename;
}


std::string LogView::get_source_filename() const
{
   return source_filename;
}


std::string LogView::get_log_text()
{
   Blast::FileExistenceChecker existence_checker(source_filename);
   if (!existence_checker.exists())
   {
      return "[ file not found at expected location ]\n[ looking in " + source_filename + " ]";
   }
   return php::file_get_contents(source_filename);
}


} // namespace Chat
} // namespace ChatGPTIntegration
} // namespace Hexagon


