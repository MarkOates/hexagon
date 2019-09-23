#pragma once


#include <Hexagon/StageInterface.hpp>
#include <string>


namespace Hexagon
{
   namespace FileNavigator
   {
      class Stage : public StageInterface
      {
      private:

      public:
         Stage();
         ~Stage();


      std::string run();
      };
   }
}



