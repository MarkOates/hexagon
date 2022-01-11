#pragma once


#include <string>


namespace Hexagon
{
   namespace Daemus
   {
      namespace Builds
      {
         class Base
         {
         private:
            std::string type;

         public:
            Base(std::string type="Base");
            ~Base();

            std::string get_type();
            std::string run();
         };
      }
   }
}



