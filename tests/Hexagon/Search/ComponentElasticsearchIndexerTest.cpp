
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(stmt, etype, whatstring) ASSERT_THROW( \
        try { \
            stmt; \
        } catch (const etype& ex) { \
            ASSERT_EQ(std::string(ex.what()), whatstring); \
            throw; \
        } \
    , etype)

#include <Hexagon/Search/ComponentElasticsearchIndexer.hpp>

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest, can_be_created_without_blowing_up)
{
   Hexagon::Search::ComponentElasticsearchIndexer component_elasticsearch_indexer;
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest,
   generate_uid__returns_a_uid_in_the_expected_format)
{
   Blast::Project::Component component("Component/Name", "hexagon");
   Hexagon::Search::ComponentElasticsearchIndexer indexer(&component);

   std::string expected_uid = "hexagon:Component/Name";
   std::string actual_uid = indexer.generate_uid();
   ASSERT_EQ(expected_uid, actual_uid);
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest,
   import_or_update__without_a_nullptr_component__throws_an_error)
{
   Hexagon::Search::ComponentElasticsearchIndexer component_elasticsearch_indexer;
   std::string expected_error_message = "[ComponentElasticsearchIndex error:] can not \"import_or_update\" on a nullptr component";
   ASSERT_THROW_WITH_MESSAGE(
      component_elasticsearch_indexer.import_or_update(),
      std::runtime_error,
      expected_error_message
   );
}
