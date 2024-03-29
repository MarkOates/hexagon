#pragma once


#include <Hexagon/AdvancedCodeEditor/Stage.hpp>
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

   protected:


   public:
      StageCollectionHelper(std::vector<StageInterface *>* stages=nullptr);
      ~StageCollectionHelper();

      std::vector<StageInterface *> all();
      std::vector<StageInterface *> get_all_stages_not_rendered_on_hud();
      std::vector<StageInterface *> get_all_render_on_hud_stages();
      int count_code_editor_stages();
      std::vector<Hexagon::CodeEditor::Stage *> get_all_code_editor_stages();
      std::vector<Hexagon::AdvancedCodeEditor::Stage *> get_all_advanced_code_editor_stages();
      Hexagon::AdvancedCodeEditor::Stage* get_frontmost_advanced_code_editor_stage();
      Hexagon::CodeEditor::Stage* get_frontmost_code_editor_stage();
      Hexagon::GitCommitMessageInputBox::Stage* get_frontmost_git_commit_message_input_box();
      bool is_frontmost_stage_a_regex_input_box();
      StageInterface* get_frontmost_stage();
   };
}



