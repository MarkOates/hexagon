
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
   code_message_point_manager.append( { 7, 32 } );

   std::vector<CodeMessagePoint> expected_code_message_points = { { 3, 4 }, { 7, 32 } };
   std::vector<CodeMessagePoint> actual_code_message_points = code_message_point_manager.get_code_message_points();

   ASSERT_EQ(expected_code_message_points, actual_code_message_points);
}

TEST(Hexagon_CodeMessagePointManagerTest, delete_row__will_remove_all_message_points_on_the_row__and_shift_up_lower_rows)
{
   Hexagon::CodeMessagePointManager code_message_point_manager;
   std::vector<CodeMessagePoint> code_message_points = {
      { 1,  3 },
      { 15,  4 },
      { 3,  5 }, { 8, 5 },
      { 52, 6 }, { 12, 6 }, { 32, 6 }, { 19, 6 },
      { 2, 9 },
   };

   // fill with the source data
   for (auto &code_message_point : code_message_points)
   {
      code_message_point_manager.append(code_message_point);
   }
   code_message_point_manager.delete_row(5);

   std::vector<CodeMessagePoint> expected_code_message_points = {
      { 1,  3 },
      { 15,  4 },
      { 52, 5 }, { 12, 5 }, { 32, 5 }, { 19, 5 },
      { 2, 8 },
   };
   std::vector<CodeMessagePoint> actual_code_message_points = code_message_point_manager.get_code_message_points();

   ASSERT_EQ(expected_code_message_points, actual_code_message_points);
}

