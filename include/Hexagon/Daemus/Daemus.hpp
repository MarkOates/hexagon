#pragma once


#include <Hexagon/Daemus/Builds/Base.hpp>
#include <Hexagon/Daemus/Builds/ExtrapolateQuintessence.hpp>
#include <vector>


namespace Hexagon
{
   namespace Daemus
   {
      class Daemus
      {
      private:
         Hexagon::Daemus::Builds::Base* current_build;
         std::vector<Hexagon::Daemus::Builds::Base*> builds;

      public:
         Daemus();
         ~Daemus();

         Hexagon::Daemus::Builds::Base* get_current_build() const;
         std::vector<Hexagon::Daemus::Builds::Base*> &get_builds_ref();
         Hexagon::Daemus::Builds::ExtrapolateQuintessence* create_extrapolate_quintessence_build();
      };
   }
}



