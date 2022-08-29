#pragma once


#include <Hexagon/BuildSystem/Builds/Base.hpp>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace Builds
      {
         class Focused : public Hexagon::BuildSystem::Builds::Base
         {
         public:
            static constexpr char* TYPE = "Focused";

         private:

         public:
            Focused();
            ~Focused();

         };
      }
   }
}



