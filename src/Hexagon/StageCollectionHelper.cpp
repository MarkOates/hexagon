

#include <Hexagon/StageCollectionHelper.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <stdexcept>
#include <sstream>
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


