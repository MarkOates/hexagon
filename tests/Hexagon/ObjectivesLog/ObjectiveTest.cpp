
#include <gtest/gtest.h>

#include <Hexagon/ObjectivesLog/Objective.hpp>

TEST(Hexagon_ObjectivesLog_ObjectiveTest, can_be_created_without_blowing_up)
{
   Hexagon::ObjectivesLog::Objective objective;
}

TEST(Hexagon_ObjectivesLog_ObjectiveTest, has_getters_with_the_expected_default_values)
{
   Hexagon::ObjectivesLog::Objective objective;
   EXPECT_EQ("Unnamed Objective", objective.get_title());
}

TEST(Hexagon_ObjectivesLog_ObjectiveTest, mark_as_completed__will_set_completed_to_true)
{
   Hexagon::ObjectivesLog::Objective objective;
   objective.mark_as_completed();
   EXPECT_EQ(true, objective.get_completed());
}

