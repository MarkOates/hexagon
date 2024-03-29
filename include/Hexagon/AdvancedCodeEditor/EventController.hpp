#pragma once


#include <AllegroFlare/KeyboardCommandMapper.hpp>
#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <map>
#include <string>


namespace Hexagon
{
   namespace AdvancedCodeEditor
   {
      class EventController
      {
      private:
         Hexagon::AdvancedCodeEditor::Stage* stage;
         std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> events_dictionary;
         AllegroFlare::KeyboardCommandMapper keyboard_command_mapping;
         static ALLEGRO_EVENT a_default_empty_event;

      protected:


      public:
         EventController(Hexagon::AdvancedCodeEditor::Stage* stage=nullptr, std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> events_dictionary={}, AllegroFlare::KeyboardCommandMapper keyboard_command_mapping={});
         ~EventController();

         std::map<std::string, std::function<void(Hexagon::AdvancedCodeEditor::Stage&)>> &get_events_dictionary_ref();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         bool process_local_event(std::string event_name="", ActionData action_data=ActionData());
         void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      };
   }
}



