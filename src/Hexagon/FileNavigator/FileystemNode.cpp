

#include <Hexagon/FileNavigator/FileystemNode.hpp>



namespace Hexagon
{
namespace FileNavigator
{


FileystemNode::FileystemNode(ALLEGRO_FS_ENTRY* entry)
   : entry(entry)
{
}


FileystemNode::~FileystemNode()
{
}


std::string FileystemNode::run()
{
return "Hello World!";
}
} // namespace FileNavigator
} // namespace Hexagon


