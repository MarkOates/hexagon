#pragma once


#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/GitCommitMessageInputBox/Stage.hpp>
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
      Hexagon::CodeEditor::Stage* get_frontmost_code_editor_stage();
      Hexagon::GitCommitMessageInputBox::Stage* get_frontmost_git_commit_message_input_box();
      bool is_frontmost_stage_a_regex_input_box();
      StageInterface* get_frontmost_stage();
   };
}



