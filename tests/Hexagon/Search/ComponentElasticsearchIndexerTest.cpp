
#include <gtest/gtest.h>
#include "lib/nlohmann/json.hpp"

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <Hexagon/Search/ComponentElasticsearchIndexer.hpp>

#include <Hexagon/Search/Elasticsearch/HealthChecker.hpp>

static const std::string TEST_INDEX_NAME = "components_test";

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest, can_be_created_without_blowing_up)
{
   Hexagon::Search::ComponentElasticsearchIndexer component_elasticsearch_indexer;
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest,
   index_name__has_a_getter_and_is_set_to_the_expected_value_by_default)
{
   Hexagon::Search::ComponentElasticsearchIndexer indexer;
   std::string expected_default_index_name = "components_dummy";
   ASSERT_EQ(expected_default_index_name, indexer.get_index_name());
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest,
   generate_uid__with_a_nullptr_component_throws_an_error)
{
   Hexagon::Search::ComponentElasticsearchIndexer indexer(nullptr, TEST_INDEX_NAME);
   ASSERT_THROW_GUARD_ERROR(
      indexer.generate_uid(),
      "Hexagon::Search::ComponentElasticsearchIndexer::generate_uid",
      "component"
   );
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest, generate_uid__returns_a_uid_in_the_expected_format)
{
   Blast::Project::Component component("Component/Name", "hexagon");
   Hexagon::Search::ComponentElasticsearchIndexer indexer(&component, TEST_INDEX_NAME);

   std::string expected_uid = "hexagon:Component/Name";
   std::string actual_uid = indexer.generate_uid();
   ASSERT_EQ(expected_uid, actual_uid);
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest,
   generate_index_shell_command__with_a_nullptr_component__throws_an_error)
{
   Hexagon::Search::ComponentElasticsearchIndexer indexer(nullptr, TEST_INDEX_NAME);
   ASSERT_THROW_GUARD_ERROR(
      indexer.generate_index_shell_command(),
      "Hexagon::Search::ComponentElasticsearchIndexer::generate_index_shell_command",
      "component"
   );
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest,
   generate_index_shell_command__returns_the_expected_shell_command)
{
   Blast::Project::Component component("Component/Name", "hexagon");
   Hexagon::Search::ComponentElasticsearchIndexer indexer(&component, TEST_INDEX_NAME);
   std::string expected_shell_command = "curl -XPOST \"http://localhost:9200/components_test/_doc/\" " \
                                        "-H 'Content-Type: application/json' " \
                                        "-d'{\"content\":\"Component/Name\",\"id\":\"Component/Name\"," \
                                        "\"name\":\"Component/Name\",\"project\":\"hexagon\"," \
                                        "\"uid\":\"hexagon:Component/Name\"}'";

   ASSERT_EQ(expected_shell_command, indexer.generate_index_shell_command());
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest,
   import_or_update__with_a_nullptr_component__throws_an_error)
{
   Hexagon::Search::ComponentElasticsearchIndexer indexer;
   ASSERT_THROW_GUARD_ERROR(
      indexer.import_or_update(),
      "Hexagon::Search::ComponentElasticsearchIndexer::import_or_update",
      "component"
   );
}

//TEST(Hexagon_Search_ComponentElasticsearchIndexerTest,
//   import_or_update__imports_the_component_into_elasticsearch)
//{
//   ASSERT_EQ(true, Hexagon::Search::Elasticsearch::HealthChecker().is_up());
//
//   Blast::Project::Component component("Component/Name", "hexagon");
//   Hexagon::Search::ComponentElasticsearchIndexer indexer(&component, TEST_INDEX_NAME);
//
//   std::string result = indexer.import_or_update();
//   nlohmann::json result_json = nlohmann::json::parse(result);
//
//   std::string expected_result = "created";
//   std::string actual_result = result_json["result"];
//
//   ASSERT_EQ(expected_result, actual_result);
//}
