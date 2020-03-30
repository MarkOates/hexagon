#pragma once


#include <Blast/Project/Component.hpp>
#include <Hexagon/Action.hpp>
#include <Hexagon/StageInterface.hpp>
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
            int display_default_width;
            int display_default_height;
            int code_editor_width;
            static std::vector<StageInterface *> dummy_stages;

         public:
            CreateThreeSplitFromComponent(std::string project_path="/Users/markoates/Repos/hexagon/", Blast::Project::Component component={}, std::vector<StageInterface *>& stages=get_dummy_stages_ref(), int display_default_width=2430, int display_default_height=1350, int code_editor_width=1215);
            ~CreateThreeSplitFromComponent();

            void set_stages(std::vector<StageInterface *>& stages);

            std::string get_project_path();
            std::vector<StageInterface *>& get_stages();
            int get_code_editor_width();
            static std::vector<StageInterface *> &get_dummy_stages_ref();
         bool place_stage(std::string filename="/foobar.txt", float x=0.0, float align_x=0.0);
         std::string generate_header_filename();
         std::string generate_source_filename();
         std::string generate_test_filename();
         bool execute();
         };
      }
   }
}



