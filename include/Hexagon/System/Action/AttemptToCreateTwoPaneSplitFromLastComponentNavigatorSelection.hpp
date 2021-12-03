#pragma once


#include <Hexagon/Action.hpp>
#include <Hexagon/StageFactory.hpp>
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
            Hexagon::StageFactory* stage_factory;
            static std::vector<StageInterface *> dummy_stages;
            int code_editor_width;
            ALLEGRO_COLOR text_color;
            ALLEGRO_COLOR backfill_color;
            bool create_as_advanced_code_editor;

         public:
            AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection(std::string project_path="/Users/markoates/Repos/hexagon/", std::string last_component_navigator_selection="", int display_default_width=2430, int display_default_height=1350, std::vector<StageInterface *>& stages=get_dummy_stages_ref(), Hexagon::StageFactory* stage_factory=nullptr, int code_editor_width=1215, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f}, ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
            virtual ~AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection();

            void set_stages(std::vector<StageInterface *>& stages);
            void set_create_as_advanced_code_editor(bool create_as_advanced_code_editor);
            std::string get_project_path();
            std::vector<StageInterface *>& get_stages();
            int get_code_editor_width();
            bool get_create_as_advanced_code_editor();
            static std::vector<StageInterface *> &get_dummy_stages_ref();
            virtual bool execute() override;
         };
      }
   }
}



