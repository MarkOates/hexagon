#pragma once


#include <string>


namespace Hexagon
{
   class LayoutFromYAML
   {
   private:
      std::string yaml;

   public:
      LayoutFromYAML(std::string yaml="# empty");
      ~LayoutFromYAML();


   void load();
   };
}



