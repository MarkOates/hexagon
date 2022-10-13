#pragma once


#include <string>


namespace Hexagon
{
   class DarkModeDetector
   {
   public:
      static constexpr const char* DARK_MODE_RESPONSE_STRING = "Dark";

   private:
      std::string get_trimmed_command_result();

   protected:


   public:
      DarkModeDetector();
      ~DarkModeDetector();

      bool is_dark();
      bool is_light();
   };
}



