
#include <gtest/gtest.h>

#include <Hexagon/Elements/DataTable.hpp>

TEST(Hexagon_Elements_DataTableTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::DataTable data_table;
}

TEST(Hexagon_Elements_DataTableTest, run__returns_the_expected_response)
{
   Hexagon::Elements::DataTable data_table;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, data_table.run());
}
