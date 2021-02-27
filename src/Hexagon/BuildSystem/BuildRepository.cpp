

#include <Hexagon/BuildSystem/BuildRepository.hpp>



namespace Hexagon
{
namespace BuildSystem
{


BuildRepository::BuildRepository()
   : builds({})
{
}


BuildRepository::~BuildRepository()
{
}


Hexagon::BuildSystem::Build* BuildRepository::get_latest_if_exists()
{
   if (builds.empty()) return nullptr;
   return &builds.back();
}
} // namespace BuildSystem
} // namespace Hexagon


