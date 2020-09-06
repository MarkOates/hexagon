#pragma once


#include <Blast/Project/Component.hpp>
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
         class CreateThreeSplitFromComponent : public ::Action
         {
         private:
            std::string project_path;
            Blast::Project::Component component;
            std::vector<StageInterface *>& stages;
            Hexagon::StageFactory* stage_factory;
            int display_default_width;
            int display_default_height;
            int code_editor_width;
            ALLEGRO_COLOR text_color;
            ALLEGRO_COLOR backfill_color;
            static std::vector<StageInterface *> dummy_stages;

         public:
            CreateThreeSplitFromComponent(std::string project_path="/Users/markoates/Repos/hexagon/", Blast::Project::Component component={}, std::vector<StageInterface *>& stages=get_dummy_stages_ref(), Hexagon::StageFactory* stage_factory=nullptr, int display_default_width=2430, int display_default_height=1350, int code_editor_width=1215, ALLEGRO_COLOR text_color=ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f}, ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
            ~CreateThreeSplitFromComponent();

            void set_stages(std::vector<StageInterface *>& stages);

            std::string get_project_path();
            std::vector<StageInterface *>& get_stages();
            int get_code_editor_width();
            static std::vector<StageInterface *> &get_dummy_stages_ref();
         bool place_stage(std::string filename="/foobar.txt", std::string file_category="undefined", float x=0.0, float align_x=0.0);
         std::string generate_header_filename();
         std::string generate_source_filename();
         std::string generate_test_filename();
         bool execute();
         };
      }
   }
}



