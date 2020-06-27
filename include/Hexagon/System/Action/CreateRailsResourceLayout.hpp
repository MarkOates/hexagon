#pragma once


#include <Hexagon/Action.hpp>
#include <Hexagon/StageInterface.hpp>
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
            static std::vector<StageInterface *> dummy_stages;

         public:
            CreateRailsResourceLayout(std::vector<StageInterface *>& stages=get_dummy_stages_ref(), int display_default_height=1350, int code_editor_width=1215);
            virtual ~CreateRailsResourceLayout();

            void set_stages(std::vector<StageInterface *>& stages);

            std::vector<StageInterface *>& get_stages();
            int get_display_default_height();
            int get_code_editor_width();
            static std::vector<StageInterface *> &get_dummy_stages_ref();
         virtual bool execute() override;
         };
      }
   }
}



