#pragma once


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
         class CreateRailsResourceLayout : public ::Action
         {
         private:
            std::vector<StageInterface *>& stages;
            int display_default_height;
            int code_editor_width;
            std::string model_filename;
            std::string model_test_filename;
            std::string routes_filename;
            std::string controller_filename;
            std::string controller_test_filename;
            std::string view_filename;
            static std::vector<StageInterface *> dummy_stages;

         public:
            CreateRailsResourceLayout(std::vector<StageInterface *>& stages=get_dummy_stages_ref(), int display_default_height=1350, int code_editor_width=1215, std::string model_filename="app/models/disc.rb", std::string model_test_filename="test/models/disc_test.rb", std::string routes_filename="config/routes.rb", std::string controller_filename="app/controllers/discs_controller.rb", std::string controller_test_filename="test/controllers/discs_controller_test.rb", std::string view_filename="app/views/discs/index.html.erb");
            virtual ~CreateRailsResourceLayout();

            void set_stages(std::vector<StageInterface *>& stages);

            std::vector<StageInterface *>& get_stages();
            int get_display_default_height();
            int get_code_editor_width();
            static std::vector<StageInterface *> &get_dummy_stages_ref();
         bool place_and_load_code_editor(std::vector<StageInterface *>* stages_ptr=nullptr, std::string filename="", std::string file_category="undefined_file_category", float x=0.0f, float y=0.0f);
         virtual bool execute() override;
         };
      }
   }
}



