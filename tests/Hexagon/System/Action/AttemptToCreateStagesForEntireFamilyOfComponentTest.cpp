
#include <gtest/gtest.h>

#include <Hexagon/System/Action/AttemptToCreateStagesForEntireFamilyOfComponent.hpp>

typedef Hexagon::System::Action::AttemptToCreateStagesForEntireFamilyOfComponent
   AttemptToCreateStagesForEntireFamilyOfComponent;

TEST(Hexagon_System_Action_AttemptToCreateStagesForEntireFamilyOfComponentTest, can_be_created_without_blowing_up)
{
   AttemptToCreateStagesForEntireFamilyOfComponent attempt_to_create_stages_for_entire_family_of_component;
}

TEST(Hexagon_System_Action_AttemptToCreateStagesForEntireFamilyOfComponentTest, run__returns_the_expected_response)
{
   AttemptToCreateStagesForEntireFamilyOfComponent attempt_to_create_stages_for_entire_family_of_component;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, attempt_to_create_stages_for_entire_family_of_component.run());
}
