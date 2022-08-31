#pragma once


#include <Hexagon/Project.hpp>


namespace Hexagon
{
   class ProjectFactory
   {
   private:

   protected:


   public:
      ProjectFactory();
      ~ProjectFactory();

      Hexagon::Project hexagon();
      Hexagon::Project build_shopify_experts_conversations_system();
      Hexagon::Project partner_performance_dashboard();
   };
}



