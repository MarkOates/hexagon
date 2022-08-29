

#include <Hexagon/BuildSystem/BuildFactory.hpp>



namespace Hexagon
{
namespace BuildSystem
{


BuildFactory::BuildFactory()
{
}


BuildFactory::~BuildFactory()
{
}


Hexagon::BuildSystem::Builds::Focused* BuildFactory::create_focused_build()
{
   Hexagon::BuildSystem::Builds::Focused *focused_build = new Hexagon::BuildSystem::Builds::Focused;
   return focused_build;
}
} // namespace BuildSystem
} // namespace Hexagon


