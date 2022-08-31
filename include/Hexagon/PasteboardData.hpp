#pragma once


#include <string>


namespace Hexagon
{
   class PasteboardData
   {
   private:
      static std::string __replace(std::string str="", std::string from="", std::string to="");

   protected:


   public:
      PasteboardData();
      ~PasteboardData();

      static bool store(std::string content="");
      static std::string retrieve();
   };
}



