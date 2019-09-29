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


   static std::string __replace(std::string str="", std::string from="", std::string to="");
   static bool store(std::string content="");
   static std::string retrieve();
   };
}



