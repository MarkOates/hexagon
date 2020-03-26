

#include <Hexagon/Search/ComponentElasticsearchIndexer.hpp>
#include <sstream>
#include <Blast/Project/Component.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <lib/nlohmann/json.hpp>


namespace Hexagon
{
namespace Search
{


ComponentElasticsearchIndexer::ComponentElasticsearchIndexer(Blast::Project::Component* component)
   : component(component)
{
}


ComponentElasticsearchIndexer::~ComponentElasticsearchIndexer()
{
}


void ComponentElasticsearchIndexer::guard_nullptr_component(std::string function_name)
{
if (!component)
{
   std::stringstream error_message;
   error_message << "[ComponentElasticsearchIndex error:] can not "
                 << "\"" << function_name << "\""
                 << " on a nullptr component";
   throw std::runtime_error(error_message.str());
}
return;

}

std::string ComponentElasticsearchIndexer::generate_uid()
{
guard_nullptr_component(__FUNCTION__);

std::string delimiter = ":";
return component->get_project_root() + delimiter + component->get_name();

}

std::string ComponentElasticsearchIndexer::generate_index_shell_command()
{
guard_nullptr_component(__FUNCTION__);

nlohmann::json document_as_json = {
  { "uid", generate_uid() },
  { "id", component->get_name() },
  { "project", component->get_project_root() },
  { "name", component->get_name() },
  { "content", component->get_name() }
};

std::string document_as_json_string = document_as_json.dump();

std::stringstream index_shell_command;
index_shell_command << "curl -XPOST \"http://localhost:9200/components/_doc/\" "
                    << "-H 'Content-Type: application/json' -d'"
                    << document_as_json_string
                    << "'";

return index_shell_command.str();

}

std::string ComponentElasticsearchIndexer::import_or_update()
{
guard_nullptr_component(__FUNCTION__);

std::string index_shell_command = generate_index_shell_command();
Blast::ShellCommandExecutorWithCallback executor(index_shell_command);

std::string response = executor.execute();

return response;

}
} // namespace Search
} // namespace Hexagon


