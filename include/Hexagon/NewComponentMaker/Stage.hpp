#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace NewComponentMaker
   {
      class Stage : public StageInterface
      {
      private:
         std::string current_project_directory;
         std::string component_name;
         static ALLEGRO_EVENT a_default_empty_event;

      protected:


      public:
         Stage(std::string current_project_directory="/Users/markoates/Repos/hexagon/", std::string component_name="");
         virtual ~Stage();

         std::string get_current_project_directory() const;
         static ALLEGRO_EVENT &get_a_default_empty_event_ref();
         virtual void render() override;
         void process_local_event(std::string event_name="", ActionData action_data=ActionData()) override;
         void process_event(ALLEGRO_EVENT& event=get_a_default_empty_event_ref()) override;
      };
   }
}



