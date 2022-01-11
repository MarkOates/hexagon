#pragma once


#include <Hexagon/Daemus/Builds/Base.hpp>


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
            virtual ~ExtrapolateQuintessence();

            virtual void initiate() override;
         };
      }
   }
}



