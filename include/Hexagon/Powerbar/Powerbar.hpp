#pragma once


#include <string>


namespace Hexagon
{
   namespace Powerbar
   {
      class Powerbar
      {
      private:
         std::string box_1_text;
         std::string box_2_text;
         std::string box_3_text;

      public:
         Powerbar(std::string box_1_text="", std::string box_2_text="", std::string box_3_text="");
         ~Powerbar();


         std::string get_box_1_text();
         std::string get_box_2_text();
         std::string get_box_3_text();
      };
   }
}



