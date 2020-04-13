
#include <gtest/gtest.h>

#include <Hexagon/RegexStore.hpp>

#include <Hexagon/RegexMatcher.hpp>

TEST(Hexagon_RegexStoreTest, identifiers__is_able_to_match_identifiers)
{
   std::string identifiers_regex = Hexagon::RegexStore().identifiers();
   std::string source_string = ":: variableName variable 9876 last ClassName [captured] three-separate-elements";

   std::vector<std::pair<int, int>> expected_results = {
     { 3, 12 }, { 16, 8 }, { 30, 4 }, { 35, 9 }, { 46, 8 }, { 56, 5 }, { 62, 8 }, { 71, 8 }
   };

   std::vector<std::pair<int, int>> results;
   results = RegexMatcher(source_string, identifiers_regex).get_match_info();

   EXPECT_EQ(expected_results, results);

}

TEST(Hexagon_RegexStoreTest, double_quoted_strings__is_able_to_match_strings_with_and_without_escapes)
{
   std::string identifiers_regex = Hexagon::RegexStore().double_quoted_strings_with_escapes();
   std::string source_string = R"END(This "should" match and "this \"should\" should not")END";

   std::vector<std::pair<int, int>> expected_results = {
     { 5, 8 }, { 24, 28 },
   };

   std::vector<std::pair<int, int>> results;
   results = RegexMatcher(source_string, identifiers_regex).get_match_info();

   EXPECT_EQ(expected_results, results);

}

