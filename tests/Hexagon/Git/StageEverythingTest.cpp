
#include <gtest/gtest.h>

#include <Hexagon/Git/StageEverything.hpp>

TEST(Hexagon_Git_StageEverythingTest, can_be_created_without_blowing_up)
{
   Hexagon::Git::StageEverything stage_everything;
}

TEST(Hexagon_Git_StageEverythingTest, stage_everything__sets_all_the_unstaged_files_to_staged)
{
   Hexagon::Git::StageEverything stage_everything;
   EXPECT_EQ(true, stage_everything.stage_everything());
}
