#pragma once


#include <string>


namespace Hexagon
{
   namespace Testing
   {
      class ClangBuildOutputResult
      {
      private:

      public:
         ClangBuildOutputResult();
         ~ClangBuildOutputResult();

         std::string run();
      };
   }
}



