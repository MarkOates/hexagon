#pragma once


#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/StageInterface.hpp>
#include <vector>


namespace Hexagon
{
   class StageCollectionHelper
   {
   private:
      std::vector<StageInterface *>* stages;

   public:
      StageCollectionHelper(std::vector<StageInterface *>* stages=nullptr);
      ~StageCollectionHelper();


   std::vector<StageInterface *> all();
   int count_code_editor_stages();
   std::vector<Hexagon::CodeEditor::Stage *> get_all_code_editor_stages_as_code_editor_stages();
   StageInterface* get_frontmost_stage();
   };
}



