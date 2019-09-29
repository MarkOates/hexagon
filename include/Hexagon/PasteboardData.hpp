#pragma once


#include <string>


namespace Hexagon
{
   class PasteboardData
   {
   private:

   public:
      PasteboardData();
      ~PasteboardData();


   static bool store(std::string content="");
   static std::string retrieve();
   };
}



