#pragma once


#include <string>


namespace Hexagon
{
   namespace Testing
   {
      class GoogleTestRunOutputParser
      {
      private:

      public:
         GoogleTestRunOutputParser();
         ~GoogleTestRunOutputParser();


      std::string run();
      };
   }
}



