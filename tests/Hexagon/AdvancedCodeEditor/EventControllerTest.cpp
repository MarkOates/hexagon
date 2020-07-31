
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/EventController.hpp>

TEST(Hexagon_AdvancedCodeEditor_EventControllerTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::EventController event_controller;
}

TEST(Hexagon_AdvancedCodeEditor_EventControllerTest, can_be_created_with_an_events_dictionary)
{
   std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> events_dictionary = {
     { "cursor_move_up", &Hexagon::AdvancedCodeEditor::Stage::cursor_move_up },
   };
   Hexagon::AdvancedCodeEditor::EventController event_controller(nullptr, events_dictionary);
}

TEST(DISABLED_Hexagon_AdvancedCodeEditor_EventControllerTest, process_local_event__processes_the_event)
{
}

TEST(DISABLED_Hexagon_AdvancedCodeEditor_EventControllerTest, process_event__processes_the_event)
{
}

