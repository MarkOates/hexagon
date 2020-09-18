

#include <Hexagon/StageCollectionHelper.hpp>
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
} // namespace Hexagon


