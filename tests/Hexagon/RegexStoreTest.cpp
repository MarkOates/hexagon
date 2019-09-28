
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

