
#include <gtest/gtest.h>

#include <Hexagon/Search/ComponentElasticsearchIndexer.hpp>

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest, can_be_created_without_blowing_up)
{
   Hexagon::Search::ComponentElasticsearchIndexer component_elasticsearch_indexer;
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest,
   import_or_update__without_a_nullptr_component__throws_an_error)
{
   Blast::Project::Component component;

   Hexagon::Search::ComponentElasticsearchIndexer component_elasticsearch_indexer;
   //std::string expected_error_message = "[ComponentElasticsearchIndex error:] can not import_or_update on a nullptr component";
   EXPECT_THROW(component_elasticsearch_indexer.import_or_update(), std::runtime_error); //, expected_error_message);
}
