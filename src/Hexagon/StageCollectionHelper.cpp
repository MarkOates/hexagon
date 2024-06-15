

#include <Hexagon/StageCollectionHelper.hpp>

#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/GitCommitMessageInputBox/Stage.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>


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
      error_message << "[Hexagon::StageCollectionHelper::all]: error: guard \"stages\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageCollectionHelper::all]: error: guard \"stages\" not met");
   }
   return *stages;
}

std::vector<StageInterface *> StageCollectionHelper::get_all_stages_not_rendered_on_hud()
{
   if (!(stages))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageCollectionHelper::get_all_stages_not_rendered_on_hud]: error: guard \"stages\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageCollectionHelper::get_all_stages_not_rendered_on_hud]: error: guard \"stages\" not met");
   }
   std::vector<StageInterface *> result;
   for (auto &stage : *stages)
   {
      if (!stage->get_render_on_hud()) result.push_back(stage);
   }
   return result;
}

std::vector<StageInterface *> StageCollectionHelper::get_all_render_on_hud_stages()
{
   if (!(stages))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageCollectionHelper::get_all_render_on_hud_stages]: error: guard \"stages\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageCollectionHelper::get_all_render_on_hud_stages]: error: guard \"stages\" not met");
   }
   std::vector<StageInterface *> result;
   for (auto &stage : *stages)
   {
      if (stage->get_render_on_hud()) result.push_back(stage);
   }
   return result;
}

int StageCollectionHelper::count_code_editor_stages()
{
   if (!(stages))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageCollectionHelper::count_code_editor_stages]: error: guard \"stages\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageCollectionHelper::count_code_editor_stages]: error: guard \"stages\" not met");
   }
   int result = 0;
   for (auto &stage : *stages)
   {
      if (stage->get_type() == StageInterface::CODE_EDITOR) result++;
   }
   return result;
}

std::vector<Hexagon::CodeEditor::Stage *> StageCollectionHelper::get_all_code_editor_stages()
{
   if (!(stages))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageCollectionHelper::get_all_code_editor_stages]: error: guard \"stages\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageCollectionHelper::get_all_code_editor_stages]: error: guard \"stages\" not met");
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

std::vector<Hexagon::AdvancedCodeEditor::Stage *> StageCollectionHelper::get_all_advanced_code_editor_stages()
{
   if (!(stages))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::StageCollectionHelper::get_all_advanced_code_editor_stages]: error: guard \"stages\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageCollectionHelper::get_all_advanced_code_editor_stages]: error: guard \"stages\" not met");
   }
   std::vector<Hexagon::AdvancedCodeEditor::Stage *> result;
   for (auto &stage : (*stages))
   {
      StageInterface::type_t type = stage->get_type();
      if (type == StageInterface::ADVANCED_CODE_EDITOR)
      {
         result.push_back(static_cast<Hexagon::AdvancedCodeEditor::Stage *>(stage));
      }
   }
   return result;
}

Hexagon::AdvancedCodeEditor::Stage* StageCollectionHelper::get_frontmost_advanced_code_editor_stage()
{
   StageInterface *frontmost_stage = get_frontmost_stage();
   if (!frontmost_stage) return nullptr;

   StageInterface::type_t type = frontmost_stage->get_type();
   if (type == StageInterface::ADVANCED_CODE_EDITOR)
   {
      return static_cast<Hexagon::AdvancedCodeEditor::Stage *>(get_frontmost_stage());
   }
   return nullptr;
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
      error_message << "[Hexagon::StageCollectionHelper::get_frontmost_stage]: error: guard \"stages\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::StageCollectionHelper::get_frontmost_stage]: error: guard \"stages\" not met");
   }
   std::vector<StageInterface *> stages = *(this->stages);
   if (stages.size() == 0) return nullptr;
   return stages.back();
}


} // namespace Hexagon


