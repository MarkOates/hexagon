#pragma once


#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace ReportRenderers
      {
         class Base
         {
         private:

         public:
            Base();
            ~Base();

            std::string run();
         };
      }
   }
}



