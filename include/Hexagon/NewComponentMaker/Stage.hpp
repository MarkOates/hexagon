#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace NewComponentMaker
   {
      class Stage : public StageInterface
      {
      private:
         std::string current_project_directory;
         std::string component_name;
         bool shell_command_has_executed;
         std::string last_executed_shell_response;
         std::string path_to_executable;
         static ALLEGRO_EVENT a_default_empty_event;

      public:
         Stage(std::string current_project_directory="/Users/markoates/Repos/hexagon/", std::string component_name="");
         virtual ~Stage();


         std::string get_current_project_directory();
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
      virtual void render() override;
      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref());
      std::string get_shell_response();
      std::vector<std::string> get_shell_response_lines();
      std::string build_shell_command();
      };
   }
}



