
#include <gtest/gtest.h>

#include <Hexagon/RegexStore.hpp>

TEST(Hexagon_RegexStoreTest, identifiers__returns_the_expected_regex_string)
{
   Hexagon::RegexStore regex_store;
   std::string expected_string = "[a-z_][0-9a-z_]{0,31}";
   EXPECT_EQ(expected_string, regex_store.identifiers());
}

TEST(Hexagon_RegexStoreTest, class_names_returns_the_expected_regex_string)
{
   Hexagon::RegexStore regex_store;
   std::string expected_string = "[A-Z][0-9A-Za-z_]{0,31}";
   EXPECT_EQ(expected_string, regex_store.());
}

