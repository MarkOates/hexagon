
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::MatchesRegex;

#include <Blast/Search/Elasticsearch/HealthChecker.hpp>

TEST(Blast_Search_Elasticsearch_HealthCheckerTest, can_be_created_without_blowing_up)
{
   Blast::Search::Elasticsearch::HealthChecker health_checker;
}

TEST(Blast_Search_Elasticsearch_HealthCheckerTest,
   request_health__returns_the_health_of_the_elasticsearch_host)
{
   Blast::Search::Elasticsearch::HealthChecker health_checker;
   std::string expected_matching_regex = "[0-9]+ [0-9]+:[0-9]+:[0-9]+ [0-0a-zA-Z_]+ (yellow|red|green) .+";
   std::string actual_health_string = health_checker.request_health();
   //EXPECT_EQ(expected_health_string, actual_health_string);
   EXPECT_THAT(actual_health_string, MatchesRegex(expected_matching_regex));
}
