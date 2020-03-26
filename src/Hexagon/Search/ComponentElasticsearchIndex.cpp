

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


std::string ComponentElasticsearchIndex::run()
{
return "Hello World!";
}

std::string ComponentElasticsearchIndex::get_index_name()
{
return "components";
}

std::string ComponentElasticsearchIndex::get_index_mapping()
{
std::string index_mapping = R"INDEX_MAPPING({
  "mappings": {
    "uid": { "type": "keyword" },
    "id": { "type": "keyword" },
    "project": { "type": "keyword" },
    "name": { "type": "text" },
    "content": { "type": "text" }
  }
})INDEX_MAPPING";
return index_mapping;

}
} // namespace Search
} // namespace Hexagon


