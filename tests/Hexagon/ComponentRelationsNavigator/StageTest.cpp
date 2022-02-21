
#include <gtest/gtest.h>

#include <Hexagon/ComponentRelationsNavigator/Stage.hpp>


TEST(Hexagon_ComponentRelationsNavigator_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::ComponentRelationsNavigator::Stage stage;
}


TEST(Hexagon_ComponentRelationsNavigator_StageTest,
   get_current_selection_label_or_empty_string__when_on_the_dependents_menu__will_return_the_currently_selected_item)
{
   // TODO
}


TEST(Hexagon_ComponentRelationsNavigator_StageTest,
   get_current_selection_label_or_empty_string__when_on_the_relatives_menu__will_return_the_currently_selected_item)
{
   // TODO
}


TEST(Hexagon_ComponentRelationsNavigator_StageTest,
   get_current_selection_label_or_empty_string__when_on_the_dependencies_menu__will_return_the_currently_selected_item)
{
   // TODO
}


