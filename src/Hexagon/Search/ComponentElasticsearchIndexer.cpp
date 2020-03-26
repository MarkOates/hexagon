

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

bool ComponentElasticsearchIndexer::import_or_update()
{
guard_nullptr_component(__FUNCTION__);

// this is the mapping for reference:
//
//"uid": { "type": "keyword" },
//"id": { "type": "keyword" },
//"project": { "type": "keyword" },
//"name": { "type": "text" },
//"content": { "type": "text" }

nlohmann::json document_as_json = {
  { "uid", generate_uid() }
};

return true;

}
} // namespace Search
} // namespace Hexagon


