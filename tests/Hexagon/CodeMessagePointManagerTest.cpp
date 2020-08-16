
#include <gtest/gtest.h>

#include <Hexagon/CodeMessagePointManager.hpp>

TEST(Hexagon_CodeMessagePointManagerTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeMessagePointManager code_message_point_manager;
}

TEST(Hexagon_CodeMessagePointManagerTest, append__will_add_a_new_message_point_to_the_end)
{
   Hexagon::CodeMessagePointManager code_message_point_manager;

   code_message_point_manager.append( { 3, 4 } );

   std::vector<CodeMessagePoint> expected_code_message_points = { { 3, 4 } };
   std::vector<CodeMessagePoint> actual_code_message_points = code_message_point_manager.get_code_message_points();

   ASSERT_EQ(expected_code_message_points, actual_code_message_points);
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

