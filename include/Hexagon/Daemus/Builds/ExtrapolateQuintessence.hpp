#pragma once


#include <Hexagon/Daemus/Builds/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace Daemus
   {
      namespace Builds
      {
         class ExtrapolateQuintessence : public Hexagon::Daemus::Builds::Base
         {
         private:

         public:
            ExtrapolateQuintessence();
            ~ExtrapolateQuintessence();

            std::string run();
         };
      }
   }
}



