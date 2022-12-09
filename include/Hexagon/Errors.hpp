#pragma once


#include <string>


namespace Hexagon
{
   class Errors
   {
   private:

   protected:


   public:
      Errors();
      ~Errors();

      static std::string build_error_message(std::string from="[unset-from]", std::string message="[unset-message]");
   };
}



