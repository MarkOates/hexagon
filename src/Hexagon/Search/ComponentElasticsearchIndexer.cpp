

#include <Hexagon/Search/ComponentElasticsearchIndexer.hpp>

#include <Blast/Project/Component.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace Search
{


ComponentElasticsearchIndexer::ComponentElasticsearchIndexer(Blast::Project::Component* component, std::string index_name)
   : component(component)
   , index_name(index_name)
{
}


ComponentElasticsearchIndexer::~ComponentElasticsearchIndexer()
{
}


std::string ComponentElasticsearchIndexer::get_index_name() const
{
   return index_name;
}


std::string ComponentElasticsearchIndexer::generate_uid()
{
   if (!(component))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Search::ComponentElasticsearchIndexer::generate_uid]: error: guard \"component\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Search::ComponentElasticsearchIndexer::generate_uid]: error: guard \"component\" not met");
   }
   std::string delimiter = ":";
   return component->get_project_root() + delimiter + component->get_name();
}

std::string ComponentElasticsearchIndexer::generate_index_shell_command()
{
   if (!(component))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Search::ComponentElasticsearchIndexer::generate_index_shell_command]: error: guard \"component\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Search::ComponentElasticsearchIndexer::generate_index_shell_command]: error: guard \"component\" not met");
   }
   nlohmann::json document_as_json = {
     { "uid", generate_uid() },
     { "id", component->get_name() },
     { "project", component->get_project_root() },
     { "name", component->get_name() },
     { "content", component->get_name() }
   };

   std::string document_as_json_string = document_as_json.dump();

   // TODO: we need to escape single quote strings inside document_as_json_string

   std::stringstream index_shell_command;
   index_shell_command << "curl -XPOST \"http://localhost:9200/"
                       << get_index_name()
                       << "/_doc/\" "
                       << "-H 'Content-Type: application/json' -d'"
                       << document_as_json_string
                       << "'";

   return index_shell_command.str();
}

std::string ComponentElasticsearchIndexer::import_or_update()
{
   if (!(component))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Search::ComponentElasticsearchIndexer::import_or_update]: error: guard \"component\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Search::ComponentElasticsearchIndexer::import_or_update]: error: guard \"component\" not met");
   }
   std::string index_shell_command = generate_index_shell_command();
   Blast::ShellCommandExecutorWithCallback executor(index_shell_command);

   std::string response = executor.execute();

   return response;
}


} // namespace Search
} // namespace Hexagon


