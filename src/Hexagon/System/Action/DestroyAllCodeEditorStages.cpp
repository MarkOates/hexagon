

#include <Hexagon/System/Action/DestroyAllCodeEditorStages.hpp>
#include <Hexagon/CodeEditor/CodeEditor.hpp>


namespace Hexagon
{
namespace System
{
namespace Action
{


std::vector<StageInterface *> DestroyAllCodeEditorStages::dummy_stages = {};


DestroyAllCodeEditorStages::DestroyAllCodeEditorStages(std::vector<StageInterface *>& stages)
   : ::Action("System::Action::DestroyAllCodeEditorStages", ActionData())
   , stages(stages)
{
}


DestroyAllCodeEditorStages::~DestroyAllCodeEditorStages()
{
}


void DestroyAllCodeEditorStages::set_stages(std::vector<StageInterface *>& stages)
{
   this->stages = stages;
}


std::vector<StageInterface *>& DestroyAllCodeEditorStages::get_stages()
{
   return stages;
}


std::vector<StageInterface *> &DestroyAllCodeEditorStages::get_dummy_stages_ref()
{
   return dummy_stages;
}


bool DestroyAllCodeEditorStages::execute()
{
for (unsigned i=0; i<stages.size(); i++)
{
   auto &stage = stages[i];

   if (
        stage->get_type() == StageInterface::CODE_EDITOR
        || stage->get_type() == StageInterface::MISSING_FILE
      )
   {
      CodeEditor::Stage *code_editor = static_cast<CodeEditor::Stage *>(stage);
      delete code_editor;
      stages.erase(stages.begin()+i);
      i--;
   }
}
return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


