#pragma once


#include <string>
#include <vector>


namespace Hexagon
{
   namespace Rails
   {
      class ComponentLister
      {
      private:

      public:
         ComponentLister();
         ~ComponentLister();


      std::vector<std::string> components();
      };
   }
}



