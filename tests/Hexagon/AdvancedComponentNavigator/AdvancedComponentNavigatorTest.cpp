
#include <gtest/gtest.h>

#include <Hexagon/AdvancedComponentNavigator/AdvancedComponentNavigator.hpp>

#include <Hexagon/ClipboardData.hpp>


TEST(Hexagon_AdvancedComponentNavigator_AdvancedComponentNavigatorTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator advanced_component_navigator;
}


TEST(Hexagon_AdvancedComponentNavigator_AdvancedComponentNavigatorTest,
   mode__has_a_getter_that_is_set_to_the_expected_default_value)
{
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator advanced_component_navigator;
   ASSERT_EQ("navigating_list", advanced_component_navigator.get_mode());
}


TEST(Hexagon_AdvancedComponentNavigator_AdvancedComponentNavigatorTest,
   is_mode_navigating_list__returns_true_if_mode_is_currently_navigating_list)
{
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator advanced_component_navigator;
   advanced_component_navigator.set_mode_to_navigating_list();
   ASSERT_EQ(true, advanced_component_navigator.is_mode_navigating_list());
}


TEST(DISABLED_Hexagon_AdvancedComponentNavigator_AdvancedComponentNavigatorTest,
   is_mode_navigating_list__returns_false_if_mode_is_currently_navigating_list)
{
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator advanced_component_navigator;
   advanced_component_navigator.set_mode_to_typing_in_search_bar();
   ASSERT_EQ(false, advanced_component_navigator.is_mode_navigating_list());
}


TEST(Hexagon_AdvancedComponentNavigator_AdvancedComponentNavigatorTest,
   yank_selected_text_as_quintessence_dependency_lines__copies_the_expected_lines_to_the_clipboard)
{
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator advanced_component_navigator;
   advanced_component_navigator.set_nodes(
      { Blast::Project::Component("This/Is/An/Example/Component")});

   ClipboardData::clear();
   advanced_component_navigator.yank_selected_text_as_quintessence_dependency_lines();

   std::vector<std::string> actual_clipboard_lines = ClipboardData::retrieve();
   std::vector<std::string> expected_clipboard_lines = {
      "  - symbol: This::Is::An::Example::Component",
      "    headers: [ This/Is/An/Example/Component.hpp ]",
   };
   EXPECT_EQ(expected_clipboard_lines, actual_clipboard_lines);

   ClipboardData::clear();
}


TEST(Hexagon_AdvancedComponentNavigator_AdvancedComponentNavigatorTest,
   yank_selected_text_as_public_parent_class_lines__copies_the_expected_lines_to_the_clipboard)
{
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator advanced_component_navigator;
   advanced_component_navigator.set_nodes(
      { Blast::Project::Component("This/Is/An/Example/Component")});

   ClipboardData::clear();
   advanced_component_navigator.yank_selected_text_as_public_parent_class_lines();

   std::vector<std::string> actual_clipboard_lines = ClipboardData::retrieve();
   std::vector<std::string> expected_clipboard_lines = {
      "  - class: This::Is::An::Example::Component",
      "    scope: public",
      "    init_with: ''",
   };
   EXPECT_EQ(expected_clipboard_lines, actual_clipboard_lines);

   ClipboardData::clear();
}


TEST(Hexagon_AdvancedComponentNavigator_AdvancedComponentNavigatorTest,
   yank_selected_text_as_injected_dependency_property__copies_the_expected_lines_to_the_clipboard)
{
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator advanced_component_navigator;
   advanced_component_navigator.set_nodes(
      { Blast::Project::Component("This/Is/An/Example/Component")});

   ClipboardData::clear();
   advanced_component_navigator.yank_selected_text_as_injected_dependency_property();

   std::vector<std::string> actual_clipboard_lines = ClipboardData::retrieve();
   std::vector<std::string> expected_clipboard_lines = {
      "  - name: component",
      "    type: This::Is::An::Example::Component*",
      "    constructor_arg: true",
      "    init_with: nullptr",
      "    getter: true",
      "    setter: true",
      "",
      "",
   };
   EXPECT_EQ(expected_clipboard_lines, actual_clipboard_lines);

   ClipboardData::clear();
}


