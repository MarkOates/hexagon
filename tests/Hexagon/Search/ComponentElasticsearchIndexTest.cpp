
#include <gtest/gtest.h>

#include <Hexagon/Search/ComponentElasticsearchIndex.hpp>

TEST(Hexagon_Search_ComponentElasticsearchIndexTest, can_be_created_without_blowing_up)
{
   Hexagon::Search::ComponentElasticsearchIndex component_elasticsearch_index;
}

TEST(Hexagon_Search_ComponentElasticsearchIndexTest, get_index_mapping__returns_the_expected_index_mapping)
{
   Hexagon::Search::ComponentElasticsearchIndex component_elasticsearch_index;

   std::string expected_index_mapping = R"INDEX_MAPPING({
  "mappings": {
    "project": {
      "type": "keyword"
    }
  }
})INDEX_MAPPING";

   std::string actual_index_mapping = component_elasticsearch_index.get_index_mapping();

   EXPECT_EQ(expected_index_mapping, actual_index_mapping);
}
