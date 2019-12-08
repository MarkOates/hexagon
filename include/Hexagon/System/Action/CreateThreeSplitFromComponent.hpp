#pragma once


#include <Blast/Project/Component.hpp>
#include <Hexagon/Action.hpp>
#include <Hexagon/StageInterface.hpp>
#include <allegro_flare/placement3d.h>
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
            Blast::Project::Component component;
            std::vector<StageInterface *>& stages;
            int display_default_width;
            int display_default_height;
            static std::vector<StageInterface *> dummy_stages;

         public:
            CreateThreeSplitFromComponent(std::vector<StageInterface *>& stages=get_dummy_stages_ref(), int display_default_width=2430, int display_default_height=1350);
            ~CreateThreeSplitFromComponent();

            void set_stages(std::vector<StageInterface *>& stages);

            std::vector<StageInterface *>& get_stages();
            static std::vector<StageInterface *> &get_dummy_stages_ref();
         bool place_stage(std::string filename="/foobar.txt", std::string file_contents="/Hello World", placement3d place={});
         bool execute();
         };
      }
   }
}



