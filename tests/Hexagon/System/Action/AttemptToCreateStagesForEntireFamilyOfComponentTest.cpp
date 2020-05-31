
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/System/Action/AttemptToCreateStagesForEntireFamilyOfComponent.hpp>

#include <Blast/Project/Component.hpp>

typedef Hexagon::System::Action::AttemptToCreateStagesForEntireFamilyOfComponent
   AttemptToCreateStagesForEntireFamilyOfComponent;

TEST(Hexagon_System_Action_AttemptToCreateStagesForEntireFamilyOfComponentTest,
   can_be_created_without_blowing_up)
{
   AttemptToCreateStagesForEntireFamilyOfComponent attempt_to_create_stages_for_entire_family_of_component;
}

TEST(Hexagon_System_Action_AttemptToCreateStagesForEntireFamilyOfComponentTest,
   execute__with_valid_inputs__returns_the_expected_response)
{
   std::vector<StageInterface *> stages;
   Blast::Project::Component component("Hexagon/CodeEditor/CodeEditor");
   AttemptToCreateStagesForEntireFamilyOfComponent attempt_to_create_stages_for_entire_family_of_component(
      component.get_name(), &stages);
   EXPECT_EQ(true, attempt_to_create_stages_for_entire_family_of_component.execute());
}

TEST(Hexagon_System_Action_AttemptToCreateStagesForEntireFamilyOfComponentTest,
   execute__with_nullptr_stages__raises_an_exception)
{
   Blast::Project::Component component_that_does_not_exist("Hexagon/CodeEditor/CodeEditor");
   AttemptToCreateStagesForEntireFamilyOfComponent action(component_that_does_not_exist.get_name(), nullptr);
   std::string expected_error_message = "stages must be present";
   ASSERT_THROW_WITH_MESSAGE(action.execute(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_Action_AttemptToCreateStagesForEntireFamilyOfComponentTest,
   execute__with_a_component_that_does_not_exist__raises_an_exception)
{
   std::vector<StageInterface *> stages;
   Blast::Project::Component component_that_does_not_exist("Component/That/Does/Not/Exist");
   AttemptToCreateStagesForEntireFamilyOfComponent action(component_that_does_not_exist.get_name(), &stages);
   std::string expected_error_message = "[Hexagon/System/Action/AttemptToCreateStagesForEntireFamilyOfComponent " \
                                        "error:] can not execute with a component that does not exist.";

   ASSERT_THROW_WITH_MESSAGE(action.execute(), std::runtime_error, expected_error_message);
}

