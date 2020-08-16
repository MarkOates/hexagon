
#include <gtest/gtest.h>

#include <Hexagon/CodeMessagePointManager.hpp>

TEST(Hexagon_CodeMessagePointManagerTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeMessagePointManager code_message_point_manager;
}

TEST(Hexagon_CodeMessagePointManagerTest, append__will_add_a_new_message_point_to_the_end)
{
   // TODO
   Hexagon::CodeMessagePointManager code_message_point_manager;

   std::vector<CodeMessagePoint> expected_code_message_points = {};
   std::vector<CodeMessagePoint> actual_code_message_points = {};

   //code_message_point_manager.

   ASSERT_EQ(expected_code_message_points.size(), actual_code_message_points.size());
}

TEST(Hexagon_CodeMessagePointManagerTest, delete_row__will_remove_all_message_points_on_the_row)
{
   // TODO
   //Hexagon::CodeMessagePointManager code_message_point_manager;
}

TEST(Hexagon_CodeMessagePointManagerTest, delete_row__will_shift_all_the_consequent_lines_up_by_a_row)
{
   // TODO
   //Hexagon::CodeMessagePointManager code_message_point_manager;
}

