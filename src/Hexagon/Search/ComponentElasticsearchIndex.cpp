

#include <Hexagon/Search/ComponentElasticsearchIndex.hpp>



namespace Hexagon
{
namespace Search
{


ComponentElasticsearchIndex::ComponentElasticsearchIndex()
{
}


ComponentElasticsearchIndex::~ComponentElasticsearchIndex()
{
}


std::string ComponentElasticsearchIndex::get_index_name()
{
   return "components";
}

std::string ComponentElasticsearchIndex::get_index_mapping()
{
   std::string index_mapping;
   index_mapping += "{\n";
   index_mapping += "  \"mappings\": {\n";
   index_mapping += "    \"uid\": { \"type\": \"keyword\" },\n";
   index_mapping += "    \"id\": { \"type\": \"keyword\" },\n";
   index_mapping += "    \"project\": { \"type\": \"keyword\" },\n";
   index_mapping += "    \"name\": { \"type\": \"text\" },\n";
   index_mapping += "    \"content\": { \"type\": \"text\" }\n";
   index_mapping += "  }\n";
   index_mapping += "}";
   return index_mapping;
}
} // namespace Search
} // namespace Hexagon


