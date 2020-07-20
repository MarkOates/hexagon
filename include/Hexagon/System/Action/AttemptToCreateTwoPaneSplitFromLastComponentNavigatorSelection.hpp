#pragma once


#include <Hexagon/Action.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro5/allegro_color.h>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection : public ::Action
         {
         private:
            std::string project_path;
            std::string last_component_navigator_selection;
            int display_default_width;
            int display_default_height;
            std::vector<StageInterface *>& stages;
            static std::vector<StageInterface *> dummy_stages;
            int code_editor_width;
            ALLEGRO_COLOR text_color;
            ALLEGRO_COLOR backfill_color;

         public:
            AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection(std::string project_path="/Users/markoates/Repos/hexagon/", std::string last_component_navigator_selection="", int display_default_width=2430, int display_default_height=1350, std::vector<StageInterface *>& stages=get_dummy_stages_ref(), int code_editor_width=1215, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f}, ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
            virtual ~AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection();

            void set_stages(std::vector<StageInterface *>& stages);

            std::string get_project_path();
            std::vector<StageInterface *>& get_stages();
            int get_code_editor_width();
            static std::vector<StageInterface *> &get_dummy_stages_ref();
         std::string run();
         virtual bool execute() override;
         };
      }
   }
}



