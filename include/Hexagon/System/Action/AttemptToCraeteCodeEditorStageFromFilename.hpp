#pragma once


#include <Hexagon/StageInterface.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class AttemptToCraeteCodeEditorStageFromFilename
         {
         private:
            std::string filename;
            int display_default_height;
            int display_default_width;
            int stage_width;
            std::vector<StageInterface *>* stages;

         public:
            AttemptToCraeteCodeEditorStageFromFilename(std::string filename="file.txt", int display_default_height=1, int display_default_width=1, int stage_width=1, std::vector<StageInterface *>* stages=nullptr);
            ~AttemptToCraeteCodeEditorStageFromFilename();


            int get_display_default_height();
            int get_display_default_width();
            int get_stage_width();
         bool execute();
         };
      }
   }
}



