
#include <gtest/gtest.h>

#include <Hexagon/System/Action/AttemptToCreateStagesForEntireFamilyOfComponent.hpp>

typedef Hexagon::System::Action::AttemptToCreateStagesForEntireFamilyOfComponent
   AttemptToCreateStagesForEntireFamilyOfComponent;

TEST(Hexagon_System_Action_AttemptToCreateStagesForEntireFamilyOfComponentTest,
   can_be_created_without_blowing_up)
{
   AttemptToCreateStagesForEntireFamilyOfComponent attempt_to_create_stages_for_entire_family_of_component;
}

TEST(Hexagon_System_Action_AttemptToCreateStagesForEntireFamilyOfComponentTest,
   execute__returns_the_expected_response)
{
   std::vector<StageInterface *> stages;
   AttemptToCreateStagesForEntireFamilyOfComponent attempt_to_create_stages_for_entire_family_of_component;
   //EXPECT_EQ(true, attempt_to_create_stages_for_entire_family_of_component.execute());
}

TEST(Hexagon_System_Action_AttemptToCreateStagesForEntireFamilyOfComponentTest,
   execute__with_a_component_that_does_not_exist__raises_an_exception)
{
   AttemptToCreateStagesForEntireFamilyOfComponent attempt_to_create_stages_for_entire_family_of_component;
   //EXPECT_EQ(true, attempt_to_create_stages_for_entire_family_of_component.execute());
}

