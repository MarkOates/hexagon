

#include <Hexagon/StageCollectionHelper.hpp>
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
} // namespace Hexagon


