
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

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest, generate_uid__with_a_nullptr_component_throws_an_error)
{
   Hexagon::Search::ComponentElasticsearchIndexer indexer(nullptr);
   std::string expected_error_message = "[ComponentElasticsearchIndex error:] can not \"generate_uid\" on a nullptr component";
   ASSERT_THROW_WITH_MESSAGE(indexer.generate_uid(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest, generate_uid__returns_a_uid_in_the_expected_format)
{
   Blast::Project::Component component("Component/Name", "hexagon");
   Hexagon::Search::ComponentElasticsearchIndexer indexer(&component);

   std::string expected_uid = "hexagon:Component/Name";
   std::string actual_uid = indexer.generate_uid();
   ASSERT_EQ(expected_uid, actual_uid);
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest, generate_index_shell_command__with_a_nullptr_component__throws_an_error)
{
   Hexagon::Search::ComponentElasticsearchIndexer indexer;
   std::string expected_error_message = "[ComponentElasticsearchIndex error:] can not \"generate_index_shell_command\" on a nullptr component";
   ASSERT_THROW_WITH_MESSAGE(indexer.generate_index_shell_command(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest, generate_index_shell_command__returns_the_expected_shell_command)
{
   Blast::Project::Component component("Component/Name", "hexagon");
   Hexagon::Search::ComponentElasticsearchIndexer indexer(&component);
   std::string expected_shell_command = "curl -XPOST \"http://localhost:9200/components/_doc/\" " \
                                        "-H 'Content-Type: application/json' " \
                                        "-d'{\"content\":\"Component/Name\",\"id\":\"Component/Name\"," \
                                        "\"name\":\"Component/Name\",\"project\":\"hexagon\"," \
                                        "\"uid\":\"hexagon:Component/Name\"}'";

   ASSERT_EQ(expected_shell_command, indexer.generate_index_shell_command());
}

TEST(Hexagon_Search_ComponentElasticsearchIndexerTest, import_or_update__with_a_nullptr_component__throws_an_error)
{
   Hexagon::Search::ComponentElasticsearchIndexer indexer;
   std::string expected_error_message = "[ComponentElasticsearchIndex error:] can not \"import_or_update\" on a nullptr component";
   ASSERT_THROW_WITH_MESSAGE(indexer.import_or_update(), std::runtime_error, expected_error_message);
}
