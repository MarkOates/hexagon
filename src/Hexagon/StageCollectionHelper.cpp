

#include <Hexagon/StageCollectionHelper.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <stdexcept>
#include <sstream>
#include <Hexagon/GitCommitMessageInputBox/Stage.hpp>
#include <iostream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


StageCollectionHelper::StageCollectionHelper(std::vector<StageInterface *>* stages)
   : stages(stages)
{
}


StageCollectionHelper::~StageCollectionHelper()
{
}


std::vector<StageInterface *> StageCollectionHelper::all()
{
   if (!(stages))
      {
         std::stringstream error_message;
         error_message << "StageCollectionHelper" << "::" << "all" << ": error: " << "guard \"stages\" not met";
         throw std::runtime_error(error_message.str());
      }
   return *stages;
}

int StageCollectionHelper::count_code_editor_stages()
{
   if (!(stages))
      {
         std::stringstream error_message;
         error_message << "StageCollectionHelper" << "::" << "count_code_editor_stages" << ": error: " << "guard \"stages\" not met";
         throw std::runtime_error(error_message.str());
      }
   int result = 0;
   for (auto &stage : *stages)
   {
      if (stage->get_type() == StageInterface::CODE_EDITOR) result++;
   }
   return result;
}

std::vector<Hexagon::CodeEditor::Stage *> StageCollectionHelper::get_all_code_editor_stages_as_code_editor_stages()
{
   if (!(stages))
      {
         std::stringstream error_message;
         error_message << "StageCollectionHelper" << "::" << "get_all_code_editor_stages_as_code_editor_stages" << ": error: " << "guard \"stages\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::vector<Hexagon::CodeEditor::Stage *> result;
   for (auto &stage : (*stages))
   {
      StageInterface::type_t type = stage->get_type();
      if (type == StageInterface::CODE_EDITOR)
      {
         result.push_back(static_cast<Hexagon::CodeEditor::Stage *>(stage));
      }
   }
   return result;
}

Hexagon::CodeEditor::Stage* StageCollectionHelper::get_frontmost_code_editor_stage()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return nullptr;

   StageInterface::type_t type = frontmost_stage->get_type();
   if (type == StageInterface::ONE_LINE_INPUT_BOX
      || type == StageInterface::CODE_EDITOR
      || type == StageInterface::ADVANCED_CODE_EDITOR
      || type == StageInterface::GIT_COMMIT_MESSAGE_INPUT_BOX)
   {
      return static_cast<Hexagon::CodeEditor::Stage *>(get_frontmost_stage());
   }
   return nullptr;
}

Hexagon::GitCommitMessageInputBox::Stage* StageCollectionHelper::get_frontmost_git_commit_message_input_box()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return nullptr;

   StageInterface::type_t type = frontmost_stage->get_type();
   //if (type == StageInterface::ONE_LINE_INPUT_BOX
   // || type == StageInterface::CODE_EDITOR
   if (type == StageInterface::GIT_COMMIT_MESSAGE_INPUT_BOX)
   {
      return static_cast<Hexagon::GitCommitMessageInputBox::Stage *>(get_frontmost_stage());
      //return static_cast<Hexagon::CodeEditor::Stage *>(get_frontmost_stage());
   }
   return nullptr;
}

bool StageCollectionHelper::is_frontmost_stage_a_regex_input_box()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage)
   {
      std::cout << "Warning: attempting to infer if is_current_stage_a_regex_input_box() but no "
                << "frontmost stage exists" << std::endl;
      return false;
   }
   return frontmost_stage && (frontmost_stage->get_type() == StageInterface::ONE_LINE_INPUT_BOX);
}

StageInterface* StageCollectionHelper::get_frontmost_stage()
{
   if (!(stages))
      {
         std::stringstream error_message;
         error_message << "StageCollectionHelper" << "::" << "get_frontmost_stage" << ": error: " << "guard \"stages\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::vector<StageInterface *> stages = *(this->stages);
   if (stages.size() == 0) return nullptr;
   return stages.back();
}
} // namespace Hexagon


