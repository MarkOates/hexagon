

#include <Hexagon/RerunOutputWatcher.hpp>



namespace Hexagon
{


RerunOutputWatcher::RerunOutputWatcher()
   : StageInterface(StageInterface::RERUN_OUTPUT_WATCHER)
{
}


RerunOutputWatcher::~RerunOutputWatcher()
{
}


std::string RerunOutputWatcher::run()
{
return "Hello Buddy!";
}
} // namespace Hexagon


