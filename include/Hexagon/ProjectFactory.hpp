#pragma once


#include <Hexagon/Project.hpp>


namespace Hexagon
{
   class ProjectFactory
   {
   private:

   public:
      ProjectFactory();
      ~ProjectFactory();


   Hexagon::Project hexagon();
   Hexagon::Project partner_performance_dashboard();
   };
}



