

#include <Hexagon/Search/ComponentElasticsearchIndexer.hpp>
#include <sstream>
#include <Blast/Project/Component.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <lib/nlohmann/json.hpp>


namespace Hexagon
{
namespace Search
{


ComponentElasticsearchIndexer::ComponentElasticsearchIndexer()
   : component(nullptr)
{
}


ComponentElasticsearchIndexer::~ComponentElasticsearchIndexer()
{
}


bool ComponentElasticsearchIndexer::import_or_update(Blast::Project::Component* component)
{
if (!component)
{
   std::stringstream error_message;
   error_message << "[ComponentElasticsearchIndex error:] can not import_or_update on a nullptr component";
   throw std::runtime_error(error_message.str());
}

nlohmann::json document_as_json = {};

return true;

}
} // namespace Search
} // namespace Hexagon


