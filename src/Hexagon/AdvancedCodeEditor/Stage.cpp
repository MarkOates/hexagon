

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>



namespace Hexagon
{
namespace AdvancedCodeEditor
{


Stage::Stage()
   : StageInterface(StageInterface::ADVANCED_CODE_EDITOR)
{
}


Stage::~Stage()
{
}


std::string Stage::run()
{
return "Hello World!";
}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


