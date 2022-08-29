#pragma once


#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace ReportRenderers
      {
         class Basic
         {
         private:

         public:
            Basic();
            ~Basic();

            std::string run();
         };
      }
   }
}



